#include "GuildAchievementMgr.h"
#include "Common.h"
#include "DBCEnums.h"
#include "ObjectMgr.h"
#include "ArenaTeamMgr.h"
#include "GuildMgr.h"
#include "World.h"
#include "WorldPacket.h"
#include "DatabaseEnv.h"
#include "AchievementMgr.h"
#include "ArenaTeam.h"
#include "CellImpl.h"
#include "GameEventMgr.h"
#include "GridNotifiersImpl.h"
#include "Guild.h"
#include "Language.h"
#include "Player.h"
#include "SpellMgr.h"
#include "DisableMgr.h"
#include "ScriptMgr.h"
#include "MapManager.h"
#include "Battleground.h"
#include "BattlegroundAB.h"
#include "Map.h"
#include "InstanceScript.h"

GuildAchievementMgr::GuildAchievementMgr(Guild* guild)
{
    m_guild = guild;
}

GuildAchievementMgr::~GuildAchievementMgr()
{
}

void GuildAchievementMgr::SendDirectMessageToAll(WorldPacket* data)
{
    Guild::Members list = m_guild->GetMembers();
    for (Guild::Members::iterator itr = list.begin(); itr != list.end(); ++itr)
        if (Player* player = itr->second->FindPlayer())
            player->SendDirectMessage(data);
}

void GuildAchievementMgr::Reset()
{
    for (CompletedAchievementMap::const_iterator iter = m_completedAchievements.begin(); iter != m_completedAchievements.end(); ++iter)
    {
        WorldPacket data(SMSG_ACHIEVEMENT_DELETED, 4); // ToDo, find opcode for guild
        data << uint32(iter->first);
        SendDirectMessageToAll(&data);
    }

    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
    {
        WorldPacket data(SMSG_CRITERIA_DELETED, 4); // ToDo, find opcode for guild
        data << uint32(iter->first);
        SendDirectMessageToAll(&data);
    }

    m_completedAchievements.clear();
    m_criteriaProgress.clear();
    DeleteFromDB(m_guild->GetId());

    // re-fill data
    CheckAllAchievementCriteria();
}

void GuildAchievementMgr::ResetAchievementCriteria(AchievementCriteriaTypes type, uint32 miscvalue1, uint32 miscvalue2, bool evenIfCriteriaComplete)
{
    AchievementCriteriaEntryList const& achievementCriteriaList = sAchievementMgr->GetAchievementCriteriaByType(type);
    
    for (AchievementCriteriaEntryList::const_iterator i = achievementCriteriaList.begin(); i != achievementCriteriaList.end(); ++i)
    {
        AchievementCriteriaEntry const *achievementCriteria = (*i);

        AchievementEntry const *achievement = sAchievementStore.LookupEntry(achievementCriteria->referredAchievement);
        if (!achievement)
            continue;
        
        if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
            continue;
            
        // don't update already completed criteria if not forced or achievement already complete
        if ((IsCompletedCriteria(achievementCriteria, achievement) && !evenIfCriteriaComplete) || HasAchieved(achievement->ID))
            continue;
            
        for (uint8 j = 0; j < MAX_CRITERIA_REQUIREMENTS; ++j)
        {
            if (achievementCriteria->additionalRequirements[j].additionalRequirement_type == miscvalue1 &&
                (!achievementCriteria->additionalRequirements[j].additionalRequirement_value ||
                achievementCriteria->additionalRequirements[j].additionalRequirement_value == miscvalue2))
            {
                RemoveCriteriaProgress(achievementCriteria);
                break;
            }
        }
    }
}

void GuildAchievementMgr::DeleteFromDB(uint32 id)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    trans->PAppend("DELETE FROM guild_achievement WHERE id = %u", id);
    trans->PAppend("DELETE FROM guild_achievement_progress WHERE id = %u", id);
    CharacterDatabase.CommitTransaction(trans);
}

