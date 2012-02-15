/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 Trinity <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://www.getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SkyFireScript_Name: Westfall
%Complete: 90
Comment: Alot of this needs moved to db... it doesnt belong in core script.
Category: Westfall
EndScriptData */

/* ContentData
npc_thug
npc_horatio
npc_westplains_drifter
npc_crate_mine
npc_homeless_citizen
npc_shadowy_trigger
npc_shadowy_tower
npc_rise_br
npc_defias_blackguard
npc_fire_trigger
npc_summoner
npc_horatio_investigate
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum eThug
{
    QUEST_LOUS_PARTING_THOUGHTS     = 26232,
    NPC_THUG                        = 42387,
    NPC_TRIGGER                     = 42562
};

class npc_thug: public CreatureScript
{
    public:
    npc_thug() : CreatureScript("npc_thug") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_thugAI (creature);
    }

    struct npc_thugAI : public ScriptedAI
    {
        npc_thugAI(Creature *creature) : ScriptedAI(creature) {}

        uint32 SummonTimer;
        uint64 PlayerGUID;
        uint64 Thug1GUID;
        uint64 Thug2GUID;
        uint64 Thug3GUID;
        uint64 Thug4GUID;
        uint8 Phase;

        bool bSummoned;

        void Reset()
        {
            Phase               = 0;
            PlayerGUID          = 0;
            Thug1GUID           = 0;
            Thug2GUID           = 0;
            Thug3GUID           = 0;
            Thug4GUID           = 0;
            bSummoned           = false;
            SummonTimer         = 2000;
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (who->ToPlayer()->GetQuestStatus(QUEST_LOUS_PARTING_THOUGHTS) == QUEST_STATUS_INCOMPLETE)
            {
                if (who->IsWithinDistInMap(me, 10.0f) && !bSummoned)
                {
                    PlayerGUID = who->GetGUID();
                    StartEvent();
                }
            }
        }

        void StartEvent()
        {
            if(!bSummoned)
            {
                if (Creature* Thug1 = me->SummonCreature(NPC_THUG, -9859.36f, 1332.42f, 41.985f, 2.495f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Thug2 = me->SummonCreature(NPC_THUG, -9862.51f, 1332.079f, 41.985f, 0.85f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Thug3 = me->SummonCreature(NPC_THUG, -9863.49f, 1335.489f, 41.985f, 5.63f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Thug4 = me->SummonCreature(NPC_THUG, -9860.42f, 1335.459f, 41.985f, 4.11f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                {
                    Thug1GUID      = Thug1->GetGUID();
                    Thug2GUID      = Thug2->GetGUID();
                    Thug3GUID      = Thug3->GetGUID();
                    Thug4GUID      = Thug4->GetGUID();
                    bSummoned      = true;
                    SummonTimer    = 2000;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (SummonTimer < diff)
            {
                if (bSummoned)
                {
                    if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* Thug1 = me->GetCreature(*me, Thug1GUID))
                    if (Creature* Thug2 = me->GetCreature(*me, Thug2GUID))
                    if (Creature* Thug3 = me->GetCreature(*me, Thug3GUID))
                    if (Creature* Thug4 = me->GetCreature(*me, Thug4GUID))
                    {
                        switch (Phase)
                        {    // MonsterSay move to ->creature_texts
                            case 0:
                            {
                                Thug1->MonsterSay("Did you... did you meet her?", 0, 0);
                                SummonTimer = 3500;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                Thug2->MonsterSay("Yep. She's for real?", 0, 0);
                                SummonTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                Thug2->MonsterSay("She wanted me to tell you that she appreciates the job that we did for her on the Furlbrows. Gave me a pile o'gold to split with you all.", 0, 0);
                                SummonTimer = 7000;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                Thug3->MonsterSay(" See her face. It is really...", 0, 0);
                                SummonTimer = 4000;
                                Phase++;
                            }
                            break;
                            case 4:
                            {
                                Thug1->SetFacingToObject(player);
                                Thug2->SetFacingToObject(player);
                                Thug3->SetFacingToObject(player);
                                Thug4->SetFacingToObject(player);
                                SummonTimer = 1000;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                Thug1->MonsterSay("Whoa, what do we have here? Looks like we have ourselves an eavesdropper, boys.", 0, 0);
                                SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                Thug1->MonsterSay("Only one thing to do with a louisy, good-for-nothin eavesdropper.", 0, 0);
                                SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                Thug1->MonsterSay("DIE!!!", 0, 0);
                                SummonTimer = 2000;
                                Phase++;
                                break;
                            }
                            case 8:
                            {
                                Thug1->SetReactState(REACT_AGGRESSIVE);
                                Thug1->setFaction(14);
                                Thug1->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
                                Thug2->SetReactState(REACT_AGGRESSIVE);
                                Thug2->setFaction(14);
                                Thug2->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
                                Thug3->SetReactState(REACT_AGGRESSIVE);
                                Thug3->setFaction(14);
                                Thug3->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
                                Thug4->SetReactState(REACT_AGGRESSIVE);
                                Thug4->setFaction(14);
                                Thug4->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
                                SummonTimer = 1000;
                                Phase++;
                                break;
                            }
                            case 9:
                            {
                                Thug1->CombatStart(player, true);
                                Thug2->CombatStart(player, true);
                                Thug3->CombatStart(player, true);
                                Thug4->CombatStart(player, true);
                                SummonTimer = 5000;
                                Phase++;
                                break;
                            }
                            case 10:
                            {
                                if (Player* player = me->GetPlayer(*me, PlayerGUID))
                                    player->KilledMonsterCredit(42417, PlayerGUID);
                                    SummonTimer = 2500;
                                    Phase++;
                                    break;
                            }
                            case 11:
                            {
                                player->CastSpell(player, 79346, true);
                                me->MonsterTextEmote("Hurry back to the Furlbrow's Cottage", 0, true);
                                if (player->GetQuestStatus(QUEST_LOUS_PARTING_THOUGHTS) == QUEST_STATUS_COMPLETE)
                                {
                                    if (Creature* two = me->FindNearestCreature(42405, 200.0f, true))
                                    {
                                        two->SetVisible(false);
                                    }
                                }
                                SummonTimer = 15000;
                                Phase++;
                                break;
                            }
                            case 12:
                                Reset();
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            else SummonTimer -= diff;
        }
    };
};

/*############
##npc_horatio#
############*/

enum eHoratio
{
    QUEST_HERO_WESTFALL1     = 28562,
    QUEST_HERO_WESTFALL2     = 26378,

    SPELL_INVISIBILITY       = 79488,

    NPC_HORATIO              = 42308,
    NPC_INVESTIGATOR1          = 42309,
    NPC_INVESTIGATOR2          = 42745
};

