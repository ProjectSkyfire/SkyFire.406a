/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011 MigCore <http://wow-mig.ru/>
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
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        
        uint32 uiShadowflameBreathTimer;
        uint32 uiShadowCowardiceTimer;

        void Reset()
        {
            uiShadowflameBreathTimer = 10*IN_MILLISECONDS;
            uiShadowCowardiceTimer = 13*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            pInstance->SetData(DATA_NEFARIAN, IN_PROGRESS);
        }
        
        void JustDied(Unit* /*Killer*/)
        {
            pInstance->SetData(DATA_NEFARIAN, DONE);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiShadowflameBreathTimer <= uiDiff)
            {
                me->CastSpell(me->getVictim(), SPELL_SHADOWFLAME_BREATH, true);

                uiShadowflameBreathTimer = urand(10*IN_MILLISECONDS, 12*IN_MILLISECONDS);
            } else uiShadowflameBreathTimer -= uiDiff;

            if (uiShadowCowardiceTimer <= uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_SHADOW_COWARDICE , true);

                uiShadowCowardiceTimer = urand(8*IN_MILLISECONDS, 9*IN_MILLISECONDS);
            } else uiShadowCowardiceTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_bd_nefarian()
{
    new boss_bd_nefarian();
}
