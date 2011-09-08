/*
 * Copyright (C) 2010-2011 SkyFire <http://www.projectskyfire.org/>
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

#include"ScriptPCH.h"
#include"WorldPacket.h"
#include"halls_of_origination.h"
#include"ScriptMgr.h"
#include"ScriptedCreature.h"
#include"SpellScript.h"
#include"SpellAuraEffects.h"

enum ScriptTexts
{
    SAY_AGGRO                = 0,
    SAY_BEACON               = 1,
    SAY_KILL_1               = 2,
    SAY_KILL_2               = 3,
    SAY_DEATH                = 4,
};

enum Spells
{
    SPELL_DIVINE_RECKONING   = 75592,
    H_SPELL_DIVINE_RECKONING = 94949,
    SPELL_REVERBERATING_HYMN = 75322,
    SPELL_SHIELD_OF_LIGHT    = 74938,
};

enum Events
{
    EVENT_DIVINE_RECKONING   = 1,
    EVENT_REVERBERATING_HYMN = 2,
    EVENT_SHIELD_OF_LIGHT    = 3,
};

enum BossPhases
{   //Don't use phase conditionals for the moment
    PHASE_1 = 1,
    PHASE_2 = 2,
    PHASE_3 = 3,
};

class boss_temple_guardian_anhuur : public CreatureScript
{
    public:
        boss_temple_guardian_anhuur() : CreatureScript("boss_temple_guardian_anhuur") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_temple_guardian_anhuurAI(pCreature);
        }
	 struct boss_temple_guardian_anhuurAI : public ScriptedAI
        {
            boss_temple_guardian_anhuurAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript *pInstance;
            EventMap events;
            bool check_in;

            void Reset()
            {
                events.Reset();

                if (pInstance && (pInstance->GetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT) != DONE && !check_in))
                    pInstance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, NOT_STARTED);

                check_in = false;
            }

            void KilledUnit(Unit* /*Killed*/)
            {
                DoScriptText(RAND(SAY_KILL_1, SAY_KILL_2), me);
            }

            void JustDied(Unit* /*Kill*/)
            {
                DoScriptText(SAY_DEATH, me);
                if (pInstance)
                    pInstance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, DONE);
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                DoScriptText(SAY_AGGRO, me);
				if (pInstance)
                    pInstance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, IN_PROGRESS);

                DoZoneInCombat();
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                if (!HealthAbovePct(66) && HealthAbovePct(33)) // Need to add teleportation location with phase swap
                {
                    DoCast(me, SPELL_SHIELD_OF_LIGHT);
                    events.ScheduleEvent(EVENT_REVERBERATING_HYMN, 3000);
                }

                if (!HealthAbovePct(33)) // Need to add teleportation location with phase swap
                {
                    DoCast(me, SPELL_SHIELD_OF_LIGHT);
                    events.ScheduleEvent(EVENT_REVERBERATING_HYMN, 1000);
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())     /*No target to kill*/
                    return;

                events.Update(uiDiff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_DIVINE_RECKONING:
                            DoCast(me->getVictim(), SPELL_DIVINE_RECKONING);
                            events.ScheduleEvent(EVENT_DIVINE_RECKONING, urand(4000, 9000));
                            break;
                        case EVENT_SHIELD_OF_LIGHT:
                            DoCast(me, SPELL_SHIELD_OF_LIGHT);
                            events.ScheduleEvent(EVENT_SHIELD_OF_LIGHT, 4500);
                            break;
                        case EVENT_REVERBERATING_HYMN:
                            DoCast(me, SPELL_REVERBERATING_HYMN);
                            events.ScheduleEvent(EVENT_REVERBERATING_HYMN, 3000);
                            break;
                        default:
                            break;
                    }
                }
            DoMeleeAttackIfReady();
            }
         };
};

void AddSC_boss_temple_guardian_anhuur()
{
    new boss_temple_guardian_anhuur();
}