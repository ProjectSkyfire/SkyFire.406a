/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#ifndef RUBY_SANCTUM_H_
#define RUBY_SANCTUM_H_

#include "SpellScript.h"
#include "Map.h"
#include "Creature.h"

#define RSScriptName "instance_ruby_sanctum"
uint32 const EncounterCount = 4;

Position const HalionControllerSpawnPos = {3156.037f, 533.2656f, 72.97205f, 0.0f};

enum DataTypes
{
    // Encounter States/Boss GUIDs
    DATA_BALTHARUS_THE_WARBORN              = 0,
    DATA_GENERAL_ZARITHRIAN                 = 1,
    DATA_SAVIANA_RAGEFIRE                   = 2,
    DATA_HALION                             = 3,
    DATA_HALION_TWILIGHT                    = 4,
    // Etc
    DATA_XERESTRASZA                        = 5,
    DATA_CRYSTAL_CHANNEL_TARGET             = 6,
    DATA_BALTHARUS_SHARED_HEALTH            = 7,
    DATA_ZARITHIAN_SPAWN_STALKER_1          = 8,
    DATA_ZARITHIAN_SPAWN_STALKER_2          = 9,
    DATA_HALION_CONTROLLER                  = 10,
    DATA_BURNING_TREE_1                     = 11,
    DATA_BURNING_TREE_2                     = 12,
    DATA_BURNING_TREE_3                     = 13,
    DATA_BURNING_TREE_4                     = 14,
    DATA_FLAME_RING                         = 15,
    DATA_HALION_EVENT                       = 16,
    DATA_ORB_DIRECTION                      = 17,
    DATA_ORB_S                              = 18,
    DATA_ORB_N                              = 19,
};

enum SharedActions
{
    ACTION_INTRO_BALTHARUS                  = -3975101,
    ACTION_BALTHARUS_DEATH                  = -3975102,
    ACTION_INTRO_HALION                     = -4014601,
};

enum CreaturesIds
{
    // Baltharus the Warborn
    NPC_BALTHARUS_THE_WARBORN               = 39751,
    NPC_BALTHARUS_THE_WARBORN_CLONE         = 39899,
    NPC_BALTHARUS_TARGET                    = 26712,

    // General Zarithrian
    NPC_GENERAL_ZARITHRIAN                  = 39746,
    NPC_ONYX_FLAMECALLER                    = 39814,
    NPC_ZARITHIAN_SPAWN_STALKER             = 39794,

    // Saviana Ragefire
    NPC_SAVIANA_RAGEFIRE                    = 39747,

    // Halion
    NPC_HALION                              = 39863,
    NPC_HALION_TWILIGHT                     = 40142,
    NPC_HALION_CONTROLLER                   = 40146,
    NPC_LIVING_INFERNO                      = 40681,
    NPC_LIVING_EMBER                        = 40683,

    // meteorstrike
    NPC_COMBUSTION                          = 40001,
    NPC_METEOR_STRIKE_MARK                  = 40029,
    NPC_METEOR_STRIKE_NORTH                 = 40041,
    NPC_METEOR_STRIKE_EAST                  = 40042,
    NPC_METEOR_STRIKE_WEST                  = 40043,
    NPC_METEOR_STRIKE_SOUTH                 = 40044,
    NPC_METEOR_STRIKE_FLAME                 = 40055,

    // Orb rotation
    NPC_SHADOW_PULSAR_N                     = 40083, //spinning orb N spawn
    NPC_SHADOW_PULSAR_S                     = 40100, //spinning orb S spawn
    NPC_SHADOW_PULSAR_E                     = 40468, //spinning orb E spawn
    NPC_SHADOW_PULSAR_W                     = 40469, //spinning orb W spawn
    NPC_ORB_CARRIER                         = 40081,
    NPC_ORB_ROTATION_FOCUS                  = 40091,
    NPC_SHADOW_ORB_N                        = 40083,
    NPC_SHADOW_ORB_S                        = 40100,

    TYPE_COUNTER                            = 6, // for WorldUpdateState
    COUNTER_OFF                             = 255,

    // Xerestrasza
    NPC_XERESTRASZA                         = 40429,
};

enum GameObjectsIds
{
    GO_HALION_PORTAL_1                      = 202794,   // Unknown spell 75074, should be somehow be linked to 74807
    GO_HALION_PORTAL_2                      = 202795,   // Also spell 75074
    GO_HALION_PORTAL_EXIT                   = 202796,   // Leave Twilight Realm (74812)
    GO_FIRE_FIELD                           = 203005,
    GO_FLAME_WALLS                          = 203006,
    GO_FLAME_RING                           = 203007,
    GO_BURNING_TREE_1                       = 203034,
    GO_BURNING_TREE_2                       = 203035,
    GO_BURNING_TREE_3                       = 203036,
    GO_BURNING_TREE_4                       = 203037,
};

enum AchievementData
{
    TWILIGHT_DESTROYER_NORMAL_10            = 4817,
    TWILIGHT_DESTROYER_NORMAL_25            = 4815,
    TWILIGHT_DESTROYER_HEROIC_10            = 4818,
    TWILIGHT_DESTROYER_HEROIC_25             = 4816
};

enum WorldStatesRS
{
    WORLDSTATE_CORPOREALITY_MATERIAL        = 5049,
    WORLDSTATE_CORPOREALITY_TWILIGHT        = 5050,
    WORLDSTATE_CORPOREALITY_TOGGLE          = 5051,
};

template<class AI>
CreatureAI* GetRubySanctumAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(RSScriptName))
                return new AI(creature);
    return NULL;
}

#endif // RUBY_SANCTUM_H_
