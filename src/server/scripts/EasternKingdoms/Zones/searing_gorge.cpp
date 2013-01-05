/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2005-2013 MaNGOS <http://www.getmangos.com/>
 * Copyright (C) 2008-2013 Trinity <http://www.trinitycore.org/>
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
SkyFireScript_Name: Searing_Gorge
%Complete: 95
Comment: Author Kiper
Category: Searing Gorge
EndScriptData */

/* ContentData
npc_kalaran_windblade
npc_lothos_riftwaker
npc_zamael_lunthistle
npc_glassweb_spid
npc_lunk_spider_ride
npc_dark_iron_steamsmith
npc_lunk_dwarf_ride
EndContentData */

#include "ScriptPCH.h"
#include "CreatureTextMgr.h"

/*######
## npc_kalaran_windblade
######*/

#define GOSSIP_HELLO_KW    "Tell me what drives this vengance?"
#define GOSSIP_SELECT_KW1  "Continue please"
#define GOSSIP_SELECT_KW2  "Let me confer with my colleagues"

class npc_kalaran_windblade : public CreatureScript
{
public:
    npc_kalaran_windblade() : CreatureScript("npc_kalaran_windblade") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT_KW1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(1954, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT_KW2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(1955, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(3441);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(3441) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_KW, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

/*######
## npc_lothos_riftwaker
######*/

#define GOSSIP_HELLO_LR "Teleport me to the Molten Core"

class npc_lothos_riftwaker : public CreatureScript
{
public:
    npc_lothos_riftwaker() : CreatureScript("npc_lothos_riftwaker") { }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(409, 1096, -467, -104.6f, 3.64f);
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestRewardStatus(7487) || player->GetQuestRewardStatus(7848))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_LR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

/*######
## npc_zamael_lunthistle
######*/

#define GOSSIP_HELLO_ZL     "Tell me your story"
#define GOSSIP_SELECT_ZL1   "Please continue..."
#define GOSSIP_SELECT_ZL2   "Goodbye"

class npc_zamael_lunthistle : public CreatureScript
{
public:
    npc_zamael_lunthistle() : CreatureScript("npc_zamael_lunthistle") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT_ZL1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(1921, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT_ZL2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(1922, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(3377);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(3377) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_ZL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(1920, creature->GetGUID());

        return true;
    }
};

enum eGlasswebSpider
{
    QUEST_A_PROPER_ANTIVENOM             = 27958,
    QUEST_LUNKS_ADVENTURE_SPIDER_RIDER   = 27959
};

class npc_glassweb_spider : public CreatureScript
{
public:
    npc_glassweb_spider() : CreatureScript("npc_glassweb_spider") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_glassweb_spiderAI (creature);
    }

    struct npc_glassweb_spiderAI : public ScriptedAI
    {
        npc_glassweb_spiderAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustDied(Unit* killer)
        {
            if (killer->ToPlayer()->GetQuestStatus(QUEST_LUNKS_ADVENTURE_SPIDER_RIDER) == QUEST_STATUS_INCOMPLETE)
                return;

            if (killer->ToPlayer()->GetQuestStatus(QUEST_A_PROPER_ANTIVENOM) == QUEST_STATUS_INCOMPLETE)
                killer->CastSpell(killer->GetPositionX(), killer->GetPositionY(),killer->GetPositionZ(), 88152, true);
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            me->GetMotionMaster()->MoveRandom(20);
            me->CombatStop();
            me->DeleteThreatList();
            me->RemoveAllAuras();
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
          DoMeleeAttackIfReady();
        }
    };
};

enum eLunkSpiderRide
{
    NPC_GLASSWEB_SPIDER             = 5856,
    SPELL_TUMMY_VENOM               = 88154,
    SPELL_RIDE_VEHICLE_HARDCODED    = 46598
};

class npc_lunk_spider_ride : public CreatureScript
{
public:
    npc_lunk_spider_ride() : CreatureScript("npc_lunk_spider_ride") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_A_PROPER_ANTIVENOM) == QUEST_STATUS_INCOMPLETE)
        {
            player->AddItem(62809,(urand(1, 4)));
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->RemoveAurasDueToSpell(SPELL_TUMMY_VENOM);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lunk_spider_rideAI (creature);
    }

    struct npc_lunk_spider_rideAI : public ScriptedAI
    {
        npc_lunk_spider_rideAI(Creature* creature) : ScriptedAI(creature)  {}

        uint32 Step;
        uint32 Timer;

        void Reset()
        {
            Step   = 0;
            Timer  = 2000;
            if (Unit *summoner = me->ToTempSummon()->GetSummoner())
                if (summoner->GetTypeId() == TYPEID_PLAYER)
                    me->GetMotionMaster()->MoveFollow(summoner, 0.0f, 0.0f);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
        {
            if (quest->GetQuestId() == QUEST_LUNKS_ADVENTURE_SPIDER_RIDER)
            {
                me->DisappearAndDie();
            }
            return true;
        }

        void UpdateAI(const uint32 diff)
        {
            if (Creature* Spider = me->FindNearestCreature(NPC_GLASSWEB_SPIDER, 10))
            {
                if (Spider->HealthBelowPct(50))
                {
                    if (Timer < diff)
                    {
                        switch (Step)
                        {
                            case 0:
                                me->CastSpell(Spider, SPELL_RIDE_VEHICLE_HARDCODED, true);
                                Timer = 2000;
                                ++Step;
                                break;
                            case 1:
                                sCreatureTextMgr->SendChat(me, 0, 0);
                                Timer = 2000;
                                ++Step;
                                break;
                            case 2:
                                Timer = 3000;
                                ++Step;
                                break;
                            case 3:
                                me->ExitVehicle(0);
                                Spider->DisappearAndDie();
                                me->CastSpell(me, SPELL_TUMMY_VENOM, true);
                                sCreatureTextMgr->SendChat(me, 1, 0);
                                if (Unit *summoner = me->ToTempSummon()->GetSummoner())
                                    if (summoner->GetTypeId() == TYPEID_PLAYER)
                                        me->GetMotionMaster()->MoveFollow(summoner, 0.0f, 0.0f);
                                Timer = 2000;
                                Step = 0;
                                break;
                        }
                    }
                    else Timer -= diff;
                }
            }

            if (me->HasAura(SPELL_TUMMY_VENOM))
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            if (Unit *summoner = me->ToTempSummon()->GetSummoner())
                if (summoner->GetTypeId() == TYPEID_PLAYER)
                    if (summoner->ToPlayer()->GetQuestStatus(QUEST_LUNKS_ADVENTURE_SPIDER_RIDER) == QUEST_STATUS_INCOMPLETE)
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
                    else
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
        }
    };
};

enum eDarkIronSteamsmith
{
    QUEST_RECON_ESSENTIALS                     = 27977,
    QUEST_LUNKS_ADVENTURE_CRANKY_LITTLE_DWARFS = 27983
};

class npc_dark_iron_steamsmith : public CreatureScript
{
public:
    npc_dark_iron_steamsmith() : CreatureScript("npc_dark_iron_steamsmith") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_iron_steamsmithAI (creature);
    }

    struct npc_dark_iron_steamsmithAI : public ScriptedAI
    {
        npc_dark_iron_steamsmithAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustDied(Unit* killer)
        {
            if (killer->GetTypeId() == TYPEID_PLAYER)
            {
                if (killer->ToPlayer()->GetQuestStatus(QUEST_LUNKS_ADVENTURE_CRANKY_LITTLE_DWARFS) == QUEST_STATUS_INCOMPLETE)
                    return;

                if (killer->ToPlayer()->GetQuestStatus(QUEST_RECON_ESSENTIALS) == QUEST_STATUS_INCOMPLETE)
                    killer->CastSpell(killer->GetPositionX(), killer->GetPositionY(), killer->GetPositionZ(), 88291, true);
            }
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            me->CombatStop();
            me->DeleteThreatList();
            me->RemoveAllAuras();
            sCreatureTextMgr->SendChat(me, 0, 0);
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            DoMeleeAttackIfReady();
        }
    };
};

enum eLunkDwavrfRide
{
    NPC_DARK_IRON_STEAMSMITH      = 5840,
    SPELL_HOLDING_LOOT            = 88320,
};

class npc_lunk_dwarf_ride : public CreatureScript
{
public:
    npc_lunk_dwarf_ride() : CreatureScript("npc_lunk_dwarf_ride") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lunk_dwarf_rideAI (creature);
    }

