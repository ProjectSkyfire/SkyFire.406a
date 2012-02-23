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

#ifndef GUILD_ACHIEV_MGR_H
#define GUILD_ACHIEV_MGR_H

#include <map>
#include <string>

#include "Common.h"
#include <ace/Singleton.h>
#include "DatabaseEnv.h"
#include "DBCEnums.h"
#include "DBCStores.h"
#include "Guild.h"
#include "AchievementMgrBase.h"

class Player;
class Unit;
class Guild;

class GuildAchievementMgr : public AchievementMgrBase
{
    public:
        GuildAchievementMgr(Guild* guild);
        ~GuildAchievementMgr();

        void Reset();
        void CheckAllAchievementCriteria();
        static void DeleteFromDB(uint32 guid_low);
        void LoadFromDB();
        void SaveToDB(SQLTransaction& trans);
        Guild* GetGuild() { return _guild; }
        void ResetAchievementCriteria(AchievementCriteriaTypes type, uint32 miscvalue1 = 0, uint32 miscvalue2 = 0, bool evenIfCriteriaComplete = false);
        void CompletedAchievement(AchievementEntry const* entry, Player* player);
        void SendAllAchievementData();

    private:
        void SendAchievementEarned(AchievementEntry const* achievement);
};

#endif
