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
#include "SpellAuraEffects.h"
#include "blackwing_descent.h"

enum eSpell
{
    SPELL_CONSUMING_FLAMES          = 77786,
    SPELL_ARCANE_STORM              = 77896,
    SPELL_SCORCHING_BLAST           = 77679,
    SPELL_REMEDY                    = 77912,
};

class boss_maloriak : public CreatureScript
{
public:
    boss_maloriak() : CreatureScript("boss_maloriak") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_maloriakAI (creature);
    }

    struct boss_maloriakAI : public ScriptedAI
    {
        boss_maloriakAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        uint32 uiConsumingFlames;
        uint32 uiArcaneStorm;
        uint32 uiScorchingBlast;
        uint32 uiRemedy;

        void Reset()
        {
            pInstance->SetData(DATA_MALORIAK, NOT_STARTED);

            uiConsumingFlames = 5*IN_MILLISECONDS;
            uiArcaneStorm = 15*IN_MILLISECONDS;
            uiScorchingBlast = 120*IN_MILLISECONDS;
            uiRemedy = 30*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            pInstance->SetData(DATA_MALORIAK, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            pInstance->SetData(DATA_MALORIAK, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            pInstance->SetData(DATA_MALORIAK, DONE);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiConsumingFlames <= uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_CONSUMING_FLAMES, true);

                uiConsumingFlames = urand(10*IN_MILLISECONDS, 12*IN_MILLISECONDS);
            } else uiConsumingFlames -= uiDiff;

            if (uiArcaneStorm <= uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ARCANE_STORM, true);

                uiArcaneStorm = urand(15*IN_MILLISECONDS, 17*IN_MILLISECONDS);
            } else uiArcaneStorm -= uiDiff;

            if (uiScorchingBlast <= uiDiff)
            {
                me->CastSpell(me->getVictim(), SPELL_SCORCHING_BLAST, true);

                uiScorchingBlast = urand(120*IN_MILLISECONDS, 130*IN_MILLISECONDS);
            } else uiScorchingBlast -= uiDiff;

            if (uiRemedy <= uiDiff)
            {
                me->CastSpell(me, SPELL_REMEDY, true);

                uiRemedy = urand(30*IN_MILLISECONDS, 32*IN_MILLISECONDS);
            } else uiRemedy -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_gen_maloriak_remedy : public SpellScriptLoader
{
public:
    spell_gen_maloriak_remedy() : SpellScriptLoader("spell_gen_maloriak_remedy") { }

    class spell_gen_maloriak_remedy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_gen_maloriak_remedy_AuraScript);
        void HandleTick(AuraEffect const* aurEff)
        {
            Unit* target = GetTarget();
            if (target && target->GetTypeId() == TYPEID_UNIT)
            {
                int32 baseAmount = aurEff->GetBaseAmount();
                //sLog->outBasic("spell_remedy: amount %d, baseamount %d, tick %u", aurEff->GetAmount(), baseAmount, aurEff->GetTickNumber());
                if (baseAmount > 0)
                    const_cast<AuraEffect*>(aurEff)->SetAmount(baseAmount * aurEff->GetTickNumber());
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_gen_maloriak_remedy_AuraScript::HandleTick, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_gen_maloriak_remedy_AuraScript();
    }
};

void AddSC_boss_maloriak()
{
    new boss_maloriak();
    new spell_gen_maloriak_remedy();
}