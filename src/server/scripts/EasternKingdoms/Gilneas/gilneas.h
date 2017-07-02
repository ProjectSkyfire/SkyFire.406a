/*
 * Copyright (C) 2011-2017 Project SkyFire <http://www.projectskyfire.org/>
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

#ifndef DEF_GILNEAS_H
#define DEF_GILNEAS_H

enum Data
{
};

enum Data64
{
};

enum CreatureIds
{
    NPC_PRINCE_LIAM_GREYMANE                          = 34913,
    NPC_GILNEAS_CITY_GUARD                            = 34916,
    NPC_RAMPAGING_WORGEN_1                            = 34884,
    NPC_RAMPAGING_WORGEN_2                            = 35660,
    NPC_BLOODFANG_WORGEN                              = 35118,
    NPC_SERGEANT_CLEESE                               = 35839,
    NPC_MYRIAM_SPELLWALKER                            = 35872,
    NPC_GILNEAN_ROYAL_GUARD                           = 35232,
    NPC_FRIGHTENED_CITIZEN_1                          = 34981,
    NPC_FRIGHTENED_CITIZEN_2                          = 35836,
    NPC_DARIUS_CROWLEY                                = 35230,
    NPC_NORTHGATE_REBEL_1                             = 36057, // phase 8 outside cathedral
    NPC_NORTHGATE_REBEL_2                             = 41015, // phase 1024 inside cathedral
    NPC_BLOODFANG_STALKER_C1                          = 35229, // Main spawns
    NPC_BLOODFANG_STALKER_C2                          = 51277,
    NPC_BLOODFANG_STALKER_CREDIT                      = 35582,
    NPC_CROWLEY_HORSE                                 = 35231,
    NPC_LORD_DARIUS_CROWLEY_C1                        = 35077, // Quest - By the skin of his teeth start/stop
    NPC_WORGEN_ALPHA_C1                               = 35170, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_ALPHA_C2                               = 35167, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_RUNT_C1                                = 35188, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_RUNT_C2                                = 35456, // Quest - By the skin of his teeth spawns
    NPC_SEAN_DEMPSEY                                  = 35081, // Quest - By the skin of his teeth controller= 35370,
    NPC_JOSIAH_AVERY_P4                               = 35370, // NPC for worgen bite
    NPC_JOSIAH_AVERY_TRIGGER                          = 50415, // Controller for Worgen Bite
    NPC_LORNA_CROWLEY_P4                              = 35378, // Quest - From the Shadows
    NPC_BLOODFANG_RIPPER_P4                           = 35505, // General AI spawns
    NPC_GILNEAN_MASTIFF                               = 35631,
    NPC_GILNEAS_CITY_GUARD_P8                         = 50474,
    NPC_AFFLICTED_GILNEAN_P8                          = 50471,
    NPC_COMMANDEERED_CANNON                           = 35914,
    NPC_KRENNAN_ARANAS_TREE                           = 35753,
    NPC_GREYMANE_HORSE_P4                             = 35905
};

enum GameObjectIds
{
};

enum QuestIds
{
    QUEST_LOCKDOWN                                     = 14078,
    QUEST_EVAC_MERC_SQUA                               = 14098,
    QUEST_SOMETHINGS_AMISS                             = 14091,
    QUEST_ALL_HELL_BREAKS_LOOSE                        = 14093,
    QUEST_ROYAL_ORDERS                                 = 14099,
    QUEST_BY_THE_SKIN_ON_HIS_TEETH                     = 14154,
    QUEST_SAVE_KRENNAN_ARANAS                          = 14293,
    QUEST_SACRIFICES                                   = 14212,
    QUEST_THE_REBEL_LORDS_ARSENAL                      = 14159,
    QUEST_FROM_THE_SHADOWS                             = 14204,
    QUEST_YOU_CANT_TAKE_EM_ALONE                       = 14348
};

enum QuestKC
{
    QUEST_14348_KILL_CREDIT                            = 36233
};

enum SpellIds
{
    SPELL_ENRAGE                                       = 8599,
    SPELL_FROSTBOLT_VISUAL_ONLY                        = 74277, // Dummy spell, visual only
    SPELL_SUMMON_CROWLEY                               = 67004,
    SPELL_RIDE_HORSE                                   = 43671,
    SPELL_THROW_TORCH                                  = 67063,
    SPELL_RIDE_VEHICLE_HARDCODED                       = 46598,
    SPELL_LEFT_HOOK                                    = 67825,
    SPELL_DEMORALIZING_SHOUT                           = 61044,
    SPELL_SNAP_KICK                                    = 67827,
    SPELL_BY_THE_SKIN_ON_HIS_TEETH                     = 66914,
    SPELL_SHOOT                                        = 6660,
    SPELL_WORGEN_BITE                                  = 72870,
    SPELL_INFECTED_BITE                                = 72872,
    SPELL_CANNON_FIRE                                  = 68235,
    SPELL_GILNEAS_CANNON_CAMERA                        = 93555,
    SPELL_SUMMON_JOSIAH_AVERY                          = 67350,
    SPELL_GET_SHOT                                     = 67349,
    SPELL_SUMMON_JOSIAH                                = 67350,
    SPELL_PULL_TO                                      = 67357,
    SPELL_PHASE_QUEST_2                                = 59073,
    SPELL_SUMMON_GILNEAN_MASTIFF                       = 67807,
    SPELL_DISMISS_GILNEAN_MASTIFF                      = 43511,
    SPELL_ATTACK_LURKER                                = 67805,
    SPELL_SHADOWSTALKER_STEALTH                        = 5916,
    SPELL_PING_GILNEAN_CROW                            = 93275,
    SPELL_BARREL_KEG                                   = 69094
};

enum NpcTextIds
{
    SAY_PRINCE_LIAM_GREYMANE_1                         = -1638000,
    SAY_PRINCE_LIAM_GREYMANE_2                         = -1638001,
    SAY_PRINCE_LIAM_GREYMANE_3                         = -1638002,
    DELAY_SAY_PRINCE_LIAM_GREYMANE                     = 20000, // 20 seconds repetition time

    YELL_PRINCE_LIAM_GREYMANE_1                        = -1638025,
    YELL_PRINCE_LIAM_GREYMANE_2                        = -1638026,
    YELL_PRINCE_LIAM_GREYMANE_3                        = -1638027,
    YELL_PRINCE_LIAM_GREYMANE_4                        = -1638028,
    YELL_PRINCE_LIAM_GREYMANE_5                        = -1638029,
    DELAY_YELL_PRINCE_LIAM_GREYMANE                    = 2000,

    SAY_PANICKED_CITIZEN_1                             = -1638016,
    SAY_PANICKED_CITIZEN_2                             = -1638017,
    SAY_PANICKED_CITIZEN_3                             = -1638018,
    SAY_PANICKED_CITIZEN_4                             = -1638019,

    SAY_GILNEAS_CITY_GUARD_GATE_1                      = -1638022,
    SAY_GILNEAS_CITY_GUARD_GATE_2                      = -1638023,
    SAY_GILNEAS_CITY_GUARD_GATE_3                      = -1638024,

    SAY_CITIZEN_1                                      = -1638003,
    SAY_CITIZEN_2                                      = -1638004,
    SAY_CITIZEN_3                                      = -1638005,
    SAY_CITIZEN_4                                      = -1638006,
    SAY_CITIZEN_5                                      = -1638007,
    SAY_CITIZEN_6                                      = -1638008,
    SAY_CITIZEN_7                                      = -1638009,
    SAY_CITIZEN_8                                      = -1638010,
    SAY_CITIZEN_1b                                     = -1638011,
    SAY_CITIZEN_2b                                     = -1638012,
    SAY_CITIZEN_3b                                     = -1638013,
    SAY_CITIZEN_4b                                     = -1638014,
    SAY_CITIZEN_5b                                     = -1638015,

    SAY_KRENNAN_C2                                     = 0,
    SAY_GREYMANE_HORSE                                 = 0,
    SAY_CROWLEY_HORSE_1                                = 0,    // Let''s round up as many of them as we can.  Every worgen chasing us is one less worgen chasing the survivors!
    SAY_CROWLEY_HORSE_2                                = 1,    // You'll never catch us, you blasted mongrels! || Come and get us, you motherless beasts! || Over here, you flea bags!
    SAY_JOSIAH_AVERY_P2                                = 1,
    SAY_JOSAIH_AVERY_P4                                = 1,
    SAY_JOSAIH_AVERY_TRIGGER                           = 1,
    SAY_LORNA_CROWLEY_P4                               = 0,
    SAY_KING_GENN_GREYMANE_P4                          = 1,
    SAY_GILNEAS_CITY_GUARD_P8                          = 1,
    SAY_LORD_GODFREY_P4                                = 0,
    SAY_NPC_KRENNAN_ARANAS_TREE                        = 0
};

enum SoundIds
{
    SOUND_SWORD_FLESH                                 = 143,
    SOUND_SWORD_PLATE                                 = 147,
    SOUND_WORGEN_ATTACK                               = 558,
    DELAY_SOUND                                       = 500,
    DELAY_ANIMATE                                     = 2000
};

struct Waypoint
{
    float X, Y, Z;
};

Waypoint NW_WAYPOINT_LOC1[2]=
{
    { -1630.62f, 1480.55f, 70.40f }, // Worgen Runt 1 top edge of Roof Waypoint
    { -1636.01f, 1475.81f, 64.51f }  // Worgen Runt 1 Edge of Roof Waypoint
};

Waypoint NW_WAYPOINT_LOC2[2]=
{
    { -1637.26f, 1488.86f, 69.95f }, // Worgen Runt 1 top edge of Roof Waypoint
    { -1642.45f, 1482.23f, 64.30f }  // Worgen Runt 1 Edge of Roof Waypoint
};

Waypoint SW_WAYPOINT_LOC1[2]=
{
    { -1718.31f, 1526.62f, 55.91f }, // Worgen Runt 2 Corner where we turn
    { -1717.86f, 1490.77f, 56.61f }  // Worgen Runt 2 Edge of Roof Waypoint
};

Waypoint SW_WAYPOINT_LOC2[2]=
{
    { -1718.31f, 1526.62f, 55.91f }, // Worgen Alpha 1 Corner where we turn
    { -1717.86f, 1487.00f, 57.07f }  // Worgen Alpha 1 Edge of Roof Waypoint
};

Waypoint N_WAYPOINT_LOC[1]=
{
    { -1593.38f, 1408.02f, 72.64f } // Worgen Runt 2 Edge of Roof Waypoint
};

// Q.14348 These need moved to Db at first chance...
// Start
#define SAY_BARREL_1 "I gots bad feeling...."
#define SAY_BARREL_2 "GAH! I CAN'T SEE IN HERE!"
#define SAY_BARREL_3 "Get back here! I smashes you!"
#define SAY_BARREL_4 "Uh-oh... this gonna hurts me..."
#define SAY_BARREL_5 "Barrel smell like gunpowder..."
#define SAY_BARREL_6 "This not be good..."
// End

#define DELAY_EMOTE_PANICKED_CITIZEN                  urand(5000, 15000)   // 5-15 second time
#define DELAY_SAY_PANICKED_CITIZEN                    urand(30000, 120000) // 30sec - 1.5min
#define DELAY_SAY_GILNEAS_CITY_GUARD_GATE             urand(30000, 120000) // 30sec - 1.5min
#define PATHS_COUNT_PANICKED_CITIZEN                  8
#define CD_ENRAGE                                     30000
#define SUMMON1_TTL                                   300000
#define PATHS_COUNT                                   2
#define DOOR_TIMER                                    30*IN_MILLISECONDS
#define KRENNAN_END_X                                 -1772.4172f
#define KRENNAN_END_Y                                 1430.6125f
#define KRENNAN_END_Z                                 19.79f
#define KRENNAN_END_O                                 2.79f
#define CROWLEY_SPEED                                 1.85f // if set much lower than this, the horse automatically despawns before reaching the end of his waypoints
#define AI_MIN_HP                                     85
#define Event_Time                                    118500
#define WORGEN_EVENT_SPAWNTIME                        20000 // Default Despawn Timer
#define NW_ROOF_SPAWN_LOC_1                           -1618.86f, 1505.68f, 70.24f, 3.91f
#define NW_ROOF_SPAWN_LOC_2                           -1611.40f, 1498.49f, 69.82f, 3.79f
#define SW_ROOF_SPAWN_LOC_1                           -1732.81f, 1526.34f, 55.39f, 0.01f
#define SW_ROOF_SPAWN_LOC_2                           -1737.49f, 1526.11f, 55.51f, 0.01f
#define N_ROOF_SPAWN_LOC                              -1562.59f, 1409.35f, 71.66f, 3.16f
#define PLATFORM_Z                                    52.29f

#endif
