/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
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

/* ScriptData
Name: Npc_Multi_Professions Trainer
%Complete: 4
Comment: Provides support for multi-profession trainer new to cataclysm
Category: NPCs
EndScriptData */

#include "ScriptPCH.h"

#define SAY_GATHER1 "Tell me about the gathering professions"
#define SAY_PRODUC1 "Tell me about the production professions"
#define SAY_TEST1 "Learn Herbalism"
#define SAY_TEST2 "Learn Inscription"

enum ProfessionSpells
{
    S_LEARN_HERB1 = 182,
    S_LEARN_INSC1 = 773
};

class multi_profession_npc : public CreatureScript
{
public:

    multi_profession_npc()
        : CreatureScript("multi_profession_npc")
    {
    }

    void SendActionMenu(Player* player, Creature* creature, uint32 action)
    {
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, S_LEARN_HERB1, true);
                player->CLOSE_GOSSIP_MENU();
            break;

            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, S_LEARN_INSC1, true);
                player->CLOSE_GOSSIP_MENU();
            break;

            case GOSSIP_ACTION_INFO_DEF + 2:
                player->SEND_GOSSIP_MENU(17126, creature->GetGUID());
            break;

            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SEND_GOSSIP_MENU(17127, creature->GetGUID());
            break;
        }
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, SAY_TEST1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, SAY_TEST2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, SAY_GATHER1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, SAY_PRODUC1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        player->PlayerTalkClass->SendGossipMenu(17125, creature->GetGUID());

        return true;
    }
};

void AddSC_multi_profession_npc()
{
    new multi_profession_npc();
}
