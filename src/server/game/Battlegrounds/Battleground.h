/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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

#ifndef __BATTLEGROUND_H
#define __BATTLEGROUND_H

#include "Common.h"
#include "SharedDefines.h"
#include "DBCEnums.h"

class Creature;
class GameObject;
class Group;
class Player;
class WorldPacket;
class BattlegroundMap;

struct PvPDifficultyEntry;
struct WorldSafeLocsEntry;

enum BattlegroundSounds
{
    SOUND_HORDE_WINS                = 8454,
    SOUND_ALLIANCE_WINS             = 8455,
    SOUND_BG_START                  = 3439,
    SOUND_BG_START_L70ETC           = 11803,
};

enum BattlegroundQuests
{
    SPELL_WS_QUEST_REWARD           = 43483,
    SPELL_AB_QUEST_REWARD           = 43484,
    SPELL_AV_QUEST_REWARD           = 43475,
    SPELL_AV_QUEST_KILLED_BOSS      = 23658,
    SPELL_EY_QUEST_REWARD           = 43477,
    SPELL_SA_QUEST_REWARD           = 61213,
    SPELL_AB_QUEST_REWARD_4_BASES   = 24061,
    SPELL_AB_QUEST_REWARD_5_BASES   = 24064
};

enum BattlegroundMarks
{
    SPELL_WS_MARK_LOSER             = 24950,
    SPELL_WS_MARK_WINNER            = 24951,
    SPELL_AB_MARK_LOSER             = 24952,
    SPELL_AB_MARK_WINNER            = 24953,
    SPELL_AV_MARK_LOSER             = 24954,
    SPELL_AV_MARK_WINNER            = 24955,
    SPELL_SA_MARK_WINNER            = 61160,
    SPELL_SA_MARK_LOSER             = 61159,
    ITEM_AV_MARK_OF_HONOR           = 20560,
    ITEM_WS_MARK_OF_HONOR           = 20558,
    ITEM_AB_MARK_OF_HONOR           = 20559,
    ITEM_EY_MARK_OF_HONOR           = 29024,
    ITEM_SA_MARK_OF_HONOR           = 42425
};

enum BattlegroundMarksCount
{
    ITEM_WINNER_COUNT               = 3,
    ITEM_LOSER_COUNT                = 1
};

enum BattlegroundCreatures
{
    BG_CREATURE_ENTRY_A_SPIRITGUIDE      = 13116,           // alliance
    BG_CREATURE_ENTRY_H_SPIRITGUIDE      = 13117,           // horde
};

enum BattlegroundSpells
{
    SPELL_WAITING_FOR_RESURRECT     = 2584,                 // Waiting to Resurrect
    SPELL_SPIRIT_HEAL_CHANNEL       = 22011,                // Spirit Heal Channel
    SPELL_SPIRIT_HEAL               = 22012,                // Spirit Heal
    SPELL_RESURRECTION_VISUAL       = 24171,                // Resurrection Impact Visual
    SPELL_ARENA_PREPARATION         = 32727,                // use this one, 32728 not correct
    SPELL_ALLIANCE_GOLD_FLAG        = 32724,
    SPELL_ALLIANCE_GREEN_FLAG       = 32725,
    SPELL_HORDE_GOLD_FLAG           = 35774,
    SPELL_HORDE_GREEN_FLAG          = 35775,
    SPELL_PREPARATION               = 44521,                // Preparation
    SPELL_SPIRIT_HEAL_MANA          = 44535,                // Spirit Heal
    SPELL_RECENTLY_DROPPED_FLAG     = 42792,                // Recently Dropped Flag
    SPELL_AURA_PLAYER_INACTIVE      = 43681,                // Inactive
    SPELL_HONORABLE_DEFENDER_25Y    = 68652,                // +50% honor when standing at a capture point that you control, 25yards radius (added in 3.2)
    SPELL_HONORABLE_DEFENDER_60Y    = 66157,                // +50% honor when standing at a capture point that you control, 60yards radius (added in 3.2), probably for 40+ player battlegrounds
    SPELL_THE_LAST_STANDING         = 26549,                // Arena achievement related
};

