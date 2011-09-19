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
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*pWho*/) {}

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 Diff)
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
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PASSIVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*pWho*/) { }

        void JustDied(Unit* /*Killer*/) { }

        void UpdateAI(const uint32 Diff)
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
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        uint32 uiArcaneAnnihilatorTimer;

        void Reset()
        {
            pInstance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, NOT_STARTED);

            uiArcaneAnnihilatorTimer = 5*IN_MILLISECONDS;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            pInstance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            pInstance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            pInstance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if (uiArcaneAnnihilatorTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ARCANE_ANNIHILATOR, true);

                uiArcaneAnnihilatorTimer = urand(5*IN_MILLISECONDS, 7*IN_MILLISECONDS);
            } else uiArcaneAnnihilatorTimer -= Diff;

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
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PASSIVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*pWho*/) { }

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 Diff)
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