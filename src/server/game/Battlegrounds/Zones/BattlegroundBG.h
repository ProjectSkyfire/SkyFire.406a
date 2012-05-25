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

class Battleground;

enum BG_BG_WorldStates
{
    BG_BG_OP_OCCUPIED_BASES_HORDE       = 1778,
    BG_BG_OP_OCCUPIED_BASES_ALLY        = 1779,
    BG_BG_OP_RESOURCES_ALLY             = 1776,
    BG_BG_OP_RESOURCES_HORDE            = 1777,
    BG_BG_OP_RESOURCES_MAX              = 1780,
    BG_BG_OP_RESOURCES_WARNING          = 1955
};

const uint32 BG_BG_OP_NODESTATES[3] =    {1767, 1772, 1782};
const uint32 BG_BG_OP_NODEICONS[3]  =    {1842, 1845, 1846};

enum BG_BG_NodeObjectId
{
    // This is what I did but requires changes in Database
    BG_BG_OBJECTID_NODE_BANNER_0    = 208779,       // Lighthouse banner
    BG_BG_OBJECTID_NODE_BANNER_1    = 208780,       // Mines banner
    BG_BG_OBJECTID_NODE_BANNER_2    = 208781,       // Waterworks banner
};

enum BG_BG_ObjectType
{
    BG_BG_OBJECT_BANNER_NEUTRAL          = 0,
    BG_BG_OBJECT_BANNER_CONT_A           = 1,
    BG_BG_OBJECT_BANNER_CONT_H           = 2,
    BG_BG_OBJECT_BANNER_ALLY             = 3,
    BG_BG_OBJECT_BANNER_HORDE            = 4,
    BG_BG_OBJECT_AURA_ALLY               = 5,
    BG_BG_OBJECT_AURA_HORDE              = 6,
    BG_BG_OBJECT_AURA_CONTESTED          = 7,
    BG_BG_OBJECT_GATE_A                  = 24,
    BG_BG_OBJECT_GATE_H                  = 25,
    BG_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE    = 26,
    BG_BG_OBJECT_REGENBUFF_LIGHTHOUSE    = 27,
    BG_BG_OBJECT_BERSERKBUFF_LIGHTHOUSE  = 28,
    BG_BG_OBJECT_SPEEDBUFF_WATERWORKS    = 29,
    BG_BG_OBJECT_REGENBUFF_WATERWORKS    = 30,
    BG_BG_OBJECT_BERSERKBUFF_WATERWORKS  = 31,
    BG_BG_OBJECT_SPEEDBUFF_MINE          = 32,
    BG_BG_OBJECT_REGENBUFF_MINE          = 33,
    BG_BG_OBJECT_BERSERKBUFF_MINE        = 34,
    BG_BG_OBJECT_MAX                     = 35,
};

/* Object id templates from DB */
enum BG_BG_ObjectTypes
{
    BG_BG_OBJECTID_BANNER_A             = 180058,
    BG_BG_OBJECTID_BANNER_CONT_A        = 180059,
    BG_BG_OBJECTID_BANNER_H             = 180060,
    BG_BG_OBJECTID_BANNER_CONT_H        = 180061,

    BG_BG_OBJECTID_AURA_A               = 180100,
    BG_BG_OBJECTID_AURA_H               = 180101,
    BG_BG_OBJECTID_AURA_C               = 180102,

    BG_BG_OBJECTID_GATE_A               = 207177,
    BG_BG_OBJECTID_GATE_H               = 207178,
};

enum BG_BG_Timers
{
    BG_BG_FLAG_CAPTURING_TIME   = 60000,
};

enum BG_BG_Score
{
    BG_BG_WARNING_NEAR_VICTORY_SCORE    = 1800,  // 1800 or 1760?
    BG_BG_MAX_TEAM_SCORE                = 2000
};

/* do NOT change the order, else wrong behavior */
enum BG_BG_BattlegroundNodes
{
    BG_BG_NODE_LIGHTHOUSE       = 0,
    BG_BG_NODE_WATERWORKS       = 1,
    BG_BG_NODE_MINE             = 2,

    BG_BG_DYNAMIC_NODES_COUNT   = 3,                        // dynamic nodes that can be captured

    BG_BG_SPIRIT_ALIANCE        = 3,
    BG_BG_SPIRIT_HORDE          = 4,

    BG_BG_ALL_NODES_COUNT       = 5,                        // all nodes (dynamic and static)
};

enum BG_BG_NodeStatus
{
    BG_BG_NODE_TYPE_NEUTRAL             = 0,
    BG_BG_NODE_TYPE_CONTESTED           = 1,
    BG_BG_NODE_STATUS_ALLY_CONTESTED    = 1,
    BG_BG_NODE_STATUS_HORDE_CONTESTED   = 2,
    BG_BG_NODE_TYPE_OCCUPIED            = 3,
    BG_BG_NODE_STATUS_ALLY_OCCUPIED     = 3,
    BG_BG_NODE_STATUS_HORDE_OCCUPIED    = 4
};

