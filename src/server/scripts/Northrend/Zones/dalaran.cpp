/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011-2012 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
 SFName: Dalaran
 SF%Complete: 80%
 SFComment:
 SFCategory: Northrend script
 Script Data End */

#include "ScriptPCH.h"
#include "AchievementMgr.h"
#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "BattlefieldWG.h"

/*******************************************************
 * npc_mageguard_dalaran
 *******************************************************/

enum Spells
{
    SPELL_TRESPASSER_A      = 54028,
    SPELL_TRESPASSER_H      = 54029,
    SPELL_DETECTION         = 70465,

    SPELL_SUNREAVER_DISGUISE_FEMALE        = 70973,
    SPELL_SUNREAVER_DISGUISE_MALE          = 70974,
    SPELL_SILVER_COVENANT_DISGUISE_FEMALE  = 70971,
    SPELL_SILVER_COVENANT_DISGUISE_MALE    = 70972,
};

enum NPCs // All outdoor guards are within 35.0f of these NPCs
{
    NPC_APPLEBOUGH_A        = 29547,
    NPC_SWEETBERRY_H        = 29715,
};

class npc_mageguard_dalaran : public CreatureScript
{
public:
    npc_mageguard_dalaran() : CreatureScript("npc_mageguard_dalaran") {}

    struct npc_mageguard_dalaranAI : public Scripted_NoMovementAI
    {
        npc_mageguard_dalaranAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, true);
            creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
        }

        void Reset()
        {
            me->CastSpell(me, SPELL_DETECTION, true);
        }

        void EnterCombat(Unit* /*who*/) {}

        void AttackStart(Unit* /*who*/) {}

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld() || who->GetZoneId() != 4395)
                return;

            if (!me->IsWithinDist(who, 65.0f, false))
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();

            if (!player || player->isGameMaster() || player->IsBeingTeleported() ||
                // If player has Disguise aura for quest A Meeting With The Magister or An Audience With The Arcanist, do not teleport it away but let it pass
                player->HasAura(SPELL_SUNREAVER_DISGUISE_FEMALE) || player->HasAura(SPELL_SUNREAVER_DISGUISE_MALE) ||
                player->HasAura(SPELL_SILVER_COVENANT_DISGUISE_FEMALE) || player->HasAura(SPELL_SILVER_COVENANT_DISGUISE_MALE))
                return;

            switch (me->GetEntry())
            {
                case 29254:
                if (player->GetTeam() == HORDE)              // Horde unit found in Alliance area
                {
                    if (GetClosestCreatureWithEntry(me, NPC_APPLEBOUGH_A, 32.0f))
                    {
                        if (me->isInBackInMap(who, 12.0f)) // In my line of sight, "outdoors", and behind me
                            DoCast(who, SPELL_TRESPASSER_A); // Teleport the Horde unit out
                    }
                    else   // In my line of sight, and "indoors"
                        DoCast(who, SPELL_TRESPASSER_A); // Teleport the Horde unit out
                }
                break;
                case 29255:
                if (player->GetTeam() == ALLIANCE)           // Alliance unit found in Horde area
                {
                    if (GetClosestCreatureWithEntry(me, NPC_SWEETBERRY_H, 32.0f))
                    {
                        if (me->isInBackInMap(who, 12.0f)) // In my line of sight, "outdoors", and behind me
                            DoCast(who, SPELL_TRESPASSER_H); // Teleport the Alliance unit out
                    }
                    else // In my line of sight, and "indoors"
                        DoCast(who, SPELL_TRESPASSER_H); // Teleport the Alliance unit out
                }
                break;
            }
            me->SetOrientation(me->GetHomePosition().GetOrientation());
            return;
        }

        void UpdateAI(const uint32 /*diff*/) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mageguard_dalaranAI(creature);
    }
};

/*######
 ## npc_hira_snowdawn
 ######*/

enum eHiraSnowdawn
{
    SPELL_COLD_WEATHER_FLYING       = 54197
};

