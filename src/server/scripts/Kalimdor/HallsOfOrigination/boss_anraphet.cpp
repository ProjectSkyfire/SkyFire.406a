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
    SAY_INTRO                  = 0,
    SAY_AGGRO                  = 1,
    SAY_KILL_1                 = 2,
    SAY_KILL_2                 = 3,
    SAY_OMEGA                  = 4,
    SAY_DEATH                  = 5,
};

enum Spells
{
    SPELL_ALPHA_BEAMS          = 39788,
    SPELL_CRUMBLING_RUIN       = 75609,
    H_SPELL_CRUMBLING_RUIN     = 91206,
    SPELL_DESTRUCTION_PROTOCOL = 77437,
    SPELL_NEMESIS_STRIKE       = 75604,
    H_SPELL_NEMESIS_STRIKE     = 91175,
    SPELL_OMEGA_STANCE         = 75622,
    H_SPELL_OMEGA_STANCE       = 91208,
};

enum Events
{
    EVENT_ALPHA_BEAMS          = 1,
    EVENT_CRUMBLING_RUIN       = 2,
    EVENT_DESTRUCTION_PROTOCOL = 3,
    EVENT_NEMESIS_STRIKE       = 4,
    EVENT_OMEGA_STANCE         = 5,
};

class boss_anraphet : public CreatureScript
{
    public:
        boss_anraphet() : CreatureScript("boss_anraphet") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_anraphetAI(pCreature);
        }
        struct boss_anraphetAI : public ScriptedAI
        {
            boss_anraphetAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript *pInstance;
            EventMap events;
            bool check_in;

            void Reset()
            {
                events.Reset();

                if (pInstance && (pInstance->GetData(DATA_ANRAPHET_EVENT) != DONE && !check_in))
                   pInstance->SetData(DATA_ANRAPHET_EVENT, NOT_STARTED);
                check_in = false;
            }

            void JustDied(Unit* /*Kill*/)
            {
                DoScriptText(SAY_DEATH, me);
                if (pInstance)
                    pInstance->SetData(DATA_ANRAPHET_EVENT, DONE);
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                DoScriptText(SAY_AGGRO, me);
				if (pInstance)
                    pInstance->SetData(DATA_ANRAPHET_EVENT, IN_PROGRESS);

                DoZoneInCombat();
			}

            void KilledUnit(Unit* /*Killed*/)
            {
                DoScriptText(RAND(SAY_KILL_1, SAY_KILL_2), me);
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                   return;
                events.Update(uiDiff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_ALPHA_BEAMS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(me->getVictim(), SPELL_ALPHA_BEAMS);
                                events.ScheduleEvent(EVENT_ALPHA_BEAMS, 1000);
                            break;
                        case EVENT_CRUMBLING_RUIN:
                            DoCast(me->getVictim(), SPELL_CRUMBLING_RUIN);
                            events.ScheduleEvent(EVENT_CRUMBLING_RUIN, urand(10000, 16000));
                            break;
                        case EVENT_NEMESIS_STRIKE:
                            DoCast(me->getVictim(), SPELL_NEMESIS_STRIKE);
                            events.ScheduleEvent(EVENT_NEMESIS_STRIKE, 2000);
                            break;
                        case EVENT_OMEGA_STANCE:
                            DoCast(me, SPELL_OMEGA_STANCE);
                            events.ScheduleEvent(EVENT_OMEGA_STANCE, 14000);
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

void AddSC_boss_anraphet()
{
    new boss_anraphet();
}