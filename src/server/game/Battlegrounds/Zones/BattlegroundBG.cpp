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

#include "BattlegroundBG.h"

uint32 GILNEAS_BG_HonorScoreTicks[BG_HONOR_MODE_NUM] =
{
    330, // normal honor
    200  // holiday
};

uint32 GILNEAS_BG_Reputation[BG_HONOR_MODE_NUM][GILNEAS_BG_REWARD_NUM] =
{
    200, // normal honor
    150  // holiday
};

BattlegroundBG::BattlegroundBG()
{
    _BuffChange = true;
    BgObjects.resize(GILNEAS_BG_OBJECT_MAX);
    BgCreatures.resize(GILNEAS_BG_ALL_NODES_COUNT + 3); // +3 for aura triggers

    StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_BG_BG_START_TWO_MINUTES;
    StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_BG_START_ONE_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_BG_BG_START_HALF_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_BG_HAS_BEGUN;
}

BattlegroundBG::~BattlegroundBG() {}

void BattlegroundBG::Update(uint32 diff) // PostUpdateImpl...
{
    if (GetStatus() == STATUS_IN_PROGRESS)
    {
        int team_points[BG_TEAMS_COUNT] = { 0, 0 };

        for (int node = 0; node < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++node)
        {
            // 3sec delay to spawn new a banner.
            if (_BannerTimers[node].timer)
            {
                if (_BannerTimers[node].timer > diff)
                    _BannerTimers[node].timer -= diff;
                else
                {
                    _BannerTimers[node].timer = 0;
                    _CreateBanner(node, _BannerTimers[node].type, _BannerTimers[node].teamIndex, false);
                }
            }
            // 1 minute cap timer on each node from a contested state.
            if (_NodeTimers[node])
            {
                if (_NodeTimers[node] > diff)
                    _NodeTimers[node] -= diff;
                else
                {
                    _NodeTimers[node] = 0;

                    // Change from contested to occupied !
                    uint8 teamIndex = _Nodes[node]-1;
                    _prevNodes[node] = _Nodes[node];
                    _Nodes[node] += 2;

                    // burn current contested banner
                    _DelBanner(node, GILNEAS_BG_NODE_TYPE_CONTESTED, teamIndex);

                    // create new occupied banner
                    _CreateBanner(node, GILNEAS_BG_NODE_TYPE_OCCUPIED, teamIndex, true);
                    _SendNodeUpdate(node);
                    _NodeOccupied(node, (teamIndex == 0) ? ALLIANCE:HORDE);

                    // Message to chatlog
                    if (teamIndex == 0)
                    {
                        // FIXME: need to fix Locales for team and nodes names.
                        SendMessage2ToAll(LANG_BG_BG_NODE_TAKEN, CHAT_MSG_BG_SYSTEM_ALLIANCE, NULL, LANG_BG_BG_ALLY, _GetNodeNameId(node));
                        PlaySoundToAll(GILNEAS_BG_SOUND_NODE_CAPTURED_ALLIANCE);
                    }
                    else
                    {
                        // FIXME: team and node names not localized
                        SendMessage2ToAll(LANG_BG_BG_NODE_TAKEN, CHAT_MSG_BG_SYSTEM_HORDE, NULL, LANG_BG_BG_HORDE, _GetNodeNameId(node));
                        PlaySoundToAll(GILNEAS_BG_SOUND_NODE_CAPTURED_HORDE);
                    }
                }
            }

            for (int team = 0; team < BG_TEAMS_COUNT; ++team)
                if (_Nodes[node] == team + GILNEAS_BG_NODE_TYPE_OCCUPIED)
                    ++team_points[team];
        }

        // Accumulate points
        for (int team = 0; team < BG_TEAMS_COUNT; ++team)
        {
            int points = team_points[team];
            if (!points)
                continue;

            _lastTick[team] += diff;
            if (_lastTick[team] > GILNEAS_BG_TickIntervals[points])
            {
                _lastTick[team] -= GILNEAS_BG_TickIntervals[points];
                _TeamScores[team] += GILNEAS_BG_TickPoints[points];
                _HonorScoreTicks[team] += GILNEAS_BG_TickPoints[points];
                _ReputationScoreTicks[team] += GILNEAS_BG_TickPoints[points];

                if (_ReputationScoreTicks[team] >= _ReputationTicks)
                {
                    (team == BG_TEAM_ALLIANCE) ? RewardReputationToTeam(509, 10, ALLIANCE) : RewardReputationToTeam(510, 10, HORDE);
                    _ReputationScoreTicks[team] -= _ReputationTicks;
                }

                if (_HonorScoreTicks[team] >= _HonorTicks)
                {
                    RewardHonorToTeam(GetBonusHonorFromKill(1), (team == BG_TEAM_ALLIANCE) ? ALLIANCE : HORDE);
                    _HonorScoreTicks[team] -= _HonorTicks;
                }

                if (!_IsInformedNearVictory && _TeamScores[team] > GILNEAS_BG_WARNING_NEAR_VICTORY_SCORE)
                {
                    if (team == BG_TEAM_ALLIANCE)
                        SendMessageToAll(LANG_BG_AB_A_NEAR_VICTORY, CHAT_MSG_BG_SYSTEM_NEUTRAL);
                    else
                        SendMessageToAll(LANG_BG_AB_H_NEAR_VICTORY, CHAT_MSG_BG_SYSTEM_NEUTRAL);

                    PlaySoundToAll(GILNEAS_BG_SOUND_NEAR_VICTORY);
                    _IsInformedNearVictory = true;
                }

                if (_TeamScores[team] > GILNEAS_BG_MAX_TEAM_SCORE)
                    _TeamScores[team] = GILNEAS_BG_MAX_TEAM_SCORE;

                if (team == BG_TEAM_ALLIANCE)
                    UpdateWorldState(GILNEAS_BG_OP_RESOURCES_ALLY, _TeamScores[team]);

                if (team == BG_TEAM_HORDE)
                    UpdateWorldState(GILNEAS_BG_OP_RESOURCES_HORDE, _TeamScores[team]);
                // update achievement flags
                // we increased _TeamScores[team] so we just need to check if it is 500 more than other teams resources
                uint8 otherTeam = (team + 1) % BG_TEAMS_COUNT;
                if (_TeamScores[team] > _TeamScores[otherTeam] + 500)
                    _TeamScores500Disadvantage[otherTeam] = true;
            }
        }

        // Test win condition
        if (_TeamScores[BG_TEAM_ALLIANCE] >= GILNEAS_BG_MAX_TEAM_SCORE)
            EndBattleground(ALLIANCE);

        if (_TeamScores[BG_TEAM_HORDE] >= GILNEAS_BG_MAX_TEAM_SCORE)
            EndBattleground(HORDE);
    }
}

