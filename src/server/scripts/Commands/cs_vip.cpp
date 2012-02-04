/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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
Name: vip_commandscript
%Complete: ?
Comment: All vip related commands
Category: commandscripts
EndScriptData */

#include "ScriptPCH.h"

class vip_commandscript : public CommandScript
{
    public:
        vip_commandscript() : CommandScript("vip_commandscript") { }

        ChatCommand* GetCommands() const
        {
            static ChatCommand vipteleCommandTable[] =
            {
                { "dalaran",          SEC_VIP,		  false,  &HandleVipTeleDalaranCommand,      "", NULL },
                { "shattrath",        SEC_VIP,        false,  &HandleVipTeleShattrathCommand,    "", NULL },
                { "guruarena",        SEC_VIP,        false,  &HandleVipTeleGuruarenaCommand,    "", NULL },
				{ "stormwind",        SEC_VIP,		  false,  &HandleVipTeleStormwindCommand,    "", NULL },
                { "ironforge",        SEC_VIP,        false,  &HandleVipTeleIronforgeCommand,    "", NULL },
                { "darnassus",        SEC_VIP,        false,  &HandleVipTeleDarnassusCommand,    "", NULL },
				{ "exodar",           SEC_VIP,		  false,  &HandleVipTeleExodarCommand,       "", NULL },
                { "orgrimmar",        SEC_VIP,        false,  &HandleVipTeleOrgrimmarCommand,    "", NULL },
                { "thunderbluff",     SEC_VIP,        false,  &HandleVipTeleThunderbluffCommand, "", NULL },
				{ "undercity",        SEC_VIP,		  false,  &HandleVipTeleUndercityCommand,    "", NULL },
                { "silvermoon",       SEC_VIP,        false,  &HandleVipTeleSilvermoonCommand,   "", NULL },
                { NULL,               0,              false,  NULL,                              "", NULL }
            };
            static ChatCommand vipCommandTable[] =
            {
                { "bank",          SEC_VIP,      false, &HandleVipBankCommand,        "", NULL },
                { "save",          SEC_VIP,      false, &HandleVipSaveCommand,        "", NULL },
                { "tele",          SEC_VIP,      false, NULL,						  "", vipteleCommandTable },
                { "gamble",        SEC_VIP,      false,    &HandleVipGambleCommand,      "", NULL },
                { "roulette",      SEC_VIP,      false,    &HandleVipRouletteCommand,    "", NULL },
                { NULL,            0,            false, NULL,                         "", NULL }
            };
            static ChatCommand commandTable[] =
            {
                { "vip",            SEC_VIP,            false,  NULL,     "", vipCommandTable  },
                { NULL,             0,                  false,  NULL,     "", NULL }
            };
            return commandTable;
        }

		static bool HandleVipTeleDalaranCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			_player->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);

			return true;
		}

		static bool HandleVipTeleShattrathCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			_player->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);

			return true;
		}

		static bool HandleVipTeleGuruarenaCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			_player->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);

			return true;
		}

		static bool HandleVipTeleStormwindCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_ALLIANCE)
				_player->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleIronforgeCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_ALLIANCE)
				_player->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleDarnassusCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_ALLIANCE)
				_player->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleExodarCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_ALLIANCE)
				_player->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleOrgrimmarCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_HORDE)
				_player->TeleportTo(1, 1629.36f, -4373.39f, 31.2564f, 3.54839f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleThunderbluffCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_HORDE)
				_player->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleUndercityCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_HORDE)
				_player->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);
			else
				return false;

			return true;
		}

		static bool HandleVipTeleSilvermoonCommand(ChatHandler* handler, const char * /*args*/)
		{
			Player* _player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->IsFlying() || _player->IsMounted() || _player->isUsingLfg() || _player->InArena()  || _player->InBattleground() || _player->isInFlight())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, Mounted, Flying, Using Dungeon Finder, In BattleGround or Arena");
				return false;
            }

			if (_player->isInCombat())
			{
				handler->SendSysMessage(LANG_YOU_IN_COMBAT);
				handler->SetSentErrorMessage(true);
				return false;
			}

			if(_player->GetTeamId() == TEAM_HORDE)
				_player->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);
			else
				return false;

			return true;
		}

		static bool HandleVipSaveCommand(ChatHandler* handler, const char* /*args*/)
		{
			Player *player = handler->GetSession()->GetPlayer();

			// save GM account without delay and output message
			if (handler->GetSession()->GetSecurity() > SEC_PLAYER)
			{
				player->SaveToDB();
				handler->SendSysMessage(LANG_PLAYER_SAVED);
				return true;
			}

			// save if the player has last been saved over 20 seconds ago
			uint32 save_interval = sWorld->getIntConfig(CONFIG_INTERVAL_SAVE);
			if (save_interval == 0 || (save_interval > 20*IN_MILLISECONDS && player->GetSaveTimer() <= save_interval - 20*IN_MILLISECONDS))
				player->SaveToDB();

			return true;
		}

		static bool HandleVipBankCommand(ChatHandler* handler, const char* /*args*/)
		{
			Player *_player = handler->GetSession()->GetPlayer();

			if (!_player || _player->isDead() || _player->InArena()  || _player->InBattleground())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, In BattleGround or Arena");
				return false;
            }

			handler->GetSession()->SendShowBank(handler->GetSession()->GetPlayer()->GetGUID());

            return true;
        }

        static bool HandleVipGambleCommand(ChatHandler* handler, const char* args)
        {
            Player* _player = handler->GetSession()->GetPlayer();

            if (!_player || _player->isDead() || _player->InArena()  || _player->InBattleground())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, In BattleGround or Arena");
                return false;
            }

            if (_player->isInCombat())
            {
                handler->SendSysMessage(LANG_YOU_IN_COMBAT);
                handler->SetSentErrorMessage(true);
                return false;
            }

            char* px = strtok((char*)args, " ");

            if (!px)
                return false;

            uint32 money = (uint32)atoi(px);

            if (_player->GetMoney() < money)
            {
                handler->SendSysMessage("You can not bet with money you do not have!");
                return false;
            }
            else
            {
                if (money > 0)
                    if (rand()%100 < 50)
                    {
                        _player->ModifyMoney(money * 2);
                        handler->SendSysMessage("You have won and doubled your bet");
                    }
                    else
                    {
                        _player->ModifyMoney(-int(money));
                        handler->SendSysMessage("You have lost");
                    }
            }
            return true;
        }

        static bool HandleVipRouletteCommand(ChatHandler* handler, const char* args)
        {
            Player* _player = handler->GetSession()->GetPlayer();

            if (!_player || _player->isDead() || _player->InArena()  || _player->InBattleground())
            {
                handler->SendSysMessage("Error. Check if you are not: Dead, In BattleGround or Arena");
                return false;
            }

            if (_player->isInCombat())
            {
                handler->SendSysMessage(LANG_YOU_IN_COMBAT);
                handler->SetSentErrorMessage(true);
                return false;
            }

            char* px = strtok((char*)args, " ");

            if (!px)
                return false;

            uint32 money = (uint32)atoi(px);

            if (_player->GetMoney() < money)
            {
                handler->SendSysMessage("You can not bet with money you do not have!");
                return false;
            }
            else
            {
                if (money > 0)
                {
                    if (rand()%36 < 1)
                    {
                        _player->ModifyMoney(money * 7);
                        handler->SendSysMessage("You have won 7 times your bet, congratulations!");
                    }
                    else
                    {
                        _player->ModifyMoney(-int(money));
                        handler->SendSysMessage("You have lost");
                    }
                }
            }
			
			return true;
		}
};

void AddSC_vip_commandscript()
{
    new vip_commandscript();
}