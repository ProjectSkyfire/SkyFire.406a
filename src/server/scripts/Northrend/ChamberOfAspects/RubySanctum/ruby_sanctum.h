/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef DEF_RUBY_SANCTUM_H
#define DEF_RUBY_SANCTUM_H

enum
{
    MAX_ENCOUNTERS		= 6,

    TYPE_EVENT			= 0,
    TYPE_RAGEFIRE		= 1,
    TYPE_BALTHARUS		= 2,
    TYPE_XERESTRASZA	= 3,
    TYPE_ZARITHRIAN		= 4,
    TYPE_HALION			= 5,

    TYPE_COUNTER		= 6, // for WorldUpdateState
    TYPE_HALION_EVENT	= 7,
    COUNTER_OFF			= 255,

    TYPE_EVENT_TIMER	= 50,
    TYPE_EVENT_NPC		= 51,

    NPC_HALION_REAL		= 39863, // Halion Physical Realm NPC
    NPC_HALION_TWILIGHT	= 40142, // Halion Twilight Realm NPC
    NPC_HALION_CONTROL	= 40146,

    NPC_BALTHARUS		= 39751,
    NPC_CLONE			= 39899,
    NPC_ZARITHIAN		= 39746,
    NPC_RAGEFIRE		= 39747,

    NPC_XERESTRASZA		= 40429,

    NPC_BALTHARUS_TARGET			= 26712,
    NPC_ZARITHIAN_SPAWN_STALKER		= 39794,

    // Orb rotation
    NPC_SHADOW_PULSAR_N = 40083, //spinning orb N spawn
    NPC_SHADOW_PULSAR_S = 40100, //spinning orb S spawn
    NPC_SHADOW_PULSAR_E = 40468, //spinning orb E spawn
    NPC_SHADOW_PULSAR_W = 40469, //spinning orb W spawn
    NPC_ORB_CARRIER					= 40081,
    NPC_ORB_ROTATION_FOCUS			= 40091,

    GO_HALION_PORTAL_1				= 202794, //1327 ENTRY
    GO_HALION_PORTAL_2				= 202795, //1327 ENTRY
    GO_HALION_PORTAL_3				= 202796, //1327 EXIT

    GO_FIRE_FIELD					= 203005,
    GO_FLAME_WALLS					= 203006,
    GO_FLAME_RING					= 203007,

    DATA_EVENT_TIMER				= 101,
    DATA_EVENT						= 102,

    DATA_ORB_DIRECTION				= 110,
    DATA_ORB_S						= 111,
    DATA_ORB_N						= 112,
};

enum uiWorldStates
{
    UPDATE_STATE_UI_COUNT_R			= 5050,
    UPDATE_STATE_UI_COUNT_T			= 5050,
    UPDATE_STATE_UI_SHOW			= 5051,
};

#endif