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
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        
        uint32 uiLavaSpewTimer;
        uint32 uiMagmaSpitTimer;
        uint32 uiLavaParasiteSummonTimer;

        void Reset()
        {
            pInstance->SetData(DATA_MAGMAW, NOT_STARTED);
            
            uiLavaSpewTimer = 10*IN_MILLISECONDS;
            uiMagmaSpitTimer = 14*IN_MILLISECONDS;
            uiLavaParasiteSummonTimer = 30*IN_MILLISECONDS;
            
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            pInstance->SetData(DATA_MAGMAW, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            pInstance->SetData(DATA_MAGMAW, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            pInstance->SetData(DATA_MAGMAW, DONE);
        }

        void SummonCreatureWithRandomTarget(uint32 creatureId)
        {
            Unit* Summoned = me->SummonCreature(creatureId, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 240000);
            if (Summoned)
            {
                Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                if (target)
                    Summoned->AddThreat(target, 1.0f);
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiLavaSpewTimer <= uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_LAVA_SPEW, true);

                uiLavaSpewTimer = urand(10*IN_MILLISECONDS, 12*IN_MILLISECONDS);
            } else uiLavaSpewTimer -= uiDiff;

            if (uiMagmaSpitTimer <= uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_MAGMA_SPIT , true);

                uiMagmaSpitTimer = urand(12*IN_MILLISECONDS, 14*IN_MILLISECONDS);
            } else uiMagmaSpitTimer -= uiDiff;

            if (uiLavaParasiteSummonTimer <= uiDiff)
            {
                for(int i = 0; i < 2; ++i)
                    SummonCreatureWithRandomTarget(42321);

                uiLavaParasiteSummonTimer = 30*IN_MILLISECONDS;
            } else uiLavaParasiteSummonTimer -= uiDiff;

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
        
        uint32 uiCheckDistanceTimer;

        void Reset()
        {
            uiCheckDistanceTimer = 2*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*pWho*/) { }
        
        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;
            
            if (me->IsWithinDistInMap(me->getVictim(), 2.0f))
            {
                if (uiCheckDistanceTimer <= uiDiff)
                {
                    me->CastSpell(me->getVictim(), 94679 , true);

                    uiCheckDistanceTimer = 86400*IN_MILLISECONDS;
                } else uiCheckDistanceTimer -= uiDiff;
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
                        Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
                        if (pTarget)
                            Summoned->AddThreat(pTarget, 1.0f);
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