enum BattlegroundTimeIntervals
{
    RESURRECTION_INTERVAL           = 30000,                // ms
    //REMIND_INTERVAL                 = 10000,                // ms
    INVITATION_REMIND_TIME          = 20000,                // ms
    INVITE_ACCEPT_WAIT_TIME         = 40000,                // ms
    TIME_TO_AUTOREMOVE              = 120000,               // ms
    MAX_OFFLINE_TIME                = 300,                  // secs
    RESPAWN_ONE_DAY                 = 86400,                // secs
    RESPAWN_IMMEDIATELY             = 0,                    // secs
    BUFF_RESPAWN_TIME               = 180,                  // secs
};

enum BattlegroundStartTimeIntervals
{
    BG_START_DELAY_2M               = 120000,               // ms (2 minutes)
    BG_START_DELAY_1M               = 60000,                // ms (1 minute)
    BG_START_DELAY_30S              = 30000,                // ms (30 seconds)
    BG_START_DELAY_15S              = 15000,                // ms (15 seconds) Used only in arena
    BG_START_DELAY_NONE             = 0,                    // ms
};

enum BattlegroundBuffObjects
{
    BG_OBJECTID_SPEEDBUFF_ENTRY     = 179871,
    BG_OBJECTID_REGENBUFF_ENTRY     = 179904,
    BG_OBJECTID_BERSERKERBUFF_ENTRY = 179905
};

enum BattlegroundRandomRewards
{
    BG_REWARD_WINNER_HONOR_FIRST    = 150,
    BG_REWARD_WINNER_ARENA_FIRST    = 25,
    BG_REWARD_WINNER_HONOR_LAST     = 100,
    BG_REWARD_WINNER_ARENA_LAST     = 0,
    BG_REWARD_LOSER_HONOR_FIRST     = 40,
    BG_REWARD_LOSER_HONOR_LAST      = 30
};

const uint32 Buff_Entries[3] = { BG_OBJECTID_SPEEDBUFF_ENTRY, BG_OBJECTID_REGENBUFF_ENTRY, BG_OBJECTID_BERSERKERBUFF_ENTRY };

enum BattlegroundStatus
{
    STATUS_NONE         = 0,                                // first status, should mean bg is not instance
    STATUS_WAIT_QUEUE   = 1,                                // means bg is empty and waiting for queue
    STATUS_WAIT_JOIN    = 2,                                // this means, that BG has already started and it is waiting for more players
    STATUS_IN_PROGRESS  = 3,                                // means bg is running
    STATUS_WAIT_LEAVE   = 4                                 // means some faction has won BG and it is ending
};

struct BattlegroundPlayer
{
    time_t  OfflineRemoveTime;                              // for tracking and removing offline players from queue after 5 minutes
    uint32  Team;                                           // Player's team
};

struct BattlegroundObjectInfo
{
    BattlegroundObjectInfo() : object(NULL), timer(0), spellid(0) {}

    GameObject  *object;
    int32       timer;
    uint32      spellid;
};

// handle the queue types and bg types separately to enable joining queue for different sized arenas at the same time
enum BattlegroundQueueTypeId
{
    BATTLEGROUND_QUEUE_NONE     = 0,
    BATTLEGROUND_QUEUE_AV       = 1,
    BATTLEGROUND_QUEUE_WS       = 2,
    BATTLEGROUND_QUEUE_AB       = 3,
    BATTLEGROUND_QUEUE_EY       = 4,
    BATTLEGROUND_QUEUE_SA       = 5,
    BATTLEGROUND_QUEUE_IC       = 6,
    BATTLEGROUND_QUEUE_TP       = 7,
    BATTLEGROUND_QUEUE_BG       = 8,
    BATTLEGROUND_QUEUE_RB       = 9,
    BATTLEGROUND_QUEUE_2v2      = 10,
    BATTLEGROUND_QUEUE_3v3      = 11,
    BATTLEGROUND_QUEUE_5v5      = 12,
    MAX_BATTLEGROUND_QUEUE_TYPES
};

