/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2011 MigCore <http://wow-mig.ru/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

class boss_elementium_monstrosity : public CreatureScript
{
public:
    boss_elementium_monstrosity() : CreatureScript("boss_elementium_monstrosity") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_elementium_monstrosityAI (creature);
    }

    struct boss_elementium_monstrosityAI : public ScriptedAI
    {
        boss_elementium_monstrosityAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            pInstance->SetData(DATA_ASCENDANT_COUNCIL, NOT_STARTED);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            pInstance->SetData(DATA_ASCENDANT_COUNCIL, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            pInstance->SetData(DATA_ASCENDANT_COUNCIL, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_assembly_of_ascendents()
{
    new boss_elementium_monstrosity();
}