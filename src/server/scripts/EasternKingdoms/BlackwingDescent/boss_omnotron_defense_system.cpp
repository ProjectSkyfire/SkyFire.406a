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

enum eSpell
{
    SPELL_ARCANE_ANNIHILATOR    = 79710
};

class boss_toxitron : public CreatureScript
{
public:
    boss_toxitron() : CreatureScript("boss_toxitron") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_toxitronAI (creature);
    }

    struct boss_toxitronAI : public ScriptedAI
    {
        boss_toxitronAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/) {}

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class boss_magmatron : public CreatureScript
{
public:
    boss_magmatron() : CreatureScript("boss_magmatron") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_magmatronAI (creature);
    }

    struct boss_magmatronAI : public ScriptedAI
    {
        boss_magmatronAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*Killer*/) { }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class boss_arcanotron : public CreatureScript
{
public:
    boss_arcanotron() : CreatureScript("boss_arcanotron") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_arcanotronAI (creature);
    }

    struct boss_arcanotronAI : public ScriptedAI
    {
        boss_arcanotronAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 ArcaneAnnihilatorTimer;

        void Reset()
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, NOT_STARTED);

            ArcaneAnnihilatorTimer = 5*IN_MILLISECONDS;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if (ArcaneAnnihilatorTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ARCANE_ANNIHILATOR, true);

                ArcaneAnnihilatorTimer = urand(5*IN_MILLISECONDS, 7*IN_MILLISECONDS);
            } else ArcaneAnnihilatorTimer -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

class boss_electron : public CreatureScript
{
public:
    boss_electron() : CreatureScript("boss_electron") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_electronAI (creature);
    }

    struct boss_electronAI : public ScriptedAI
    {
        boss_electronAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_omnotron_defense_system()
{
    new boss_toxitron();
    new boss_magmatron();
    new boss_arcanotron();
    new boss_electron();
}