enum ScoreType
{
    SCORE_KILLING_BLOWS         = 1,
    SCORE_DEATHS                = 2,
    SCORE_HONORABLE_KILLS       = 3,
    SCORE_BONUS_HONOR           = 4,
    //EY, but in MSG_PVP_LOG_DATA opcode!
    SCORE_DAMAGE_DONE           = 5,
    SCORE_HEALING_DONE          = 6,
    //WS
    SCORE_FLAG_CAPTURES         = 7,
    SCORE_FLAG_RETURNS          = 8,
    //AB and IC
    SCORE_BASES_ASSAULTED       = 9,
    SCORE_BASES_DEFENDED        = 10,
    //AV
    SCORE_GRAVEYARDS_ASSAULTED  = 11,
    SCORE_GRAVEYARDS_DEFENDED   = 12,
    SCORE_TOWERS_ASSAULTED      = 13,
    SCORE_TOWERS_DEFENDED       = 14,
    SCORE_MINES_CAPTURED        = 15,
    SCORE_LEADERS_KILLED        = 16,
    SCORE_SECONDARY_OBJECTIVES  = 17,
    //SOTA
    SCORE_DESTROYED_DEMOLISHER  = 18,
    SCORE_DESTROYED_WALL        = 19,
};

enum ArenaType
{
    ARENA_TYPE_2v2          = 2,
    ARENA_TYPE_3v3          = 3,
    ARENA_TYPE_5v5          = 5
};

enum BattlegroundType
{
    TYPE_BATTLEGROUND     = 3,
    TYPE_ARENA            = 4
};

enum BattlegroundWinner
{
    WINNER_HORDE            = 0,
    WINNER_ALLIANCE         = 1,
    WINNER_NONE             = 2
};

enum BattlegroundTeamId
{
    BG_TEAM_ALLIANCE        = 0,
    BG_TEAM_HORDE           = 1
};
#define BG_TEAMS_COUNT  2

enum BattlegroundStartingEvents
{
    BG_STARTING_EVENT_NONE  = 0x00,
    BG_STARTING_EVENT_1     = 0x01,
    BG_STARTING_EVENT_2     = 0x02,
    BG_STARTING_EVENT_3     = 0x04,
    BG_STARTING_EVENT_4     = 0x08
};

enum BattlegroundStartingEventsIds
{
    BG_STARTING_EVENT_FIRST     = 0,
    BG_STARTING_EVENT_SECOND    = 1,
    BG_STARTING_EVENT_THIRD     = 2,
    BG_STARTING_EVENT_FOURTH    = 3
};
#define BG_STARTING_EVENT_COUNT 4

enum GroupJoinBattlegroundResult
{
    // positive values are indexes in BattlemasterList.dbc
    ERR_GROUP_JOIN_BATTLEGROUND_FAIL        = 0,            // Your group has joined a battleground queue, but you are not eligible (showed for non existing BattlemasterList.dbc indexes)
    ERR_BATTLEGROUND_NONE                   = -1,           // not show anything
    ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS   = -2,           // You cannot join the battleground yet because you or one of your party members is flagged as a Deserter.
    ERR_ARENA_TEAM_PARTY_SIZE               = -3,           // Incorrect party size for this arena.
    ERR_BATTLEGROUND_TOO_MANY_QUEUES        = -4,           // You can only be queued for 2 battles at once
    ERR_BATTLEGROUND_CANNOT_QUEUE_FOR_RATED = -5,           // You cannot queue for a rated match while queued for other battles
    ERR_BATTLEDGROUND_QUEUED_FOR_RATED      = -6,           // You cannot queue for another battle while queued for a rated arena match
    ERR_BATTLEGROUND_TEAM_LEFT_QUEUE        = -7,           // Your team has left the arena queue
    ERR_BATTLEGROUND_NOT_IN_BATTLEGROUND    = -8,           // You can't do that in a battleground.
    ERR_BATTLEGROUND_JOIN_XP_GAIN           = -9,           // wtf, doesn't exist in client...
    ERR_BATTLEGROUND_JOIN_RANGE_INDEX       = -10,          // Cannot join the queue unless all members of your party are in the same battleground level range.
    ERR_BATTLEGROUND_JOIN_TIMED_OUT         = -11,          // %s was unavailable to join the queue. (uint64 guid exist in client cache)
    ERR_BATTLEGROUND_JOIN_FAILED            = -12,          // Join as a group failed (uint64 guid doesn't exist in client cache)
    ERR_BATTLEGROUND_TEAM_LEFT_QUEUE2       = -13,
    ERR_LFG_CANT_USE_BATTLEGROUND           = -14,          // You cannot queue for a battleground or arena while using the dungeon system.
    ERR_IN_RANDOM_BG                        = -15,          // Can't do that while in a Random Battleground queue.
    ERR_IN_NON_RANDOM_BG                    = -16,          // Can't queue for Random Battleground while in another Battleground queue.
    ERR_BG_DEVELOPER_ONLY                   = -17,
    ERR_BATTLEGROUND_INVITATION_DECLINED    = -18,
    ERR_MEETING_STONE_NOT_FOUND             = -19,
    ERR_WARGAME_REQUEST_FAILURE             = -20,
    ERR_BATTLEFIELD_TEAM_PARTY_SIZE         = -22,
};
class BattlegroundScore
{
    public:
        BattlegroundScore() : KillingBlows(0), Deaths(0), HonorableKills(0),
            BonusHonor(0), DamageDone(0), HealingDone(0)
        {}
        virtual ~BattlegroundScore() {}                     //virtual destructor is used when deleting score from scores map

