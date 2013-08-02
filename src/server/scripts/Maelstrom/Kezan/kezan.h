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
    NPC_HOTROD                          = 34840,
    NPC_HIRED_LOOTER                    = 35234,
    NPC_GAPPY_SILVERTOOTH               = 35126,
    NPC_MISSA_SPEKKIES                  = 35130,
    NPC_SZABO                           = 35128,
};

enum Spells
{
    SPELL_KNOCKBACK                     = 66301,
    SPELL_LIGHTNING_VISUAL              = 45870,
    SPELL_HOTROD                        = 66392,
    SPELL_KICK_FOOTBOMB                 = 70051,
    SPELL_CATS_MARK_AURA_INVIS          = 70086,
    SPELL_EARTHQUAKE                    = 90615,
    SPELL_SOUND_DEATHWING               = 69988,
    SPELL_DEATHWING_ATTACK              = 66858,
    SPELL_PANICKED_CITIZEN_INVIS        = 90636,
    SPELL_SUMMON_DEATHWING              = 66322,
    SPELL_CREATE_ROBBING                = 67041,
    SPELL_CREATE_SHINY_BLING            = 66780,
    SPELL_CREATE_NEW_OUTFIT             = 66781,
    SPELL_CREATE_COOL_SHADES            = 66782,
    SPELL_OUTFIT_MALE                   = 66928,
    SPELL_OUTFIT_FEMALE                 = 66927,
    SPELL_OUTFIT_SECONDARY              = 66985,
    SPELL_AWESOME_PARTY                 = 66908,
    SPELL_COSMETIC_STUN                 = 46957,
    SPELL_DRUNKEN_STATE                 = 55664,
    SPELL_BUBBLY                        = 75042,
    SPELL_BUCKET                        = 75044,
    SPELL_DANCE                         = 75046,
    SPELL_FIREWORKS                     = 75048,
    SPELL_HORS_DEV                      = 75050,
    SPELL_HAPPY_GUEST                   = 66916, 
     SPELL_ENTER_VAULT                  = 67476,
    SPELL_VAULT_CRACKED                 = 67492,
    SPELL_VAULT_INTERACT                = 67555,
    SPELL_POWER_CORRECT                 = 67493,
    SPELL_POWER_INCORRECT               = 67494,
    SPELL_SUMMON_BUNNY_VEH              = 67488,
    SPELL_EMTEC_VEHICLE                 = 67579,
    SPELL_DRILL                         = 67495,
    SPELL_EXPLOSIVE                     = 67496,
    SPELL_GRAY                          = 67499,
    SPELL_LISTEN                        = 67497,
    SPELL_LOCKPICK                      = 67498,
    SPELL_TIMER                         = 67502,

    //VEHICLE SPELLS
    SPELL_GRAY_VEH                      = 67526,
    SPELL_LOCKPICK_VEH                  = 67525,
    SPELL_LISTEN_VEH                    = 67524,
    SPELL_DRILL_VEH                     = 67522,
    SPELL_EXPLOSIVE_VEH                 = 67508   

};

enum Objects
{
    GO_DEPOSIT                          = 195489,
    KEYS_TO_THE_HOTROD                  = 46856,
};

enum Quests
{
    QUEST_FOURTH_AND_GOAL_1             = 24503,
    QUEST_FOURTH_AND_GOAL_2             = 28414,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND     = 14069,
    QUEST_ROLLING_WITH_MY_HOMIES        = 14071,
    QUEST_THE_NEW_YOU                   = 14109,
    QUEST_LIFE_OF_THE_PARTY             = 14113,
    QUEST_PIRATE_PARTY                  = 14115,
};

#endif
