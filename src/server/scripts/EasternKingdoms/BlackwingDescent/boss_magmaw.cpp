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
    SPELL_LAVA_SPEW     = 77690,
    SPELL_MAGMA_SPIT    = 77690,
};

class boss_magmaw : public CreatureScript
{
public:
    boss_magmaw() : CreatureScript("boss_magmaw") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_magmawAI (creature);
    }

    struct boss_magmawAI : public ScriptedAI
    {
        boss_magmawAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 LavaSpewTimer;
        uint32 MagmaSpitTimer;
        uint32 LavaParasiteSummonTimer;

        void Reset()
        {
            instance->SetData(DATA_MAGMAW, NOT_STARTED);

            LavaSpewTimer = 10*IN_MILLISECONDS;
            MagmaSpitTimer = 14*IN_MILLISECONDS;
            LavaParasiteSummonTimer = 30*IN_MILLISECONDS;

            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(DATA_MAGMAW, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            instance->SetData(DATA_MAGMAW, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_MAGMAW, DONE);
        }

        void SummonCreatureWithRandomTarget(uint32 creatureId)
        {
            Unit* Summoned = me->SummonCreature(creatureId, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 240000);
            if (Summoned)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if (target)
                    Summoned->AddThreat(target, 1.0f);
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if (LavaSpewTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_LAVA_SPEW, true);

                LavaSpewTimer = urand(10*IN_MILLISECONDS, 12*IN_MILLISECONDS);
            } else LavaSpewTimer -= Diff;

            if (MagmaSpitTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_MAGMA_SPIT , true);

                MagmaSpitTimer = urand(12*IN_MILLISECONDS, 14*IN_MILLISECONDS);
            } else MagmaSpitTimer -= Diff;

            if (LavaParasiteSummonTimer <= Diff)
            {
                for (int i = 0; i < 2; ++i)
                    SummonCreatureWithRandomTarget(42321);

                LavaParasiteSummonTimer = 30*IN_MILLISECONDS;
            } else LavaParasiteSummonTimer -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

class mobs_lava_parasite : public CreatureScript
{
public:
    mobs_lava_parasite() : CreatureScript("mobs_lava_parasite") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mobs_lava_parasiteAI (creature);
    }

    struct mobs_lava_parasiteAI : public ScriptedAI
    {
        mobs_lava_parasiteAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 CheckDistanceTimer;

        void Reset()
        {
            CheckDistanceTimer = 2*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if (me->IsWithinDistInMap(me->getVictim(), 2.0f))
            {
                if (CheckDistanceTimer <= Diff)
                {
                    me->CastSpell(me->getVictim(), 94679 , true);

                    CheckDistanceTimer = 86400*IN_MILLISECONDS;
                } else CheckDistanceTimer -= Diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class spell_parasitic_infection : public SpellScriptLoader
{
    public:
        spell_parasitic_infection() : SpellScriptLoader("spell_parasitic_infection") { }

        class spell_parasitic_infection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_parasitic_infection_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit * caster = GetCaster();
                for (int i = 0; i < 2; ++i)
                {
                    Unit* Summoned = caster->SummonCreature(42321, caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 240000);
                    /*if (Summoned)
                    {
                        Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                        if (target)
                            Summoned->AddThreat(target, 1.0f);
                    }*/
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_parasitic_infection_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_parasitic_infection_AuraScript();
        }
};

void AddSC_boss_magmaw()
{
    new boss_magmaw();
    new mobs_lava_parasite();
    new spell_parasitic_infection();
}
