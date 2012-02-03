/*
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

/* ScriptData
Name: modadd_commandscript
%Complete: 100
Comment: Allows moderators to add specific items or spells to anyone
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"

class modadd_commandscript : public CommandScript
{
public:
    modadd_commandscript() : CommandScript("modadd_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand modAddCommandTable[] =
        {
            { "item",               SEC_MODERATOR,  false, &HandleModAddItemCommand,          "", NULL },
            { "spell",              SEC_MODERATOR,  false, &HandleModAddSpellCommand,         "", NULL },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "modadd",            SEC_PLAYER,      false, NULL,                "", modAddCommandTable },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        return commandTable;
    }

    static bool HandleModAddItemCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        uint32 itemId = 0;
        int32 count = 1;

        char* cId = handler->extractKeyFromLink((char*)args, "Hitem");
        if (!cId)
            return false;
        itemId = atol(cId);

        Player* pl = handler->GetSession()->GetPlayer();
        Player* plTarget = handler->getSelectedPlayer();
        if (!plTarget)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 pclass = plTarget->getClass();

        QueryResult result = WorldDatabase.PQuery("SELECT class FROM moderator_add WHERE id = %u AND type = 0", itemId);
        if (!result)
        {
            handler->PSendSysMessage("Item not found.");
            return true;
        }

        uint32 allowed_class = (*result)[0].GetUInt32();

        if (allowed_class > 0 && pclass != allowed_class)
        {
            handler->PSendSysMessage("Player class not allowed to have this item.");
            return true;
        }

        sLog->outDetail(handler->GetSkyFireString(LANG_ADDITEM), itemId, count);

        ItemTemplate const *pProto = sObjectMgr->GetItemTemplate(itemId);
        if (!pProto)
        {
            handler->PSendSysMessage(LANG_COMMAND_ITEMIDINVALID, itemId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        //Adding items
        uint32 noSpaceForCount = 0;

        // check space and find places
        ItemPosCountVec dest;
        InventoryResult msg = plTarget->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
        if (msg != EQUIP_ERR_OK)                               // convert to possible store amount
            count -= noSpaceForCount;

        if (count == 0 || dest.empty())                         // can't add any
        {
            handler->PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Item* item = plTarget->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

        if (count > 0 && item)
        {
            pl->SendNewItem(item, count, false, true);
            if (pl != plTarget)
                plTarget->SendNewItem(item, count, true, false);
        }

        if (noSpaceForCount > 0)
            handler->PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

        return true;
    }

    static bool HandleModAddSpellCommand(ChatHandler* handler, const char* args)
    {
        Player* targetPlayer = handler->getSelectedPlayer();

        if (!targetPlayer)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spell = handler->extractSpellIdFromLink((char*)args);
        if (!spell || !sSpellMgr->GetSpellInfo(spell))
            return false;

        uint32 pclass = targetPlayer->getClass();

        QueryResult result = WorldDatabase.PQuery("SELECT class FROM moderator_add WHERE id = %u AND type = 1", spell);
        if (!result)
        {
            handler->PSendSysMessage("Spell not found.");
            return true;
        }

        uint32 allowed_class = (*result)[0].GetUInt32();

        if (allowed_class > 0 && pclass != allowed_class)
        {
            handler->PSendSysMessage("Player class not allowed to learn this spell.");
            return true;
        }

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
        if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer()))
        {
            handler->PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spell);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (targetPlayer->HasSpell(spell))
        {
            if (targetPlayer == handler->GetSession()->GetPlayer())
                handler->SendSysMessage(LANG_YOU_KNOWN_SPELL);
            else
                handler->PSendSysMessage(LANG_TARGET_KNOWN_SPELL, handler->GetNameLink(targetPlayer).c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        targetPlayer->learnSpell(spell, false);

        return true;
    }
};

void AddSC_modadd_commandscript()
{
    new modadd_commandscript();
}
