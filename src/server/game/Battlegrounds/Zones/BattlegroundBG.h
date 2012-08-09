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

#ifndef __BattlegroundBG_H
#define __BattlegroundBG_H

#include "Player.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "Language.h"

class Battleground;

enum GILNEAS_BG_Rewards
{
    GILNEAS_BG_MAP_COMPLETE,
    GILNEAS_BG_REWARD_NUM
};

enum GILNEAS_BG_WorldStates
{
    GILNEAS_BG_OP_OCCUPIED_BASES_HORDE       = 1778,
    GILNEAS_BG_OP_OCCUPIED_BASES_ALLY        = 1779,
    GILNEAS_BG_OP_RESOURCES_ALLY             = 1776,
    GILNEAS_BG_OP_RESOURCES_HORDE            = 1777,
    GILNEAS_BG_OP_RESOURCES_MAX              = 1780,
    GILNEAS_BG_OP_RESOURCES_WARNING          = 1955
};

const uint32 GILNEAS_BG_OP_NODESTATES[3] =    {1767, 1772, 1782};
const uint32 GILNEAS_BG_OP_NODEICONS[3]  =    {1842, 1845, 1846};

enum GILNEAS_BG_NodeObjectId
{
    GILNEAS_BG_OBJECTID_NODE_BANNER_0    = 208779,       // Lighthouse banner
    GILNEAS_BG_OBJECTID_NODE_BANNER_1    = 208780,       // Waterworks banner
    GILNEAS_BG_OBJECTID_NODE_BANNER_2    = 208781,       // Mines banner
};

enum GILNEAS_BG_ObjectType
{
    GILNEAS_BG_OBJECT_BANNER_NEUTRAL          = 0,
    GILNEAS_BG_OBJECT_BANNER_CONT_A           = 1,
    GILNEAS_BG_OBJECT_BANNER_CONT_H           = 2,
    GILNEAS_BG_OBJECT_BANNER_ALLY             = 3,
    GILNEAS_BG_OBJECT_BANNER_HORDE            = 4,
    GILNEAS_BG_OBJECT_AURA_ALLY               = 5,
    GILNEAS_BG_OBJECT_AURA_HORDE              = 6,
    GILNEAS_BG_OBJECT_AURA_CONTESTED          = 7,
    GILNEAS_BG_OBJECT_GATE_A_1                = 24,
    GILNEAS_BG_OBJECT_GATE_A_2                = 25,
    GILNEAS_BG_OBJECT_GATE_H_1                = 26,
    GILNEAS_BG_OBJECT_GATE_H_2                = 27,
    //buffs
    GILNEAS_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE    = 28,
    GILNEAS_BG_OBJECT_REGENBUFF_LIGHTHOUSE    = 29,
    GILNEAS_BG_OBJECT_BERSERKBUFF_LIGHTHOUSE  = 30,
    GILNEAS_BG_OBJECT_SPEEDBUFF_WATERWORKS    = 31,
    GILNEAS_BG_OBJECT_REGENBUFF_WATERWORKS    = 32,
    GILNEAS_BG_OBJECT_BERSERKBUFF_WATERWORKS  = 33,
    GILNEAS_BG_OBJECT_SPEEDBUFF_MINE          = 34,
    GILNEAS_BG_OBJECT_REGENBUFF_MINE          = 35,
    GILNEAS_BG_OBJECT_BERSERKBUFF_MINE        = 36,
    GILNEAS_BG_OBJECT_MAX                     = 37,
};

enum GILNEAS_BG_ObjectTypes
{
    GILNEAS_BG_OBJECTID_BANNER_A             = 180058,
    GILNEAS_BG_OBJECTID_BANNER_CONT_A        = 180059,
    GILNEAS_BG_OBJECTID_BANNER_H             = 180060,
    GILNEAS_BG_OBJECTID_BANNER_CONT_H        = 180061,

    GILNEAS_BG_OBJECTID_AURA_A               = 180100,
    GILNEAS_BG_OBJECTID_AURA_H               = 180101,
    GILNEAS_BG_OBJECTID_AURA_C               = 180102,

    GILNEAS_BG_OBJECTID_GATE_A_1             = 207177,
    GILNEAS_BG_OBJECTID_GATE_A_2             = 180322,
    GILNEAS_BG_OBJECTID_GATE_H_1             = 207178,
    GILNEAS_BG_OBJECTID_GATE_H_2             = 180322,
};

