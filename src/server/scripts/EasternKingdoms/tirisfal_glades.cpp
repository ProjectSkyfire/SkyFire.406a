/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Tirisfal_Glades
SD%Complete: 100
SDComment: Quest support: 590, 1819
SDCategory: Tirisfal Glades
EndScriptData */

/* ContentData
npc_calvin_montague
go_mausoleum_door
go_mausoleum_trigger
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_calvin_montague
######*/

enum eCalvin
{
    SAY_COMPLETE        = -1000431,
    SPELL_DRINK         = 2639,                             // possibly not correct spell (but iconId is correct)
    QUEST_590           = 590,
    FACTION_HOSTILE     = 168
};

class npc_calvin_montague : public CreatureScript
{
public:
    npc_calvin_montague() : CreatureScript("npc_calvin_montague") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_590)
        {
            creature->setFaction(FACTION_HOSTILE);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
            CAST_AI(npc_calvin_montague::npc_calvin_montagueAI, creature->AI())->AttackStart(player);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_calvin_montagueAI (creature);
    }

    struct npc_calvin_montagueAI : public ScriptedAI
    {
        npc_calvin_montagueAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 Phase;
        uint32 PhaseTimer;
        uint64 PlayerGUID;

        void Reset()
        {
            Phase = 0;
            PhaseTimer = 5000;
            PlayerGUID = 0;

            me->RestoreFaction();

            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE))
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        }

        void EnterCombat(Unit* /*who*/) {}

        void AttackedBy(Unit* attacker)
        {
            if (me->getVictim() || me->IsFriendlyTo(attacker))
                return;

            AttackStart(attacker);
        }

        void DamageTaken(Unit* doneBy, uint32 &Damage)
        {
            if (Damage > me->GetHealth() || me->HealthBelowPctDamaged(15, Damage))
            {
                Damage = 0;

                me->RestoreFaction();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                me->CombatStop(true);

                Phase = 1;

                if (doneBy->GetTypeId() == TYPEID_PLAYER)
                    PlayerGUID = doneBy->GetGUID();
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            if (Phase)
            {
                if (PhaseTimer <= Diff)
                    PhaseTimer = 7500;
                else
                {
                    PhaseTimer -= Diff;
                    return;
                }

                switch (Phase)
                {
                    case 1:
                        DoScriptText(SAY_COMPLETE, me);
                        ++Phase;
                        break;
                    case 2:
                        if (Player* player = Unit::GetPlayer(*me, PlayerGUID))
                            player->AreaExploredOrEventHappens(QUEST_590);

                        DoCast (me, SPELL_DRINK, true);
                        ++Phase;
                        break;
                    case 3:
                        EnterEvadeMode();
                        break;
                }

                return;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## go_mausoleum_door
## go_mausoleum_trigger
######*/

enum eMausoleum
{
    QUEST_ULAG      = 1819,
    NPC_ULAG        = 6390,
    GO_TRIGGER      = 104593,
    GO_DOOR         = 176594
};

class go_mausoleum_door : public GameObjectScript
{
public:
    go_mausoleum_door() : GameObjectScript("go_mausoleum_door") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->GetQuestStatus(QUEST_ULAG) != QUEST_STATUS_INCOMPLETE)
            return false;

        if (GameObject* trigger = player->FindNearestGameObject(GO_TRIGGER, 30.0f))
        {
            trigger->SetGoState(GO_STATE_READY);
            player->SummonCreature(NPC_ULAG, 2390.26f, 336.47f, 40.01f, 2.26f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
            return false;
        }

        return false;
    }
};

class go_mausoleum_trigger : public GameObjectScript
{
public:
    go_mausoleum_trigger() : GameObjectScript("go_mausoleum_trigger") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_ULAG) != QUEST_STATUS_INCOMPLETE)
            return false;

        if (GameObject* door = player->FindNearestGameObject(GO_DOOR, 30.0f))
        {
            go->SetGoState(GO_STATE_ACTIVE);
            door->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
            return true;
        }

        return false;
    }
};

void AddSC_tirisfal_glades()
{
    new npc_calvin_montague();
    new go_mausoleum_door();
    new go_mausoleum_trigger();
}