/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/> 
 * Copyright (C) 2011 TrilliumEMU <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
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

/* Script complete: 10% */

#ifndef DEF_FIRELANDS_H
#define DEF_FIRELANDS_H

enum Data
{
    DATA_INTRO_EVENT,       //ragnaros intro
    DATA_BETHTILAC_EVENT,
    DATA_RHYOLITH_EVENT,
    DATA_ALYSRAZAR_EVENT,
    DATA_SHANNOX_EVENT,
    DATA_BALOROC_EVENT,
    DATA_MAJORDOMUS_EVENT,
    DATA_RAGNAROS_CATA_EVENT,
};

enum Data64
{
    DATA_INTRO,            //ragnaros intro
    DATA_BETHTILAC,
    DATA_RHYOLITH,
    DATA_ALYSRAZAR,
    DATA_SHANNOX,
    DATA_BALOROC,
    DATA_MAJORDOMUS,
    DATA_RAGNAROS_CATA,
};

enum creatures
{
    //bosses
    BOSS_BETHTILAC         = 52498,
    BOSS_RHYOLITH          = 52558,
    BOSS_ALYSRAZAR         = 52530,
    BOSS_SHANNOX           = 53691,
    BOSS_BALOROC           = 53494,
    BOSS_MAJORDOMUS        = 52571, //54015 <-- maybe this entry
    BOSS_RAGNAROS_CATA     = 52409,

    //other npc's
    NPC_SULFURAS           = 53420, //ragnaros boss weapon
    NPC_LIVING_METEOR      = 53500,
    NPC_MOLTEN_ELEMENTAR   = 53189,
};

enum DataVar
{
    DATA_PHASE,
};

enum MovePoints
{
    POINT_RAGNAROS_DOWN         //end of each phase
    POINT_RAGNAROS_UP           //start of each next phase
    POINT_RAGNAROS_STANDUP      //only on heroic mode
    POINT_SULFURAS_SMASH        //target for smashes
};

enum Actions
{
    ACTION_RAGNAROS_DOWN       //end of each phase
    ACTION_RAGNAROS_UP         //start of each next phase
    ACTION_RAGNAROS_STANDUP    //only on heroic mode
    ACTION_SULFURAS_SMASH      //target for smashes
};

#endif