class npc_horatio : public CreatureScript
{
    public:
    npc_horatio() : CreatureScript("npc_horatio") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_horatioAI (creature);
    }

    struct npc_horatioAI : public ScriptedAI
    {
        npc_horatioAI(Creature *creature) : ScriptedAI(creature) {}

        uint8 Phase;
        uint32 TextTimer;
        uint64 PlayerGUID;
        uint64 Investigator01GUID;
        uint64 Investigator02GUID;

        bool bSummoned;
        bool bSummoned1;
        bool bSummoned2;

        void Reset()
        {
            Phase                 = 0;
            PlayerGUID            = 0;
            Investigator01GUID    = 0;
            Investigator02GUID    = 0;
            bSummoned             = false;
            bSummoned1            = false;
            bSummoned2            = false;
            TextTimer             = 1000;
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (who->IsWithinDistInMap(me, 25.0f) && !bSummoned)
            {
                PlayerGUID = who->GetGUID();
                StartSummon();
            }
        }

        void StartSummon()
        {
            if (!bSummoned)
            {
                if (Creature* Investigator01 = me->SummonCreature(NPC_INVESTIGATOR2,-9854.414f, 916.481f, 30.100f, 5.3867f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 66000))
                {
                    Investigator01GUID = Investigator01->GetGUID();
                    bSummoned1 = true;
                }
                if (Creature* Investigator02 = me->SummonCreature(NPC_INVESTIGATOR2, -9854.252f, 906.651f, 29.833f, 0.730950f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 66000))
                {
                    Investigator02GUID = Investigator02->GetGUID();
                    bSummoned2 = true;
                }
                if (bSummoned1 && bSummoned2)
                {
                    bSummoned = true;
                    TextTimer = 2000;
                }
            }
        }
        void UpdateAI(const uint32 diff)
        {
            if (TextTimer < diff)
            {
                if (bSummoned)
                {
                    if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* Investigator01 = me->GetCreature(*me, Investigator01GUID))
                    if (Creature* Investigator02 = me->GetCreature(*me, Investigator02GUID))
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                Investigator01->MonsterSay("It's a bloodbath, lieutenant. They've been murdered.", 0, 0);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                Investigator01->MonsterSay("Given the body temperature. I'd say they've been dead no more than 6 hours.",0, 0);
                                Investigator01->SetStandState(UNIT_STAND_STATE_KNEEL);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                Investigator02->MonsterSay("Damn shame what they did to Old Blanchy...",0, 0);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                me->MonsterSay("No kidding, rookie.",0, 0);
                                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                me->GetMotionMaster()->MovePoint(0, -9852.267f, 911.928f, 30.028f);
                                me->GetMotionMaster()->MovePoint(1, -9851.928f, 909.8602f, 29.931f);
                                me->SetStandState(UNIT_STAND_STATE_KNEEL);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 4:
                            {
                                me->MonsterSay("Looks like they really put the cart.",0, 0);
                                TextTimer = 5000;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                me->MonsterSay("...before the horse.",0, 0);
                                TextTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                me->SetStandState(UNIT_STAND_STATE_STAND);
                                me->GetMotionMaster()->MovePoint(0, -9852.267f, 911.928f, 30.028f);
                                me->GetMotionMaster()->MovePoint(1, -9849.818f, 914.904f, 30.27f);
                                me->GetMotionMaster()->MovePoint(2, -9849.86f, 914.859f, 30.268f);
                                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                TextTimer = 8000;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                me->SetFacingToObject(player);
                                TextTimer = 60000;
                                Phase++;
                                break;
                            }
                            case 8:
                                Reset();
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            else TextTimer -=diff;
        }
    };
};

/*######
## npc_westplains_drifter
######*/

enum edrifter
{
    CREDIT_SAY1    = 42414,
    CREDIT_SAY2    = 42415,
    CREDIT_SAY3    = 42416,
    CREDIT_SAY4    = 42417,

    QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME    = 26209
};

#define GOSSIP_COST                2
#define GOSSIP_HELLO_DRIFTER1   "Did you see who killed the Furlbrows?"
#define GOSSIP_HELLO_DRIFTER2   "Maybe a couple copper will loosen your tongue. Now tell me, did you see who killed the Furlbrows?"

class npc_westplains_drifter : public CreatureScript
{
    public:
    npc_westplains_drifter() : CreatureScript("npc_westplains_drifter") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(26209) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DRIFTER1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (player->GetQuestStatus(26209) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DRIFTER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            switch (rand() % 7)
            {  // MonsterSay needs moved to creature_texts
                case 0:
                {
                    creature->MonsterSay("Listen, pal. I don't want any trouble, ok? I didn't see who murdered 'em, but I sure heard it! Lots of yelling. Human voices... you dig? Now get out of here before I change my mind about beating you up and takin' your shoes.", 0, 0);
                    player->KilledMonsterCredit(CREDIT_SAY1, 0);
                    creature->SetStandState(UNIT_STAND_STATE_STAND);
                    creature->ForcedDespawn(5000);
                    break;
                }
                case 1:
                {
                    creature->MonsterSay("I didn't see who killed 'm, bub/sis, but I got a whiff. Smelled rich, kinda like you. Damn shame too. Furlbrows were a fixture around here. Nice people, always willin' to share a meal or a patch of dirt.",0, 0);
                    player->KilledMonsterCredit(CREDIT_SAY2, 0);
                    creature->SetStandState(UNIT_STAND_STATE_STAND);
                    creature->ForcedDespawn(5000);
                    break;
                }
                case 2:
                {
                    creature->MonsterSay("Who killed the Furlbrows? I'll tell you who killed the Furlbrows: KING VARIAN WRYNN. THAT'S WHO! And he's killin' the rest of us too. One bum at a time. The only thing I can tell you is that I saw some gnolls leavin' the place a few hours before the law arrived.", 0, 0);
                    player->KilledMonsterCredit(CREDIT_SAY3, 0);
                    creature->SetStandState(UNIT_STAND_STATE_STAND);
                    creature->ForcedDespawn(5000);
                    break;
                }
                case 3:
                {
                    creature->MonsterSay("Between you, me, and the tree, murlocs killed the Furlbrows. Yep, saw 'em with my own two eyes. Think they'd been casin' the joint for days, maybe months. They left in a hurry once they got wind of 'Johnny Law' and the idiot brigade over there...", 0, 0);
                    player->KilledMonsterCredit(CREDIT_SAY4, 0);
                    creature->SetStandState(UNIT_STAND_STATE_STAND);
                    creature->ForcedDespawn(5000);
                    break;
                }   player->CLOSE_GOSSIP_MENU();
            }
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 2)
        {
            if (!player->HasEnoughMoney(2))
            {
                        player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
                        player->CLOSE_GOSSIP_MENU();
            }
            else
            {
                player->ModifyMoney(-2);
                switch (rand() % 7)
                {
                    case 0:
                    {
                        creature->MonsterSay("Listen, pal. I don't want any trouble, ok? I didn't see who murdered 'em, but I sure heard it! Lots of yelling. Human voices... you dig? Now get out of here before I change my mind about beating you up and takin' your shoes.", 0, 0);
                        player->KilledMonsterCredit(CREDIT_SAY1, 0);
                        creature->ForcedDespawn(5000);
                        break;
                    }
                    case 1:
                    {
                        creature->MonsterSay("I didn't see who killed 'm, bub/sis, but I got a whiff. Smelled rich, kinda like you. Damn shame too. Furlbrows were a fixture around here. Nice people, always willin' to share a meal or a patch of dirt.", 0, 0);
                        player->KilledMonsterCredit(CREDIT_SAY2, 0);
                        creature->ForcedDespawn(5000);
                        break;
                    }
                    case 2:
                    {
                        creature->MonsterSay("Who killed the Furlbrows? I'll tell you who killed the Furlbrows: KING VARIAN WRYNN. THAT'S WHO! And he's killin' the rest of us too. One bum at a time. The only thing I can tell you is that I saw some gnolls leavin' the place a few hours before the law arrived.", 0, 0);
                        player->KilledMonsterCredit(CREDIT_SAY3, 0);
                        creature->ForcedDespawn(5000);
                        break;
                    }
                    case 3:
                    {
                        creature->MonsterSay("Between you, me, and the tree, murlocs killed the Furlbrows. Yep, saw 'em with my own two eyes. Think they'd been casin' the joint for days, maybe months. They left in a hurry once they got wind of 'Johnny Law' and the idiot brigade over there...", 0, 0);
                        player->KilledMonsterCredit(CREDIT_SAY4, 0);
                        creature->ForcedDespawn(5000);
                        break;
                    }
                    case 4:
                    {
                        creature->MonsterSay("I wonder if it's possible to eat rocks? Got plenty of rocks around here. Just imagine it! I'd be the richest person in the world for making that discovery!", 0, 0);
                        creature->SetReactState(REACT_AGGRESSIVE);
                        creature->AI()->AttackStart(player);
                        break;
                    }
                    case 5:
                    {
                        creature->MonsterSay("Looks like I found us a savory and clean piece of dirt! Tonight we eat like kings, Mr. Penguin! Of course I'll share it with you! You're my best friend!", 0, 0);
                        creature->SetReactState(REACT_AGGRESSIVE);
                        creature->AI()->AttackStart(player);
                        break;
                    }
                    case 6:
                    {
                        creature->MonsterSay("HAHAHAH! Good one, Mr. Penguin! GOOD ONE!", 0, 0);
                        creature->SetReactState(REACT_AGGRESSIVE);
                        creature->AI()->AttackStart(player);
                        break;
                    }
                    case 7:
                    {
                        creature->MonsterSay("What happened to me? I used to be the king of Stormwind!", 0, 0);
                        creature->SetReactState(REACT_AGGRESSIVE);
                        creature->AI()->AttackStart(player);
                        break;

                        player->CLOSE_GOSSIP_MENU();
                    }
                }
            }
        }
        return true;
    }
};

