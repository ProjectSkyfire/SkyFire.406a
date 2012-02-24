/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2011 MigCore <http://wow-mig.ru/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
#include "bastion_of_twilight.h"

class boss_valiona : public CreatureScript
{
public:
    boss_valiona() : CreatureScript("boss_valiona") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_valionaAI (creature);
    }

    struct boss_valionaAI : public ScriptedAI
    {
        boss_valionaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            instance->SetData(DATA_THERALION_ANA_VALIONA, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(DATA_THERALION_ANA_VALIONA, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_THERALION_ANA_VALIONA, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_theralion_and_valiona()
{
    new boss_valiona();
}