enum BG_BG_Sounds
{
    BG_BG_SOUND_NODE_CLAIMED            = 8192,
    BG_BG_SOUND_NODE_CAPTURED_ALLIANCE  = 8173,
    BG_BG_SOUND_NODE_CAPTURED_HORDE     = 8213,
    BG_BG_SOUND_NODE_ASSAULTED_ALLIANCE = 8212,
    BG_BG_SOUND_NODE_ASSAULTED_HORDE    = 8174,
    BG_BG_SOUND_NEAR_VICTORY            = 8456
};

enum BG_BG_Objectives
{
    BG_OBJECTIVE_ASSAULT_BASE           = 122,
    BG_OBJECTIVE_DEFEND_BASE            = 123
};

const float BG_BG_NodePositions[BG_BG_DYNAMIC_NODES_COUNT][4] =
{
    {1057.8f, 1278.150f, 3.25f, 5.0f},      // Lighthouse
    {980.130f, 948.8f, 12.75f, 2.770f},     // Waterworks
    {1250.986f, 958.25f, 5.9f, 5.90f},      // Mine
};

// x, y, z, o, rot0, rot1, rot2, rot3
const float BG_BG_DoorPositions[2][8] = {
    {918.876f, 1336.56f, 27.6195f, 2.77481f, 0.0f, 0.0f, 0.983231f, 0.182367f},
    {1396.15f, 977.014f, 7.43169f, 6.27043f, 0.0f, 0.0f, 0.006378f, -0.99998f}
};

const uint32 BG_BG_TickIntervals[4] = {0, 12000, 6000, 1000};
const uint32 BG_BG_TickPoints[4] = {0, 10, 10, 30};

//Light, Water, Mine, Ally, Horde
const uint32 BG_BG_GraveyardIds[BG_BG_ALL_NODES_COUNT] = {1736, 1738, 1735, 1740, 1739};

const float BG_BG_SpiritGuidePos[BG_BG_ALL_NODES_COUNT][4] = {
    {1034.82f, 1335.58f, 12.0095f, 5.15f},                  // Lighthouse
    {887.578f, 937.337f, 23.7737f, 0.45f},                  // Waterworks
    {1252.23f, 836.547f, 27.7895f, 1.60f},                  // Mine
    {908.274f, 1338.6f, 27.6449f, 5.95f},                   // Alliance
    {1401.38f, 977.125f, 7.44215f, 3.04f},                  // Horde
};

const float BG_BG_BuffPositions[BG_BG_DYNAMIC_NODES_COUNT][4] = {
    {1063.57f, 1313.42f, 4.91f, 4.14f},                    // Lighthouse
    {961.830f, 977.03f, 14.15f, 4.55f},                    // Waterworks
    {1193.09f, 1017.46f, 7.98f, 0.24f},                    // Mine
};

struct BG_BG_BannerTimer
{
    uint32      timer;
    uint8       type;
    uint8       teamIndex;
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
        virtual void AddPlayer(Player *player);
        virtual void StartingEventCloseDoors();
        virtual void StartingEventOpenDoors();
        virtual void Reset();
        virtual WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);

        void RemovePlayer(Player *player, uint64 guid);
        void HandleAreaTrigger(Player *Source, uint32 Trigger);
        bool SetupBattleground();
        void EndBattleground(uint32 winner);

        /* Scorekeeping */
        void UpdatePlayerScore(Player *Source, uint32 type, uint32 value, bool doAddHonor = true);
        void _CreateBanner(uint8 node, uint8 type, uint8 teamIndex, bool delay);
        void _DelBanner(uint8 node, uint8 type, uint8 teamIndex);

        int32 _GetNodeNameId(uint8 node);
        void FillInitialWorldStates(WorldPacket& data);
        void _SendNodeUpdate(uint8 node);
        void _NodeOccupied(uint8 node, Team team);
        void _NodeDeOccupied(uint8 node);
        void EventPlayerClickedOnFlag(Player *source, GameObject* /*target_obj*/);

        bool IsAllNodesConrolledByTeam(uint32 team) const;

    private:
        uint8               m_Nodes[BG_BG_DYNAMIC_NODES_COUNT];
        uint8               m_prevNodes[BG_BG_DYNAMIC_NODES_COUNT];
        BG_BG_BannerTimer   m_BannerTimers[BG_BG_DYNAMIC_NODES_COUNT];
        uint32              m_NodeTimers[BG_BG_DYNAMIC_NODES_COUNT];
        uint32              m_lastTick[BG_TEAMS_COUNT];
        uint32              m_HonorScoreTicks[BG_TEAMS_COUNT];
        uint32              m_ReputationScoreTics[BG_TEAMS_COUNT];
        bool                m_IsInformedNearVictory;
        uint32              m_HonorTics;
        bool                m_TeamScores500Disadvantage[BG_TEAMS_COUNT];
};

#endif
