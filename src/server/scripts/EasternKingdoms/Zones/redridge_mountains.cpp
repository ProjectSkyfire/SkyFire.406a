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

/* Script Data Start
SDName: Redridge Mountains
SD%Complete: 100%
SDComment: Support for quest 219.
Script Data End */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum eCorporalKeeshan
{
    QUEST_MISSING_IN_ACTION       = 219,

    SAY_CORPORAL_1                = -1000464,
    SAY_CORPORAL_2                = -1000465,
    SAY_CORPORAL_3                = -1000466,
    SAY_CORPORAL_4                = -1000467,
    SAY_CORPORAL_5                = -1000468,

    SPELL_MOCKING_BLOW            = 21008,
    SPELL_SHIELD_BASH             = 11972,
};

class npc_corporal_keeshan : public CreatureScript
{
public:
    npc_corporal_keeshan() : CreatureScript("npc_corporal_keeshan") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_MISSING_IN_ACTION)
        {
            CAST_AI(npc_corporal_keeshan::npc_corporal_keeshanAI, creature->AI())->Start(true, false, player->GetGUID(), quest);
            DoScriptText(SAY_CORPORAL_1, creature);
        }

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_corporal_keeshanAI(creature);
    }

    struct npc_corporal_keeshanAI : public npc_escortAI
    {
        npc_corporal_keeshanAI(Creature* creature) : npc_escortAI(creature) {}

        uint32 Phase;
        uint32 Timer;
        uint32 MockingBlowTimer;
        uint32 ShieldBashTimer;

        void Reset()
        {
            Timer            = 0;
            Phase            = 0;
            MockingBlowTimer = 5000;
            ShieldBashTimer  = 8000;
        }

        void WaypointReached(uint32 uiI)
        {
            Player* player = GetPlayerForEscort();

            if (!player)
                return;

            if (uiI >= 65 && me->GetUnitMovementFlags() == MOVEMENTFLAG_WALKING)
                me->SetWalk(false);

            switch (uiI)
            {
                case 39:
                    SetEscortPaused(true);
                    Timer = 2000;
                    Phase = 1;
                    break;
                case 65:
                    me->SetWalk(false);
                    break;
                case 115:
                    player->AreaExploredOrEventHappens(QUEST_MISSING_IN_ACTION);
                    Timer = 2000;
                    Phase = 4;
                    break;
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            if (HasEscortState(STATE_ESCORT_NONE))
                return;

            npc_escortAI::UpdateAI(Diff);

            if (Phase)
            {
                if (Timer <= Diff)
                {
                    switch (Phase)
                    {
                        case 1:
                            me->SetStandState(UNIT_STAND_STATE_SIT);
                            Timer = 1000;
                            Phase = 2;
                            break;
                        case 2:
                            DoScriptText(SAY_CORPORAL_2, me);
                            Timer = 15000;
                            Phase = 3;
                            break;
                        case 3:
                            DoScriptText(SAY_CORPORAL_3, me);
                            me->SetStandState(UNIT_STAND_STATE_STAND);
                            SetEscortPaused(false);
                            Timer = 0;
                            Phase = 0;
                            break;
                        case 4:
                            DoScriptText(SAY_CORPORAL_4, me);
                            Timer = 2500;
                            Phase = 5;
                        case 5:
                            DoScriptText(SAY_CORPORAL_5, me);
                            Timer = 0;
                            Phase = 0;
                    }
                } else Timer -= Diff;
            }

            if (!UpdateVictim())
                return;

            if (MockingBlowTimer <= Diff)
            {
                DoCast(me->getVictim(), SPELL_MOCKING_BLOW);
                MockingBlowTimer = 5000;
            } else MockingBlowTimer -= Diff;

            if (ShieldBashTimer <= Diff)
            {
                DoCast(me->getVictim(), SPELL_MOCKING_BLOW);
                ShieldBashTimer = 8000;
            } else ShieldBashTimer -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_redridge_mountains()
{
    new npc_corporal_keeshan();
}