/*##############
npc_crate_Jangelode_Mine#
##############*/

enum eCrate
{
    QUEST_LIVIN_THE_LIFE    = 26228
};

class npc_crate_mine : public CreatureScript
{
    public:
    npc_crate_mine() : CreatureScript("npc_crate_mine") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crate_mineAI (creature);
    }

    struct npc_crate_mineAI  : public ScriptedAI
    {
        npc_crate_mineAI(Creature *creature) : ScriptedAI(creature) {}

        uint8 Phase;
        uint32 EntryTime;
        uint64 PlayerGUID;
        uint64 Shadowy1GUID;
        uint64 GlubtoklGUID;

        bool bSummoned;

        void Reset()
        {
            Phase = 0;
            EntryTime = 1000;
            Shadowy1GUID = 0;
            GlubtoklGUID = 0;
            PlayerGUID = 0;
            bSummoned = false;
            PartySummoned();
        }

        void PartySummoned()
        {
            if(!bSummoned)
            {
                if (Creature* glubtok1 = me->SummonCreature(42492, -9848.11f, 1395.29f, 37.70f, 0.56f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 85000))
                if (Creature* shadowy1 = me->SummonCreature(42515, -9826.083f, 1406.738f, 36.885f, 3.56f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 85000))
                {
                    GlubtoklGUID = glubtok1->GetGUID();
                    Shadowy1GUID = shadowy1->GetGUID();

                    bSummoned = true;
                    EntryTime = 250;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (EntryTime <= diff)
            {
                if (bSummoned)
                {
                    //if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* glubtok1 = me->GetCreature(*me, GlubtoklGUID))
                    if (Creature* shadowy1 = me->GetCreature(*me, Shadowy1GUID))
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                EntryTime = 2500;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                shadowy1->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                shadowy1->GetMotionMaster()->MovePoint(0, -9840.526f, 1399.37f, 37.177f);
                                EntryTime = 7000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                glubtok1->MonsterSay("What little human want? Why you call Glubtok?", 0, 0);
                                EntryTime = 5000;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                shadowy1->MonsterSay("Sad... Is this the life that you had hoped for, Glubtok? Running two bit extortion operations out of a cave?", 0, 0);
                                EntryTime = 8500;
                                Phase++;
                                break;
                            }
                            case 4:
                            {
                                glubtok1->MonsterSay("Glubtok crash you!", 0, 0);
                                EntryTime = 4000;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                shadowy1->MonsterSay("Oh will you? Do you dare cross that line and risk your life?", 0, 0);
                                EntryTime = 6500;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                shadowy1->MonsterSay("You may attempt to kill me - and fail - or you make take option two.", 0, 0);
                                EntryTime = 6500;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                glubtok1->MonsterSay("What is option two.", 0, 0);
                                EntryTime = 4000;
                                Phase++;
                                break;
                            }
                            case 8:
                            {
                                shadowy1->MonsterSay("You join me and I shower wealth and power upon you.", 0, 0);
                                EntryTime = 7000;
                                Phase++;
                                break;
                            }
                            case 9:
                            {
                                glubtok1->MonsterSay("So Glubtok have two choices die or be rich and powerful?", 0, 0);
                                EntryTime = 7000;
                                Phase++;
                                break;
                            }
                            case 10:
                            {
                                glubtok1->MonsterSay("Glubtok take choice two.", 0, 0);
                                EntryTime = 6000;
                                Phase++;
                                break;
                            }
                            case 11:
                            {
                                shadowy1->MonsterSay("I thought you'd see it my way.", 0, 0);
                                EntryTime = 6000;
                                Phase++;
                                break;
                            }
                            case 12:
                            {
                                shadowy1->MonsterSay("I will call you when the dawning is upon us.", 0, 0);
                                EntryTime = 6000;
                                Phase++;
                                break;
                            }
                            case 13:
                            {
                                me->ForcedDespawn(5000);
                                glubtok1->CastSpell(glubtok1, 64446, true);
                                glubtok1->ForcedDespawn(1000);
                                shadowy1->CastSpell(shadowy1, 64446, true);
                                shadowy1->ForcedDespawn(1000);

                                std::list<Player*> players;

                                Trinity::AnyPlayerInObjectRangeCheck checker(me, 25.0f);
                                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
                                me->VisitNearbyWorldObject(20.0f, searcher);

                                for (std::list<Player*>::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                                    (*itr)->GroupEventHappens(QUEST_LIVIN_THE_LIFE, me);

                                Phase = 0;
                            }
                            break;
                            default:
                            break;
                        }
                    }
                }
            }
            else EntryTime -= diff;
        }
    };
};

/*#####################
##npc_homeless_citizen#
#####################*/

enum eCitizen
{
    QUEST_FEEDING_THE_HUNGRY    = 26271,
    NPC_HUNGRY                  = 42386,
    NPC_HUNGRY2                 = 42384,
    NPC_STEW                    = 42617,
    SPELL_FULL_BELLY            = 79451,

    HUNGRY_SAY1                 = -1642384,
    HUNGRY_SAY2                 = -1642385,
    HUNGRY_SAY3                 = -1642386
};

class npc_homeless_citizen : public CreatureScript
{
    public:
    npc_homeless_citizen() : CreatureScript("npc_homeless_citizen") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_homeless_citizenAI (creature);
    }

    struct npc_homeless_citizenAI  : public ScriptedAI
    {
        npc_homeless_citizenAI(Creature *creature) : ScriptedAI(creature) {}

        uint8 Phase;
        uint32 HungryTimer;

        void Reset()
        {
            Phase = 0;
            HungryTimer = 2000;

            me->SetStandState(UNIT_STAND_STATE_SLEEP);
        }

        void Eat()
        {
            me->CastSpell(me, SPELL_FULL_BELLY, true);
            me->SetStandState(UNIT_STAND_STATE_SIT);
            DoScriptText(RAND(-1642384,-1642385,-1642386), me);
        }

        void MoveInFront(Unit* Source, Unit* Target)
        {
            float Distance;
            Distance = Source->GetDistanceOrder(Source, Target);
            if (Distance < 0)
                Distance = Distance*2;

            float x = Target->GetPositionX();
            float y = Target->GetPositionY();
            float z = Target->GetPositionZ();

            Source->GetClosePoint(x, y, z, DEFAULT_WORLD_OBJECT_SIZE, Distance);
            Source->GetMotionMaster()->MovePoint(1, x, y, z);
        }

        void UpdateAI(const uint32 diff)
        {
            if (HungryTimer < diff)
            {
                if (Creature* stew = me->FindNearestCreature(NPC_STEW, 10.0f, true))
                {
                    if (me->HasAura(SPELL_FULL_BELLY) && Phase == 0)
                        return;

                    switch (Phase)
                    {
                        case 0:
                        {
                            me->RemoveStandFlags(UNIT_STAND_STATE_SLEEP);
                            me->SetStandFlags(UNIT_STAND_STATE_STAND);
                            HungryTimer = 1000;
                            Phase++;
                            break;
                        }
                        case 1:
                        {
                            MoveInFront(me, stew);
                            HungryTimer = 1500;
                            Phase++;
                            break;
                        }
                        case 2:
                        {
                            Eat();
                            HungryTimer = 2000;
                            Phase++;
                            break;
                        }
                        case 3:
                        {
                            if (Unit* player = me->GetPlayer(*stew, stew->GetUInt64Value(UNIT_FIELD_SUMMONEDBY)))
                                player->ToPlayer()->KilledMonsterCredit(42617, NULL);
                                HungryTimer = 25000;
                                Phase++;
                                break;
                        }
                        default:
                        break;
                    }
                }
                else HungryTimer = 3000;

                if (Phase == 4)
                    Reset();
            }
            else HungryTimer -= diff;
        }
    };
};