void BattlegroundBG::StartingEventCloseDoors()
{
    // Remove banners, auras and buffs
    for (int object = GILNEAS_BG_OBJECT_BANNER_NEUTRAL; object < GILNEAS_BG_DYNAMIC_NODES_COUNT * 8; ++object)
        SpawnBGObject(object, RESPAWN_ONE_DAY);
    for (int i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT * 3; ++i)
        SpawnBGObject(GILNEAS_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + i, RESPAWN_ONE_DAY);

    // Starting doors
    DoorClose(GILNEAS_BG_OBJECT_GATE_A_1);
    SpawnBGObject(GILNEAS_BG_OBJECT_GATE_A_2, RESPAWN_IMMEDIATELY);
    DoorClose(GILNEAS_BG_OBJECT_GATE_H_1);
    SpawnBGObject(GILNEAS_BG_OBJECT_GATE_H_2, RESPAWN_IMMEDIATELY);

    // Starting base spirit guides
    _NodeOccupied(GILNEAS_BG_SPIRIT_ALIANCE, ALLIANCE);
    _NodeOccupied(GILNEAS_BG_SPIRIT_HORDE, HORDE);
}

void BattlegroundBG::StartingEventOpenDoors()
{
    for (int banner = GILNEAS_BG_OBJECT_BANNER_NEUTRAL, i = 0; i < 5; banner += 8, ++i)
        SpawnBGObject(banner, RESPAWN_IMMEDIATELY);
    for (int i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
    {
        uint8 buff = urand(0, 2);
        SpawnBGObject(GILNEAS_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + buff + i * 3, RESPAWN_IMMEDIATELY);
    }
    DoorOpen(GILNEAS_BG_OBJECT_GATE_A_1);
    GetBGObject(GILNEAS_BG_OBJECT_GATE_A_2)->RemoveFromWorld();
    DoorOpen(GILNEAS_BG_OBJECT_GATE_H_1);
    GetBGObject(GILNEAS_BG_OBJECT_GATE_H_2)->RemoveFromWorld();
}

void BattlegroundBG::AddPlayer(Player* player)
{
    Battleground::AddPlayer(player);
    // Create score and add it to map, default values are set in constructor
    BattlegroundBGScore* score = new BattlegroundBGScore;

    PlayerScores[player->GetGUID()] = score;
}

void BattlegroundBG::RemovePlayer(Player* /*player*/, uint64 /*guid*/) { }
void BattlegroundBG::HandleAreaTrigger(Player * /*Source*/, uint32 /*Trigger*/)
{
    // this is  wrong way to implement these things. On official it done by gameobject spell cast.
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;
}

void BattlegroundBG::_CreateBanner(uint8 node, uint8 type, uint8 teamIndex, bool delay)
{
    // Just put it into the queue
    if (delay)
    {
        _BannerTimers[node].timer       = 2000;
        _BannerTimers[node].type        = type;
        _BannerTimers[node].teamIndex   = teamIndex;
        return;
    }

    uint8 object = node*8 + type + teamIndex;

    SpawnBGObject(object, RESPAWN_IMMEDIATELY);

    // Handle banner and auras
    if (!type)
        return;

    object = node * 8 + ((type == GILNEAS_BG_NODE_TYPE_OCCUPIED) ? (5 + teamIndex) : 7);
    SpawnBGObject(object, RESPAWN_IMMEDIATELY);
}

void BattlegroundBG::_DelBanner(uint8 node, uint8 type, uint8 teamIndex)
{
    uint8 object = node*8 + type + teamIndex;
    SpawnBGObject(object, RESPAWN_ONE_DAY);

    // Handle banner and auras
    if (!type)
        return;

    object = node * 8 + ((type == GILNEAS_BG_NODE_TYPE_OCCUPIED) ? (5 + teamIndex) : 7);
    SpawnBGObject(object, RESPAWN_ONE_DAY);
}

int32 BattlegroundBG::_GetNodeNameId(uint8 node)
{
    switch (node)
    {
        case GILNEAS_BG_NODE_LIGHTHOUSE: return LANG_BG_BG_NODE_LIGHTHOUSE;
        case GILNEAS_BG_NODE_WATERWORKS: return LANG_BG_BG_NODE_WATERWORKS;
        case GILNEAS_BG_NODE_MINE: return LANG_BG_BG_NODE_MINE;
        default:
            ASSERT(0);
    }
    return 0;
}

void BattlegroundBG::FillInitialWorldStates(WorldPacket& data)
{
    const uint8 plusArray[] = { 0, 2, 3, 0, 1 };

    // Node icons
    for (uint8 node = 0; node < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++node)
        data << uint32(GILNEAS_BG_OP_NODEICONS[node]) << uint32((_Nodes[node] == 0)?1:0);

    // Node occupied states
    for (uint8 node = 0; node < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++node)
        for (uint8 i = 1; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
            data << uint32(GILNEAS_BG_OP_NODESTATES[node] + plusArray[i]) << uint32((_Nodes[node] == i)?1:0);

    // How many bases each team owns
    uint8 ally = 0, horde = 0;
    for (uint8 node = 0; node < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++node)
        if (_Nodes[node] == GILNEAS_BG_NODE_STATUS_ALLY_OCCUPIED)
            ++ally;
        else if (_Nodes[node] == GILNEAS_BG_NODE_STATUS_HORDE_OCCUPIED)
            ++horde;

    data << uint32(GILNEAS_BG_OP_OCCUPIED_BASES_ALLY)  << uint32(ally);
    data << uint32(GILNEAS_BG_OP_OCCUPIED_BASES_HORDE) << uint32(horde);

    // Team scores
    data << uint32(GILNEAS_BG_OP_RESOURCES_MAX)      << uint32(GILNEAS_BG_MAX_TEAM_SCORE);
    data << uint32(GILNEAS_BG_OP_RESOURCES_WARNING)  << uint32(GILNEAS_BG_WARNING_NEAR_VICTORY_SCORE);
    data << uint32(GILNEAS_BG_OP_RESOURCES_ALLY)     << uint32(_TeamScores[BG_TEAM_ALLIANCE]);
    data << uint32(GILNEAS_BG_OP_RESOURCES_HORDE)    << uint32(_TeamScores[BG_TEAM_HORDE]);

    // other unknown
    //data << uint32(0x745) << uint32(0x2);           // 37 1861 unk
}

void BattlegroundBG::_SendNodeUpdate(uint8 node)
{
    // Send to client owner node state updates to refresh map icons.
    const uint8 plusArray[] = { 0, 2, 3, 0, 1 };

    if (_prevNodes[node])
        UpdateWorldState(GILNEAS_BG_OP_NODESTATES[node] + plusArray[_prevNodes[node]], 0);
    else
        UpdateWorldState(GILNEAS_BG_OP_NODEICONS[node], 0);

    UpdateWorldState(GILNEAS_BG_OP_NODESTATES[node] + plusArray[_Nodes[node]], 1);

    // How many bases each team owns
    uint8 ally = 0, horde = 0;

    for (uint8 i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
        if (_Nodes[i] == GILNEAS_BG_NODE_STATUS_ALLY_OCCUPIED)
            ++ally;
        else if (_Nodes[i] == GILNEAS_BG_NODE_STATUS_HORDE_OCCUPIED)
            ++horde;

    UpdateWorldState(GILNEAS_BG_OP_OCCUPIED_BASES_ALLY, ally);
    UpdateWorldState(GILNEAS_BG_OP_OCCUPIED_BASES_HORDE, horde);
}

void BattlegroundBG::_NodeOccupied(uint8 node, Team team)
{
    if (!AddSpiritGuide(node, GILNEAS_BG_SpiritGuidePos[node][0], GILNEAS_BG_SpiritGuidePos[node][1], GILNEAS_BG_SpiritGuidePos[node][2], GILNEAS_BG_SpiritGuidePos[node][3], team))
        sLog->outError("Failed to spawn spirit guide! point: %u, team: %u, ", node, team);

    uint8 capturedNodes = 0;
    for (uint8 i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
    {
        if (_Nodes[node] == GetTeamIndexByTeamId(team) + GILNEAS_BG_NODE_TYPE_OCCUPIED && !_NodeTimers[i])
            ++capturedNodes;
    }
    // Todo finish me
    //if (capturedNodes >= 5)
        //CastSpellOnTeam(SPELL_BG_QUEST_REWARD_5_BASES, team);
    //if (capturedNodes >= 4)
        //CastSpellOnTeam(SPELL_BG_QUEST_REWARD_4_BASES, team);

    if (node >= GILNEAS_BG_DYNAMIC_NODES_COUNT) // only dynamic nodes, no start points
        return;

    Creature* trigger = GetBGCreature(node+5); // 0-5 spirit guides

    if (!trigger)
       trigger = AddCreature(WORLD_TRIGGER, node+5, team, GILNEAS_BG_NodePositions[node][0], GILNEAS_BG_NodePositions[node][1], GILNEAS_BG_NodePositions[node][2], GILNEAS_BG_NodePositions[node][3]);

    // Add bonus honor aura trigger creature when node is occupied
    // Cast bonus aura (+50% honor in 25yards)
    // aura should only apply to players who have occupied the node, set correct faction for trigger
    if (trigger)
    {
        trigger->setFaction(team == ALLIANCE ? 84 : 83);
        trigger->CastSpell(trigger, SPELL_HONORABLE_DEFENDER_25Y, false);
    }
}

void BattlegroundBG::_NodeDeOccupied(uint8 node)
{
    if (node >= GILNEAS_BG_DYNAMIC_NODES_COUNT)
        return;

    // Remove bonus honor aura trigger bunny when node is lost
    if (node < GILNEAS_BG_DYNAMIC_NODES_COUNT)  // Only dynamic nodes, no start points
        DelCreature(node+7);                    // NULL checks are in DelCreature! 0-6 spirit guides

    // Players waiting to resurrect at this node are sent to closest owned graveyard
    std::vector<uint64> ghost_list = _ReviveQueue[BgCreatures[node]];
    if (!ghost_list.empty())
    {
        WorldSafeLocsEntry const *ClosestGrave = NULL;
        for (std::vector<uint64>::const_iterator itr = ghost_list.begin(); itr != ghost_list.end(); ++itr)
        {
            Player* player = ObjectAccessor::FindPlayer(*itr);
            if (!player)
                continue;

            if (!ClosestGrave)
                ClosestGrave = GetClosestGraveYard(player);

            if (ClosestGrave)
                player->TeleportTo(GetMapId(), ClosestGrave->x, ClosestGrave->y, ClosestGrave->z, player->GetOrientation());
        }
    }

    if (BgCreatures[node])
        DelCreature(node);

    // Buff object is not removed
}

/* Invoked if a player used a banner as a GameObject */
void BattlegroundBG::EventPlayerClickedOnFlag(Player* source, GameObject* /*target_obj*/)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    uint8 node = GILNEAS_BG_NODE_LIGHTHOUSE;
    GameObject* object=GetBgMap()->GetGameObject(BgObjects[node*8+3]);
    while ((node < GILNEAS_BG_DYNAMIC_NODES_COUNT) && ((!object) || (!source->IsWithinDistInMap(object, 10))))
    {
        ++node;
        object=GetBgMap()->GetGameObject(BgObjects[node*8+GILNEAS_BG_OBJECT_AURA_CONTESTED]);
    }

    if (node == GILNEAS_BG_DYNAMIC_NODES_COUNT)
    {
        // this means our player isn't close to any of banners - maybe cheater ??
        return;
    }

    BattlegroundTeamId teamIndex = GetTeamIndexByTeamId(source->GetTeam());

    // Check if player really could use this banner, and has not cheated
    if (!(_Nodes[node] == 0 || teamIndex == _Nodes[node]%2))
        return;

    source->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_ENTER_PVP_COMBAT);
    uint32 sound = 0;
    // If node is neutral, change to contested
    if (_Nodes[node] == GILNEAS_BG_NODE_TYPE_NEUTRAL)
    {
        UpdatePlayerScore(source, SCORE_BASES_ASSAULTED, 1);
        _prevNodes[node] = _Nodes[node];
        _Nodes[node] = teamIndex + 1;

        // burn current neutral banner
        _DelBanner(node, GILNEAS_BG_NODE_TYPE_NEUTRAL, 0);

        // create new contested banner
        _CreateBanner(node, GILNEAS_BG_NODE_TYPE_CONTESTED, teamIndex, true);
        _SendNodeUpdate(node);
        _NodeTimers[node] = GILNEAS_BG_FLAG_CAPTURING_TIME;

        // FIXME: need to fix Locales for team and node names.
        if (teamIndex == 0)
            SendMessage2ToAll(LANG_BG_BG_NODE_CLAIMED, CHAT_MSG_BG_SYSTEM_ALLIANCE, source, _GetNodeNameId(node), LANG_BG_BG_ALLY);
        else
            SendMessage2ToAll(LANG_BG_BG_NODE_CLAIMED, CHAT_MSG_BG_SYSTEM_HORDE, source, _GetNodeNameId(node), LANG_BG_BG_HORDE);

        sound = GILNEAS_BG_SOUND_NODE_CLAIMED;
    }
    // If node is contested
    else if ((_Nodes[node] == GILNEAS_BG_NODE_STATUS_ALLY_CONTESTED) || (_Nodes[node] == GILNEAS_BG_NODE_STATUS_HORDE_CONTESTED))
    {
        // If last state is NOT occupied, change node to enemy-contested
        if (_prevNodes[node] < GILNEAS_BG_NODE_TYPE_OCCUPIED)
        {
            UpdatePlayerScore(source, SCORE_BASES_ASSAULTED, 1);
            _prevNodes[node] = _Nodes[node];
            _Nodes[node] = teamIndex + GILNEAS_BG_NODE_TYPE_CONTESTED;

            // burn current contested banner
            _DelBanner(node, GILNEAS_BG_NODE_TYPE_CONTESTED, !teamIndex);

            // create new contested banner
            _CreateBanner(node, GILNEAS_BG_NODE_TYPE_CONTESTED, teamIndex, true);
            _SendNodeUpdate(node);
            _NodeTimers[node] = GILNEAS_BG_FLAG_CAPTURING_TIME;

            // FIXME: need to fix Locales for team and node names.
            if (teamIndex == BG_TEAM_ALLIANCE)
                SendMessage2ToAll(LANG_BG_BG_NODE_ASSAULTED, CHAT_MSG_BG_SYSTEM_ALLIANCE, source, _GetNodeNameId(node));
            else
                SendMessage2ToAll(LANG_BG_BG_NODE_ASSAULTED, CHAT_MSG_BG_SYSTEM_HORDE, source, _GetNodeNameId(node));
        }
        // If contested, change back to occupied
        else
        {
            UpdatePlayerScore(source, SCORE_BASES_DEFENDED, 1);
            _prevNodes[node] = _Nodes[node];
            _Nodes[node] = teamIndex + GILNEAS_BG_NODE_TYPE_OCCUPIED;

            // burn current contested banner
            _DelBanner(node, GILNEAS_BG_NODE_TYPE_CONTESTED, !teamIndex);

            // create new occupied banner
            _CreateBanner(node, GILNEAS_BG_NODE_TYPE_OCCUPIED, teamIndex, true);
            _SendNodeUpdate(node);
            _NodeTimers[node] = 0;
            _NodeOccupied(node, (teamIndex == BG_TEAM_ALLIANCE) ? ALLIANCE:HORDE);

            // FIXME: need to fix Locales for team and node names.
            if (teamIndex == BG_TEAM_ALLIANCE)
                SendMessage2ToAll(LANG_BG_BG_NODE_DEFENDED, CHAT_MSG_BG_SYSTEM_ALLIANCE, source, _GetNodeNameId(node));
            else
                SendMessage2ToAll(LANG_BG_BG_NODE_DEFENDED, CHAT_MSG_BG_SYSTEM_HORDE, source, _GetNodeNameId(node));
        }
        sound = (teamIndex == BG_TEAM_ALLIANCE) ? GILNEAS_BG_SOUND_NODE_ASSAULTED_ALLIANCE : GILNEAS_BG_SOUND_NODE_ASSAULTED_HORDE;
    }
    // If node is occupied, change to enemy-contested
    else
    {
        UpdatePlayerScore(source, SCORE_BASES_ASSAULTED, 1);
        _prevNodes[node] = _Nodes[node];
        _Nodes[node] = teamIndex + GILNEAS_BG_NODE_TYPE_CONTESTED;

        // burn current occupied banner
        _DelBanner(node, GILNEAS_BG_NODE_TYPE_OCCUPIED, !teamIndex);

        // create new contested banner
        _CreateBanner(node, GILNEAS_BG_NODE_TYPE_CONTESTED, teamIndex, true);
        _SendNodeUpdate(node);
        _NodeDeOccupied(node);
        _NodeTimers[node] = GILNEAS_BG_FLAG_CAPTURING_TIME;

        // FIXME: need to fix Locales for team and node names.
        if (teamIndex == BG_TEAM_ALLIANCE)
            SendMessage2ToAll(LANG_BG_BG_NODE_ASSAULTED, CHAT_MSG_BG_SYSTEM_ALLIANCE, source, _GetNodeNameId(node));
        else
            SendMessage2ToAll(LANG_BG_BG_NODE_ASSAULTED, CHAT_MSG_BG_SYSTEM_HORDE, source, _GetNodeNameId(node));

        sound = (teamIndex == BG_TEAM_ALLIANCE) ? GILNEAS_BG_SOUND_NODE_ASSAULTED_ALLIANCE : GILNEAS_BG_SOUND_NODE_ASSAULTED_HORDE;
    }

    // If node is occupied again, send "X has taken the Y" msg.
    if (_Nodes[node] >= GILNEAS_BG_NODE_TYPE_OCCUPIED)
    {
        // FIXME: need to fix Locales for team and node names.
        if (teamIndex == BG_TEAM_ALLIANCE)
            SendMessage2ToAll(LANG_BG_BG_NODE_TAKEN, CHAT_MSG_BG_SYSTEM_ALLIANCE, NULL, LANG_BG_BG_ALLY, _GetNodeNameId(node));
        else
            SendMessage2ToAll(LANG_BG_BG_NODE_TAKEN, CHAT_MSG_BG_SYSTEM_HORDE, NULL, LANG_BG_BG_HORDE, _GetNodeNameId(node));
    }
    PlaySoundToAll(sound);
}

bool BattlegroundBG::SetupBattleground()
{
    for (int i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
    {
        if (!AddObject(GILNEAS_BG_OBJECT_BANNER_NEUTRAL + 8*i, GILNEAS_BG_OBJECTID_NODE_BANNER_0 + i, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_BANNER_CONT_A + 8*i, GILNEAS_BG_OBJECTID_BANNER_CONT_A, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_BANNER_CONT_H + 8*i, GILNEAS_BG_OBJECTID_BANNER_CONT_H, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_BANNER_ALLY + 8*i, GILNEAS_BG_OBJECTID_BANNER_A, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_BANNER_HORDE + 8*i, GILNEAS_BG_OBJECTID_BANNER_H, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_AURA_ALLY + 8*i, GILNEAS_BG_OBJECTID_AURA_A, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_AURA_HORDE + 8*i, GILNEAS_BG_OBJECTID_AURA_H, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_AURA_CONTESTED + 8*i, GILNEAS_BG_OBJECTID_AURA_C, GILNEAS_BG_NodePositions[i][0], GILNEAS_BG_NodePositions[i][1], GILNEAS_BG_NodePositions[i][2], GILNEAS_BG_NodePositions[i][3], 0, 0, sin(GILNEAS_BG_NodePositions[i][3]/2), cos(GILNEAS_BG_NodePositions[i][3]/2), RESPAWN_ONE_DAY))
        {
            sLog->outErrorDb("BattleForGilneas: Can't Create Some Object");
            return false;
        }
    }

    if (!AddObject(GILNEAS_BG_OBJECT_GATE_A_1, GILNEAS_BG_OBJECTID_GATE_A_1, GILNEAS_BG_DoorPositions[0][0], GILNEAS_BG_DoorPositions[0][1], GILNEAS_BG_DoorPositions[0][2], GILNEAS_BG_DoorPositions[0][3], GILNEAS_BG_DoorPositions[0][4], GILNEAS_BG_DoorPositions[0][5], GILNEAS_BG_DoorPositions[0][6], GILNEAS_BG_DoorPositions[0][7], RESPAWN_IMMEDIATELY)
        || !AddObject(GILNEAS_BG_OBJECT_GATE_A_2, GILNEAS_BG_OBJECTID_GATE_A_2, GILNEAS_BG_DoorPositions[1][0], GILNEAS_BG_DoorPositions[1][1], GILNEAS_BG_DoorPositions[1][2], GILNEAS_BG_DoorPositions[1][3], GILNEAS_BG_DoorPositions[1][4], GILNEAS_BG_DoorPositions[1][5], GILNEAS_BG_DoorPositions[1][6], GILNEAS_BG_DoorPositions[1][7], RESPAWN_IMMEDIATELY)
        || !AddObject(GILNEAS_BG_OBJECT_GATE_H_1, GILNEAS_BG_OBJECTID_GATE_H_1, GILNEAS_BG_DoorPositions[2][0], GILNEAS_BG_DoorPositions[2][1], GILNEAS_BG_DoorPositions[2][2], GILNEAS_BG_DoorPositions[2][3], GILNEAS_BG_DoorPositions[2][4], GILNEAS_BG_DoorPositions[2][5], GILNEAS_BG_DoorPositions[2][6], GILNEAS_BG_DoorPositions[2][7], RESPAWN_IMMEDIATELY)
        || !AddObject(GILNEAS_BG_OBJECT_GATE_H_2, GILNEAS_BG_OBJECTID_GATE_H_2, GILNEAS_BG_DoorPositions[3][0], GILNEAS_BG_DoorPositions[3][1], GILNEAS_BG_DoorPositions[3][2], GILNEAS_BG_DoorPositions[3][3], GILNEAS_BG_DoorPositions[3][4], GILNEAS_BG_DoorPositions[3][5], GILNEAS_BG_DoorPositions[3][6], GILNEAS_BG_DoorPositions[3][7], RESPAWN_IMMEDIATELY))
    {
        sLog->outErrorDb("BattleForGilneas: Can't Create Doors");
        return false;
    }

    // Buffs
    for (int i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
    {
        if (!AddObject(GILNEAS_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + 3 * i, Buff_Entries[0], GILNEAS_BG_BuffPositions[i][0], GILNEAS_BG_BuffPositions[i][1], GILNEAS_BG_BuffPositions[i][2], GILNEAS_BG_BuffPositions[i][3], 0, 0, sin(GILNEAS_BG_BuffPositions[i][3]/2), cos(GILNEAS_BG_BuffPositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + 3 * i + 1, Buff_Entries[1], GILNEAS_BG_BuffPositions[i][0], GILNEAS_BG_BuffPositions[i][1], GILNEAS_BG_BuffPositions[i][2], GILNEAS_BG_BuffPositions[i][3], 0, 0, sin(GILNEAS_BG_BuffPositions[i][3]/2), cos(GILNEAS_BG_BuffPositions[i][3]/2), RESPAWN_ONE_DAY)
            || !AddObject(GILNEAS_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE + 3 * i + 2, Buff_Entries[2], GILNEAS_BG_BuffPositions[i][0], GILNEAS_BG_BuffPositions[i][1], GILNEAS_BG_BuffPositions[i][2], GILNEAS_BG_BuffPositions[i][3], 0, 0, sin(GILNEAS_BG_BuffPositions[i][3]/2), cos(GILNEAS_BG_BuffPositions[i][3]/2), RESPAWN_ONE_DAY))
            sLog->outErrorDb("BattleForGilneas: Can't Create Buffs");
    }

    return true;
}

void BattlegroundBG::Reset()
{
    //call parent's class reset
    Battleground::Reset();

    _TeamScores[BG_TEAM_ALLIANCE]               = 0;
    _TeamScores[BG_TEAM_HORDE]                  = 0;
    _lastTick[BG_TEAM_ALLIANCE]                 = 0;
    _lastTick[BG_TEAM_HORDE]                    = 0;
    _HonorScoreTicks[BG_TEAM_ALLIANCE]          = 0;
    _HonorScoreTicks[BG_TEAM_HORDE]             = 0;
    _ReputationScoreTicks[BG_TEAM_ALLIANCE]     = 0;
    _ReputationScoreTicks[BG_TEAM_HORDE]        = 0;
    _IsInformedNearVictory                      = false;
    bool isBGWeekend = sBattlegroundMgr->IsBGWeekend(GetTypeID());
    _HonorTicks = (isBGWeekend) ? GILNEAS_BG_BGWeekendHonorTicks : GILNEAS_BG_NotBGWeekendHonorTicks;
    _ReputationTicks = (isBGWeekend) ? GILNEAS_BG_BGWeekendRepTicks : GILNEAS_BG_NotBGWeekendRepTicks;
    _TeamScores500Disadvantage[BG_TEAM_ALLIANCE] = false;
    _TeamScores500Disadvantage[BG_TEAM_HORDE]    = false;

    for (uint8 i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
    {
        _Nodes[i]       = 0;
        _prevNodes[i]   = 0;
        _NodeTimers[i]  = 0;
        _BannerTimers[i].timer = 0;
    }

    for (uint8 i = 0; i < GILNEAS_BG_ALL_NODES_COUNT + 3; ++i)// +3 for aura triggers
        if (BgCreatures[i])
            DelCreature(i);
}

void BattlegroundBG::UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor)
{
    BattlegroundScoreMap::iterator itr = PlayerScores.find(Source->GetGUID());

    if (itr == PlayerScores.end())      // player was not found...
        return;

    switch (type)
    {
        case SCORE_BASES_ASSAULTED:
            ((BattlegroundBGScore*)itr->second)->BasesAssaulted += value;
            Source->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE, BG_OBJECTIVE_ASSAULT_BASE);
            break;
        case SCORE_BASES_DEFENDED:
            ((BattlegroundBGScore*)itr->second)->BasesDefended += value;
            Source->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE, BG_OBJECTIVE_DEFEND_BASE);
            break;
        default:
            Battleground::UpdatePlayerScore(Source, type, value, doAddHonor);
            break;
    }
}

void BattlegroundBG::EndBattleground(uint32 winner)
{
    // Win reward
    if (winner == ALLIANCE)
        RewardHonorToTeam(GetBonusHonorFromKill(1), ALLIANCE);

    if (winner == HORDE)
        RewardHonorToTeam(GetBonusHonorFromKill(1), HORDE);

    // Complete map_end rewards (even if no team wins)
    RewardHonorToTeam(GetBonusHonorFromKill(1), HORDE);
    RewardHonorToTeam(GetBonusHonorFromKill(1), ALLIANCE);

    Battleground::EndBattleground(winner);
}

WorldSafeLocsEntry const* BattlegroundBG::GetClosestGraveYard(Player* player)
{
    BattlegroundTeamId teamIndex = GetTeamIndexByTeamId(player->GetTeam());

    // Is there any occupied node for this team?
    std::vector<uint8> nodes;
    for (uint8 i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
        if (_Nodes[i] == teamIndex + 3)
            nodes.push_back(i);

    WorldSafeLocsEntry const* good_entry = NULL;

    // If so, select the closest node to place ghost on
    if (!nodes.empty())
    {
        float player_x = player->GetPositionX();
        float player_y = player->GetPositionY();

        float mindist = 999999.0f; // Temp Hack
        for (uint8 i = 0; i < nodes.size(); ++i)
        {
            WorldSafeLocsEntry const* entry = sWorldSafeLocsStore.LookupEntry(GILNEAS_BG_GraveyardIds[nodes[i]]);

            if (!entry)
                continue;

            float dist = (entry->x - player_x)*(entry->x - player_x)+(entry->y - player_y)*(entry->y - player_y);

            if (mindist > dist)
            {
                mindist = dist;
                good_entry = entry;
            }
        }
        nodes.clear();
    }

    // If not, place ghost on starting location
    if (!good_entry)
        good_entry = sWorldSafeLocsStore.LookupEntry(GILNEAS_BG_GraveyardIds[teamIndex+3]);

    return good_entry;
}

bool BattlegroundBG::IsAllNodesConrolledByTeam(uint32 team) const
{
    uint32 count = 0;
    for (int i = 0; i < GILNEAS_BG_DYNAMIC_NODES_COUNT; ++i)
        if ((team == ALLIANCE && _Nodes[i] == GILNEAS_BG_NODE_STATUS_ALLY_OCCUPIED) || (team == HORDE && _Nodes[i] == GILNEAS_BG_NODE_STATUS_HORDE_OCCUPIED))
            ++count;

    return count == GILNEAS_BG_DYNAMIC_NODES_COUNT;
}