        uint32 KillingBlows;
        uint32 Deaths;
        uint32 HonorableKills;
        uint32 BonusHonor;
        uint32 DamageDone;
        uint32 HealingDone;
};

enum BGHonorMode
{
    BG_NORMAL = 0,
    BG_HOLIDAY,
    BG_HONOR_MODE_NUM
};

#define BG_AWARD_ARENA_POINTS_MIN_LEVEL 71
#define ARENA_TIMELIMIT_POINTS_LOSS    -16

/*
This class is used to:
1. Add player to battleground
2. Remove player from battleground
3. some certain cases, same for all battlegrounds
4. It has properties same for all battlegrounds
*/
class Battleground
{
    public:
        Battleground();
        virtual ~Battleground();

        void Update(uint32 diff);

        virtual bool SetupBattleground()                    // must be implemented in BG subclass
        {
            return true;
        }
        virtual void Reset();                               // resets all common properties for battlegrounds, must be implemented and called in BG subclass
        virtual void StartingEventCloseDoors() {}
        virtual void StartingEventOpenDoors() {}
        virtual void ResetBGSubclass() {}                   // must be implemented in BG subclass

        virtual void DestroyGate(Player* /*player*/, GameObject* /*go*/) {}

        /* achievement req. */
        virtual bool IsAllNodesConrolledByTeam(uint32 /*team*/) const { return false; }
        bool IsTeamScoreInRange(uint32 team, uint32 minScore, uint32 maxScore) const;
        void StartTimedAchievement(AchievementCriteriaTimedTypes type, uint32 entry);

        /* Battleground */
        // Get methods:
        char const* GetName() const         { return _Name; }
        BattlegroundTypeId GetTypeID(bool GetRandom = false) const { return GetRandom ? _RandomTypeID : _TypeID; }
        BattlegroundBracketId GetBracketId() const { return _BracketId; }
        uint32 GetInstanceID() const        { return _InstanceID; }
        BattlegroundStatus GetStatus() const { return _Status; }
        uint32 GetClientInstanceID() const  { return _ClientInstanceID; }
        uint32 GetStartTime() const         { return _StartTime; }
        uint32 GetEndTime() const           { return _EndTime; }
        uint32 GetLastResurrectTime() const { return _LastResurrectTime; }
        uint32 GetMaxPlayers() const        { return _MaxPlayers; }
        uint32 GetMinPlayers() const        { return _MinPlayers; }

        uint32 GetMinLevel() const          { return _LevelMin; }
        uint32 GetMaxLevel() const          { return _LevelMax; }

        uint32 GetMaxPlayersPerTeam() const { return _MaxPlayersPerTeam; }
        uint32 GetMinPlayersPerTeam() const { return _MinPlayersPerTeam; }

        int32 GetStartDelayTime() const     { return m_StartDelayTime; }
        uint8 GetArenaType() const          { return _ArenaType; }
        uint8 GetWinner() const             { return _Winner; }
        uint32 GetScriptId() const          { return ScriptId; }
        uint32 GetBonusHonorFromKill(uint32 kills) const;
        bool IsRandom() const { return _IsRandom; }

