/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2013 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#ifndef DEF_MAGISTERS_TERRACE_H
#define DEF_MAGISTERS_TERRACE_H

enum Data
{
    DATA_SELIN_EVENT            = 1,
    DATA_VEXALLUS_EVENT         = 2,
    DATA_DELRISSA_EVENT         = 3,
    DATA_KAELTHAS_EVENT         = 4,

    DATA_SELIN                  = 5,
    DATA_FEL_CRYSTAL            = 6,
    DATA_FEL_CRYSTAL_SIZE       = 7,

    DATA_VEXALLUS_DOOR          = 8,
    DATA_SELIN_DOOR             = 9,
    DATA_DELRISSA               = 10,
    DATA_DELRISSA_DOOR          = 11,
    DATA_SELIN_ENCOUNTER_DOOR   = 12,

    DATA_KAEL_DOOR              = 13,
    DATA_KAEL_STATUE_LEFT       = 14,
    DATA_KAEL_STATUE_RIGHT      = 15,

    DATA_DELRISSA_DEATH_COUNT   = 16
};

#define ERROR_INST_DATA      "TSCR Error: Instance Data not set properly for Magister's Terrace instance (map 585). Encounters will be buggy."

#endif