#define GOSSIP_TEXT_TRAIN_HIRA "I seek training to ride a steed."

class npc_hira_snowdawn: public CreatureScript
{
public:
    npc_hira_snowdawn() : CreatureScript("npc_hira_snowdawn") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!creature->isVendor() || !creature->isTrainer())
            return false;

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_TRAIN_HIRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

        if (player->getLevel() >= 80 && player->HasSpell(SPELL_COLD_WEATHER_FLYING))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action == GOSSIP_ACTION_TRAIN)
            player->GetSession()->SendTrainerList(creature->GetGUID());

        if (action == GOSSIP_ACTION_TRADE)
            player->GetSession()->SendListInventory(creature->GetGUID());

        return true;
    }
};

/*######
 ## npc_archmage_vargoth
 ######*/

enum eArchmageVargoth
{
    ZONE_DALARAN                 = 4395,
    ITEM_ACANE_MAGIC_MASTERY     = 43824,
    SPELL_CREATE_FAMILAR         = 61457,
    SPELL_FAMILAR_PET            = 61472,
    ITEM_FAMILAR_PET             = 44738
};

#define GOSSIP_TEXT_FAMILIAR_WELCOME "I have a book that might interest you. Would you like to take a look?"
#define GOSSIP_TEXT_FAMILIAR_THANKS  "Thank you! I will be sure to notify you if I find anything else."

class npc_archmage_vargoth: public CreatureScript
{
public:
    npc_archmage_vargoth() : CreatureScript("npc_archmage_vargoth") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver() && creature->GetZoneId() != ZONE_DALARAN)
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->HasItemCount(ITEM_ACANE_MAGIC_MASTERY, 1, false))
        {
            if (!player->HasSpell(SPELL_FAMILAR_PET) && !player->HasItemCount(ITEM_FAMILAR_PET, 1, true))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FAMILIAR_WELCOME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FAMILIAR_THANKS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(40006, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            creature->CastSpell(player, SPELL_CREATE_FAMILAR, false);
            player->CLOSE_GOSSIP_MENU();
            break;
        }

        return true;
    }
};

/*######
 ## npc_rhonin
 ######*/

enum npcRhonin
{
    ACHIEVEMENT_HIGHER_LEARNING                = 1956,
    ITEM_THE_SCHOOLS_OF_ARCANE_MAGIC           = 43824,
    SPELL_THE_SCHOOLS_OF_ARCANE_MAGIC          = 59983,
//QUEST_ALL_IS_WELL_THAT_ENDS_WELL             = 13631,
//QUEST_HEROIC_ALL_IS_WELL_THAT_ENDS_WELL      = 13819
};

#define GOSSIP_TEXT_RESTORE_ITEM       "[PH] Please give me a new <The Schools of Arcane Magic - Mastery>"

class npc_rhonin: public CreatureScript
{
public:
    npc_rhonin() : CreatureScript("npc_rhonin") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        // Fixme... "HasAchieved" needs to be a member of player
        // if (player->HasAchieved(ACHIEVEMENT_HIGHER_LEARNING) && !player->HasItemCount(ITEM_THE_SCHOOLS_OF_ARCANE_MAGIC, 1, true))
            // player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_RESTORE_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->CastSpell(player, SPELL_THE_SCHOOLS_OF_ARCANE_MAGIC, false);
            player->CLOSE_GOSSIP_MENU();
        }

        return true;
    }

    // FIXME: add Quest 13631, 13819 Event

    //bool OnQuestComplete(Player* /*player*/, Creature* /*creature*/, Quest const* /*quest*/)
    //{
    //    return true;
    //}
};

///- WinterGrasp Battle-mages
enum WintergraspBattleMage
{
    SPELL_PORTAL_VISUAL        = 60223,
    GO_WINTERGRASP_PORTAL      = 193772
};

