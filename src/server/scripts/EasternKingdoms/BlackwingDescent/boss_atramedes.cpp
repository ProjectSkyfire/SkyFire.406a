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

#include "ScriptPCH.h"
#include "blackwing_descent.h"

class boss_atramedes : public CreatureScript
{
public:
    boss_atramedes() : CreatureScript("boss_atramedes") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_atramedesAI (creature);
    }

    struct boss_atramedesAI : public ScriptedAI
    {
        boss_atramedesAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset() { }

        void EnterCombat(Unit* /*who*/) {}

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_ATRAMEDES, DONE);
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_atramedes()
{
    new boss_atramedes();
}
