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