class npc_alliance_wg_battle_mage : public CreatureScript
{
public:
    npc_alliance_wg_battle_mage() : CreatureScript("npc_alliance_wg_battle_mage") { }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_alliance_wg_battle_mageAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!sWorld->getBoolConfig(CONFIG_WINTERGRASP_ENABLE))
            return false;

        if (BattlefieldWG *battleWG = (BattlefieldWG*) sBattlefieldMgr->GetBattlefieldToZoneId(4197))
        {
            if (battleWG->IsWarTime())
            {
                if (battleWG->GetDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14777, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14781, creature->GetGUID());
            }
            else
            {
                if (battleWG->GetDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14775, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14782, creature->GetGUID());
            }
        }
        return true;
    }

    struct npc_alliance_wg_battle_mageAI : public ScriptedAI
    {
        npc_alliance_wg_battle_mageAI(Creature* creature) : ScriptedAI(creature)
        {
            portalTimer = 0;
            portalPhase = 0;
            Check = true;
        }

        uint32 portalTimer;
        uint8 portalPhase;
        GameObject* WintergraspPortal;
        bool Player;
        bool Check;
        bool Check2;

        void UpdateAI(const uint32 diff)
        {
            // If WG is disabled, don't do anything.
            if (!sWorld->getBoolConfig(CONFIG_WINTERGRASP_ENABLE))
                return;

            if (Battlefield *battleWG = (Battlefield*)sBattlefieldMgr->GetBattlefieldToZoneId(4197))
            {
                // Get playerlist if there is.
                if (battleWG->IsWarTime() && Check == true)
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (!PlayerList.isEmpty())
                        {
                            if (i->getSource()->GetDistance2d(me) <= 75)
                            {
                                Player = true;
                                Check = false;
                            }
                            else
                            {
                                Player = false;
                                Check = false;
                                Check2 = true;
                            }
                        }
                        else
                        {
                            Player = false;
                            Check = false;
                            Check2 = true;
                        }
                    }
                }

                if (battleWG->IsWarTime())
                {
                    if (Player == true) //(false) If there isn't any player, then, don't cast the portal spell. Just summon gameobject.
                    {
                        if (portalTimer <= diff)
                        {
                            switch (portalPhase)
                            {
                            case 0:
                                me->SetOrientation(4.037271f);
                                me->SendMovementFlagUpdate();
                                ++portalPhase;
                                portalTimer = 100;
                                break;
                            case 1:
                                me->AI()->DoCast(SPELL_PORTAL_VISUAL);
                                ++portalPhase;
                                portalTimer = 900;
                                break;
                            case 2:
                                WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5686.974609f, 773.303711f, 647.753235f, 5.572729f, 0, 0, 0.324484f, -0.945891f, 0);
                                me->SetOrientation(5.515240f);
                                me->SendMovementFlagUpdate();
                                me->MonsterYell("Reinforcements are needed on the Wintergrasp battlefield! I have opened a portal for quick travel to the battle at The Silver Enclave.", LANG_UNIVERSAL, 0);
                                ++portalPhase;
                                portalTimer = 1000;
                                break;
                            }
                        } else portalTimer -= diff;
                    }
                    else
                    {
                        if (Check2 == true) // If the portal isn't exist
                        {
                            WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5686.974609f, 773.303711f, 647.753235f, 5.572729f, 0, 0, 0.324484f, -0.945891f, 0);
                            Check2 = false;
                        }
                    }
                }
                else
                {
                    if (battleWG->GetDefenderTeam() == TEAM_ALLIANCE)
                    {
                        if (battleWG->GetTimer() <= 3600000) // the portal will disappear, for an hour after each match.
                        {
                            portalTimer = 0;
                            portalPhase = 0;
                            Check = true;
                            Check2 = false;
                            if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                                WintergraspPortal->RemoveFromWorld();
                        }
                    }
                    else
                    {
                        portalTimer = 0;
                        portalPhase = 0;
                        Check = true;
                        Check2 = false;
                        if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                            WintergraspPortal->RemoveFromWorld();
                    }
                }
            }
        }
    };
};