void GuildAchievementMgr::SaveToDB(SQLTransaction& trans)
{
    if (!m_completedAchievements.empty())
    {
        bool need_execute = false;
        std::ostringstream ssdel;
        std::ostringstream ssins;
        for (CompletedAchievementMap::iterator iter = m_completedAchievements.begin(); iter != m_completedAchievements.end(); ++iter)
        {
            if (!iter->second.changed)
                continue;

            /// first new/changed record prefix
            if (!need_execute)
            {
                ssdel << "DELETE FROM guild_achievement WHERE id = " << m_guild->GetId() << " AND achievement IN (";
                ssins << "INSERT INTO guild_achievement (id, achievement, date) VALUES ";
                need_execute = true;
            }
            /// next new/changed record prefix
            else
            {
                ssdel << ',';
                ssins << ',';
            }

            // new/changed record data
            ssdel << iter->first;
            ssins << '(' << m_guild->GetId() << ',' << iter->first << ',' << uint64(iter->second.date) << ')';

            /// mark as saved in db
            iter->second.changed = false;
        }

        if (need_execute)
        {
            ssdel << ')';
            trans->Append(ssdel.str().c_str());
            trans->Append(ssins.str().c_str());
        }
    }
    
    if (!m_criteriaProgress.empty())
    {
        /// prepare deleting and insert
        bool need_execute_del = false;
        bool need_execute_ins = false;
        std::ostringstream ssdel;
        std::ostringstream ssins;
        for (CriteriaProgressMap::iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        {
            if (!iter->second.changed)
                continue;

            // deleted data (including 0 progress state)
            {
                /// first new/changed record prefix (for any counter value)
                if (!need_execute_del)
                {
                    ssdel << "DELETE FROM guild_achievement_progress WHERE id = " << m_guild->GetId() << " AND criteria IN (";
                    need_execute_del = true;
                }
                /// next new/changed record prefix
                else
                    ssdel << ',';

                // new/changed record data
                ssdel << iter->first;
            }

            // store data only for real progress
            if (iter->second.counter != 0)
            {
                /// first new/changed record prefix
                if (!need_execute_ins)
                {
                    ssins << "INSERT INTO guild_achievement_progress (id, criteria, counter, date) VALUES ";
                    need_execute_ins = true;
                }
                /// next new/changed record prefix
                else
                    ssins << ',';

                // new/changed record data
                ssins << '(' << m_guild->GetId() << ',' << iter->first << ',' << iter->second.counter << ',' << iter->second.date << ')';
            }

            /// mark as updated in db
            iter->second.changed = false;
        }

        if (need_execute_del)                                // DELETE ... IN (.... _)_
            ssdel << ')';

        if (need_execute_del || need_execute_ins)
        {
            if (need_execute_del)
                trans->Append(ssdel.str().c_str());
            if (need_execute_ins)
                trans->Append(ssins.str().c_str());
        }
    }
}

void GuildAchievementMgr::LoadFromDB()
{
    QueryResult achievementResult = CharacterDatabase.PQuery("SELECT achievement, date FROM guild_achievement WHERE id = %u", m_guild->GetId());
    QueryResult criteriaResult = CharacterDatabase.PQuery("SELECT criteria, counter, date FROM guild_achievement_progress WHERE id = %u", m_guild->GetId());
    if (achievementResult)
    {
        do
        {
            Field* fields = achievementResult->Fetch();
            uint32 achievementid = fields[0].GetUInt16();

            // must not happen: cleanup at server startup in sAchievementMgr->LoadCompletedAchievements()
            AchievementEntry const* achievement = sAchievementStore.LookupEntry(achievementid);
            if (!achievement)
                continue;
                
            if(!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
                continue;

            CompletedAchievementData& ca = m_completedAchievements[achievementid];
            ca.date = time_t(fields[1].GetUInt32());
            ca.changed = false;

        } while (achievementResult->NextRow());
    }
    
    if (criteriaResult)
    {
        do
        {
            Field* fields  = criteriaResult->Fetch();
            uint32 id      = fields[0].GetUInt16();
            uint32 counter = fields[1].GetUInt32();
            time_t date    = time_t(fields[2].GetUInt32());

            AchievementCriteriaEntry const* criteria = sAchievementCriteriaStore.LookupEntry(id);
            if (!criteria)
            {
                // we will remove not existed criteria for all characters
                sLog->outError("Non-existing achievement criteria %u data removed from table `guild_achievement_progress`.", id);
                CharacterDatabase.PExecute("DELETE FROM guild_achievement_progress WHERE criteria = %u", id);
                continue;
            }

            if (criteria->timeLimit && time_t(date + criteria->timeLimit) < time(NULL))
                continue;

            CriteriaProgress& progress = m_criteriaProgress[id];
            progress.counter = counter;
            progress.date    = date;
            progress.changed = false;
        } while (criteriaResult->NextRow());
    }
}

void GuildAchievementMgr::SendAchievementEarned(AchievementEntry const* achievement)
{
    if (achievement->flags & ACHIEVEMENT_FLAG_HIDDEN)
        return;
    
    if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return;
        
    /*Trinity::AchievementChatBuilder say_builder(*GetPlayer(), CHAT_MSG_GUILD_ACHIEVEMENT, LANG_ACHIEVEMENT_EARNED, achievement->ID);
    Trinity::LocalizedPacketDo<Trinity::AchievementChatBuilder> say_do(say_builder);
    m_guild->BroadcastWorker(say_do, GetPlayer());*/
    sLog->outString("Guild %u earned achievement %u", m_guild->GetId(), achievement->ID);
    
    // ToDo: Check structure
    WorldPacket data(SMSG_GUILD_ACHIEVEMENT_EARNED, 8+4+8);
    data << uint32(achievement->ID);
    data << uint64(MAKE_NEW_GUID(m_guild->GetId(), 0, HIGHGUID_GUILD));
    data << uint32(secsToTimeBitFields(time(NULL)));
    SendDirectMessageToAll(&data);
}

void GuildAchievementMgr::SendCriteriaUpdate(AchievementCriteriaEntry const* entry, CriteriaProgress const* progress, uint32 timeElapsed, bool timedCompleted, Player* completer)
{
    WorldPacket data(SMSG_CRITERIA_UPDATE, 8+4+8);
    data << uint32(entry->ID);

    // the counter is packed like a packed Guid
    data.appendPackGUID(progress->counter);

    uint64 guid = MAKE_NEW_GUID(m_guild->GetId(), 0, HIGHGUID_GUILD);
    data.appendPackGUID(guid);

    if (!entry->timeLimit)
        data << uint32(0);
    else
        data << uint32(timedCompleted ? 0 : 1); // this are some flags, 1 is for keeping the counter at 0 in client
    data << uint32(secsToTimeBitFields(progress->date));
    data << uint32(timeElapsed);    // time elapsed in seconds
    data << uint32(0);              // unk
    SendDirectMessageToAll(&data);
}

void GuildAchievementMgr::CheckAllAchievementCriteria()
{
    // suppress sending packets
    for (uint32 i = 0; i < ACHIEVEMENT_CRITERIA_TYPE_TOTAL; ++i)
        UpdateAchievementCriteria(AchievementCriteriaTypes(i), NULL); // ToDO: Fix this
}

bool GuildAchievementMgr::IsCriteriaMet(AchievementCriteriaEntry const* criteria, AchievementEntry const* achievement, Player* player, uint32 miscValue1, uint32 miscValue2, Unit* unit)
{
    for(uint32 i = 0; i < 3; ++i)
    {
        if(!criteria->moreRequirement[i])
            continue;
            
        switch(criteria->moreRequirement[i])
        {
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_GUILD_REP:
            {
                if (player->GetReputationMgr().GetReputation(1168) < criteria->moreRequirementValue[i])
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_CREATURE_TYPE:
            {
                if(miscValue1 != criteria->moreRequirementValue[i])
                    return false;
                break;
            }
            default:
                break;
        }
    }
}

void GuildAchievementMgr::UpdateAchievementCriteria(AchievementCriteriaTypes type, Player* player /*=NULL*/, uint32 miscValue1 /*= 0*/, uint32 miscValue2 /*= 0*/, Unit* unit /*= NULL*/)
{
    AchievementCriteriaEntryList const& achievementCriteriaList = sAchievementMgr->GetAchievementCriteriaByType(type);
    for (AchievementCriteriaEntryList::const_iterator i = achievementCriteriaList.begin(); i != achievementCriteriaList.end(); ++i)
    {
        AchievementCriteriaEntry const *achievementCriteria = (*i);
        AchievementEntry const *achievement = sAchievementStore.LookupEntry(achievementCriteria->referredAchievement);
        if (!achievement)
            continue;
            
        if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
            continue;

        if (!CanUpdateCriteria(achievementCriteria, achievement, player))
            continue;
            
        if(!IsCriteriaMet(achievementCriteria, achievement, player, miscValue1, miscValue2, unit))
            continue;
        
        sLog->outString("Updating criteria for guild achievement %u", achievement->ID);
        switch (type)
        {
            case ACHIEVEMENT_CRITERIA_TYPE_REACH_GUILD_LEVEL: // ACHIEVEMENT_CRITERIA_TYPE_****
            {
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, m_guild->GetLevel(), player, PROGRESS_HIGHEST);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM:
            {
                if (miscValue1 && achievementCriteria->own_item.itemID != miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue2, player, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT:
            {
                if (m_completedAchievements.find(achievementCriteria->complete_achievement.linkedAchievement) != m_completedAchievements.end())
                    SetCriteriaProgress(achievementCriteria, 1, player);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST:
            {
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE_GUILD:
            {
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            }
        }

        if (IsCompletedCriteria(achievementCriteria, achievement))
            CompletedCriteriaFor(achievement);

        // check again the completeness for SUMM and REQ COUNT achievements,
        // as they don't depend on the completed criteria but on the sum of the progress of each individual criteria
        if (achievement->flags & ACHIEVEMENT_FLAG_SUMM)
            if (IsCompletedAchievement(achievement))
                CompletedAchievement(achievement);

        if (AchievementEntryList const* achRefList = sAchievementMgr->GetAchievementByReferencedId(achievement->ID))
            for (AchievementEntryList::const_iterator itr = achRefList->begin(); itr != achRefList->end(); ++itr)
                if (IsCompletedAchievement(*itr))
                    CompletedAchievement(*itr);
    }
}

bool GuildAchievementMgr::IsCompletedCriteria(AchievementCriteriaEntry const* achievementCriteria, AchievementEntry const* achievement)
{
    if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return false;
            
    // counter can never complete
    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER)
        return false;
        
    CriteriaProgress const* progress = GetCriteriaProgress(achievementCriteria);
    if (!progress)
        return false;
        
    switch (achievementCriteria->requiredType)
    {
        case ACHIEVEMENT_CRITERIA_TYPE_REACH_GUILD_LEVEL:
            return progress->counter >= achievementCriteria->reach_guild_level.level;
        case ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM:
            return progress->counter >= achievementCriteria->own_item.itemCount;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT:
            return progress->counter >= 1;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST:
            return progress->counter >= achievementCriteria->complete_daily_quest.questCount;
        case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE_GUILD:
            return progress->counter >= achievementCriteria->kill_creature_type.count;
        default:
            break;
    }
    return false;
}

void GuildAchievementMgr::CompletedCriteriaFor(AchievementEntry const* achievement)
{
    if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return;
        
    // counter can never complete
    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER)
        return;

    // already completed and stored
    if (HasAchieved(achievement->ID))
        return;

    if (IsCompletedAchievement(achievement))
        CompletedAchievement(achievement);
}

bool GuildAchievementMgr::IsCompletedAchievement(AchievementEntry const* entry)
{
    if (!(entry->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return false;
        
    // counter can never complete
    if (entry->flags & ACHIEVEMENT_FLAG_COUNTER)
        return false;
        
    // for achievement with referenced achievement criterias get from referenced and counter from self
    uint32 achievmentForTestId = entry->refAchievement ? entry->refAchievement : entry->ID;
    uint32 achievmentForTestCount = entry->count;

    AchievementCriteriaEntryList const* cList = sAchievementMgr->GetAchievementCriteriaByAchievement(achievmentForTestId);
    if (!cList)
        return false;
    uint32 count = 0;

    // For SUMM achievements, we have to count the progress of each criteria of the achievement.
    // Oddly, the target count is NOT countained in the achievement, but in each individual criteria
    if (entry->flags & ACHIEVEMENT_FLAG_SUMM)
    {
        for (AchievementCriteriaEntryList::const_iterator itr = cList->begin(); itr != cList->end(); ++itr)
        {
            AchievementCriteriaEntry const* criteria = *itr;

            CriteriaProgress const* progress = GetCriteriaProgress(criteria);
            if (!progress)
                continue;

            count += progress->counter;

            // for counters, field4 contains the main count requirement
            if (count >= criteria->raw.count)
                return true;
        }
        return false;
    }

    // Default case - need complete all or
    bool completed_all = true;
    for (AchievementCriteriaEntryList::const_iterator itr = cList->begin(); itr != cList->end(); ++itr)
    {
        AchievementCriteriaEntry const* criteria = *itr;

        bool completed = IsCompletedCriteria(criteria, entry);

        // found an uncompleted criteria, but DONT return false yet - there might be a completed criteria with ACHIEVEMENT_CRITERIA_COMPLETE_FLAG_ALL
        if (completed)
            ++count;
        else
            completed_all = false;

        // completed as have req. count of completed criterias
        if (achievmentForTestCount > 0 && achievmentForTestCount <= count)
           return true;
    }

    // all criterias completed requirement
    if (completed_all && achievmentForTestCount == 0)
        return true;

    return false;
}

CriteriaProgress* GuildAchievementMgr::GetCriteriaProgress(AchievementCriteriaEntry const* entry)
{
    CriteriaProgressMap::iterator iter = m_criteriaProgress.find(entry->ID);

    if (iter == m_criteriaProgress.end())
        return NULL;

    return &(iter->second);
}

void GuildAchievementMgr::SetCriteriaProgress(AchievementCriteriaEntry const* entry, uint32 changeValue, Player* player, ProgressType ptype)
{
    // Don't allow to cheat - doing timed achievements without timer active
    TimedAchievementMap::iterator timedIter = m_timedAchievements.find(entry->ID);
    if (entry->timeLimit && timedIter == m_timedAchievements.end())
        return;
        
    CriteriaProgress* progress = GetCriteriaProgress(entry);
    if (!progress)
    {
        // not create record for 0 counter but allow it for timed achievements
        // we will need to send 0 progress to client to start the timer
        if (changeValue == 0 && !entry->timeLimit)
            return;

        progress = &m_criteriaProgress[entry->ID];
        progress->counter = changeValue;
    }
    else
    {
        uint32 newValue = 0;
        switch (ptype)
        {
            case PROGRESS_SET:
                newValue = changeValue;
                break;
            case PROGRESS_ACCUMULATE:
            {
                // avoid overflow
                uint32 max_value = std::numeric_limits<uint32>::max();
                newValue = max_value - progress->counter > changeValue ? progress->counter + changeValue : max_value;
                break;
            }
            case PROGRESS_HIGHEST:
                newValue = progress->counter < changeValue ? changeValue : progress->counter;
                break;
            default:
                break;        
        }

        // not update (not mark as changed) if counter will have same value
        if (progress->counter == newValue && !entry->timeLimit)
            return;

        progress->counter = newValue;
    }

    progress->changed = true;
    progress->date = time(NULL); // set the date to the latest update.

    uint32 timeElapsed = 0;
    bool timedCompleted = false;

    if (entry->timeLimit)
    {
        // has to exist else we wouldn't be here
        timedCompleted = IsCompletedCriteria(entry, sAchievementStore.LookupEntry(entry->referredAchievement));
        // Client expects this in packet
        timeElapsed = entry->timeLimit - (timedIter->second/IN_MILLISECONDS);

        // Remove the timer, we wont need it anymore
        if (timedCompleted)
            m_timedAchievements.erase(timedIter);
    }

    SendCriteriaUpdate(entry, progress, timeElapsed, timedCompleted, player);
}

void GuildAchievementMgr::RemoveCriteriaProgress(const AchievementCriteriaEntry *entry)
{
    CriteriaProgressMap::iterator criteriaProgress = m_criteriaProgress.find(entry->ID);
    if (criteriaProgress == m_criteriaProgress.end())
        return;

    WorldPacket data(SMSG_GUILD_CRITERIA_DELETED, 4);
    data << uint32(entry->ID);
    data << uint64(time(NULL));
    SendDirectMessageToAll(&data);

    m_criteriaProgress.erase(criteriaProgress);
}

void GuildAchievementMgr::UpdateTimedAchievements(uint32 timeDiff)
{
    if (!m_timedAchievements.empty())
    {
        for (TimedAchievementMap::iterator itr = m_timedAchievements.begin(); itr != m_timedAchievements.end();)
        {
            // Time is up, remove timer and reset progress
            if (itr->second <= timeDiff)
            {
                AchievementCriteriaEntry const *entry = sAchievementCriteriaStore.LookupEntry(itr->first);
                RemoveCriteriaProgress(entry);
                m_timedAchievements.erase(itr++);
            }
            else
            {
                itr->second -= timeDiff;
                ++itr;
            }
        }
    }
}

void GuildAchievementMgr::CompletedAchievement(AchievementEntry const* achievement)
{
    if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return;
        
    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER || HasAchieved(achievement->ID))
        return;
    
    SendAchievementEarned(achievement);
    CompletedAchievementData& ca =  m_completedAchievements[achievement->ID];
    ca.date = time(NULL);
    ca.changed = true;
    
    UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT, NULL);
}

void GuildAchievementMgr::SendAllAchievementData()
{
    // handler at 0x8C30 (not rebased)
    // Looks like only completed achievements data is sent in this packet
    WorldPacket data(SMSG_GUILD_ACHIEVEMENT_DATA, m_completedAchievements.size() * 4 * 4);
    
    data << uint32(m_completedAchievements.size());
    
    for (CompletedAchievementMap::const_iterator iter = m_completedAchievements.begin(); iter != m_completedAchievements.end(); ++iter)
        data << uint32(secsToTimeBitFields(iter->second.date));
    
    for (CompletedAchievementMap::const_iterator iter = m_completedAchievements.begin(); iter != m_completedAchievements.end(); ++iter)
        data << uint32(iter->first);
        
    SendDirectMessageToAll(&data);
    
    WorldPacket data2(SMSG_GUILD_CRITERIA_DATA);
    
    data2 << uint32(m_criteriaProgress.size());
    
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint64(iter->second.counter);
        
    time_t now = time(NULL);
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint32(now - iter->second.date);
        
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint32(secsToTimeBitFields(iter->second.date));
    
    for(CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint64(iter->second.counter);
        
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint32(now - iter->second.date);
        
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint32(iter->first);
        
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data << uint32(0); // Unk
        
    SendDirectMessageToAll(&data2);
}

bool GuildAchievementMgr::HasAchieved(uint32 achievementId)
{
    return m_completedAchievements.find(achievementId) != m_completedAchievements.end();
}

bool GuildAchievementMgr::CanUpdateCriteria(AchievementCriteriaEntry const* criteria, AchievementEntry const* achievement, Player* player)
{
    if (DisableMgr::IsDisabledFor(DISABLE_TYPE_ACHIEVEMENT_CRITERIA, criteria->ID, NULL))
        return false;
        
    if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return false;

    if (achievement->mapID != -1 && player->GetMapId() != uint32(achievement->mapID))
        return false;

    
    // ToDo: Enable this later
    /*if ((achievement->requiredFaction == ACHIEVEMENT_FACTION_HORDE    && player->GetTeam() != HORDE) ||
        (achievement->requiredFaction == ACHIEVEMENT_FACTION_ALLIANCE && player->GetTeam() != ALLIANCE))
        return false;

    for (uint32 i = 0; i < MAX_CRITERIA_REQUIREMENTS; ++i)
    {
        if (!criteria->additionalRequirements[i].additionalRequirement_type)
            continue;

        switch (criteria->additionalRequirements[i].additionalRequirement_type)
        {
            case ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP:
                if (player->GetMapId() != criteria->additionalRequirements[i].additionalRequirement_value)
                    return false;
                break;
            case ACHIEVEMENT_CRITERIA_CONDITION_NOT_IN_GROUP:
                if (player->GetGroup())
                    return false;
                break;
            default:
                break;
        }
    }
*/
    // don't update already completed criteria
    if (IsCompletedCriteria(criteria, achievement))
        return false;

    return true;
}