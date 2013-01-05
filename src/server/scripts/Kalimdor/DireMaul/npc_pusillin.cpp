/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"

enum pus
{
    SAY_1   = -1901000, 
    SAY_2   = -1901001, 
    SAY_3   = -1901002, 
    SAY_4   = -1901003, 
    SAY_5   = -1901004, 

    NPC_IMP = 13276
};

enum eSpells
{
    SPELL_BLAST_WAVE            = 17145, 
    SPELL_FIRE_BLAST            = 14145, 
    SPELL_FIREBALL              = 15228, 
    SPELL_RUNN                  = 22735
};

const Position SpawnPosition1 = {23.019f, -703.442f, -12.642f, 3.23f};
const Position SpawnPosition2 = {22.646f, -691.948f, -12.642f, 4.13f};
const Position SpawnPosition3 = {12.277f, -676.333f, -12.642f, 4.97f};
const Position SpawnPosition4 = {24.416f, -680.573f, -12.642f, 4.31f};

#define GOSSIP_HELLO "Game? Are your crazy?"
#define Gossip_2 "Why you little..."
#define Gossip_3 "Mark my words, I will catch you, Imp. And when I do!"
#define Gossip_4 "DIE!"
#define Gossip_5 "Prepare to meet your Maker."

class npc_pusillin : public CreatureScript
{
public:
    npc_pusillin() : CreatureScript("npc_pusillin") { }

    struct npc_pusillinAI : public npc_escortAI
    {
        npc_pusillinAI(Creature* creature) : npc_escortAI(creature)
        {}

        uint32 uiPhase;
        uint32 uiGossipStep;
        uint32 uiBlastWaveTimer;
        uint32 uiFireBlastTimer;
        uint32 uiFireBallTimer;
        uint32 uiSpiritOfRunnTimer;
        bool buffed;

        void Reset()
        {
            uiPhase = 0;
            uiGossipStep = 0;
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            uiBlastWaveTimer = urand(7000, 9000);
            uiFireBlastTimer = urand(3000, 6000);
            uiFireBallTimer  = urand(11000, 13000);
            uiSpiritOfRunnTimer = urand(5000, 7000);
            buffed=false;
        }

        void SetHoldState(bool bOnHold)
        {
            SetEscortPaused(bOnHold);
        }

        void WaypointReached(uint32 uiPointId)
        {
            switch (uiPointId)
            {
            case 0:
                break;
            case 2:
                uiGossipStep = 1;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                SetHoldState(true);
                break;
            case 4:
                uiGossipStep = 2;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                SetHoldState(true);
                break;
            case 10:
                uiGossipStep = 3;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                SetHoldState(true);
                break;
            case 16:
                uiGossipStep = 4;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                break;
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if (uiPhase)
            {
                switch (uiPhase)
                {
                case 1:
                    DoScriptText(SAY_1, me);
                    uiPhase=0;
                    break;
                case 2:
                    DoScriptText(SAY_2, me);
                    uiPhase=0;
                    break;
                case 3:
                    DoScriptText(SAY_3, me);
                    uiPhase=0;
                    break;
                case 4:
                    DoScriptText(SAY_4, me);
                    uiPhase=0;
                    break;
                case 5:
                    DoScriptText(SAY_5, me);
                    me->setFaction(14);
                    float scale = me->GetFloatValue(OBJECT_FIELD_SCALE_X);
                    me->SetFloatValue(OBJECT_FIELD_SCALE_X, scale * 3);
                    Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0);
                    me->AI()->AttackStart(target);
                    for (uint8 i = 0; i<5; i++)
                    {
                        switch (i)
                        {
                        case 1:
                            if (Creature *pImp=me->SummonCreature(NPC_IMP, SpawnPosition1, TEMPSUMMON_CORPSE_DESPAWN, 120000))
                                {
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                    pImp->AI()->AttackStart(target);
                                }
                            break;
                        case 2:
                            if (Creature *pImp=me->SummonCreature(NPC_IMP, SpawnPosition2, TEMPSUMMON_CORPSE_DESPAWN, 120000))
                                {
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                    pImp->AI()->AttackStart(target);
                                }
                            break;
                        case 3:
                            if (Creature *pImp=me->SummonCreature(NPC_IMP, SpawnPosition3, TEMPSUMMON_CORPSE_DESPAWN, 120000))
                                {
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                    pImp->AI()->AttackStart(target);
                                }
                            break;
                        case 4:
                            if (Creature *pImp=me->SummonCreature(NPC_IMP, SpawnPosition4, TEMPSUMMON_CORPSE_DESPAWN, 120000))
                                {
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                    pImp->AI()->AttackStart(target);
                                }
                            break;
                        }
                    }
                    uiPhase=6;
                    break;
                }
            }

            if (uiPhase == 6)
            {
                if (!UpdateVictim())
                    return;

                if (uiBlastWaveTimer <= uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_BLAST_WAVE);
                    uiBlastWaveTimer = urand(7000, 9000);
                }
                else uiBlastWaveTimer -= uiDiff;

                if (uiFireBlastTimer <= uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_FIRE_BLAST);
                    uiFireBlastTimer = urand(3000, 6000);
                }
                else uiFireBlastTimer -= uiDiff;

                if (uiFireBallTimer <= uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_FIREBALL);
                    uiFireBallTimer  = urand(11000, 13000);
                }
                else uiFireBallTimer -= uiDiff;

                if (uiSpiritOfRunnTimer <= uiDiff && buffed == false)
                {
                    DoCast(me, SPELL_RUNN);
                    buffed = true;
                }
                else uiSpiritOfRunnTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_pusillinAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        npc_pusillinAI* pAI = CAST_AI(npc_pusillinAI, creature->AI());

        switch (pAI->uiGossipStep)
        {
        case 0:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(6877, creature->GetGUID());
            break;
        case 1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, Gossip_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(6878, creature->GetGUID());
            break;
        case 2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, Gossip_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->SEND_GOSSIP_MENU(6879, creature->GetGUID());
            break;
        case 3:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, Gossip_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            player->SEND_GOSSIP_MENU(6880, creature->GetGUID());
            break;
        case 4:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, Gossip_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            player->SEND_GOSSIP_MENU(6881, creature->GetGUID());
            break;
        }

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 action)
    {
        npc_pusillinAI* pAI = CAST_AI(npc_pusillinAI, creature->AI());

        if (!pAI)
            return false;

        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            CAST_AI(npc_pusillinAI, creature->AI())->Start(false, true, player->GetGUID());
            pAI->SetHoldState(false);
            pAI->uiPhase = 1;
        }

        if (action == GOSSIP_ACTION_INFO_DEF+2)
        {
            pAI->uiPhase = 2;
            pAI->SetHoldState(false);
        }

        if (action == GOSSIP_ACTION_INFO_DEF+3)
        {
            pAI->uiPhase = 3;
            pAI->SetHoldState(false);
        }

        if (action == GOSSIP_ACTION_INFO_DEF+4)
        {
            pAI->uiPhase = 4;
            pAI->SetHoldState(false);
        }

        if (action == GOSSIP_ACTION_INFO_DEF+5)
        {
            pAI->uiPhase = 5;
        }

        player->CLOSE_GOSSIP_MENU();
        pAI->SetDespawnAtEnd(false);
        pAI->SetDespawnAtFar(false);
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        return true;
    }
};

void AddSC_npc_pusillin()
{
    new npc_pusillin();
}
