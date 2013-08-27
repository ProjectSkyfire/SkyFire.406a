/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
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

#ifndef _KEZAN_H
#define _KEZAN_H

enum Creatures
{
    NPC_ACE                             = 34957,
    NPC_IZZY                            = 34959,
    NPC_GOBBLER                         = 34958,
    NPC_CITIZEN                         = 35075,
    NPC_HOTROD                          = 34840, //used with Quest 28607, 14071
    NPC_HOTROD_2                        = 37676, //not much info on this npc - still researching
    NPC_GOLBIN_HOTROD                   = 49131, //not much info on this npc - still researching
    NPC_HIRED_LOOTER                    = 35234,
    NPC_BILGEWATER_BUCCANEER            = 48526,
    NPC_GAPPY_SILVERTOOTH               = 35126,
    NPC_MISSA_SPEKKIES                  = 35130,
    NPC_SZABO                           = 35128,
};

enum Spells
{

    SPELL_LIGHTNING_VISUAL              = 45870,
    SPELL_KICK_FOOTBOMB                 = 70051,
    SPELL_CATS_MARK_AURA_INVIS          = 70086,
    SPELL_EARTHQUAKE                    = 90615,
    SPELL_SOUND_DEATHWING               = 69988,
    SPELL_DEATHWING_ATTACK              = 66858,
    SPELL_SUMMON_DEATHWING              = 66322,
    SPELL_CREATE_ROBBING                = 67041,
    SPELL_CREATE_SHINY_BLING            = 66780,
    SPELL_CREATE_NEW_OUTFIT             = 66781,
    SPELL_CREATE_COOL_SHADES            = 66782,
    SPELL_PANICKED_CITIZEN_INVIS        = 90636, //  Fourth and Goal

    // Quest 28607,14071,14126: Keys To The Hot Rod | Rolling With My Homies | Life Savings
    SPELL_RWMH_SUMMON_HOTROD            = 66393,
    SPELL_RWMH_KNOCKBACK_HOTROD         = 66301,   
    //NYI
    /*
    SPELL_RWMH_EXIT_HOTROD              = 66611,
    SPELL_RWMH_SUMMON_ACE               = 66597,
    SPELL_RWMH_SUMMON_GOBBER            = 66599,
    SPELL_RWMH_SUMMON_IZZY              = 66600,
    SPELL_RWMH_INVISIBILITY_1           = 66403, "Ace"
    SPELL_RWMH_INVISIBILITY_2           = 66404, "Gobber"
    SPELL_RWMH_INVISIBILITY_3           = 66405, "Izzy"
    SPELL_RWMH_RESUMMON_ACE             = 66644,
    SPELL_RWMH_RESUMMON_GOBBER          = 66645,
    SPELL_RWMH_RESUMMON_IZZY            = 66646,

    SPELL_LS_HAND_OVER_THE_KEYS         = 70318,
    SPELL_LS__FORCED_CAST-SUMMON_THE_HOTROD = 70319,
    SPELL_LS_SUMMON_THE_HOTROD          = 70321,
    SPELL_LS_HOTROD_SKID                = 70325,
    SPELL_LS_HOTROD_KNOCKBACK_TRIGGER   = 70329,
    SPELL_LS_HOTROD_KNOCKBACK           = 70330,
    SPELL_LS_QUEST_COMPLETE             = 91847,
    SPELL_LS_ROPE_LADDER_1              = 70390,
    SPELL_LS_ROPE_LADDER_2              = 70389,  - Cover
    SPELL_LAST_CHANCE_YACHT_BOARDING    = 92629,  - Cover
    SPELL_PORT_AND_BIND_TO_LOST_ISLES   = 74100
    */
    
    // Extras
    SPELL_KEYS_TO_THE_HOTROD            = 91551,
    SPELL_HOTROD                        = 66392,

