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
    SAY_AGGRO          = 0,
    SAY_KILL_1         = 1,
    SAY_KILL_2         = 2,
    SAY_DEATH          = 3,
};

enum Spells
{
    SPELL_FLAME_BOLT   = 77370,
    SPELL_RAGING_SMASH = 83650,
};

enum Events
{
    EVENT_FLAME_BOLT   = 1,
    EVENT_RAGING_SMASH = 2,
};

class boss_earthrager_ptah : public CreatureScript
{
    public:
        boss_earthrager_ptah() : CreatureScript("boss_earthrager_ptah") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_earthrager_ptahAI(pCreature);
        }
        struct boss_earthrager_ptahAI : public ScriptedAI
        {
            boss_earthrager_ptahAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript *pInstance;
            EventMap events;
            bool check_in;

            void Reset()
            {
                events.Reset();

                if (pInstance && (pInstance->GetData(DATA_EARTHRAGER_PTAH_EVENT) != DONE && !check_in))
                   pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, NOT_STARTED);
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
                    pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, DONE);
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                DoScriptText(SAY_AGGRO, me);
				if (pInstance)
                    pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, IN_PROGRESS);

                DoZoneInCombat();
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
                        case EVENT_FLAME_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(target, SPELL_FLAME_BOLT);
                                events.ScheduleEvent(EVENT_FLAME_BOLT, 7500);
                            break;
                        case EVENT_RAGING_SMASH:
                            DoCast(me->getVictim(), SPELL_RAGING_SMASH);
                            events.ScheduleEvent(EVENT_RAGING_SMASH, urand(4000, 10000));
                            break;
                        default:
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

void AddSC_boss_earthrager_ptah()
{
    new boss_earthrager_ptah();
}