enum eShadowy2
{
    QUEST_THE_DAWNING_OF_NEW_DAY     = 26297,
    NPC_SHADOWY2                     = 42680,
    NPC_TRIGGER2                     = 43515,
    NPC_LISTENER                     = 42383
};

class npc_shadowy_trigger : public CreatureScript
{
    public:
    npc_shadowy_trigger() : CreatureScript("npc_shadowy_trigger") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowy_triggerAI (creature);
    }

    struct npc_shadowy_triggerAI  : public ScriptedAI
    {
        npc_shadowy_triggerAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 SummonTimer;
        uint64 PlayerGUID;
        uint64 Shadowy2GUID;
        uint64 Witness1GUID;
        uint64 Witness2GUID;
        uint64 Witness3GUID;
        uint64 Witness4GUID;
        uint64 Witness5GUID;
        uint64 Witness6GUID;
        uint64 Witness7GUID;
        uint64 Witness8GUID;
        uint64 Witness9GUID;
        uint64 Witness10GUID;
        uint64 Witness11GUID;
        uint64 Witness12GUID;
        uint64 Witness13GUID;
        uint64 Witness14GUID;
        uint64 Witness15GUID;
        uint64 Witness16GUID;
        uint64 Witness17GUID;
        uint64 Witness18GUID;
        uint64 Witness19GUID;
        uint64 Witness20GUID;
        uint64 Witness21GUID;
        uint64 Witness22GUID;
        uint64 Witness23GUID;
        uint64 Witness24GUID;
        uint64 Witness25GUID;
        uint64 Witness26GUID;
        uint64 Witness27GUID;

        uint8 Phase;

        bool bSummoned;
        bool bSummoned1;
        bool bText;

        void Reset()
        {
            Phase = 0;
            PlayerGUID = 0;
            Shadowy2GUID = 0;
            Witness1GUID = 0;
            Witness2GUID = 0;
            Witness3GUID = 0;
            Witness4GUID = 0;
            Witness5GUID = 0;
            Witness6GUID = 0;
            Witness7GUID = 0;
            Witness8GUID = 0;
            Witness9GUID = 0;
            Witness10GUID = 0;
            Witness11GUID = 0;
            Witness12GUID = 0;
            Witness13GUID = 0;
            Witness14GUID = 0;
            Witness15GUID = 0;
            Witness16GUID = 0;
            Witness17GUID = 0;
            Witness18GUID = 0;
            Witness19GUID = 0;
            Witness20GUID = 0;
            Witness21GUID = 0;
            Witness22GUID = 0;
            Witness22GUID = 0;
            Witness23GUID = 0;
            Witness24GUID = 0;
            Witness25GUID = 0;
            Witness26GUID = 0;
            Witness27GUID = 0;
            bSummoned = false;
            bSummoned1 = false;
            bText = false;
            SummonTimer = 2000;
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (who->ToPlayer()->GetQuestStatus(QUEST_THE_DAWNING_OF_NEW_DAY) == QUEST_STATUS_INCOMPLETE)
            {
                if (who->IsWithinDistInMap(me, 20.0f) && !bSummoned)
                {
                    PlayerGUID = who->GetGUID();
                    StartSpeech();
                }
            }
        }

        void StartSpeech()
        {
            if(!bSummoned)
            {
                if (Creature* Shadowy2 = me->SummonCreature(NPC_SHADOWY2,-11016.31f, 1478.82f, 47.80f, 2.016f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                {
                    Shadowy2GUID = Shadowy2->GetGUID();
                    bSummoned = true;
                    SummonTimer = 2000;
                    SummonCrowd();
                }
            }
        }

        void SummonCrowd()
        {
            if(!bSummoned1)
            {
                if (Creature* Witness1 = me->SummonCreature(NPC_LISTENER,-11009.036f, 1490.47f, 43.58f, 4.16f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness2 = me->SummonCreature(NPC_LISTENER,-11010.76f, 1488.21f, 43.57f, 4.33f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness3 = me->SummonCreature(NPC_LISTENER,-11017.39f, 1491.76f, 43.19f, 4.78f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness4 = me->SummonCreature(NPC_LISTENER,-11021.73f, 1493.054f, 43.184f, 5.09f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness5 = me->SummonCreature(NPC_LISTENER,-11025.74f, 1487.70f, 43.17f, 5.45f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness6 = me->SummonCreature(NPC_LISTENER,-11025.25f, 1482.23f, 43.03f, 6.04f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness7 = me->SummonCreature(NPC_LISTENER,-11029.68f, 1481.255f, 43.185f, 6.20f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness8 = me->SummonCreature(NPC_LISTENER,-11024.46f, 1473.88f, 43.02f, 0.43f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness9 = me->SummonCreature(NPC_LISTENER,-11019.49f, 1471.70f, 43.21f, 1.09f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness10 = me->SummonCreature(NPC_LISTENER,-11021.56f, 1497.053f, 43.20f, 5.00f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness11 = me->SummonCreature(NPC_LISTENER,-11012.29f, 1488.14f, 43.77f, 4.16f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness12 = me->SummonCreature(NPC_LISTENER,-11014.67f, 1493.14f, 43.23f, 4.60f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness13 = me->SummonCreature(NPC_LISTENER,-11019.8f, 1494.25f, 43.2f, 4.77f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness14 = me->SummonCreature(NPC_LISTENER,-11023.6f, 1489.35f, 43.17f, 4.77f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness15 = me->SummonCreature(NPC_LISTENER,-11023.1f, 1482.51f, 43.07f, 6.25f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness16 = me->SummonCreature(NPC_LISTENER,-11027.2f, 1494.37f, 43.17f, 5.15f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness17 = me->SummonCreature(NPC_LISTENER,-11029.6f, 1488.29f, 43.19f, 5.64f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness18 = me->SummonCreature(NPC_LISTENER,-11030.8f, 1485.13f, 43.31f, 5.94f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness19 = me->SummonCreature(NPC_LISTENER,-11026.2f, 1478.62f, 42.94f, 6.17f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness20 = me->SummonCreature(NPC_LISTENER,-11013.2f, 1497.81f, 43.31f, 4.44f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness21 = me->SummonCreature(NPC_LISTENER,-11011.6f, 1492.61f, 43.39f, 4.44f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness22 = me->SummonCreature(NPC_LISTENER,-11015.4f, 1489.06f, 43.28f, 4.73f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness23 = me->SummonCreature(NPC_LISTENER,-11020.2f, 1490.15f, 43.19f, 5.07f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness24 = me->SummonCreature(NPC_LISTENER,-11009.9f, 1483.52f, 44.06f, 3.88f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness25 = me->SummonCreature(NPC_LISTENER,-11020.1f, 1484.87f, 43.18f, 5.33f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness26 = me->SummonCreature(NPC_LISTENER,-11017.7f, 1487.42f, 43.24f, 4.89f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                if (Creature* Witness27 = me->SummonCreature(NPC_LISTENER,-11017.9f, 1498.24f, 43.20f, 5.04f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                {
                    Witness1GUID = Witness1->GetGUID();
                    Witness2GUID = Witness2->GetGUID();
                    Witness3GUID = Witness3->GetGUID();
                    Witness4GUID = Witness4->GetGUID();
                    Witness5GUID = Witness5->GetGUID();
                    Witness6GUID = Witness6->GetGUID();
                    Witness7GUID = Witness7->GetGUID();
                    Witness8GUID = Witness8->GetGUID();
                    Witness9GUID = Witness9->GetGUID();
                    Witness10GUID = Witness10->GetGUID();
                    Witness11GUID = Witness11->GetGUID();
                    Witness12GUID = Witness12->GetGUID();
                    Witness13GUID = Witness13->GetGUID();
                    Witness14GUID = Witness14->GetGUID();
                    Witness15GUID = Witness15->GetGUID();
                    Witness16GUID = Witness16->GetGUID();
                    Witness17GUID = Witness17->GetGUID();
                    Witness18GUID = Witness18->GetGUID();
                    Witness19GUID = Witness19->GetGUID();
                    Witness20GUID = Witness20->GetGUID();
                    Witness21GUID = Witness21->GetGUID();
                    Witness22GUID = Witness22->GetGUID();
                    Witness23GUID = Witness23->GetGUID();
                    Witness24GUID = Witness24->GetGUID();
                    Witness25GUID = Witness25->GetGUID();
                    Witness26GUID = Witness26->GetGUID();
                    Witness27GUID = Witness27->GetGUID();

                    bSummoned1 = true;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (SummonTimer < diff)
            {
                if (bSummoned)
                {
                    if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* Shadowy2 = me->GetCreature(*me, Shadowy2GUID))
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                me->MonsterTextEmote("The rally is about to begin!", NULL, true);
                                SummonTimer = 1500;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                Shadowy2->MonsterYell("Gather, brothers and sisters! Come, all, and listen!", 0, 0);
                                SummonTimer = 3000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                Shadowy2->MonsterYell("Brothers. Sisters. We are ABANDONED - the orphaned children of Stormwind.", 0, 0);
                                SummonTimer = 5500;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                Shadowy2->MonsterYell("Our 'king' sits atop his throne made of gold and shrugs at our plight!", 0, 0);
                                SummonTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 4:
                            {
                                Shadowy2->MonsterYell("Meanwhile, our children die of starvation on these very streets!", 0, 0);
                                SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                Shadowy2->MonsterYell("HIS war, not ours, cost us our livelihood. WE paid for the Alliance's victories with our blood and the blood of our loved ones!", 0, 0);
                                SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                Shadowy2->MonsterYell("The time has come, brothers and sisters, to stop this injustice!", 0, 0);
                                SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                Shadowy2->MonsterYell("The government of Stormwind, of the ALLIANCE, must be made accountable for what it has done to us!", 0, 0); SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 8:
                            {
                                Shadowy2->MonsterYell("Today, we are reborn! Today, we take a stand as men and women, not nameless, faceless numbers!", 0, 0);
                                SummonTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 9:
                            {
                                if (Creature* listener = me->FindNearestCreature(NPC_LISTENER, 35.0f, true))
                                {
                                    if(!bText)
                                    {
                                        me->MonsterTextEmote("<homeless people applaud and cheer>", NULL, true);
                                        listener->TextEmote(TEXT_EMOTE_APPLAUD, PlayerGUID, false);
                                        bText = true;
                                    }
                                    listener->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
                                    player->KilledMonsterCredit(42680, PlayerGUID);
                                    Shadowy2->CastSpell(me, 64446, true);
                                    Shadowy2->ForcedDespawn(1000);
                                }
                            }
                            break;
                            default:
                            break;
                        }
                    }
                }
            }
            else SummonTimer -= diff;
        }
    };
};

enum eTower
{
    SPELL_POTION_SHROUDING = 79528,
    QUEST_SECRETS_OF_THE_TOWER = 26290
};

class npc_shadowy_tower : public CreatureScript
{
    public:
    npc_shadowy_tower() : CreatureScript("npc_shadowy_tower") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowy_towerAI (creature);
    }

    struct npc_shadowy_towerAI  : public ScriptedAI
    {
        npc_shadowy_towerAI(Creature *creature) : ScriptedAI(creature) {}

        uint8 Phase;
        uint32 SummonTimer;
        uint64 PlayerGUID;
        uint64 Glubtok3GUID;
        uint64 Shadowy3GUID;

        bool bSumm;
        bool bSumm1;
        bool bSumm2;
        bool bExit;

        void Reset()
        {
            Phase = 0;
            PlayerGUID = 0;
            Glubtok3GUID = 0;
            Shadowy3GUID = 0;
            SummonTimer = 2000;
            bSumm = false;
            bSumm1 = false;
            bSumm2 = false;
            bExit = false;
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_PLAYER)
                return;
            //if (who->HasAura(79528))
              //  return true;

            if (who->ToPlayer()->GetQuestStatus(QUEST_SECRETS_OF_THE_TOWER) == QUEST_STATUS_INCOMPLETE)
            {
                if (who->IsWithinDistInMap(me, 10.0f) && !bSumm)
                {
                    PlayerGUID = who->GetGUID();
                    StartEvent();
                }
            }
        }

        void StartEvent()
        {
            if(!bSumm)
            {
                if(!bSumm1)
                {
                    if (Creature* Shadowy3 = me->SummonCreature(42662, -11138.659f, 545.20f, 70.30f, 0.19f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                    {
                        Shadowy3GUID = Shadowy3->GetGUID();
                        Shadowy3->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        Shadowy3->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        Shadowy3->GetMotionMaster()->MovePoint(0, -11131.710f, 546.810f, 70.380f);
                        bSumm1 = true;
                    }
                }

                if(!bSumm2)
                {
                    if (Creature* Glubtok3 = me->SummonCreature(42492,-11128.11f, 547.52f, 70.41f, 3.32f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000))
                    {
                        Glubtok3GUID = Glubtok3->GetGUID();
                        Glubtok3->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        bSumm2 = true;
                    }
                }

                if (bSumm1 && bSumm2)
                {
                    bSumm = true;
                    SummonTimer = 2000;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (SummonTimer < diff)
            {
                if (bSumm)
                {
                    if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* Glubtok3 = me->GetCreature(*me, Glubtok3GUID))
                    if (Creature* Shadowy3 = me->GetCreature(*me, Shadowy3GUID))
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                Glubtok3->SetInFront(me);
                                SummonTimer = 1000;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                Glubtok3->MonsterSay("The gnolls have failed, mistress.", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                Shadowy3->MonsterSay("They provided the distraction I required. We continue as planned.", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                Glubtok3->MonsterSay("But mistress, the admiral is sti...", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 4:
                            {
                                Shadowy3->MonsterSay("We will free the admiral during the dawning.", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                Glubtok3->MonsterSay("Yes, mistress.", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                Shadowy3->MonsterSay("Judgment day is soon upon us, Helix.", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                Shadowy3->MonsterSay("Call for the people. I wish to speak to them one last time before the dawning.", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 8:
                            {
                                Glubtok3->MonsterSay("Moonbrook, mistress?", 0, 0);
                                SummonTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 9:
                            {
                                Shadowy3->MonsterSay("Aye. Tonight.", 0, 0);
                                SummonTimer = 2000;
                                Phase++;
                                break;
                            }
                            case 10:
                            {
                                player->CastSpell(player, 79534, true);
                                SummonTimer = 1000;
                                Phase++;
                                break;
                            }
                            case 11:
                            {
                                if(!bExit)
                                {
                                    Shadowy3->CastSpell(Shadowy3, 64446, true);
                                    Shadowy3->ForcedDespawn(1000);
                                    Glubtok3->CastSpell(Shadowy3, 64446, true);
                                    Glubtok3->ForcedDespawn(1000);
                                    bExit = true;
                                }
                            }
                            break;
                            default :
                            break;
                        }
                    }
                }
            }
            else SummonTimer -= diff;
        }
    };
};

/*#####################
#Westfall Ending Event#
#####################*/

enum eEnd
{
    SPELL_TRANSFORM_HUMAN       = 79745,
    SPELL_ADMIRAL_HAT           = 79750,
    SPELL_TRANSFORM_VANEESA     = 79709,
    SPELL_SUMMON_BLACKGUARD     = 79712,
    SPELL_TIED_UP_GOOD_GUYS     = 79723,
    SPELL_TIED_UP_VISUAL        = 79724,
    SPELL_DEFIAS_FINALE_EVENT   = 79758,
    SPELL_SUMMON_GLUBTOK        = 79762,
    SPELL_SUMMON_HELIX          = 79763,
    SPELL_TOSS_TORCH            = 79778,
    SPELL_TOSS_TORCH_TRIGGER    = 79779,
    SPELL_SMOKE                 = 67690,
    SPELL_HIT_ME                = 65600,

    NPC_HOPE                    = 42575,
    NPC_GRYAN                   = 42750,
    NPC_RIPSNARL                = 42635, // 42748
    NPC_INVESTIGATOR            = 42745,
    NPC_INVESTIGATOR3           = 46614,
    NPC_THIEF                   = 42769,
    NPC_GUARD                   = 878,
    NPC_HORATIO2                = 42744,
    NPC_DANUVIN                 = 821,

    QUEST_RISE_OF_THE_BROTHERHOOD = 26322
};

class npc_rise_br : public CreatureScript
{
    public:
    npc_rise_br() : CreatureScript("npc_rise_br") {}

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_RISE_OF_THE_BROTHERHOOD)
        {
            if(!(CAST_AI(npc_rise_br::npc_rise_brAI, creature->AI())->EventStarted))
            {
                CAST_AI(npc_rise_br::npc_rise_brAI, creature->AI())->EventStarted = true;
                CAST_AI(npc_rise_br::npc_rise_brAI, creature->AI())->PlayerGUID = player->GetGUID();
            }
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rise_brAI (creature);
    }

    struct npc_rise_brAI  : public ScriptedAI
    {
        npc_rise_brAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 PlayerGUID;
        uint64 Glubok4GUID;
        uint64 Helix2GUID;
        uint64 Thief1GUID;
        uint64 Thief2GUID;
        uint64 Thief3GUID;
        uint64 Thief4GUID;
        uint64 Thief5GUID;
        uint64 Thief6GUID;
        uint64 Thief7GUID;
        uint64 Thief8GUID;
        uint64 Thief9GUID;
        uint64 Thief10GUID;
        uint64 Fire1GUID;
        uint64 Fire2GUID;
        uint64 Fire3GUID;
        uint64 Fire4GUID;
        uint64 Fire5GUID;
        uint64 Fire6GUID;
        uint64 Fire7GUID;
        uint64 Fire8GUID;
        uint64 Fire9GUID;
        uint64 Fire10GUID;
        uint64 Fire11GUID;
        uint64 Fire12GUID;
        uint64 Fire13GUID;

        uint32 EventTimer;

        uint8 Phase;

        bool EventStarted;

        void Reset()
        {
            Phase = 0;
            PlayerGUID = 0;
            Thief1GUID = 0;
            Thief2GUID = 0;
            Thief3GUID = 0;
            Thief4GUID = 0;
            Thief5GUID = 0;
            Thief6GUID = 0;
            Thief7GUID = 0;
            Thief8GUID = 0;
            Thief9GUID = 0;
            Thief10GUID = 0;
            Glubok4GUID = 0;
            Helix2GUID = 0;
            Fire1GUID = 0;
            Fire2GUID = 0;
            Fire3GUID = 0;
            Fire4GUID = 0;
            Fire5GUID = 0;
            Fire6GUID = 0;
            Fire7GUID = 0;
            Fire8GUID = 0;
            Fire9GUID = 0;
            Fire10GUID = 0;
            Fire11GUID = 0;
            Fire12GUID = 0;
            Fire13GUID = 0;

            EventTimer = 2000;

            EventStarted = false;
            me->RemoveAllAuras();
        }

        void SummonBrotherHood()
        {
            if (Creature* Thief1 = me->SummonCreature(NPC_THIEF,-10500.37f, 1042.65f, 60.51f, 3.06f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief2 = me->SummonCreature(NPC_THIEF,-10500.99f, 1046.73f, 60.517f, 3.29f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief3 = me->SummonCreature(NPC_THIEF,-10505.202f, 1040.46f, 60.51f, 1.88f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief4 = me->SummonCreature(NPC_THIEF,-10507.89f, 1039.52f, 60.51f, 1.95f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief5 = me->SummonCreature(NPC_THIEF,-10513.54f, 1038.66f, 60.51f, 0.51f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief6 = me->SummonCreature(NPC_THIEF,-10514.930f, 1042.012f, 60.51f, 0.399f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief7 = me->SummonCreature(NPC_THIEF,-10516.797f, 1048.61f, 59.95f, 5.32f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief8 = me->SummonCreature(NPC_THIEF,-10514.032f, 1049.80f, 59.92f, 5.11f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief9 = me->SummonCreature(NPC_THIEF,-10509.012f, 1051.92f, 59.85f, 5.11f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Thief10 = me->SummonCreature(NPC_THIEF,-10504.77f, 1053.57f, 59.86f, 4.84f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000))
            if (Creature* Glubtok4 = me->SummonCreature(42755,-10506.12f, 1053.13f, 59.10f, 4.92f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000))
            if (Creature* Helix2 = me->SummonCreature(42753,-10509.368f, 1057.28f, 57.86f, 4.95f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000))
            {
                Thief1GUID = Thief1->GetGUID();
                Thief2GUID = Thief2->GetGUID();
                Thief3GUID = Thief3->GetGUID();
                Thief4GUID = Thief4->GetGUID();
                Thief5GUID = Thief5->GetGUID();
                Thief6GUID = Thief6->GetGUID();
                Thief7GUID = Thief7->GetGUID();
                Thief8GUID = Thief8->GetGUID();
                Thief9GUID = Thief9->GetGUID();
                Thief10GUID = Thief10->GetGUID();
            }
        }

        void RemoveStun()
        {
            if (Creature* Horatio = me->FindNearestCreature(NPC_HORATIO2, 50.0f, true))
            if (Creature* Danuvin = me->FindNearestCreature(NPC_DANUVIN, 50.0f, true))
            if (Creature* Guard = me->FindNearestCreature(NPC_GUARD, 50.0f, true))
            if (Creature* Investigator = me->FindNearestCreature(NPC_INVESTIGATOR, 50.0f, true))
            if (Creature* Investigator2 = me->FindNearestCreature(NPC_INVESTIGATOR3, 50.0f, true))
            {
                Horatio->RemoveAurasDueToSpell(79724);
                Danuvin->RemoveAurasDueToSpell(79724);
                Guard->RemoveAurasDueToSpell(79724);
                Investigator->RemoveAurasDueToSpell(79724);
                Investigator2->RemoveAurasDueToSpell(79724);
            }
        }

        void DoStun()
        {
            if (Creature* Horatio = me->FindNearestCreature(NPC_HORATIO2, 50.0f, true))
            if (Creature* Danuvin = me->FindNearestCreature(NPC_DANUVIN, 50.0f, true))
            if (Creature* Guard = me->FindNearestCreature(NPC_GUARD, 50.0f, true))
            if (Creature* Investigator = me->FindNearestCreature(NPC_INVESTIGATOR, 50.0f, true))
            if (Creature* Investigator2 = me->FindNearestCreature(NPC_INVESTIGATOR3, 50.0f, true))
            {
                Horatio->CastSpell(Horatio, 79724, true);
                Danuvin->CastSpell(Danuvin, 79724, true);
                Guard->CastSpell(Guard, 79724, true);
                Investigator->CastSpell(Investigator, 79724, true);
                Investigator2->CastSpell(Investigator2, 79724, true);
            }
        }

        void SummonFireTrigger()
        {
            if (Creature* Fire1 = me->SummonCreature(45937,-10507.5f, 1050.6f, 60.5189f, 3.06f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire2 = me->SummonCreature(45937,-10502.0f, 1051.81f, 67.7637f, 3.29f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire3 = me->SummonCreature(45937,-10504.9f, 1038.74f, 68.2617f, 1.88f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire4 = me->SummonCreature(45937,-10507.4f, 1039.3f, 68.1306f, 1.95f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire5 = me->SummonCreature(45937,-10512.0f, 1040.95f, 60.5179f, 0.51f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire6 = me->SummonCreature(45937,-10516.2f, 1043.94f, 70.1173f, 0.399f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire7 = me->SummonCreature(45937,-10501.6f, 1039.39f, 71.2453f, 5.32f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire8 = me->SummonCreature(45937,-10520.0f, 1053.13f, 57.8726f, 5.11f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire9 = me->SummonCreature(45937,-10504.0f, 1063.19f, 56.481f, 5.11f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire10 = me->SummonCreature(45937,-10492.4f, 1048.5f, 67.612f, 4.84f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire11 = me->SummonCreature(45937,-10503.8f, 1033.96f, 60.6086f, 4.92f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire12 = me->SummonCreature(45937,-10502.4f, 1037.98f, 102.67f, 4.95f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            if (Creature* Fire13 = me->SummonCreature(45937,-10528.7f, 1038.45f, 56.4513f, 4.95f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000))
            {
                Fire1GUID = Fire1->GetGUID();
                Fire2GUID = Fire2->GetGUID();
                Fire3GUID = Fire3->GetGUID();
                Fire4GUID = Fire4->GetGUID();
                Fire5GUID = Fire5->GetGUID();
                Fire6GUID = Fire6->GetGUID();
                Fire7GUID = Fire7->GetGUID();
                Fire8GUID = Fire8->GetGUID();
                Fire9GUID = Fire9->GetGUID();
                Fire10GUID = Fire10->GetGUID();
                Fire11GUID = Fire11->GetGUID();
                Fire12GUID = Fire12->GetGUID();
                Fire13GUID = Fire13->GetGUID();
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (EventStarted)
            {
                if (EventTimer < diff)
                {
                    if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* Hope = me->FindNearestCreature(NPC_HOPE, 50.0f, true))
                    if (Creature* Ripsnarl = me->FindNearestCreature(NPC_RIPSNARL, 50.0f, true))
                    if (Creature* Horatio = me->FindNearestCreature(NPC_HORATIO2, 50.0f, true))
                    if (Creature* Danuvin = me->FindNearestCreature(NPC_DANUVIN, 50.0f, true))
                    if (Creature* Guard = me->FindNearestCreature(NPC_GUARD, 50.0f, true))
                    if (Creature* Investigator = me->FindNearestCreature(NPC_INVESTIGATOR, 50.0f, true))
                    if (Creature* Investigator2 = me->FindNearestCreature(NPC_INVESTIGATOR3, 50.0f, true))
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                me->MonsterSay("I don't like this, $N. Stay alert!", 0, 0);
                                EventTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                me->SetFacingToObject(Hope);
                                Hope->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                Hope->GetMotionMaster()->MovePoint(0, -10507.65f, 1042.81f, 60.51f);
                                EventTimer = 8000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                Hope->MonsterSay("You bastards will burn for what you did.",0, 0);
                                EventTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                me->MonsterSay("Hope! What...", 0, 0);
                                EventTimer = 1500;
                                Phase++;
                                break;
                            }
                            case 4:
                            {
                                Hope->MonsterSay("Hope? Is that what I was supposed fell when I saw my father decapitated by your henchmen?", 0, 0);
                                EventTimer = 12000;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                Hope->MonsterSay("Hope is a cruel joke, played upon us by a harsh and uncaring world. There is no Hope, there is only Vanessa, Vanessa VanCleef.", 0, 0);
                                EventTimer = 9500;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                Hope->CastSpell(Hope, SPELL_TRANSFORM_VANEESA, true);
                                EventTimer = 2500;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                Hope->MonsterYell("RISE UP BROTHERHOOD! THE DAWNING DAY IS UPON US!", 0, 0);
                                SummonBrotherHood();
                                EventTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 8:
                            {
                                Hope->MonsterSay("Tie them up.", 0, 0);
                                EventTimer = 1500;
                                Phase++;
                                break;
                            }
                            case 9:
                            {
                                DoCast(me, 79724);
                                DoStun();
                                EventTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 10:
                            {
                                Hope->GetMotionMaster()->MovePoint(1, -10512.36f, 1044.36f, 60.518f);
                                EventTimer = 3000;
                                Phase++;
                                break;
                            }
                            case 11:
                            {
                                Hope->CastSpell(Hope, SPELL_HIT_ME, true);
                                EventTimer = 1500;
                                Phase++;
                                break;
                            }
                            case 12:
                            {
                                Ripsnarl->CastSpell(Ripsnarl, SPELL_TRANSFORM_HUMAN, true);
                                Hope->MonsterSay("Admiral, your hat.", 0, 0);
                                EventTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 13:
                            {
                                Ripsnarl->MonsterSay("Thank you, my dear.", 0, 0);
                                Ripsnarl->CastSpell(Ripsnarl, SPELL_ADMIRAL_HAT, true);
                                EventTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 14:
                            {
                                Ripsnarl->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                Ripsnarl->GetMotionMaster()->MovePoint(2, -10513.41f, 1041.11f, 60.518f);
                                EventTimer = 2500;
                                Phase++;
                                break;
                            }
                            case 15:
                            {
                                Ripsnarl->GetMotionMaster()->MovePoint(3, -10511.34f, 1042.46f, 60.5172f);
                                EventTimer = 1500;
                                Phase++;
                                break;
                            }
                            case 16:
                            {
                                Hope->SetFacingToObject(player);
                                Hope->MonsterSay("And you, $N. I will spare your life. You have done much to help our cause, albeit unwittingly, but the next time we meet it will be as enemies.", 0, 0);
                                Ripsnarl->GetMotionMaster()->MovePoint(4, -10516.64f, 1064.78f, 55.362f);
                                EventTimer = 8000;
                                Phase++;
                                break;
                            }
                            case 17:
                            {
                                Ripsnarl->SetFacingToObject(me);
                                Hope->GetMotionMaster()->MovePoint(5, -10513.37f, 1056.48f, 57.605f);
                                me->MonsterSay("Why'd you have the Furlbrows killed?", 0, 0);
                                EventTimer = 4500;
                                Phase++;
                                break;
                            }
                            case 18:
                            {
                                Hope->SetFacingToObject(me);
                                Hope->MonsterSay("I had no choice, lieutenant. They recognized me. The only people in the world who even knew I existed, recognized my face from when I was an infant.", 0, 0);
                                EventTimer = 7000;
                                Phase++;
                                break;
                            }
                            case 19:
                            {
                                Hope->MonsterSay("I took no pleasure in their deaths.", 0, 0);
                                SummonFireTrigger();
                                EventTimer = 5000;
                                Phase++;
                                break;
                            }
                            case 20:
                            {
                                Hope->MonsterYell("Leave nothing but ashes in your wake, brothers! Burn Sentinel Hill in the ground!", 0, 0);
                                EventTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 21:
                            {
                                me->MonsterSay("$N, get to Stormwind. Tell King Wrynn everything, EVERYTHING! GO NOW!", 0, 0);
                                Hope->GetMotionMaster()->MovePoint(6, -10518.38f, 1067.99f, 54.84f);
                                Ripsnarl->SetFacingToObject(Hope);

                                if (Creature* Helix2 = me->FindNearestCreature(42753, 30.0f, true))
                                {
                                    Helix2->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                    Helix2->GetMotionMaster()->MovePoint(7, -10520.01f, 1062.31f, 55.386f);
                                }

                                if (Creature* Glubtok4 = me->FindNearestCreature(42755, 30.0f, true))
                                {
                                    Glubtok4->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                    Glubtok4->GetMotionMaster()->MovePoint(8, -10511.79f, 1065.78f, 55.085f);
                                }

                                std::list<Player*> players;

                                Trinity::AnyPlayerInObjectRangeCheck checker(me, 50.0f);
                                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
                                me->VisitNearbyWorldObject(50.0f, searcher);

                                for (std::list<Player*>::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                                    (*itr)->GroupEventHappens(26322, me);

                                EventTimer = 40000;
                                Phase++;
                                break;
                            }
                            case 22:
                            {
                                me->GetMotionMaster()->MoveTargetedHome();
                                Hope->GetMotionMaster()->MoveTargetedHome();
                                Hope->RemoveAurasDueToSpell(79709);
                                Ripsnarl->GetMotionMaster()->MoveTargetedHome();
                                Ripsnarl->RemoveAurasDueToSpell(79745);
                                Ripsnarl->RemoveAurasDueToSpell(79750);
                                me->AI()->Reset();
                                RemoveStun();
                                EventTimer = 100;
                                if (Creature* Helix2 = me->FindNearestCreature(42753, 40.0f, true))
                                {
                                    Helix2->ForcedDespawn();
                                }

                                if (Creature* Glubtok4 = me->FindNearestCreature(42755, 40.0f, true))
                                {
                                    Glubtok4->ForcedDespawn();
                                }
                                Phase++;
                            }
                            break;
                            default:
                            break;
                        }
                    }
                }
                else EventTimer -= diff;
            }
        }
    };
};

/*##########
##npc_black_thief
############*/

class npc_defias_blackguard : public CreatureScript
{
    public:
    npc_defias_blackguard() : CreatureScript("npc_defias_blackguard") {}

    CreatureAI* GetAI(Creature* creature) const
    {
         return new npc_defias_blackguardAI(creature);
    }

    struct npc_defias_blackguardAI : public ScriptedAI
    {
        npc_defias_blackguardAI(Creature *creature) : ScriptedAI(creature) {}

        uint32 timer_DoFire;
        uint32 timer_DoTheStun;
        uint32 ThrowTimer;
        bool Defias_DoFire;
        bool Defias_DoTheStun;

        void Reset()
        {
            Defias_DoFire = false;
            timer_DoFire = 53000;
            me->CastSpell(me, SPELL_SMOKE, true);
            me->CastSpell(me, 22766, true);
            ThrowTimer = 4000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (timer_DoFire)
            {
                if (timer_DoFire > diff)
                    timer_DoFire -= diff;
                else
                    Defias_DoFire = true;
            }

            if (Defias_DoFire)
            {
                if (Creature* pTarget = me->FindNearestCreature(45937, 30.0f, true))
                {
                    if (ThrowTimer < diff)
                    {
                        DoCast(pTarget, 79778, true);
                        ThrowTimer = 4000;
                        // me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        // me->GetMotionMaster()->MovePoint(0, me->GetPositionX()-5, me->GetPositionY()+5, me->GetPositionZ());
                    }
                    else ThrowTimer -= diff;
                }
            }
        }
    };
};

class npc_fire_trigger : public CreatureScript
{
    public:
    npc_fire_trigger() : CreatureScript("npc_fire_trigger") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fire_triggerAI(creature);
    }

    struct npc_fire_triggerAI : public ScriptedAI
    {
        npc_fire_triggerAI(Creature *creature) : ScriptedAI(creature) {}

        uint32 StopFireTimer;

        void Reset()
        {
            me->CastSpell(me, 71025, true);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_TOSS_TORCH)
            {
                me->CastSpell(me, 71025, true);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            /*
            if (StopFireTimer <= diff)
            {
               me->RemoveAurasDueToSpell(71025);
            }else StopFireTimer -= diff;*/
        }
    };
};

class npc_summoner : public CreatureScript
{
    public:
    npc_summoner() : CreatureScript("npc_summoner") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_summonerAI(creature);
    }

    struct npc_summonerAI : public ScriptedAI
    {
        npc_summonerAI(Creature *creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->CastSpell(me, 64446, true);
        }
    };
};

enum eInvestigate
{
    NPC_INVESTIGATOR4    = 42559,
    NPC_HOME            = 42386
};

class npc_horatio_investigate : public CreatureScript
{
    public:
    npc_horatio_investigate() : CreatureScript("npc_horatio_investigate") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_horatio_investigateAI (creature);
    }

    struct npc_horatio_investigateAI : public ScriptedAI
    {
        npc_horatio_investigateAI(Creature *creature) : ScriptedAI(creature) {}

        uint8 Phase;
        uint32 TextTimer;
        uint64 PlayerGUID;
        uint64 Investigator04GUID;
        uint64 HomeGUID;
        bool bSummonn;
        bool bSummonn1;
        bool bSummonn2;

        void Reset()
        {
            Phase = 0;
            PlayerGUID = 0;
            Investigator04GUID = 0;
            HomeGUID;
            bSummonn = false;
            bSummonn1 = false;
            bSummonn2 = false;
            TextTimer = 1000;
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (who->IsWithinDistInMap(me, 15.0f))
            {
                StartSummon();
                PlayerGUID = who->GetGUID();
            }
        }

        void StartSummon()
        {
            if(!bSummonn)
            {
                if (Creature* Investigator04 = me->SummonCreature(NPC_INVESTIGATOR4, -9856.825f, 1279.25f, 40.96f, 3.29f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 66000))
                {
                    Investigator04GUID = Investigator04->GetGUID();
                    Investigator04->CastSpell(Investigator04, 79346, true);
                    bSummonn1 = true;
                }

                if (Creature* Home = me->SummonCreature(NPC_HOME, -9862.88f, 1278.52f, 40.80f, 0.43f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 66000))
                {
                    HomeGUID = Home->GetGUID();
                    Home->CastSpell(Home, 79346, true);
                    Home->CastSpell(Home, 52384, true);
                    bSummonn2 = true;
                }

                if (bSummonn1 && bSummonn2)
                {
                    bSummonn = true;
                    TextTimer = 2000;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (TextTimer < diff)
            {
                if (bSummonn)
                {
                    if (Player* player = me->GetPlayer(*me, PlayerGUID))
                    if (Creature* Investigator04 = me->GetCreature(*me, Investigator04GUID))
                    if (Creature* Home = me->GetCreature(*me, HomeGUID))
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                Investigator04->MonsterSay("You were standing right here! What the hell did you see?Speak up!", 0, 0);
                                TextTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 1:
                            {
                                Home->MonsterSay("I... I didn't see nothin'! He...he died of natural causes.", 0, 0);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 2:
                            {
                                Investigator04->MonsterSay("Natural causes? Two bullets in the chest and his shoes are on his head. What kind of natural death would that be?", 0, 0);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 3:
                            {
                                me->MonsterSay("Doesn't look good, rookie.", 0, 0);
                                TextTimer = 6000;
                                Phase++;
                                break;
                            }
                            case 4:
                            {
                                me->MonsterSay("This was an execution. Whoever did this was sending a message,,,", 0, 0);
                                TextTimer = 5000;
                                Phase++;
                                break;
                            }
                            case 5:
                            {
                                me->MonsterSay("A message for anyone that would dare snitch on these cryminals.", 0, 0);
                                TextTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 6:
                            {
                                me->MonsterSay("It would appear that poor Lou really put this foot...", 0, 0);
                                TextTimer = 4000;
                                Phase++;
                                break;
                            }
                            case 7:
                            {
                                me->MonsterSay("In his mouth...", 0, 0);
                                TextTimer = 30000;
                                Phase++;
                                break;
                            }
                            case 8: Reset();break;
                            default:
                            break;
                        }
                    }
                }
            }
            else TextTimer -=diff;
        }
    };
};

void AddSC_westfall()
{
    new npc_thug();
    new npc_horatio();
    new npc_westplains_drifter();
    new npc_crate_mine();
    new npc_homeless_citizen();
    new npc_shadowy_trigger();
    new npc_shadowy_tower();
    new npc_rise_br();
    new npc_defias_blackguard();
    new npc_fire_trigger();
    new npc_summoner();
    new npc_horatio_investigate();
}
