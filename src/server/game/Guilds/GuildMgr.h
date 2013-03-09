/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2013 MaNGOS <http://getmangos.com/>
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

#ifndef _GUILDMGR_H
#define _GUILDMGR_H

#include "Guild.h"

struct GuildRewardsEntry
{
    uint32 item;
    uint32 price;
    uint32 achievement;
    uint32 standing;
};
typedef std::vector<GuildRewardsEntry> GuildRewardsVector;
class GuildMgr
{
    friend class ACE_Singleton<GuildMgr, ACE_Null_Mutex>;

private:
    GuildMgr();
    ~GuildMgr();

public:
    typedef UNORDERED_MAP<uint32, Guild*> GuildContainer;

    Guild* GetGuildByLeader(uint64 guid) const;
    Guild* GetGuildById(uint32 guildId) const;
    Guild* GetGuildByName(const std::string& guildName) const;
    std::string GetGuildNameById(uint32 guildId) const;
    GuildRewardsVector const& GetGuildRewards() { return mGuildRewards; }

    void LoadGuilds();
    void AddGuild(Guild* guild);
    void RemoveGuild(uint32 guildId);

    uint32 GenerateGuildId();
    void SetNextGuildId(uint32 Id) { NextGuildId = Id; }

    void LoadGuildRewards();
    void ResetTimes();
    //void LoadGuildMemberProfessions(std::vector<Guild*>& GuildVector, QueryResult& result);  // g.professions aren't finished yet
protected:
    uint32 NextGuildId;
    GuildContainer GuildStore;
    GuildRewardsVector  mGuildRewards;
};

#define sGuildMgr ACE_Singleton<GuildMgr, ACE_Null_Mutex>::instance()

#endif
