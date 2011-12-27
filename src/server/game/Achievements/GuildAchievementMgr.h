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
#include "AchievementMgr.h"

class Player;
class Unit;
class Guild;

class GuildAchievementMgr
{
    public:
        GuildAchievementMgr(Guild* guild);
        ~GuildAchievementMgr();
        
        void Reset();
        void CheckAllAchievementCriteria();
        void DeleteFromDB(uint32 guid_low);
        void SendDirectMessageToAll(WorldPacket* data);
        void LoadFromDB();
        void SaveToDB(SQLTransaction& trans);
        Guild* GetGuild() { return m_guild; }
        void ResetAchievementCriteria(AchievementCriteriaTypes type, uint32 miscvalue1 = 0, uint32 miscvalue2 = 0, bool evenIfCriteriaComplete = false);
        void UpdateAchievementCriteria(AchievementCriteriaTypes type, Player* player, uint32 miscValue1 = 0, uint32 miscValue2 = 0, Unit* unit = NULL);
        void UpdateTimedAchievements(uint32 timeDiff);
        void StartTimedAchievement(AchievementCriteriaTimedTypes type, uint32 entry, uint32 timeLost = 0); // ToDo
        void RemoveTimedAchievement(AchievementCriteriaTimedTypes type, uint32 entry);   // used for quest and scripted timed achievements ToDo
        void CompletedAchievement(AchievementEntry const* entry);
        void SendAllAchievementData();
        bool HasAchieved(uint32 achievementId);
        
        uint32 GetAchievementPoints() const { return m_achievementPoints; }
    
    private:
        void SendAchievementEarned(AchievementEntry const* achievement);
        void SendCriteriaUpdate(AchievementCriteriaEntry const* entry, CriteriaProgress const* progress, uint32 timeElapsed, bool timedCompleted, Player* completer);
        bool IsCompletedCriteria(AchievementCriteriaEntry const* achievementCriteria, AchievementEntry const* achievement);
        void CompletedCriteriaFor(AchievementEntry const* achievement);
        bool IsCompletedAchievement(AchievementEntry const* entry);
        CriteriaProgress* GetCriteriaProgress(AchievementCriteriaEntry const* entry);
        void SetCriteriaProgress(AchievementCriteriaEntry const* entry, uint32 changeValue, Player* player, ProgressType ptype = PROGRESS_SET);
        void RemoveCriteriaProgress(AchievementCriteriaEntry const* entry);
        bool CanUpdateCriteria(AchievementCriteriaEntry const* criteria, AchievementEntry const* achievement, Player* player);
        Guild* m_guild;
        uint32 m_achievementPoints;
        CriteriaProgressMap m_criteriaProgress;
        CompletedAchievementMap m_completedAchievements;
        typedef std::map<uint32, uint32> TimedAchievementMap;
        TimedAchievementMap m_timedAchievements;      // Criteria id/time left in MS
};

#endif
