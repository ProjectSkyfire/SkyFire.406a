/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
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
#include "Unit.h"
#include "gilneas.h"

//Phase 1
/*######
## npc_prince_liam_greymane_phase1
######*/

class npc_prince_liam_greymane_phase1 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase1() : CreatureScript("npc_prince_liam_greymane_phase1") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase1AI (creature);
    }

    struct npc_prince_liam_greymane_phase1AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase1AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tSay; //Time left for say
        uint32 cSay; //Current Say

        //Evade or Respawn
        void Reset()
        {
            tSay = DELAY_SAY_PRINCE_LIAM_GREYMANE; //Reset timer
            cSay = 1; //Start from 1
        }

        //Timed events
        void UpdateAI(const uint32 diff)
        {
            //Out of combat
            if (!me->getVictim())
            {
                //Timed say
                if (tSay <= diff)
                {
                    switch (cSay)
                    {
                        default:
                        case 1:
                            DoScriptText(SAY_PRINCE_LIAM_GREYMANE_1, me);
                            cSay++;
                            break;
                        case 2:
                            DoScriptText(SAY_PRINCE_LIAM_GREYMANE_2, me);
                            cSay++;
                            break;
                        case 3:
                            DoScriptText(SAY_PRINCE_LIAM_GREYMANE_3, me);
                            cSay = 1; //Reset to 1
                            break;
                    }

                    tSay = DELAY_SAY_PRINCE_LIAM_GREYMANE; //Reset the timer
                }
                else
                {
                    tSay -= diff;
                }
                return;
            }
        }
    };
};

/*######
## npc_gilneas_city_guard_phase1
######*/

class npc_gilneas_city_guard_phase1 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase1() : CreatureScript("npc_gilneas_city_guard_phase1") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase1AI (creature);
    }

    struct npc_gilneas_city_guard_phase1AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase1AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tSay; //Time left for say

        //Evade or Respawn
        void Reset()
        {
            if (me->GetGUIDLow() == 3486400)
            {
                tSay = DELAY_SAY_GILNEAS_CITY_GUARD_GATE; //Reset timer
            }
        }

        void UpdateAI(const uint32 diff)
        {
            //Out of combat and
            if (me->GetGUIDLow() == 3486400)
            {
                //Timed say
                if (tSay <= diff)
                {
                    //Random say
                    DoScriptText(RAND(
                        SAY_GILNEAS_CITY_GUARD_GATE_1,
                        SAY_GILNEAS_CITY_GUARD_GATE_2,
                        SAY_GILNEAS_CITY_GUARD_GATE_3),
                    me);

                    tSay = DELAY_SAY_GILNEAS_CITY_GUARD_GATE; //Reset timer
                }
                else
                {
                    tSay -= diff;
                }
            }
        }
    };
};

void AddSC_gilneas_phase1()
{
    new npc_gilneas_city_guard_phase1();
    new npc_prince_liam_greymane_phase1();
}