        // Set methods:
        void SetName(char const* Name)      { _Name = Name; }
        void SetTypeID(BattlegroundTypeId TypeID) { _TypeID = TypeID; }
        void SetRandomTypeID(BattlegroundTypeId TypeID) { _RandomTypeID = TypeID; }
        //here we can count minlevel and maxlevel for players
        void SetBracket(PvPDifficultyEntry const* bracketEntry);
        void SetInstanceID(uint32 InstanceID) { _InstanceID = InstanceID; }
        void SetStatus(BattlegroundStatus Status) { _Status = Status; }
        void SetClientInstanceID(uint32 InstanceID) { _ClientInstanceID = InstanceID; }
        void SetStartTime(uint32 Time)      { _StartTime = Time; }
        void SetEndTime(uint32 Time)        { _EndTime = Time; }
        void SetLastResurrectTime(uint32 Time) { _LastResurrectTime = Time; }
        void SetMaxPlayers(uint32 MaxPlayers) { _MaxPlayers = MaxPlayers; }
        void SetMinPlayers(uint32 MinPlayers) { _MinPlayers = MinPlayers; }
        void SetLevelRange(uint32 min, uint32 max) { _LevelMin = min; _LevelMax = max; }
        void SetRated(bool state)           { _IsRated = state; }
        void SetArenaType(uint8 type)       { _ArenaType = type; }
        void SetArenaorBGType(bool _isArena) { _IsArena = _isArena; }
        void SetWinner(uint8 winner)        { _Winner = winner; }
        void SetScriptId(uint32 scriptId)   { ScriptId = scriptId; }

        void ModifyStartDelayTime(int diff) { m_StartDelayTime -= diff; }
        void SetStartDelayTime(int Time)    { m_StartDelayTime = Time; }

        void SetMaxPlayersPerTeam(uint32 MaxPlayers) { _MaxPlayersPerTeam = MaxPlayers; }
        void SetMinPlayersPerTeam(uint32 MinPlayers) { _MinPlayersPerTeam = MinPlayers; }

        void AddToBGFreeSlotQueue();                        //this queue will be useful when more battlegrounds instances will be available
        void RemoveFromBGFreeSlotQueue();                   //this method could delete whole BG instance, if another free is available

        void DecreaseInvitedCount(uint32 team)      { (team == ALLIANCE) ? --_InvitedAlliance : --_InvitedHorde; }
        void IncreaseInvitedCount(uint32 team)      { (team == ALLIANCE) ? ++_InvitedAlliance : ++_InvitedHorde; }

        void SetRandom(bool isRandom) { _IsRandom = isRandom; }
        uint32 GetInvitedCount(uint32 team) const   { return (team == ALLIANCE) ? _InvitedAlliance : _InvitedHorde; }
        bool HasFreeSlots() const;
        uint32 GetFreeSlotsForTeam(uint32 Team) const;

        bool isArena() const        { return _IsArena; }
        bool isBattleground() const { return !_IsArena; }
        bool isRated() const        { return _IsRated; }

        typedef std::map<uint64, BattlegroundPlayer> BattlegroundPlayerMap;
        BattlegroundPlayerMap const& GetPlayers() const { return _Players; }
        uint32 GetPlayersSize() const { return _Players.size(); }

        typedef std::map<uint64, BattlegroundScore*> BattlegroundScoreMap;
        BattlegroundScoreMap::const_iterator GetPlayerScoresBegin() const { return PlayerScores.begin(); }
        BattlegroundScoreMap::const_iterator GetPlayerScoresEnd() const { return PlayerScores.end(); }
        uint32 GetPlayerScoresSize() const { return PlayerScores.size(); }

        uint32 GetReviveQueueSize() const { return _ReviveQueue.size(); }

        void AddPlayerToResurrectQueue(uint64 npc_guid, uint64 player_guid);
        void RemovePlayerFromResurrectQueue(uint64 player_guid);

        void StartBattleground();

        GameObject* GetBGObject(uint32 type);
        Creature* GetBGCreature(uint32 type);

        // Location
        void SetMapId(uint32 MapID) { _MapId = MapID; }
        uint32 GetMapId() const { return _MapId; }

        // Map pointers
        void SetBgMap(BattlegroundMap* map) { _Map = map; }
        BattlegroundMap* GetBgMap() const { ASSERT(_Map); return _Map; }
        BattlegroundMap* FindBgMap() const { return _Map; }

        void SetTeamStartLoc(uint32 TeamID, float X, float Y, float Z, float O);
        void GetTeamStartLoc(uint32 TeamID, float &X, float &Y, float &Z, float &O) const
        {
            BattlegroundTeamId idx = GetTeamIndexByTeamId(TeamID);
            X = _TeamStartLocX[idx];
            Y = _TeamStartLocY[idx];
            Z = _TeamStartLocZ[idx];
            O = _TeamStartLocO[idx];
        }

