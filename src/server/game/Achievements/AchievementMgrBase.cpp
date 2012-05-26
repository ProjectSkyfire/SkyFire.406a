/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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

namespace SkyFire
{
    void AchievementChatBuilder::operator()(WorldPacket& data, LocaleConstant loc_idx)
    {
        char const* text = sObjectMgr->GetSkyFireString(i_textId, loc_idx);

        data << uint8(i_msgtype);
        data << uint32(LANG_UNIVERSAL);
        data << uint64(i_player.GetGUID());
        data << uint32(5);
        data << uint64(i_player.GetGUID());
        data << uint32(strlen(text)+1);
        data << text;
        data << uint8(0);
        data << uint32(i_achievementId);
    }
}

bool AchievementCriteriaData::IsValid(AchievementCriteriaEntry const* criteria)
{
    if (dataType >= MAX_ACHIEVEMENT_CRITERIA_DATA_TYPE)
    {
        sLog->outErrorDb("Table `achievement_criteria_data` for criteria (Entry: %u) has wrong data type (%u), ignored.", criteria->ID, dataType);
        return false;
    }

    switch (criteria->requiredType)
    {
        case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE:
        case ACHIEVEMENT_CRITERIA_TYPE_WIN_BG:
        case ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING:
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST:          // only hardcoded list
        case ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL:
        case ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA:
        case ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE:
        case ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL:
        case ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL:
        case ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE:
        case ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2:
        case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET:
        case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2:
        case ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM:
        case ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT:
        case ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT:
        case ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE:
        case ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL:
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST:    // only Children's Week achievements
        case ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM:                // only Children's Week achievements
        case ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS:
        case ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL:
            break;
        default:
            if (dataType != ACHIEVEMENT_CRITERIA_DATA_TYPE_SCRIPT)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` has data for non-supported criteria type (Entry: %u Type: %u), ignored.", criteria->ID, criteria->requiredType);
                return false;
            }
            break;
    }

    switch (dataType)
    {
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_NONE:
        case ACHIEVEMENT_CRITERIA_DATA_INSTANCE_SCRIPT:
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_DEAD:
            if (player_dead.own_team_flag > 1)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_DEAD (%u) has wrong boolean value1 (%u).",
                    criteria->ID, criteria->requiredType, dataType, player_dead.own_team_flag);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_LEVEL:
            if (level.minlevel > STRONG_MAX_LEVEL)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_T_LEVEL (%u) has wrong minlevel in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, level.minlevel);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_GENDER:
            if (gender.gender > GENDER_NONE)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_T_GENDER (%u) has wrong gender in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, gender.gender);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_SCRIPT:
            if (!ScriptId)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_SCRIPT (%u) does not have ScriptName set, ignored.",
                    criteria->ID, criteria->requiredType, dataType);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_DIFFICULTY:
            if (difficulty.difficulty >= MAX_DIFFICULTY)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_DIFFICULTY (%u) has wrong difficulty in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, difficulty.difficulty);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_PLAYER_COUNT:
            if (map_players.maxcount <= 0)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_PLAYER_COUNT (%u) has wrong max players count in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, map_players.maxcount);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_TEAM:
            if (team.team != ALLIANCE && team.team != HORDE)
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_T_TEAM (%u) has unknown team in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, team.team);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_HOLIDAY:
            if (!sHolidaysStore.LookupEntry(holiday.id))
            {
                sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) for data type ACHIEVEMENT_CRITERIA_DATA_TYPE_HOLIDAY (%u) has unknown holiday in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, holiday.id);
                return false;
            }
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_BG_LOSS_TEAM_SCORE:
            return true;                                    // not check correctness node indexes
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_ID:
            if (!sMapStore.LookupEntry(map_id.mapId))
            {
                sLog->outErrorDb("Table `achievement_criteria_requirement` (Entry: %u Type: %u) for requirement ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_ID (%u) has unknown map id in value1 (%u), ignored.",
                    criteria->ID, criteria->requiredType, dataType, map_id.mapId);
                return false;
            }
            return true;
        default:
            sLog->outErrorDb("Table `achievement_criteria_data` (Entry: %u Type: %u) has data for non-supported data type (%u), ignored.", criteria->ID, criteria->requiredType, dataType);
            return false;
    }
}

bool AchievementCriteriaData::Meets(uint32 criteria_id, Player const* source, Unit const* target, uint32 miscvalue1 /*= 0*/) const
{
    const AchievementCriteriaEntry* criteria = sAchievementCriteriaStore.LookupEntry(criteria_id);

    switch (dataType)
    {
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_NONE:
            return true;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_DEAD:
            if (target && !target->isAlive())
                if (const Player* player = target->ToPlayer())
                    if (player->GetDeathTimer() != 0)
                        // flag set == must be same team, not set == different team
                        return (player->GetTeam() == source->GetTeam()) == (player_dead.own_team_flag != 0);
            return false;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_LEVEL:
            if (!target)
                return false;
            return target->getLevel() >= level.minlevel;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_GENDER:
            if (!target)
                return false;
            return target->getGender() == gender.gender;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_SCRIPT:
            return sScriptMgr->OnCriteriaCheck(this, const_cast<Player*>(source), const_cast<Unit*>(target));
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_DIFFICULTY:
            if (source->GetMap()->IsRaid())
                if (source->GetMap()->Is25ManRaid() != (difficulty.difficulty & RAID_DIFFICULTY_MASK_25MAN))
                    return false;
            return source->GetMap()->GetSpawnMode() >= difficulty.difficulty;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_PLAYER_COUNT:
            return source->GetMap()->GetPlayersCountExceptGMs() <= map_players.maxcount;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_T_TEAM:
            if (!target || target->GetTypeId() != TYPEID_PLAYER)
                return false;
            return target->ToPlayer()->GetTeam() == team.team;
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_HOLIDAY:
            return IsHolidayActive(HolidayIds(holiday.id));
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_BG_LOSS_TEAM_SCORE:
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;
            return bg->IsTeamScoreInRange(source->GetTeam() == ALLIANCE ? HORDE : ALLIANCE, bg_loss_team_score.min_score, bg_loss_team_score.max_score);
        }
        case ACHIEVEMENT_CRITERIA_DATA_INSTANCE_SCRIPT:
        {
            if (!source->IsInWorld())
                return false;
            Map* map = source->GetMap();
            if (!map->IsDungeon())
            {
                sLog->outErrorDb("Achievement system call ACHIEVEMENT_CRITERIA_DATA_INSTANCE_SCRIPT (%u) for achievement criteria %u for non-dungeon/non-raid map %u",
                    ACHIEVEMENT_CRITERIA_DATA_INSTANCE_SCRIPT, criteria_id, map->GetId());
                    return false;
            }
            InstanceScript* instance = ((InstanceMap*)map)->GetInstanceScript();
            if (!instance)
            {
                sLog->outErrorDb("Achievement system call ACHIEVEMENT_CRITERIA_DATA_INSTANCE_SCRIPT (%u) for achievement criteria %u for map %u but map does not have a instance script",
                    ACHIEVEMENT_CRITERIA_DATA_INSTANCE_SCRIPT, criteria_id, map->GetId());
                return false;
            }
            return instance->CheckAchievementCriteriaMeet(criteria_id, source, target, miscvalue1);
        }
        case ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_ID:
            return source->GetMapId() == map_id.mapId;
        default:
            break;
    }
    return false;
}

bool AchievementCriteriaDataSet::Meets(Player const* source, Unit const* target, uint32 miscvalue /*= 0*/) const
{
    for (Storage::const_iterator itr = storage.begin(); itr != storage.end(); ++itr)
        if (!itr->Meets(criteria_id, source, target, miscvalue))
            return false;

    return true;
}

void AchievementMgrBase::ResetAchievementCriteria(AchievementCriteriaTypes type, Player* player, uint32 miscvalue1, uint32 miscvalue2, bool evenIfCriteriaComplete)
{
    sLog->outDebug(LOG_FILTER_ACHIEVEMENTSYS, "AchievementMgr::ResetAchievementCriteria(%u, %u, %u)", type, miscvalue1, miscvalue2);

    // disable for gamemasters with GM-mode enabled
    if (player->isGameMaster())
        return;

    AchievementCriteriaEntryList const& achievementCriteriaList = sAchievementMgr->GetAchievementCriteriaByType(type);
    for (AchievementCriteriaEntryList::const_iterator i = achievementCriteriaList.begin(); i != achievementCriteriaList.end(); ++i)
    {
        AchievementCriteriaEntry const *achievementCriteria = (*i);

        AchievementEntry const *achievement = sAchievementStore.LookupEntry(achievementCriteria->referredAchievement);
        if (!achievement)
            continue;

        // don't update already completed criteria if not forced or achievement already complete
        if ((IsCompletedCriteria(achievementCriteria, achievement, player) && !evenIfCriteriaComplete) || HasAchieved(achievement->ID))
            continue;

        for (uint8 j = 0; j < MAX_CRITERIA_REQUIREMENTS; ++j)
            if (achievementCriteria->additionalRequirements[j].additionalRequirement_type == miscvalue1 &&
                (!achievementCriteria->additionalRequirements[j].additionalRequirement_value ||
                achievementCriteria->additionalRequirements[j].additionalRequirement_value == miscvalue2))
            {
                RemoveCriteriaProgress(achievementCriteria, player);
                break;
            }
    }
}

void AchievementMgrBase::SendCriteriaUpdate(AchievementCriteriaEntry const* entry, CriteriaProgress const* progress, uint32 timeElapsed, bool timedCompleted, Player* player)
{
    if(!_guild)
    {
        WorldPacket data(SMSG_CRITERIA_UPDATE, 8+4+8);
        data << uint32(entry->ID);

        // the counter is packed like a packed Guid
        data.appendPackGUID(progress->counter);

        data.append(player->GetPackGUID());
        if (!entry->timeLimit)
            data << uint32(0);
        else
            data << uint32(timedCompleted ? 0 : 1); // this are some flags, 1 is for keeping the counter at 0 in client
        data << uint32(secsToTimeBitFields(progress->date));
        data << uint32(timeElapsed);    // time elapsed in seconds
        data << uint32(0);              // unk
        player->SendDirectMessage(&data);

        return;
    }

    WorldPacket data(SMSG_CRITERIA_UPDATE, 8+4+8);
    data << uint32(entry->ID);

    // the counter is packed like a packed Guid
    data.appendPackGUID(progress->counter);

    uint64 guid = MAKE_NEW_GUID(_guild->GetId(), 0, HIGHGUID_GUILD);
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

void AchievementMgrBase::SendDirectMessageToAll(WorldPacket* data)
{
    if (!_guild)
        return;

    Guild::Members list = _guild->GetMembers();
    for (Guild::Members::iterator itr = list.begin(); itr != list.end(); ++itr)
        if (Player* player = itr->second->FindPlayer())
            player->SendDirectMessage(data);
}

static const uint32 achievIdByArenaSlot[MAX_ARENA_SLOT] = { 1057, 1107, 1108 };
static const uint32 achievIdForDungeon[][4] =
{
    // ach_cr_id, is_dungeon, is_raid, is_heroic_dungeon
    { 321,       true,      true,   true  },
    { 916,       false,     true,   false },
    { 917,       false,     true,   false },
    { 918,       true,      false,  false },
    { 2219,      false,     false,  true  },
    { 0,         false,     false,  false }
};

/**
 * this function will be called whenever the user might have done a criteria relevant action
 */
void AchievementMgrBase::UpdateAchievementCriteria(AchievementCriteriaTypes type, Player* player, uint32 miscValue1 /*= 0*/, uint32 miscValue2 /*= 0*/, Unit* unit /*= NULL*/)
{
    sLog->outDebug(LOG_FILTER_ACHIEVEMENTSYS, "AchievementMgr::UpdateAchievementCriteria(%u, %u, %u)", type, miscValue1, miscValue2);

    // disable for gamemasters with GM-mode enabled
    if (player->isGameMaster())
        return;

    AchievementCriteriaEntryList const& achievementCriteriaList = sAchievementMgr->GetAchievementCriteriaByType(type);
    for (AchievementCriteriaEntryList::const_iterator i = achievementCriteriaList.begin(); i != achievementCriteriaList.end(); ++i)
    {
        AchievementCriteriaEntry const *achievementCriteria = (*i);
        AchievementEntry const *achievement = sAchievementStore.LookupEntry(achievementCriteria->referredAchievement);
        if (!achievement)
            continue;

        if (!CanUpdateCriteria(achievementCriteria, achievement, player, miscValue1, miscValue2, unit))
            continue;

        switch (type)
        {
            // std. case: increment at 1
            case ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS:
            case ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL:
            case ACHIEVEMENT_CRITERIA_TYPE_CREATE_AUCTION:
            case ACHIEVEMENT_CRITERIA_TYPE_WON_AUCTIONS:    /* FIXME: for online player only currently */
            case ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED:
            case ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED:
            case ACHIEVEMENT_CRITERIA_TYPE_QUEST_ABANDONED:
            case ACHIEVEMENT_CRITERIA_TYPE_FLIGHT_PATHS_TAKEN:
            case ACHIEVEMENT_CRITERIA_TYPE_ACCEPTED_SUMMONINGS:
            case ACHIEVEMENT_CRITERIA_TYPE_USE_LFD_TO_GROUP_WITH_PLAYERS:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            // std case: increment at miscvalue1
            case ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_VENDORS:
            case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS:
            case ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD:
            case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TRAVELLING:
            case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER:
            case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL:
            case ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY:
            case ACHIEVEMENT_CRITERIA_TYPE_GOLD_EARNED_BY_AUCTIONS:/* FIXME: for online player only currently */
            case ACHIEVEMENT_CRITERIA_TYPE_TOTAL_DAMAGE_RECEIVED:
            case ACHIEVEMENT_CRITERIA_TYPE_TOTAL_HEALING_RECEIVED:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_ACCUMULATE);
                break;
            // std case: high value at miscvalue1
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_BID:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_SOLD: /* FIXME: for online player only currently */
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_DEALT:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_RECEIVED:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEAL_CASTED:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALING_RECEIVED:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_HIGHEST);
                break;

            // specialized cases
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_WIN_BG:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                if (achievementCriteria->win_bg.bgMapID != player->GetMapId())
                    continue;

                // those requirements couldn't be found in the dbc
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, unit))
                    continue;

                SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE:
            {
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                if (achievementCriteria->kill_creature.creatureID != miscValue1)
                    continue;

                // those requirements couldn't be found in the dbc
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, unit))
                    continue;

                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL:
                if (AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria))
                    if (!data->Meets(player, unit))
                        continue;
                SetCriteriaProgress(achievementCriteria, _player->getLevel());
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL:
                // update at loading or specific skill update
                if (miscValue1 && miscValue1 != achievementCriteria->reach_skill_level.skillID)
                    continue;
                if (uint32 skillvalue = player->GetBaseSkillValue(achievementCriteria->reach_skill_level.skillID))
                    SetCriteriaProgress(achievementCriteria, skillvalue);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL:
                // update at loading or specific skill update
                if (miscValue1 && miscValue1 != achievementCriteria->learn_skill_level.skillID)
                    continue;
                if (uint32 maxSkillvalue = player->GetPureMaxSkillValue(achievementCriteria->learn_skill_level.skillID))
                    SetCriteriaProgress(achievementCriteria, maxSkillvalue);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT:
                if (m_completedAchievements.find(achievementCriteria->complete_achievement.linkedAchievement) != m_completedAchievements.end())
                    SetCriteriaProgress(achievementCriteria, 1);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT:
            {
                SetCriteriaProgress(achievementCriteria, player->GetRewardedQuestCount());
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY:
            {
                time_t nextDailyResetTime = sWorld->GetNextDailyQuestsResetTime();
                CriteriaProgress *progress = GetCriteriaProgress(achievementCriteria);

                if (!miscValue1) // Login case.
                {
                    // reset if player missed one day.
                    if (progress && progress->date < (nextDailyResetTime - 2 * DAY))
                        SetCriteriaProgress(achievementCriteria, 0, PROGRESS_SET);
                    continue;
                }

                ProgressType progressType;
                if (!progress)
                    // 1st time. Start count.
                    progressType = PROGRESS_SET;
                else if (progress->date < (nextDailyResetTime - 2 * DAY))
                    // last progress is older than 2 days. Player missed 1 day => Restart count.
                    progressType = PROGRESS_SET;
                else if (progress->date < (nextDailyResetTime - DAY))
                    // last progress is between 1 and 2 days. => 1st time of the day.
                    progressType = PROGRESS_ACCUMULATE;
                else
                    // last progress is within the day before the reset => Already counted today.
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, progressType);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE:
            {
                // speedup for non-login case
                if (miscValue1 && miscValue1 != achievementCriteria->complete_quests_in_zone.zoneID)
                    continue;

                uint32 counter = 0;

                const RewardedQuestSet &rewQuests = player->getRewardedQuests();
                for (RewardedQuestSet::const_iterator itr = rewQuests.begin(); itr != rewQuests.end(); ++itr)
                {
                    Quest const* quest = sObjectMgr->GetQuestTemplate(*itr);
                    if (quest && quest->GetZoneOrSort() >= 0 && uint32(quest->GetZoneOrSort()) == achievementCriteria->complete_quests_in_zone.zoneID)
                        ++counter;
                }
                SetCriteriaProgress(achievementCriteria, counter);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                if (player->GetMapId() != achievementCriteria->complete_battleground.mapID)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                if (player->GetMapId() != achievementCriteria->death_at_map.mapID)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_DEATH:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                // skip wrong arena achievements, if not achievIdByArenaSlot then normal total death counter
                bool notfit = false;
                for (int j = 0; j < MAX_ARENA_SLOT; ++j)
                {
                    if (achievIdByArenaSlot[j] == achievement->ID)
                    {
                        Battleground* bg = player->GetBattleground();
                        if (!bg || !bg->isArena() || ArenaTeam::GetSlotByType(bg->GetArenaType()) != j)
                            notfit = true;

                        break;
                    }
                }
                if (notfit)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;

                Map const* map = player->IsInWorld() ? player->GetMap() : sMapMgr->FindMap(player->GetMapId(), player->GetInstanceId());
                if (!map || !map->IsDungeon())
                    continue;

                // search case
                bool found = false;
                for (int j = 0; achievIdForDungeon[j][0]; ++j)
                {
                    if (achievIdForDungeon[j][0] == achievement->ID)
                    {
                        if (map->IsRaid())
                        {
                            // if raid accepted (ignore difficulty)
                            if (!achievIdForDungeon[j][2])
                                break;                      // for
                        }
                        else if (player->GetDungeonDifficulty() == DUNGEON_DIFFICULTY_NORMAL)
                        {
                            // dungeon in normal mode accepted
                            if (!achievIdForDungeon[j][1])
                                break;                      // for
                        }
                        else
                        {
                            // dungeon in heroic mode accepted
                            if (!achievIdForDungeon[j][3])
                                break;                      // for
                        }

                        found = true;
                        break;                              // for
                    }
                }
                if (!found)
                    continue;

                //FIXME: work only for instances where max == min for players
                if (((InstanceMap*)map)->GetMaxPlayers() != achievementCriteria->death_in_dungeon.manLimit)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                if (miscValue1 != achievementCriteria->killed_by_creature.creatureEntry)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;

                // if team check required: must kill by opposition faction
                if (achievement->ID == 318 && miscValue2 == player->GetTeam())
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;

                // those requirements couldn't be found in the dbc
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, unit))
                    continue;

                // miscvalue1 is the ingame fallheight*100 as stored in dbc
                SetCriteriaProgress(achievementCriteria, miscValue1);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                if (miscValue2 != achievementCriteria->death_from.type)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST:
            {
                // if miscvalues != 0, it contains the questID.
                if (miscValue1)
                {
                    if (miscValue1 != achievementCriteria->complete_quest.questID)
                        continue;
                }
                else
                {
                    // login case.
                    if (!player->GetQuestRewardStatus(achievementCriteria->complete_quest.questID))
                        continue;
                }

                if (AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria))
                    if (!data->Meets(player, unit))
                        continue;

                SetCriteriaProgress(achievementCriteria, 1);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET:
            case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2:
            {
                if (!miscValue1 || miscValue1 != achievementCriteria->be_spell_target.spellID)
                    continue;

                // those requirements couldn't be found in the dbc
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data)
                    continue;

                if (!data->Meets(player, unit))
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL:
            case ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2:
            {
                if (!miscValue1 || miscValue1 != achievementCriteria->cast_spell.spellID)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL:
                if (miscValue1 && miscValue1 != achievementCriteria->learn_spell.spellID)
                    continue;

                if (player->HasSpell(achievementCriteria->learn_spell.spellID))
                    SetCriteriaProgress(achievementCriteria, 1, PROGRESS_SET);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE:
            {
                // miscvalue1=loot_type (note: 0 = LOOT_CORPSE and then it ignored)
                // miscvalue2=count of item loot
                if (!miscValue1 || !miscValue2)
                    continue;
                if (miscValue1 != achievementCriteria->loot_type.lootType)
                    continue;

                // zone specific
                if (achievementCriteria->loot_type.lootTypeCount == 1)
                {
                    // those requirements couldn't be found in the dbc
                    AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                    if (!data || !data->Meets(player, unit))
                        continue;
                }

                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM:
                // speedup for non-login case
                if (miscValue1 && achievementCriteria->own_item.itemID != miscValue1)
                    continue;
                //SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA:
                if (!miscValue1)                            // no update at login
                    continue;

                // additional requirements
                if (achievementCriteria->additionalRequirements[0].additionalRequirement_type == ACHIEVEMENT_CRITERIA_CONDITION_NO_LOSE)
                {
                    // those requirements couldn't be found in the dbc
                    AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                    if (!data || !data->Meets(player, unit, miscValue1))
                    {
                        // reset the progress as we have a win without the requirement.
                        SetCriteriaProgress(achievementCriteria, 0);
                        continue;
                    }
                }

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;

                if (achievementCriteria->use_item.itemID != miscValue1)
                    continue;

                // Children's Week achievements have extra requirements
                if (achievement->categoryId == CATEGORY_CHILDRENS_WEEK)
                {
                    AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                    if (!data || !data->Meets(player, NULL))
                        continue;
                }

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM:
                // You _have_ to loot that item, just owning it when logging in does _not_ count!
                if (!miscValue1)
                    continue;
                if (miscValue1 != achievementCriteria->own_item.itemID)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA:
            {
                WorldMapOverlayEntry const* worldOverlayEntry = sWorldMapOverlayStore.LookupEntry(achievementCriteria->explore_area.areaReference);
                if (!worldOverlayEntry)
                    break;

                bool matchFound = false;
                for (int j = 0; j < MAX_WORLD_MAP_OVERLAY_AREA_IDX; ++j)
                {
                    uint32 area_id = worldOverlayEntry->areatableID[j];
                    if (!area_id)                            // array have 0 only in empty tail
                        break;

                    int32 exploreFlag = GetAreaFlagByAreaID(area_id);
                    if (exploreFlag < 0)
                        continue;

                    uint32 playerIndexOffset = uint32(exploreFlag) / 32;
                    uint32 mask = 1<< (uint32(exploreFlag) % 32);

                    if (player->GetUInt32Value(PLAYER_EXPLORED_ZONES_1 + playerIndexOffset) & mask)
                    {
                        matchFound = true;
                        break;
                    }
                }

                if (matchFound)
                    SetCriteriaProgress(achievementCriteria, 1);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT:
                SetCriteriaProgress(achievementCriteria, player->GetBankBagSlotCount());
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION:
            {
                // skip faction check only at loading
                if (miscValue1 && miscValue1 != achievementCriteria->gain_reputation.factionID)
                    continue;

                int32 reputation = player->GetReputationMgr().GetReputation(achievementCriteria->gain_reputation.factionID);
                if (reputation > 0)
                    SetCriteriaProgress(achievementCriteria, reputation);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION:
            {
                SetCriteriaProgress(achievementCriteria, player->GetReputationMgr().GetExaltedFactionCount());
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP:
            {
                // skip for login case
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM:
            {
                // miscvalue1 = itemid
                // miscvalue2 = itemSlot
                if (!miscValue1)
                    continue;

                if (miscValue2 != achievementCriteria->equip_epic_item.itemSlot)
                    continue;

                // check item level and quality via achievement_criteria_data
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, 0, miscValue1))
                    continue;

                SetCriteriaProgress(achievementCriteria, 1);
                break;
            }

            case ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT:
            case ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT:
            {
                // miscvalue1 = itemid
                // miscvalue2 = diced value
                if (!miscValue1)
                    continue;
                if (miscValue2 != achievementCriteria->roll_greed_on_loot.rollValue)
                    continue;

                ItemTemplate const *proto = sObjectMgr->GetItemTemplate(miscValue1);
                if (!proto)
                    continue;

                // check item level via achievement_criteria_data
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, 0, proto->ItemLevel))
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE:
            {
                // miscvalue1 = emote
                if (!miscValue1)
                    continue;
                if (miscValue1 != achievementCriteria->do_emote.emoteID)
                    continue;
                if (achievementCriteria->do_emote.count)
                {
                    // those requirements couldn't be found in the dbc
                    AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                    if (!data || !data->Meets(player, unit))
                        continue;
                }

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE:
            case ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE:
            {
                if (!miscValue1)
                    continue;

                if (achievementCriteria->additionalRequirements[0].additionalRequirement_type == ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP)
                {
                    if (player->GetMapId() != achievementCriteria->additionalRequirements[0].additionalRequirement_value)
                        continue;

                    // map specific case (BG in fact) expected player targeted damage/heal
                    if (!unit || unit->GetTypeId() != TYPEID_PLAYER)
                        continue;
                }

                SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM:
                // miscvalue1 = item_id
                if (!miscValue1)
                    continue;
                if (miscValue1 != achievementCriteria->equip_item.itemID)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT:
                // miscvalue1 = go entry
                if (!miscValue1)
                    continue;
                if (miscValue1 != achievementCriteria->use_gameobject.goEntry)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT:
                if (!miscValue1)
                    continue;
                if (miscValue1 != achievementCriteria->fish_in_gameobject.goEntry)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS:
            {
                if (miscValue1 && miscValue1 != achievementCriteria->learn_skillline_spell.skillLine)
                    continue;

                uint32 spellCount = 0;
                for (PlayerSpellMap::const_iterator spellIter = player->GetSpellMap().begin();
                    spellIter != player->GetSpellMap().end();
                    ++spellIter)
                {
                    SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(spellIter->first);
                    for (SkillLineAbilityMap::const_iterator skillIter = bounds.first; skillIter != bounds.second; ++skillIter)
                    {
                        if (skillIter->second->skillId == achievementCriteria->learn_skillline_spell.skillLine)
                            spellCount++;
                    }
                }
                SetCriteriaProgress(achievementCriteria, spellCount);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL:
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;

                if (achievementCriteria->win_duel.duelCount)
                {
                    // those requirements couldn't be found in the dbc
                    AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                    if (!data)
                        continue;

                    if (!data->Meets(player, unit))
                        continue;
                }

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_GAIN_REVERED_REPUTATION:
                SetCriteriaProgress(achievementCriteria, player->GetReputationMgr().GetReveredFactionCount());
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_GAIN_HONORED_REPUTATION:
                SetCriteriaProgress(achievementCriteria, player->GetReputationMgr().GetHonoredFactionCount());
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_KNOWN_FACTIONS:
                SetCriteriaProgress(achievementCriteria, player->GetReputationMgr().GetVisibleFactionCount());
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_LOOT_EPIC_ITEM:
            case ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM:
            {
                // AchievementMgr::UpdateAchievementCriteria might also be called on login - skip in this case
                if (!miscValue1)
                    continue;
                ItemTemplate const* proto = sObjectMgr->GetItemTemplate(miscValue1);
                if (!proto || proto->Quality < ITEM_QUALITY_EPIC)
                    continue;
                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE:
            {
                if (miscValue1 && miscValue1 != achievementCriteria->learn_skill_line.skillLine)
                    continue;

                uint32 spellCount = 0;
                for (PlayerSpellMap::const_iterator spellIter = player->GetSpellMap().begin();
                    spellIter != player->GetSpellMap().end();
                    ++spellIter)
                {
                    SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(spellIter->first);
                    for (SkillLineAbilityMap::const_iterator skillIter = bounds.first; skillIter != bounds.second; ++skillIter)
                        if (skillIter->second->skillId == achievementCriteria->learn_skill_line.skillLine)
                            spellCount++;
                }
                SetCriteriaProgress(achievementCriteria, spellCount);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL:
                SetCriteriaProgress(achievementCriteria, player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS));
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS:
                if (!miscValue1 || miscValue1 != achievementCriteria->hk_class.classID)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_HK_RACE:
                if (!miscValue1 || miscValue1 != achievementCriteria->hk_race.raceID)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_GOLD_VALUE_OWNED:
                SetCriteriaProgress(achievementCriteria, player->GetMoney(), PROGRESS_HIGHEST);
                break;
            case ACHIEVEMENT_CRITERIA_TYPE_EARN_ACHIEVEMENT_POINTS:
            {
                if (!miscValue1)
                    SetCriteriaProgress(achievementCriteria, m_achievementPoints, PROGRESS_SET);
                else
                    SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE:
            {
                if (!miscValue1 || miscValue1 != achievementCriteria->bg_objective.objectiveId)
                    continue;

                // those requirements couldn't be found in the dbc
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, unit))
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL:
            case ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL:
            case ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS:
            {
                // skip login update
                if (!miscValue1)
                    continue;

                // those requirements couldn't be found in the dbc
                AchievementCriteriaDataSet const* data = sAchievementMgr->GetCriteriaDataSet(achievementCriteria);
                if (!data || !data->Meets(player, unit))
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA:
            {
                if (!miscValue1 || miscValue1 != achievementCriteria->honorable_kill_at_area.areaID)
                    continue;

                SetCriteriaProgress(achievementCriteria, 1, PROGRESS_ACCUMULATE);
                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING:
            {
                uint32 reqTeamType = achievementCriteria->highest_team_rating.teamtype;

                if (miscValue1)
                {
                    if (miscValue2 != reqTeamType)
                        continue;

                    SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_HIGHEST);
                }
                else    // login case
                {
                    for (uint32 arena_slot = 0; arena_slot < MAX_ARENA_SLOT; ++arena_slot)
                    {
                        uint32 teamId = player->GetArenaTeamId(arena_slot);
                        if (!teamId)
                            continue;

                        ArenaTeam* team = sArenaTeamMgr->GetArenaTeamById(teamId);
                        if (!team || team->GetType() != reqTeamType)
                            continue;

                        SetCriteriaProgress(achievementCriteria, team->GetStats().Rating, PROGRESS_HIGHEST);
                        break;
                    }
                }

                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_PERSONAL_RATING:
            {
                uint32 reqTeamType = achievementCriteria->highest_personal_rating.teamtype;

                if (miscValue1)
                {
                    if (miscValue2 != reqTeamType)
                        continue;

                    SetCriteriaProgress(achievementCriteria, miscValue1, PROGRESS_HIGHEST);
                }
                else    // login case
                {
                    for (uint32 arena_slot = 0; arena_slot < MAX_ARENA_SLOT; ++arena_slot)
                    {
                        uint32 teamId = player->GetArenaTeamId(arena_slot);
                        if (!teamId)
                            continue;

                        ArenaTeam* team = sArenaTeamMgr->GetArenaTeamById(teamId);
                        if (!team || team->GetType() != reqTeamType)
                            continue;

                        if (ArenaTeamMember const* member = team->GetMember(player->GetGUID()))
                        {
                            SetCriteriaProgress(achievementCriteria, member->PersonalRating, PROGRESS_HIGHEST);
                            break;
                        }
                    }
                }

                break;
            }
            case ACHIEVEMENT_CRITERIA_TYPE_CURRENCY:
                if (!miscValue1 || !miscValue2)
                    continue;
                if (miscValue1 != achievementCriteria->currencyGain.currency)
                    continue;
                if (int64(miscValue2) < 0)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
                // FIXME: not triggered in code as result, need to implement
            case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE_GUILD:
            {
                if (!miscValue1)
                    continue;
                SetCriteriaProgress(achievementCriteria, miscValue2, PROGRESS_ACCUMULATE);
                break;
            }
            // std case: not exist in DBC, not triggered in code as result
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALTH:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_ARMOR:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT:
            case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_RATING:
                break;
            // FIXME: not triggered in code as result, need to implement
            case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID:
            case ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA:
            case ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA:
            case ACHIEVEMENT_CRITERIA_TYPE_OWN_RANK:
            case ACHIEVEMENT_CRITERIA_TYPE_EARNED_PVP_TITLE:
            case ACHIEVEMENT_CRITERIA_TYPE_TOTAL:
                break;                                   // Not implemented yet :(
        }

        if (IsCompletedCriteria(achievementCriteria, achievement, player))
            CompletedCriteriaFor(achievement, player);

        // check again the completeness for SUMM and REQ COUNT achievements,
        // as they don't depend on the completed criteria but on the sum of the progress of each individual criteria
        if (achievement->flags & ACHIEVEMENT_FLAG_SUMM)
            if (IsCompletedAchievement(achievement, player))
                CompletedAchievement(achievement);

        if (AchievementEntryList const* achRefList = sAchievementMgr->GetAchievementByReferencedId(achievement->ID))
            for (AchievementEntryList::const_iterator itr = achRefList->begin(); itr != achRefList->end(); ++itr)
                if (IsCompletedAchievement(*itr, player))
                    CompletedAchievement(*itr);
    }
}

static const uint32 achievIdByClass[MAX_CLASSES] = { 0, 459, 465, 462, 458, 464, 461, 467, 460, 463, 0, 466 };
static const uint32 achievIdByRace[MAX_RACES]    = { 0, 1408, 1410, 1407, 1409, 1413, 1411, 1404, 1412, 0, 1405, 1406 };

bool AchievementMgrBase::IsCompletedCriteria(AchievementCriteriaEntry const* achievementCriteria, AchievementEntry const* achievement, Player* player)
{
    // counter can never complete
    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER)
        return false;

    if (achievement->flags & (ACHIEVEMENT_FLAG_REALM_FIRST_REACH | ACHIEVEMENT_FLAG_REALM_FIRST_KILL))
    {
        // someone on this realm has already completed that achievement
        if (sAchievementMgr->IsRealmCompleted(achievement))
            return false;
    }

    CriteriaProgress const* progress = GetCriteriaProgress(achievementCriteria);
    if (!progress)
        return false;

    switch (achievementCriteria->requiredType)
    {
        case ACHIEVEMENT_CRITERIA_TYPE_WIN_BG:
            return progress->counter >= achievementCriteria->win_bg.winCount;
        case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE:
            return progress->counter >= achievementCriteria->kill_creature.creatureCount;
        case ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL:
        {
            // skip wrong class achievements
            for (int i = 1; i < MAX_CLASSES; ++i)
                if (achievIdByClass[i] == achievement->ID && i != player->getClass())
                    return false;

            // skip wrong race achievements
            for (int i = 1; i < MAX_RACES; ++i)
                if (achievIdByRace[i] == achievement->ID && i != player->getRace())
                    return false;

            // appropriate class/race or not class/race specific
            return progress->counter >= achievementCriteria->reach_level.level;
        }
        case ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL:
            return progress->counter >= achievementCriteria->reach_skill_level.skillLevel;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT:
            return progress->counter >= 1;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT:
            return progress->counter >= achievementCriteria->complete_quest_count.totalQuestCount;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY:
            return progress->counter >= achievementCriteria->complete_daily_quest_daily.numberOfDays;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE:
            return progress->counter >= achievementCriteria->complete_quests_in_zone.questCount;
        case ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE:
        case ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE:
            return progress->counter >= achievementCriteria->healing_done.count;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST:
            return progress->counter >= achievementCriteria->complete_daily_quest.questCount;
        case ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING:
            return progress->counter >= achievementCriteria->fall_without_dying.fallHeight;
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST:
            return progress->counter >= 1;
        case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET:
        case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2:
            return progress->counter >= achievementCriteria->be_spell_target.spellCount;
        case ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL:
        case ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2:
            return progress->counter >= achievementCriteria->cast_spell.castCount;
        case ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE:
            return progress->counter >= achievementCriteria->bg_objective.completeCount;
        case ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA:
            return progress->counter >= achievementCriteria->honorable_kill_at_area.killCount;
        case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL:
            return progress->counter >= 1;
        case ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL:
        case ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL:
            return progress->counter >= achievementCriteria->honorable_kill.killCount;
        case ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM:
            return progress->counter >= achievementCriteria->own_item.itemCount;
        case ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA:
            return progress->counter >= achievementCriteria->win_rated_arena.count;
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_PERSONAL_RATING:
            return progress->counter >= achievementCriteria->highest_personal_rating.PersonalRating;
        case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL:
            return progress->counter >= (achievementCriteria->learn_skill_level.skillLevel * 75);
        case ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM:
            return progress->counter >= achievementCriteria->use_item.itemCount;
        case ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM:
            return progress->counter >= achievementCriteria->loot_item.itemCount;
        case ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA:
            return progress->counter >= 1;
        case ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT:
            return progress->counter >= achievementCriteria->buy_bank_slot.numberOfSlots;
        case ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION:
            return progress->counter >= achievementCriteria->gain_reputation.reputationAmount;
        case ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION:
            return progress->counter >= achievementCriteria->gain_exalted_reputation.numberOfExaltedFactions;
        case ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP:
            return progress->counter >= achievementCriteria->visit_barber.numberOfVisits;
        case ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM:
            return progress->counter >= achievementCriteria->equip_epic_item.count;
        case ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT:
        case ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT:
            return progress->counter >= achievementCriteria->roll_greed_on_loot.count;
        case ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS:
            return progress->counter >= achievementCriteria->hk_class.count;
        case ACHIEVEMENT_CRITERIA_TYPE_HK_RACE:
            return progress->counter >= achievementCriteria->hk_race.count;
        case ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE:
            return progress->counter >= achievementCriteria->do_emote.count;
        case ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM:
            return progress->counter >= achievementCriteria->equip_item.count;
        case ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD:
            return progress->counter >= achievementCriteria->quest_reward_money.goldInCopper;
        case ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY:
            return progress->counter >= achievementCriteria->loot_money.goldInCopper;
        case ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT:
            return progress->counter >= achievementCriteria->use_gameobject.useCount;
        case ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL:
            return progress->counter >= achievementCriteria->special_pvp_kill.killCount;
        case ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT:
            return progress->counter >= achievementCriteria->fish_in_gameobject.lootCount;
        case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS:
            return progress->counter >= achievementCriteria->learn_skillline_spell.spellCount;
        case ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL:
            return progress->counter >= achievementCriteria->win_duel.duelCount;
        case ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE:
            return progress->counter >= achievementCriteria->loot_type.lootTypeCount;
        case ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE:
            return progress->counter >= achievementCriteria->learn_skill_line.spellCount;
        case ACHIEVEMENT_CRITERIA_TYPE_EARN_ACHIEVEMENT_POINTS:
            return progress->counter >= 9000;
        case ACHIEVEMENT_CRITERIA_TYPE_USE_LFD_TO_GROUP_WITH_PLAYERS:
            return progress->counter >= achievementCriteria->use_lfg.dungeonsComplete;
        case ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS:
            return progress->counter >= achievementCriteria->get_killing_blow.killCount;
        case ACHIEVEMENT_CRITERIA_TYPE_REACH_GUILD_LEVEL:
            return progress->counter >= achievementCriteria->reach_guild_level.level;
        case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE_GUILD:
            return progress->counter >= achievementCriteria->kill_creature_type.count;
        case ACHIEVEMENT_CRITERIA_TYPE_CURRENCY:
            return progress->counter >= achievementCriteria->currencyGain.count;
        // handle all statistic-only criteria here
        case ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND:
        case ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP:
        case ACHIEVEMENT_CRITERIA_TYPE_DEATH:
        case ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON:
        case ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE:
        case ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER:
        case ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING:
        case ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_VENDORS:
        case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS:
        case ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS:
        case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER:
        case ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL:
        case ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL:
        case ACHIEVEMENT_CRITERIA_TYPE_GOLD_EARNED_BY_AUCTIONS:
        case ACHIEVEMENT_CRITERIA_TYPE_CREATE_AUCTION:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_BID:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_SOLD:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_GOLD_VALUE_OWNED:
        case ACHIEVEMENT_CRITERIA_TYPE_WON_AUCTIONS:
        case ACHIEVEMENT_CRITERIA_TYPE_GAIN_REVERED_REPUTATION:
        case ACHIEVEMENT_CRITERIA_TYPE_GAIN_HONORED_REPUTATION:
        case ACHIEVEMENT_CRITERIA_TYPE_KNOWN_FACTIONS:
        case ACHIEVEMENT_CRITERIA_TYPE_LOOT_EPIC_ITEM:
        case ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM:
        case ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED:
        case ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALTH:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER:
        case ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_ARMOR:
        case ACHIEVEMENT_CRITERIA_TYPE_QUEST_ABANDONED:
        case ACHIEVEMENT_CRITERIA_TYPE_FLIGHT_PATHS_TAKEN:
        case ACHIEVEMENT_CRITERIA_TYPE_ACCEPTED_SUMMONINGS:
        default:
            break;
    }
    return false;
}

void AchievementMgrBase::CompletedCriteriaFor(AchievementEntry const* achievement, Player* player)
{
    // counter can never complete
    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER)
        return;

    // already completed and stored
    if (HasAchieved(achievement->ID))
        return;

    if (IsCompletedAchievement(achievement, player))
    {
        if (_guild)
            CompletedAchievement(achievement, player);
        else
            CompletedAchievement(achievement);
    }
}

bool AchievementMgrBase::IsCompletedAchievement(AchievementEntry const* entry, Player* player)
{
    // counter can never complete
    if (entry->flags & ACHIEVEMENT_FLAG_COUNTER)
        return false;

    // for achievement with referenced achievement criteria get from referenced and counter from self
    uint32 achievmentForTestId = entry->refAchievement ? entry->refAchievement : entry->ID;
    uint32 achievmentForTestCount = entry->count;

    AchievementCriteriaEntryList const* cList = sAchievementMgr->GetAchievementCriteriaByAchievement(achievmentForTestId);
    if (!cList)
        return false;
    uint32 count = 0;

    // For SUMM achievements, we have to count the progress of each criteria of the achievement.
    // Oddly, the target count is NOT contained in the achievement, but in each individual criteria
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

        bool completed = IsCompletedCriteria(criteria, entry, player);

        // found an uncompleted criteria, but DONT return false yet - there might be a completed criteria with ACHIEVEMENT_CRITERIA_COMPLETE_FLAG_ALL
        if (completed)
            ++count;
        else
            completed_all = false;

        // completed as have req. count of completed criteria
        if (achievmentForTestCount > 0 && achievmentForTestCount <= count)
           return true;
    }

    // all criteria completed requirement
    if (completed_all && achievmentForTestCount == 0)
        return true;

    return false;
}

CriteriaProgress* AchievementMgrBase::GetCriteriaProgress(AchievementCriteriaEntry const* entry)
{
    CriteriaProgressMap::iterator iter = m_criteriaProgress.find(entry->ID);

    if (iter == m_criteriaProgress.end())
        return NULL;

    return &(iter->second);
}

void AchievementMgrBase::SetCriteriaProgress(AchievementCriteriaEntry const* entry, uint32 changeValue, ProgressType ptype)
{
    // Don't allow to cheat - doing timed achievements without timer active
    TimedAchievementMap::iterator timedIter = m_timedAchievements.find(entry->ID);
    if (entry->timeLimit && timedIter == m_timedAchievements.end())
        return;

    sLog->outDebug(LOG_FILTER_ACHIEVEMENTSYS, "AchievementMgr::SetCriteriaProgress(%u, %u) for (GUID:%u)", entry->ID, changeValue, _player->GetGUIDLow());

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
        timedCompleted = IsCompletedCriteria(entry, sAchievementStore.LookupEntry(entry->referredAchievement), _player);
        // Client expects this in packet
        timeElapsed = entry->timeLimit - (timedIter->second/IN_MILLISECONDS);

        // Remove the timer, we wont need it anymore
        if (timedCompleted)
            m_timedAchievements.erase(timedIter);
    }

    SendCriteriaUpdate(entry, progress, timeElapsed, timedCompleted, _player);
}

void AchievementMgrBase::RemoveCriteriaProgress(const AchievementCriteriaEntry *entry, Player* player)
{
    CriteriaProgressMap::iterator criteriaProgress = m_criteriaProgress.find(entry->ID);
    if (criteriaProgress == m_criteriaProgress.end())
        return;

    if(!_guild)
    {
        WorldPacket data(SMSG_CRITERIA_DELETED, 4);
        data << uint32(entry->ID);
        player->SendDirectMessage(&data);
    }
    else
    {
        WorldPacket data(SMSG_GUILD_CRITERIA_DELETED, 4 + 8);
        data << uint32(entry->ID);
        data << uint64(time(NULL));
        SendDirectMessageToAll(&data);
    }

    m_criteriaProgress.erase(criteriaProgress);
}

bool AchievementMgrBase::HasAchieved(uint32 achievementId) const
{
    return m_completedAchievements.find(achievementId) != m_completedAchievements.end();
}

bool AchievementMgrBase::CanUpdateCriteria(AchievementCriteriaEntry const* criteria, AchievementEntry const* achievement, Player* player, uint32 miscValue1 /*= 0*/, uint32 miscValue2 /*= 0*/, Unit* unit /*= NULL*/)
{
    if (DisableMgr::IsDisabledFor(DISABLE_TYPE_ACHIEVEMENT_CRITERIA, criteria->ID, NULL))
        return false;

    if (_guild && !(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return false;

    if (!_guild && (achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return false;

    if (achievement->mapID != -1 && player->GetMapId() != uint32(achievement->mapID))
        return false;

    if ((achievement->requiredFaction == ACHIEVEMENT_FACTION_HORDE    && player->GetTeam() != HORDE) ||
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

    for (uint32 i = 0; i < 3; ++i)
    {
        if(!criteria->moreRequirement[i])
            continue;

        uint32 value = criteria->moreRequirementValue[i];

        switch (criteria->moreRequirement[i])
        {
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_GUILD_REP:
            {
                if (uint32(player->GetReputationMgr().GetReputation(1168)) < value) // 1168 = Guild faction
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_CREATURE_TYPE:
            {
                if (miscValue1 != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_AURA:
            {
                if (!player->HasAura(value))
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_AURA_ON_TARGET:
            {
                if (!unit)
                    return false;

                if(!unit->HasAura(value))
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_RAID_DIFFICULTY:
            {
                if (uint32(player->GetRaidDifficulty()) != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_PLAYER_CLASS:
            {
                if (player->getClass() != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_PLAYER_RACE:
            {
                if (player->getRace() != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_TARGET_RACE:
            {
                if (!unit)
                    return false;

                if (unit->GetTypeId() != TYPEID_PLAYER)
                    return false;

                if (unit->ToPlayer()->getRace() != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_TARGET_CLASS:
            {
                if (!unit)
                    return false;

                if (unit->GetTypeId() != TYPEID_PLAYER)
                    return false;

                if (unit->ToPlayer()->getClass() != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_REQUIRES_GUILD_GROUP:
            {
                Group* group = player->GetGroup();
                if (!group)
                    return false;

                if (!group->IsGuildGroup(player->GetGuildId(),true, true))
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_CREATURE_ID:
            {
                if (!unit || unit->GetTypeId() != TYPEID_UNIT)
                    return false;

                if (unit->GetEntry() != value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_T_HEALTH_UNDER_PCT:
            {
                if (!unit)
                    return false;

                if (unit->GetHealthPct() > value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_ZONE_ID:
            {
                if (player->GetZoneId() != value)
                    return false;

                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_DRUNKEN_STATE:
            {
                if (player->GetDrunkValue() < value) // Not sure on this one
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_PERSONAL_RATING:
            {
                if (miscValue1 < value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_ITEM_LEVEL:
            {
                ItemTemplate const* proto = sObjectMgr->GetItemTemplate(miscValue1);
                if (!proto)
                    return false;

                if (proto->ItemLevel < value)
                    return false;
                break;
            }
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_ITEM_QUALITY_EQUIPPED:
            case ACHIEVEMENT_CRITERIA_MORE_REQ_TYPE_ITEM_QUALITY_LOOTED:
            {
                ItemTemplate const* proto = sObjectMgr->GetItemTemplate(miscValue1);
                if (!proto)
                    return false;

                if (proto->Quality < value)
                    return false;

                break;
            }
            default:
                break;
        }
    }

    // don't update already completed criteria
    if (IsCompletedCriteria(criteria, achievement, player))
        return false;

    return true;
}