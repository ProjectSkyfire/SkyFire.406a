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
#include "the_stonecore.h"

enum Spells
{
    SPELL_ERUPTION                                = 80800,
    SPELL_SUMMON_LAVA_FISSURE                     = 80803,
    SPELL_LAVA_FISSURE_PREPARATION                = 80798,
    SPELL_STALACTITE_SUMMON_OBJ                   = 92309,
    SPELL_STALACTITE_SUMMON_TRIG                  = 80656,
    SPELL_STALACTITE_VISUAL                       = 80654,
    SPELL_SANDBLAST                               = 92656,
};

enum Events
{
    EVENT_LAVA_FISSURE = 1,
    EVENT_STALACTITE_P1,
    EVENT_STALACTITE_P2,
    EVENT_SANDBLAST,
};

class boss_priestess_azil : public CreatureScript
{
public:
    boss_priestess_azil() : CreatureScript("boss_priestess_azil") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_priestess_azilAI (creature);
    }

    struct boss_priestess_azilAI : public ScriptedAI
    {
        boss_priestess_azilAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()

        {
            summons.DespawnAll();
            events.Reset();
            isFlyPhase = false;
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetFlying(false);
            DoStartMovement(me->getVictim());
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_LAVA_FISSURE, urand(7000, 10000), 0, 0);
            events.ScheduleEvent(EVENT_SANDBLAST, urand(7000, 8000), 0, 0);
            events.ScheduleEvent(EVENT_STALACTITE_P1, urand(20000, 30000), 0, 0);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_priestess_azil()
{
    new boss_priestess_azil();
}