        // Packet Transfer
        // method that should fill worldpacket with actual world states (not yet implemented for all battlegrounds!)
        virtual void FillInitialWorldStates(WorldPacket& /*data*/) {}
        void SendPacketToTeam(uint32 TeamID, WorldPacket* packet, Player* sender = NULL, bool self = true);
        void SendPacketToAll(WorldPacket* packet);
        void YellToAll(Creature* creature, const char* text, uint32 language);

        template<class Do>
        void BroadcastWorker(Do& _do);

        void PlaySoundToTeam(uint32 SoundID, uint32 TeamID);
        void PlaySoundToAll(uint32 SoundID);
        void CastSpellOnTeam(uint32 SpellID, uint32 TeamID);
        void RemoveAuraOnTeam(uint32 SpellID, uint32 TeamID);
        void RewardHonorToTeam(uint32 Honor, uint32 TeamID);
        void RewardReputationToTeam(uint32 faction_id, uint32 Reputation, uint32 TeamID);
        void UpdateWorldState(uint32 Field, uint32 Value);
        void UpdateWorldStateForPlayer(uint32 Field, uint32 Value, Player* Source);
        void EndBattleground(uint32 winner);
        void BlockMovement(Player* player);

        void SendWarningToAll(int32 entry, ...);
        void SendMessageToAll(int32 entry, ChatMsg type, Player const* source = NULL);
        void PSendMessageToAll(int32 entry, ChatMsg type, Player const* source, ...);

        // specialized version with 2 string id args
        void SendMessage2ToAll(int32 entry, ChatMsg type, Player const* source, int32 strId1 = 0, int32 strId2 = 0);

        // Raid Group
        Group* GetBgRaid(uint32 TeamID) const { return TeamID == ALLIANCE ? _BgRaids[BG_TEAM_ALLIANCE] : _BgRaids[BG_TEAM_HORDE]; }
        void SetBgRaid(uint32 TeamID, Group* bg_raid);

