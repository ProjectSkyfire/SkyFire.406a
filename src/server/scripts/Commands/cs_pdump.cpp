/*
* Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
* Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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
Name: pdump_commandscript
%Complete: 100
Comment: All pdump related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "AccountMgr.h"
#include "ObjectMgr.h"
#include "PlayerDump.h"
#include "CharacterDatabase.h"

class pdump_commandscript : public CommandScript
{
public:
    pdump_commandscript() : CommandScript("pdump_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand pdumpCommandTable[] =
        {
            { "load",           SEC_ADMINISTRATOR,  true,  &HandlePDumpLoadCommand,                 "", NULL },
            { "write",          SEC_ADMINISTRATOR,  true,  &HandlePDumpWriteCommand,                "", NULL },
            { NULL,             0,                  false, NULL,                                    "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "pdump",          SEC_ADMINISTRATOR,  true,  NULL,                                   "", pdumpCommandTable },
            { NULL,             0,                  false, NULL,                                   "", NULL }
        };
        return commandTable;
    }


    static bool HandlePDumpLoadCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* fileStr = strtok((char*)args, " ");
        if (!fileStr)
            return false;

        char* accountStr = strtok(NULL, " ");
        if (!accountStr)
            return false;

        std::string accountName = accountStr;
        if (!AccountMgr::normalizeString(accountName))
        {
            handler->PSendSysMessage(LANGUAGE_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 accountId = AccountMgr::GetId(accountName);
        if (!accountId)
        {
            accountId = atoi(accountStr);                             // use original string
            if (!accountId)
            {
                handler->PSendSysMessage(LANGUAGE_ACCOUNT_NOT_EXIST, accountName.c_str());
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        if (!AccountMgr::GetName(accountId, accountName))
        {
            handler->PSendSysMessage(LANGUAGE_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* guidStr = NULL;
        char* nameStr = strtok(NULL, " ");

        std::string name;
        if (nameStr)
        {
            name = nameStr;
            // normalize the name if specified and check if it exists
            if (!normalizePlayerName(name))
            {
                handler->PSendSysMessage(LANGUAGE_INVALID_CHARACTER_NAME);
                handler->SetSentErrorMessage(true);
                return false;
            }

            if (ObjectMgr::CheckPlayerName(name, true) != CHAR_NAME_SUCCESS)
            {
                handler->PSendSysMessage(LANGUAGE_INVALID_CHARACTER_NAME);
                handler->SetSentErrorMessage(true);
                return false;
            }

            guidStr = strtok(NULL, " ");
        }

        uint32 guid = 0;

        if (guidStr)
        {
            guid = uint32(atoi(guidStr));
            if (!guid)
            {
                handler->PSendSysMessage(LANGUAGE_INVALID_CHARACTER_GUID);
                handler->SetSentErrorMessage(true);
                return false;
            }

            if (sObjectMgr->GetPlayerAccountIdByGUID(guid))
            {
                handler->PSendSysMessage(LANGUAGE_CHARACTER_GUID_IN_USE, guid);
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        switch (PlayerDumpReader().LoadDump(fileStr, accountId, name, guid))
        {
        case DUMP_SUCCESS:
            handler->PSendSysMessage(LANGUAGE_COMMAND_IMPORT_SUCCESS);
            break;
        case DUMP_FILE_OPEN_ERROR:
            handler->PSendSysMessage(LANGUAGE_FILE_OPEN_FAIL, fileStr);
            handler->SetSentErrorMessage(true);
            return false;
        case DUMP_FILE_BROKEN:
            handler->PSendSysMessage(LANGUAGE_DUMP_BROKEN, fileStr);
            handler->SetSentErrorMessage(true);
            return false;
        case DUMP_TOO_MANY_CHARS:
            handler->PSendSysMessage(LANGUAGE_ACCOUNT_CHARACTER_LIST_FULL, accountName.c_str(), accountId);
            handler->SetSentErrorMessage(true);
            return false;
        default:
            handler->PSendSysMessage(LANGUAGE_COMMAND_IMPORT_FAILED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        return true;
    }

    static bool HandlePDumpWriteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* fileStr = strtok((char*)args, " ");
        char* playerStr = strtok(NULL, " ");

        if (!fileStr || !playerStr)
            return false;

        uint64 guid;
        // character name can't start from number
        if (isNumeric(playerStr))
            guid = MAKE_NEW_GUID(atoi(playerStr), 0, HIGHGUID_PLAYER);
        else
        {
            std::string name = handler->extractPlayerNameFromLink(playerStr);
            if (name.empty())
            {
                handler->SendSysMessage(LANGUAGE_PLAYER_NOT_FOUND);
                handler->SetSentErrorMessage(true);
                return false;
            }

            guid = sObjectMgr->GetPlayerGUIDByName(name);
        }

        if (!sObjectMgr->GetPlayerAccountIdByGUID(guid))
        {
            handler->PSendSysMessage(LANGUAGE_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        switch (PlayerDumpWriter().WriteDump(fileStr, uint32(guid)))
        {
        case DUMP_SUCCESS:
            handler->PSendSysMessage(LANGUAGE_COMMAND_EXPORT_SUCCESS);
            break;
        case DUMP_FILE_OPEN_ERROR:
            handler->PSendSysMessage(LANGUAGE_FILE_OPEN_FAIL, fileStr);
            handler->SetSentErrorMessage(true);
            return false;
        case DUMP_CHARACTER_DELETED:
            handler->PSendSysMessage(LANGUAGE_COMMAND_EXPORT_DELETED_CHAR);
            handler->SetSentErrorMessage(true);
            return false;
        default:
            handler->PSendSysMessage(LANGUAGE_COMMAND_EXPORT_FAILED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        return true;
    }
};

void AddSC_pdump_commandscript()
{
    new pdump_commandscript();
}
