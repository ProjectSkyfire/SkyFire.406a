/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2013 MaNGOS <http://getmangos.com/>
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

#ifndef DEADMINES_H
#define DEADMINES_H

enum CannonState
{
    CANNON_NOT_USED,
    CANNON_GUNPOWDER_USED,
    CANNON_BLAST_INITIATED,
    PIRATES_ATTACK,
    EVENT_DONE
};

enum Data
{
    EVENT_STATE,
    EVENT_GLUBTOK
};

enum Data64
{
    DATA_SMITE_CHEST
};

enum GameObjects
{
    GO_FACTORY_DOOR                 = 13965,
    GO_IRONCLAD_DOOR                = 16397,
    GO_DEFIAS_CANNON                = 16398,
    GO_DOOR_LEVER                   = 101833,
    GO_MR_SMITE_CHEST               = 144111
};

#endif