enum GILNEAS_BG_Timers
{
    GILNEAS_BG_FLAG_CAPTURING_TIME           = 60000,
};

enum GILNEAS_BG_Score
{
    GILNEAS_BG_WARNING_NEAR_VICTORY_SCORE    = 1800,
    GILNEAS_BG_MAX_TEAM_SCORE                = 2000
};

/* Do not change below, or this thing will go boom! */
enum GILNEAS_BG_BattlegroundNodes
{
    GILNEAS_BG_NODE_LIGHTHOUSE       = 0,
    GILNEAS_BG_NODE_WATERWORKS       = 1,
    GILNEAS_BG_NODE_MINE             = 2,

    GILNEAS_BG_DYNAMIC_NODES_COUNT   = 3,                        // Dynamic nodes that can be captured

    GILNEAS_BG_SPIRIT_ALIANCE        = 3,
    GILNEAS_BG_SPIRIT_HORDE          = 4,

    GILNEAS_BG_ALL_NODES_COUNT       = 5,                        // All nodes (dynamic and static)
};

enum GILNEAS_BG_NodeStatus
{
    GILNEAS_BG_NODE_TYPE_NEUTRAL             = 0,
    GILNEAS_BG_NODE_TYPE_CONTESTED           = 1,
    GILNEAS_BG_NODE_STATUS_ALLY_CONTESTED    = 1,
    GILNEAS_BG_NODE_STATUS_HORDE_CONTESTED   = 2,
    GILNEAS_BG_NODE_TYPE_OCCUPIED            = 3,
    GILNEAS_BG_NODE_STATUS_ALLY_OCCUPIED     = 3,
    GILNEAS_BG_NODE_STATUS_HORDE_OCCUPIED    = 4
};

enum GILNEAS_BG_Sounds
{
    GILNEAS_BG_SOUND_NODE_CLAIMED            = 8192,
    GILNEAS_BG_SOUND_NODE_CAPTURED_ALLIANCE  = 8173,
    GILNEAS_BG_SOUND_NODE_CAPTURED_HORDE     = 8213,
    GILNEAS_BG_SOUND_NODE_ASSAULTED_ALLIANCE = 8212,
    GILNEAS_BG_SOUND_NODE_ASSAULTED_HORDE    = 8174,
    GILNEAS_BG_SOUND_NEAR_VICTORY            = 8456
};

enum GILNEAS_BG_Objectives
{
    BG_OBJECTIVE_ASSAULT_BASE           = 122,
    BG_OBJECTIVE_DEFEND_BASE            = 123
};

/* Holiday/Reg Honor/Rep gains */
#define GILNEAS_BG_NotBGWeekendHonorTicks   330
#define GILNEAS_BG_BGWeekendHonorTicks      200
#define GILNEAS_BG_NotBGWeekendRepTicks     200
#define GILNEAS_BG_BGWeekendRepTicks        150

const float GILNEAS_BG_NodePositions[GILNEAS_BG_DYNAMIC_NODES_COUNT][4] =
{
    { 1057.790f, 1278.285f, 3.1500f, 1.945662f },        // Lighthouse
    { 1251.010f, 958.2685f, 5.6000f, 5.892280f },        // Waterworks
    { 980.0446f, 948.7411f, 12.650f, 5.904071f },        // Mine
};

// x, y, z, o, rot0, rot1, rot2, rot3
const float GILNEAS_BG_DoorPositions[4][8] =
{
    { 918.160f, 1336.75f, 27.6299f, 2.87927f, 0.0f, 0.0f, 0.983231f, 0.182367f },
    { 918.160f, 1336.75f, 26.6299f, 2.87927f, 0.0f, 0.0f, 0.983231f, 0.182367f },
    { 1396.15f, 977.014f, 7.43169f, 6.27043f, 0.0f, 0.0f, 0.006378f, -0.99998f },
    { 1396.15f, 977.014f, 0.33169f, 6.27043f, 0.0f, 0.0f, 0.006378f, -0.99998f },
};

const uint32 GILNEAS_BG_TickIntervals[4] = { 0, 12000, 6000, 1000 };
const uint32 GILNEAS_BG_TickPoints[4]    = { 0, 10, 10, 30 };