 // Quest 14113: life of the party (Chain)
    SPELL_OUTFIT_MALE                   = 66928,
    SPELL_OUTFIT_FEMALE                 = 66927,
    SPELL_OUTFIT_SECONDARY              = 66985,
    SPELL_PAPARAZZI                     = 66929,
    SPELL_AWESOME_PARTY                 = 66908,
    SPELL_COSMETIC_STUN                 = 46957,
    SPELL_DRUNKEN_STATE                 = 55664,
    SPELL_SUMMON_DISCO_BALL             = 66930,
    SPELL_BUBBLY_PC_LOTP                = 75122,
    SPELL_BUBBLY_1                      = 75042,
    SPELL_BUBBLY_2                      = 66909,
    SPELL_SUMMON_BUCKET_PC_LOTP         = 66931,
    SPELL_BUCKET_1                      = 75044,
    SPELL_BUCKET_2                      = 66910,
    SPELL_DANCE_PC_LOTP                 = 75123,
    SPELL_DANCE_1                       = 75046,
    SPELL_DANCE_2                       = 66911,
    SPELL_FIREWORKS_1                   = 75048,
    SPELL_FIREWORKS_2                   = 66912,
    SPELL_FIREWORKS_BLUE                = 66917,
    SPELL_FIREWORKS_GREEN               = 66918,
    SPELL_FIREWORKS_RED                 = 66919,
    SPELL_HORS_PC_LOTP                  = 75124,
    SPELL_HORS_DEV_1                    = 75050,
    SPELL_HORS_DEV_2                    = 66913,
    SPELL_HAPPY_GUEST                   = 66916,
    SPELL_LOTP_PHASE_2                  = 59073,
    SPELL_LOTP_PHASE_4                  = 59074,

    // Quest 14122: The Great Bank Heist
    SPELL_ENTER_VAULT                   = 67476,
    SPELL_VAULT_CRACKED                 = 67492,
    SPELL_VAULT_INTERACT                = 67555,
    SPELL_POWER_CORRECT                 = 67493,
    SPELL_POWER_INCORRECT               = 67494,
    SPELL_SUMMON_BUNNY_VEH              = 67488,
    SPELL_EXIT_VEHICLE                  = 67579,
    SPELL_BUNNY_1                       = 67495, // Drill Aura
    SPELL_BUNNY_2                       = 67496, // Explosives Aura
    SPELL_BUNNY_3                       = 67499, // G-Ray Aura
    SPELL_BUNNY_4                       = 67497, // Listen Aura
    SPELL_BUNNY_5                       = 67498, // Lockpick Aura
    SPELL_TIMER                         = 67502,

    //VEHICLE SPELLS
    SPELL_AMAZING_G_RAY                 = 67526,
    SPELL_INFINIFOLD_LOCKPICK           = 67525,
    SPELL_EAR_O_SCOPE                   = 67524,
    SPELL_KAJA_MITE_DRILL               = 67522,
    SPELL_BLASTCRACKERS                 = 67508

};

enum Objects
{
    GO_DEPOSIT                          = 202593,
//NYI     QUEST_ITEM_KEYS_TO_THE_HOTROD       = 46856,
//NYI     QUEST_ITEM_LIFE_SAVINGS             = 49866,

};

enum Quests
{
    QUEST_FOURTH_AND_GOAL_1             = 24503,
    QUEST_FOURTH_AND_GOAL_2             = 28414,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND     = 14069,
    QUEST_THE_NEW_YOU                   = 14109,
    QUEST_LIFE_OF_THE_PARTY             = 14113,
    QUEST_PIRATE_PARTY                  = 14115,
//NYI   QUEST_KEYS_TO_THE_HOTROD            = 28606, // not much info on this one,
    QUEST_KEYS_TO_THE_HOTROD            = 28607, // Returns lost keys to players during QUEST_ROLLING_WITH_MY_HOMIES
    QUEST_ROLLING_WITH_MY_HOMIES        = 14071,
//NYI   QUEST_LIFE_SAVINGS                  = 14126,

};

#endif
