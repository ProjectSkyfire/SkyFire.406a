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

GuildAchievementMgr::GuildAchievementMgr(Guild* guild) : AchievementMgrBase(NULL, guild)
{
}

GuildAchievementMgr::~GuildAchievementMgr()
{
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
    DeleteFromDB(_guild->GetId());

    // re-fill data
    CheckAllAchievementCriteria();
}

void GuildAchievementMgr::DeleteFromDB(uint32 id)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    trans->PAppend("DELETE FROM guild_achievement WHERE guildid = %u", id);
    trans->PAppend("DELETE FROM guild_achievement_progress WHERE guildid = %u", id);
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
                ssdel << "DELETE FROM guild_achievement WHERE guildid = " << _guild->GetId() << " AND achievement IN (";
                ssins << "INSERT INTO guild_achievement (guildid, achievement, date) VALUES ";
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
            ssins << '(' << _guild->GetId() << ',' << iter->first << ',' << uint64(iter->second.date) << ')';

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
                    ssdel << "DELETE FROM guild_achievement_progress WHERE guildid = " << _guild->GetId() << " AND criteria IN (";
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
                    ssins << "INSERT INTO guild_achievement_progress (guildid, criteria, counter, date) VALUES ";
                    need_execute_ins = true;
                }
                /// next new/changed record prefix
                else
                    ssins << ',';

                // new/changed record data
                ssins << '(' << _guild->GetId() << ',' << iter->first << ',' << iter->second.counter << ',' << iter->second.date << ')';
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
    QueryResult achievementResult = CharacterDatabase.PQuery("SELECT achievement, date FROM guild_achievement WHERE guildid = %u", _guild->GetId());
    QueryResult criteriaResult = CharacterDatabase.PQuery("SELECT criteria, counter, date FROM guild_achievement_progress WHERE guildid = %u", _guild->GetId());
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

    sLog->outString("Guild %u earned achievement %u", _guild->GetId(), achievement->ID);

    WorldPacket data(SMSG_GUILD_ACHIEVEMENT_EARNED, 8+4+8);
    data << uint32(achievement->ID);
    data << uint64(MAKE_NEW_GUID(_guild->GetId(), 0, HIGHGUID_GUILD));
    data << uint32(secsToTimeBitFields(time(NULL)));
    SendDirectMessageToAll(&data);
}

void GuildAchievementMgr::CheckAllAchievementCriteria()
{
    // suppress sending packets
    for (uint32 i = 0; i < ACHIEVEMENT_CRITERIA_TYPE_TOTAL; ++i)
        UpdateAchievementCriteria(AchievementCriteriaTypes(i), NULL); // ToDO: Fix this
}

void GuildAchievementMgr::CompletedAchievement(AchievementEntry const* achievement, Player* player)
{
    if (!(achievement->flags & ACHIEVEMENT_FLAG_GUILD_ACHIEVEMENT))
        return;

    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER || HasAchieved(achievement->ID))
        return;

    SendAchievementEarned(achievement);
    CompletedAchievementData& ca =  m_completedAchievements[achievement->ID];
    ca.date = time(NULL);
    ca.changed = true;

    m_achievementPoints += achievement->points;

    UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT, player);
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
        data2 << uint64(iter->second.counter);

    time_t now = time(NULL);
    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data2 << uint32(now - iter->second.date);

    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data2 << uint32(secsToTimeBitFields(iter->second.date));

    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data2 << uint64(iter->second.counter);

    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data2 << uint32(now - iter->second.date);

    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data2 << uint32(iter->first);

    for (CriteriaProgressMap::const_iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        data2 << uint32(0); // Unk

    SendDirectMessageToAll(&data2);
}