class npc_horde_wg_battle_mage : public CreatureScript
{
public:
    npc_horde_wg_battle_mage() : CreatureScript("npc_horde_wg_battle_mage") { }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_horde_wg_battle_mageAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!sWorld->getBoolConfig(CONFIG_WINTERGRASP_ENABLE))
            return false;

        if (Battlefield *battleWG = (Battlefield*)sBattlefieldMgr->GetBattlefieldToZoneId(4197))
        {
            if (battleWG->IsWarTime())
            {
                if (battleWG->GetDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14777, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14781, creature->GetGUID());
            }
            else
            {
                if (battleWG->GetDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14775, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14782, creature->GetGUID());
            }
        }
        return true;
    }

    struct npc_horde_wg_battle_mageAI : public ScriptedAI
    {
        npc_horde_wg_battle_mageAI(Creature* creature) : ScriptedAI(creature)
        {
            portalTimer = 0;
            portalPhase = 0;
            Check = true;
        }

        uint32 portalTimer;
        uint8 portalPhase;
        GameObject* WintergraspPortal;
        bool Player;
        bool Check;
        bool Check2;

        void UpdateAI(const uint32 diff)
        {
            // If WG is disabled, don't do anything.
            if (!sWorld->getBoolConfig(CONFIG_WINTERGRASP_ENABLE))
                return;

            if (Battlefield *battleWG = (Battlefield*)sBattlefieldMgr->GetBattlefieldToZoneId(4197))
            {
                // Get playerlist if there is.
                if (battleWG->IsWarTime() && Check == true)
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (!PlayerList.isEmpty())
                        {
                            if (i->getSource()->GetDistance2d(me) <= 75)
                            {
                                Player = true;
                                Check = false;
                            }
                            else
                            {
                                Player = false;
                                Check = false;
                                Check2 = true;
                            }
                        }
                        else
                        {
                            Player = false;
                            Check = false;
                            Check2 = true;
                        }
                    }
                }

                if (battleWG->IsWarTime())
                {
                    if (Player == true) //(false) If there isn't any player, then, don't cast the portal spell. Just summon gameobject.
                    {
                        if (portalTimer <= diff)
                        {
                            switch (portalPhase)
                            {
                            case 0:
                                me->SetOrientation(4.356160f);
                                me->SendMovementFlagUpdate();
                                ++portalPhase;
                                portalTimer = 100;
                                break;
                            case 1:
                                me->AI()->DoCast(SPELL_PORTAL_VISUAL);
                                ++portalPhase;
                                portalTimer = 900;
                                break;
                            case 2:
                                WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5924.042969f, 570.354492f, 661.087280f, 5.930885f, 0, 0, 0.324484f, -0.945891f, 0);
                                me->SetOrientation(6.003930f);
                                me->SendMovementFlagUpdate();
                                ++portalPhase;
                                portalTimer = 1000;
                                break;
                            }
                        } else portalTimer -= diff;
                    }
                    else
                    {
                        if (Check2 == true) // If the portal isn't exist
                        {
                            WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5686.974609f, 773.303711f, 647.753235f, 5.572729f, 0, 0, 0.324484f, -0.945891f, 0);
                            Check2 = false;
                        }
                    }
                }
                else
                {
                    if (battleWG->GetDefenderTeam() == TEAM_HORDE)
                    {
                        if (battleWG->GetTimer() <= 3600000) // An hour before battle begin, the portal will disappear.
                        {
                            portalTimer = 0;
                            portalPhase = 0;
                            Check = true;
                            Check2 = false;
                            if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                                WintergraspPortal->RemoveFromWorld();
                        }
                    }
                    else
                    {
                        portalTimer = 0;
                        portalPhase = 0;
                        Check = true;
                        Check2 = false;
                        if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                            WintergraspPortal->RemoveFromWorld();
                    }
                }
            }
        }
    };
};

void AddSC_dalaran()
{
    new npc_mageguard_dalaran();
    new npc_hira_snowdawn();
    new npc_archmage_vargoth();
    new npc_rhonin();
    new npc_alliance_wg_battle_mage();
    new npc_horde_wg_battle_mage();
}
