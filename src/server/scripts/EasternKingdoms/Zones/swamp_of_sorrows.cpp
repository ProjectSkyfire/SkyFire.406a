/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2013 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "ScriptedEscortAI.h"

/*######
## npc_galen_goodward
######*/

enum Galen
{
    QUEST_GALENS_ESCAPE     = 1393,

    GO_GALENS_CAGE          = 37118,

    SAY_PERIODIC            = -1000500,
    SAY_QUEST_ACCEPTED      = -1000501,
    SAY_ATTACKED_1          = -1000502,
    SAY_ATTACKED_2          = -1000503,
    SAY_QUEST_COMPLETE      = -1000504,
    EMOTE_WHISPER           = -1000505,
    EMOTE_DISAPPEAR         = -1000506
};

class npc_galen_goodward : public CreatureScript
{
public:

    npc_galen_goodward() : CreatureScript("npc_galen_goodward") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_GALENS_ESCAPE)
        {
            CAST_AI(npc_galen_goodward::npc_galen_goodwardAI, creature->AI())->Start(false, false, player->GetGUID());
            creature->setFaction(FACTION_ESCORT_N_NEUTRAL_ACTIVE);
            DoScriptText(SAY_QUEST_ACCEPTED, creature);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_galen_goodwardAI(creature);
    }

    struct npc_galen_goodwardAI : public npc_escortAI
    {
        npc_galen_goodwardAI(Creature* creature) : npc_escortAI(creature)
        {
            GalensCageGUID = 0;
            Reset();
        }

        uint64 GalensCageGUID;
        uint32 PeriodicSay;

        void Reset()
        {
            PeriodicSay = 6000;
        }

        void EnterCombat(Unit* who)
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
                DoScriptText(RAND(SAY_ATTACKED_1, SAY_ATTACKED_2), me, who);
        }

        void WaypointStart(uint32 PointId)
        {
            switch (PointId)
            {
            case 0:
                {
                    GameObject* cage = NULL;
                    if (GalensCageGUID)
                        cage = me->GetMap()->GetGameObject(GalensCageGUID);
                    else
                        cage = GetClosestGameObjectWithEntry(me, GO_GALENS_CAGE, INTERACTION_DISTANCE);
                    if (cage)
                    {
                        cage->UseDoorOrButton();
                        GalensCageGUID = cage->GetGUID();
                    }
                    break;
                }
            case 21:
                DoScriptText(EMOTE_DISAPPEAR, me);
                break;
            }
        }

        void WaypointReached(uint32 PointId)
        {
            switch (PointId)
            {
            case 0:
                if (GameObject* cage = me->GetMap()->GetGameObject(GalensCageGUID))
                    cage->ResetDoorOrButton();
                break;
            case 20:
                if (Player* player = GetPlayerForEscort())
                {
                    me->SetFacingToObject(player);
                    DoScriptText(SAY_QUEST_COMPLETE, me, player);
                    DoScriptText(EMOTE_WHISPER, me, player);
                    player->GroupEventHappens(QUEST_GALENS_ESCAPE, me);
                }
                SetRun(true);
                break;
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            npc_escortAI::UpdateAI(Diff);

            if (HasEscortState(STATE_ESCORT_NONE))
                return;

            if (PeriodicSay < Diff)
            {
                if (!HasEscortState(STATE_ESCORT_ESCORTING))
                    DoScriptText(SAY_PERIODIC, me);
                PeriodicSay = 15000;
            }
            else
                PeriodicSay -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_swamp_of_sorrows()
{
    new npc_galen_goodward();
}
