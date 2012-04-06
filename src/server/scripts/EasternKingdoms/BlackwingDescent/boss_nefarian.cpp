/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
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

enum eSpells
{
    SPELL_SHADOWFLAME_BREATH        = 94126,
    SPELL_SHADOW_COWARDICE          = 79353
};

class boss_bd_nefarian : public CreatureScript
{
public:
    boss_bd_nefarian() : CreatureScript("boss_bd_nefarian") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bd_nefarianAI (creature);
    }

    struct boss_bd_nefarianAI : public ScriptedAI
    {
        boss_bd_nefarianAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 ShadowflameBreathTimer;
        uint32 ShadowCowardiceTimer;

        void Reset()
        {
            ShadowflameBreathTimer = 10*IN_MILLISECONDS;
            ShadowCowardiceTimer = 13*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(DATA_NEFARIAN, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_NEFARIAN, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if (ShadowflameBreathTimer <= Diff)
            {
                me->CastSpell(me->getVictim(), SPELL_SHADOWFLAME_BREATH, true);

                ShadowflameBreathTimer = urand(10*IN_MILLISECONDS, 12*IN_MILLISECONDS);
            } else ShadowflameBreathTimer -= Diff;

            if (ShadowCowardiceTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_SHADOW_COWARDICE , true);

                ShadowCowardiceTimer = urand(8*IN_MILLISECONDS, 9*IN_MILLISECONDS);
            } else ShadowCowardiceTimer -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_bd_nefarian()
{
    new boss_bd_nefarian();
}