//Light, Water, Mine, Ally, Horde
const uint32 GILNEAS_BG_GraveyardIds[GILNEAS_BG_ALL_NODES_COUNT] = { 1736, 1738, 1735, 1740, 1739 };

const float GILNEAS_BG_SpiritGuidePos[GILNEAS_BG_ALL_NODES_COUNT][4] =
{
    { 1034.82f, 1335.58f, 12.0095f, 5.15f },     // Lighthouse
    { 887.578f, 937.337f, 23.7737f, 0.45f },     // Waterworks
    { 1252.23f, 836.547f, 27.7895f, 1.60f },     // Mine
    { 908.274f, 1338.6f, 27.6449f, 5.95f  },     // Alliance
    { 1401.38f, 977.125f, 7.44215f, 3.04f },     // Horde
};

const float GILNEAS_BG_BuffPositions[GILNEAS_BG_DYNAMIC_NODES_COUNT][4] =
{
    { 1063.57f, 1313.42f, 4.91f, 4.14f },        // Lighthouse
    { 961.830f, 977.03f, 14.15f, 4.55f },        // Waterworks
    { 1193.09f, 1017.46f, 7.98f, 0.24f },        // Mine
};

struct GILNEAS_BG_BannerTimer
{
    uint32 timer;
    uint8  type;
    uint8  teamIndex;
};

class BattlegroundBGScore : public BattlegroundScore
{
    public:
        BattlegroundBGScore(): BasesAssaulted(0), BasesDefended(0) {};
        virtual ~BattlegroundBGScore() {};
        uint32 BasesAssaulted;
        uint32 BasesDefended;
};

class BattlegroundBG : public Battleground
{
    friend class BattlegroundMgr;

    public:
        BattlegroundBG();
        ~BattlegroundBG();

        void Update(uint32 diff);

        /* inherited from BattlegroundClass */
        virtual void AddPlayer(Player* player);
        virtual void StartingEventCloseDoors();
        virtual void StartingEventOpenDoors();
        virtual void Reset();
        virtual WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);

        void RemovePlayer(Player* player, uint64 guid);
        void HandleAreaTrigger(Player* Source, uint32 Trigger);
        bool SetupBattleground();
        void EndBattleground(uint32 winner);

        /* Score-keeping */
        void UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor = true);
        void FillInitialWorldStates(WorldPacket& data);

        void EventPlayerClickedOnFlag(Player* source, GameObject* /*target_obj*/);

        /* achievement requirements. */
        bool IsAllNodesConrolledByTeam(uint32 team) const;
        bool IsTeamScores500Disadvantage(uint32 team) const { return _TeamScores500Disadvantage[GetTeamIndexByTeamId(team)]; }

    private:

        /* GameObject spawning/removing */
        void _SendNodeUpdate(uint8 node);
        void _CreateBanner(uint8 node, uint8 type, uint8 teamIndex, bool delay);
        void _DelBanner(uint8 node, uint8 type, uint8 teamIndex);

        /* Creature spawning/removing */
        // TODO: need to get the peons spawns scripted
        void _NodeOccupied(uint8 node, Team team);
        void _NodeDeOccupied(uint8 node);

        int32 _GetNodeNameId(uint8 node);

        /* Nodes info:
         *  0: neutral
         *  1: ally contested
         *  2: horde contested
         *  3: ally occupied
         *  4: horde occupied
         */
        uint8               _Nodes[GILNEAS_BG_DYNAMIC_NODES_COUNT];
        uint8               _prevNodes[GILNEAS_BG_DYNAMIC_NODES_COUNT];
        GILNEAS_BG_BannerTimer   _BannerTimers[GILNEAS_BG_DYNAMIC_NODES_COUNT];
        uint32              _NodeTimers[GILNEAS_BG_DYNAMIC_NODES_COUNT];

        uint32              _lastTick[BG_TEAMS_COUNT];
        uint32              _HonorScoreTicks[BG_TEAMS_COUNT];
        uint32              _ReputationScoreTicks[BG_TEAMS_COUNT];

        bool                _IsInformedNearVictory;
        uint32              _HonorTicks;
        uint32              _ReputationTicks;
        bool                _TeamScores500Disadvantage[BG_TEAMS_COUNT];
};

#endif