    struct npc_lunk_dwarf_rideAI : public ScriptedAI
    {
        npc_lunk_dwarf_rideAI(Creature* creature) : ScriptedAI(creature)  {}

        uint32 Step;
        uint32 Timer;

        void Reset()
        {
            Step    = 0;
            Timer   = 2000;
            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                if (summoner->GetTypeId() == TYPEID_PLAYER)
                    me->GetMotionMaster()->MoveFollow(summoner, 0.0f, 0.0f);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
        {
            if (quest->GetQuestId() == QUEST_LUNKS_ADVENTURE_CRANKY_LITTLE_DWARFS)
            {
                me->DisappearAndDie();
            }
            return true;
        }

        void UpdateAI(const uint32 diff)
        {
            if (Creature* Dwarf = me->FindNearestCreature(NPC_DARK_IRON_STEAMSMITH, 10))
            {
                if (Dwarf->HealthBelowPct(40))
                {
                    if (Timer < diff)
                    {
                        switch (Step)
                        {
                            case 0:
                                me->CastSpell(Dwarf, SPELL_RIDE_VEHICLE_HARDCODED, true);
                                Timer = 1000;
                                ++Step;
                                break;
                            case 1:
                                Timer = 1000;
                                ++Step;
                                break;
                            case 2:
                                Timer = 3000;
                                ++Step;
                                break;
                            case 3:
                                me->ExitVehicle(0);
                                me->Kill(Dwarf);
                                me->CastSpell(me, SPELL_HOLDING_LOOT, true);
                                sCreatureTextMgr->SendChat(me, 0, 0);
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    if (summoner->GetTypeId() == TYPEID_PLAYER)
                                         me->GetMotionMaster()->MoveFollow(summoner, 0.0f, 0.0f);
                                Timer = 2000;
                                Step = 0;
                                break;
                        }
                    }
                    else Timer -= diff;
                }
            }

                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (summoner->GetTypeId() == TYPEID_PLAYER)
                        if (summoner->ToPlayer()->GetQuestStatus(QUEST_LUNKS_ADVENTURE_CRANKY_LITTLE_DWARFS) == QUEST_STATUS_INCOMPLETE)
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
                    else
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
        }
    };
};

void AddSC_searing_gorge()
{
    new npc_kalaran_windblade();
    new npc_lothos_riftwaker();
    new npc_zamael_lunthistle();
    new npc_glassweb_spider;
    new npc_lunk_spider_ride();
    new npc_dark_iron_steamsmith();
    new npc_lunk_dwarf_ride();
}
