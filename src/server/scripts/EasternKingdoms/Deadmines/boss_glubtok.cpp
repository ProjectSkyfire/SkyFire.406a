/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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

#include "ScriptPCH.h"
#include "deadmines.h"

enum eSpels
{
    SPELL_ARCANE_POWER      = 88009,
    SPELL_FIST_OF_FLAME     = 87859,
    SPELL_FIST_OF_FROST     = 87861,
    SPELL_FIRE_BLOSSOM      = 88129,
    SPELL_FIRE_BLOSSOM_H    = 91286,
    SPELL_FROST_BLOSSOM     = 88169,
    SPELL_FROST_BLOSSOM_H   = 91287
};

class boss_glubtok : public CreatureScript
{
public:
    boss_glubtok() : CreatureScript("boss_glubtok") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_glubtokAI (creature);
    }

    struct boss_glubtokAI : public ScriptedAI
    {
        boss_glubtokAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 TrashTimer;
        uint32 SlamTimer;
        uint32 NimbleReflexesTimer;

        uint8 Health;

        uint32 Phase;
        uint32 Timer;
        // TODO: MAKE THE CORRECT SCRIPT :)
    };
};

void AddSC_boss_glubtok()
{
    new boss_glubtok();
}