        virtual void UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor = true);

        static BattlegroundTeamId GetTeamIndexByTeamId(uint32 Team) { return Team == ALLIANCE ? BG_TEAM_ALLIANCE : BG_TEAM_HORDE; }
        uint32 GetPlayersCountByTeam(uint32 Team) const { return _PlayersCount[GetTeamIndexByTeamId(Team)]; }
        uint32 GetAlivePlayersCountByTeam(uint32 Team) const;   // used in arenas to correctly handle death in spirit of redemption / last stand etc. (killer = killed) cases
        void UpdatePlayersCountByTeam(uint32 Team, bool remove)
        {
            if (remove)
                --_PlayersCount[GetTeamIndexByTeamId(Team)];
            else
                ++_PlayersCount[GetTeamIndexByTeamId(Team)];
        }

        // used for rated arena battles
        void SetArenaTeamIdForTeam(uint32 Team, uint32 ArenaTeamId) { _ArenaTeamIds[GetTeamIndexByTeamId(Team)] = ArenaTeamId; }
        uint32 GetArenaTeamIdForTeam(uint32 Team) const             { return _ArenaTeamIds[GetTeamIndexByTeamId(Team)]; }
        uint32 GetArenaTeamIdByIndex(uint32 index) const { return _ArenaTeamIds[index]; }
        void SetArenaTeamRatingChangeForTeam(uint32 Team, int32 RatingChange) { _ArenaTeamRatingChanges[GetTeamIndexByTeamId(Team)] = RatingChange; }
        int32 GetArenaTeamRatingChangeForTeam(uint32 Team) const    { return _ArenaTeamRatingChanges[GetTeamIndexByTeamId(Team)]; }
        int32 GetArenaTeamRatingChangeByIndex(uint32 index) const   { return _ArenaTeamRatingChanges[index]; }
        void SetArenaMatchmakerRating(uint32 Team, uint32 MMR){ m_ArenaTeamMMR[GetTeamIndexByTeamId(Team)] = MMR; }
        uint32 GetArenaMatchmakerRating(uint32 Team) const          { return m_ArenaTeamMMR[GetTeamIndexByTeamId(Team)]; }
        uint32 GetArenaMatchmakerRatingByIndex(uint32 index) const  { return m_ArenaTeamMMR[index]; }
        void CheckArenaAfterTimerConditions();
        void CheckArenaWinConditions();
        void UpdateArenaWorldState();
        void ScheduleArenaEnd(uint32 timer);

        // Triggers handle
        // must be implemented in BG subclass
        virtual void HandleAreaTrigger(Player* /*Source*/, uint32 /*Trigger*/) {}
        // must be implemented in BG subclass if need AND call base class generic code
        virtual void HandleKillPlayer(Player* player, Player* killer);
        virtual void HandleKillUnit(Creature* /*unit*/, Player* /*killer*/);

        // Battleground events
        virtual void EventPlayerDroppedFlag(Player* /*player*/) {}
        virtual void EventPlayerClickedOnFlag(Player* /*player*/, GameObject* /*target_obj*/) {}
        void EventPlayerLoggedIn(Player* player);
        void EventPlayerLoggedOut(Player* player);
        virtual void EventPlayerDamagedGO(Player* /*player*/, GameObject* /*go*/, uint32 /*eventType*/) {}
        virtual void EventPlayerUsedGO(Player* /*player*/, GameObject* /*go*/){}

        // this function can be used by spell to interact with the BG map
        virtual void DoAction(uint32 /*action*/, uint64 /*var*/) {}

        virtual void HandlePlayerResurrect(Player* /*player*/) {}

        // Death related
        virtual WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);

        virtual void AddPlayer(Player* player);                // must be implemented in BG subclass

        void AddOrSetPlayerToCorrectBgGroup(Player* player, uint32 team);

        virtual void RemovePlayerAtLeave(uint64 guid, bool Transport, bool SendPacket);
                                                            // can be extended in in BG subclass

        void HandleTriggerBuff(uint64 go_guid);
        void SetHoliday(bool is_holiday);

        // TODO: make this protected:
        typedef std::vector<uint64> BGObjects;
        typedef std::vector<uint64> BGCreatures;
        BGObjects BgObjects;
        BGCreatures BgCreatures;
        void SpawnBGObject(uint32 type, uint32 respawntime);
        bool AddObject(uint32 type, uint32 entry, float x, float y, float z, float o, float rotation0, float rotation1, float rotation2, float rotation3, uint32 respawnTime = 0);
        Creature* AddCreature(uint32 entry, uint32 type, uint32 teamval, float x, float y, float z, float o, uint32 respawntime = 0);
        bool DelCreature(uint32 type);
        bool DelObject(uint32 type);
        bool AddSpiritGuide(uint32 type, float x, float y, float z, float o, uint32 team);
        int32 GetObjectType(uint64 guid);

        void DoorOpen(uint32 type);
        void DoorClose(uint32 type);
        //to be removed
        const char* GetSkyFireString(int32 entry);

        virtual bool HandlePlayerUnderMap(Player* /*player*/) { return false; }

        // since arenas can be AvA or Hvh, we have to get the "temporary" team of a player
        uint32 GetPlayerTeam(uint64 guid) const;
        uint32 GetOtherTeam(uint32 teamId) const;
        bool IsPlayerInBattleground(uint64 guid) const;

        bool ToBeDeleted() const { return _SetDeleteThis; }
        void SetDeleteThis() { _SetDeleteThis = true; }

        // virtual score-array - get's used in bg-subclasses
        int32 _TeamScores[BG_TEAMS_COUNT];

        void RewardXPAtKill(Player* killer, Player* victim);
        bool CanAwardArenaPoints() const { return _LevelMin >= BG_AWARD_ARENA_POINTS_MIN_LEVEL; }

        // Arena team ids by team
        uint32 _ArenaTeamIds[BG_TEAMS_COUNT];

        int32 _ArenaTeamRatingChanges[BG_TEAMS_COUNT];
        uint32 m_ArenaTeamMMR[BG_TEAMS_COUNT];
    protected:
        // this method is called, when BG cannot spawn its own spirit guide, or something is wrong, It correctly ends Battleground
        void EndNow();
        void PlayerAddedToBGCheckIfBGIsRunning(Player* player);

        Player* _GetPlayer(uint64 guid, bool offlineRemove, const char* context) const;
        Player* _GetPlayer(BattlegroundPlayerMap::iterator itr, const char* context);
        Player* _GetPlayer(BattlegroundPlayerMap::const_iterator itr, const char* context) const;
        Player* _GetPlayerForTeam(uint32 teamId, BattlegroundPlayerMap::const_iterator itr, const char* context) const;

        void _ProcessOfflineQueue();
        void _ProcessRessurect(uint32 diff);
        void _ProcessProgress(uint32 diff);
        void _ProcessLeave(uint32 diff);
        void _ProcessJoin(uint32 diff);

        // Scorekeeping
        BattlegroundScoreMap PlayerScores;                // Player scores
        // must be implemented in BG subclass
        virtual void RemovePlayer(Player* /*player*/, uint64 /*guid*/, uint32 /*team*/) {}

        // Player lists, those need to be accessible by inherited classes
        BattlegroundPlayerMap  _Players;
        // Spirit Guide guid + Player list GUIDS
        std::map<uint64, std::vector<uint64> >  _ReviveQueue;

        // these are important variables used for starting messages
        uint8 _Events;
        BattlegroundStartTimeIntervals  StartDelayTimes[BG_STARTING_EVENT_COUNT];
        // this must be filled in constructors!
        uint32 StartMessageIds[BG_STARTING_EVENT_COUNT];

        bool   _BuffChange;
        bool   _IsRandom;

        BGHonorMode _HonorMode;
    private:
        // Battleground
        BattlegroundTypeId _TypeID;
        BattlegroundTypeId _RandomTypeID;
        uint32 _InstanceID;                                // Battleground Instance's GUID!
        BattlegroundStatus _Status;
        uint32 _ClientInstanceID;                          // the instance-id which is sent to the client and without any other internal use
        uint32 _StartTime;
        uint32 _ResetStatTimer;
        int32 _EndTime;                                    // it is set to 120000 when bg is ending and it decreases itself
        uint32 _LastResurrectTime;
        BattlegroundBracketId _BracketId;
        uint8  _ArenaType;                                 // 2=2v2, 3=3v3, 5=5v5
        bool   _InBGFreeSlotQueue;                         // used to make sure that BG is only once inserted into the BattlegroundMgr.BGFreeSlotQueue[bgTypeId] deque
        bool   _SetDeleteThis;                             // used for safe deletion of the bg after end / all players leave
        bool   _IsArena;
        uint8  _Winner;                                    // 0=alliance, 1=horde, 2=none
        int32  m_StartDelayTime;
        bool   _IsRated;                                   // is this battle rated?
        bool   _PrematureCountDown;
        uint32 _PrematureCountDownTimer;
        uint32 _arenaEndTimer;                             // Time after death of the remaining mamber of a team before arena ends
        char const* _Name;

        /* Pre- and post-update hooks */

        /**
         * @brief Pre-update hook.
         *
         * Will be called before battleground update is started. Depending on
         * the result of this call actual update body may be skipped.
         *
         * @param diff a time difference between two worldserver update loops in
         * milliseconds.
         *
         * @return @c true if update must be performed, @c false otherwise.
         *
         * @see Update(), PostUpdateImpl().
         */
        virtual bool PreUpdateImpl(uint32 /* diff */) { return true; };

        /**
         * @brief Post-update hook.
         *
         * Will be called after battleground update has passed. May be used to
         * implement custom update effects in subclasses.
         *
         * @param diff a time difference between two worldserver update loops in
         * milliseconds.
         *
         * @see Update(), PreUpdateImpl().
         */
        virtual void PostUpdateImpl(uint32 /* diff */) { };

        // Player lists
        std::vector<uint64> _ResurrectQueue;               // Player GUID
        std::deque<uint64> _OfflineQueue;                  // Player GUID

        // Invited counters are useful for player invitation to BG - do not allow, if BG is started to one faction to have 2 more players than another faction
        // Invited counters will be changed only when removing already invited player from queue, removing player from battleground and inviting player to BG
        // Invited players counters
        uint32 _InvitedAlliance;
        uint32 _InvitedHorde;

        // Raid Group
        Group* _BgRaids[BG_TEAMS_COUNT];                   // 0 - alliance, 1 - horde

        // Players count by team
        uint32 _PlayersCount[BG_TEAMS_COUNT];

        // Limits
        uint32 _LevelMin;
        uint32 _LevelMax;
        uint32 _MaxPlayersPerTeam;
        uint32 _MaxPlayers;
        uint32 _MinPlayersPerTeam;
        uint32 _MinPlayers;

        // Start location
        uint32 _MapId;
        BattlegroundMap* _Map;
        float _TeamStartLocX[BG_TEAMS_COUNT];
        float _TeamStartLocY[BG_TEAMS_COUNT];
        float _TeamStartLocZ[BG_TEAMS_COUNT];
        float _TeamStartLocO[BG_TEAMS_COUNT];
        uint32 ScriptId;
};
#endif
