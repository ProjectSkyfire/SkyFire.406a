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
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 ConsumingFlames;
        uint32 ArcaneStorm;
        uint32 ScorchingBlast;
        uint32 Remedy;

        void Reset()
        {
            instance->SetData(DATA_MALORIAK, NOT_STARTED);

            ConsumingFlames = 5*IN_MILLISECONDS;
            ArcaneStorm = 15*IN_MILLISECONDS;
            ScorchingBlast = 120*IN_MILLISECONDS;
            Remedy = 30*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(DATA_MALORIAK, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            instance->SetData(DATA_MALORIAK, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_MALORIAK, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if (ConsumingFlames <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_CONSUMING_FLAMES, true);

                ConsumingFlames = urand(10*IN_MILLISECONDS, 12*IN_MILLISECONDS);
            } else ConsumingFlames -= Diff;

            if (ArcaneStorm <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ARCANE_STORM, true);

                ArcaneStorm = urand(15*IN_MILLISECONDS, 17*IN_MILLISECONDS);
            } else ArcaneStorm -= Diff;

            if (ScorchingBlast <= Diff)
            {
                me->CastSpell(me->getVictim(), SPELL_SCORCHING_BLAST, true);

                ScorchingBlast = urand(120*IN_MILLISECONDS, 130*IN_MILLISECONDS);
            } else ScorchingBlast -= Diff;

            if (Remedy <= Diff)
            {
                me->CastSpell(me, SPELL_REMEDY, true);

                Remedy = urand(30*IN_MILLISECONDS, 32*IN_MILLISECONDS);
            } else Remedy -= Diff;

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
