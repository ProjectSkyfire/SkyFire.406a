/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2013 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "ObjectMgr.h"
#include "GuildMgr.h"
#include "Log.h"
#include "Opcodes.h"
#include "Guild.h"
#include "GossipDef.h"
#include "SocialMgr.h"

// Helper for getting guild object of session's player.
// If guild does not exist, sends error (if necessary).
inline Guild* _GetPlayerGuild(WorldSession* session, bool sendError = false)
{
    if (uint32 guildId = session->GetPlayer()->GetGuildId())    // If guild id = 0, player is not in guild
        if (Guild* guild = sGuildMgr->GetGuildById(guildId))   // Find guild by id
            return guild;
    if (sendError)
        Guild::SendCommandResult(session, GUILD_CREATE_S, ERR_GUILD_PLAYER_NOT_IN_GUILD);
    return NULL;
}

void WorldSession::HandleGuildQueryOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_QUERY");

    uint64 guildId;
    uint64 player; //4.0.6a
    recvPacket >> guildId;
    recvPacket >> player;
    // Use received guild id to access guild method (not player's guild id)
    uint32 lowGuildId = GUID_LOPART(guildId);
    if (Guild* guild = sGuildMgr->GetGuildById(lowGuildId))
        guild->HandleQuery(this);
    else
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_PLAYER_NOT_IN_GUILD);
}

void WorldSession::HandleGuildCreateOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_CREATE");

    std::string name;
    recvPacket >> name;

    if (!GetPlayer()->GetGuildId())             // Player cannot be in guild
    {
        Guild* guild = new Guild();
        if (guild->Create(GetPlayer(), name))
            sGuildMgr->AddGuild(guild);
        else
            delete guild;
    }
}

void WorldSession::HandleGuildInviteOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_INVITE");

    std::string invitedName;
    recvPacket >> invitedName;

    if (normalizePlayerName(invitedName))
        if (Guild* guild = _GetPlayerGuild(this, true))
            guild->HandleInviteMember(this, invitedName);
}

void WorldSession::HandleGuildRemoveOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_REMOVE");

    uint64 guid;
    recvPacket >> guid; // target
    recvPacket.read_skip<uint64>();

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleRemoveMember(this, guid);
}

void WorldSession::HandleGuildAcceptOpcode(WorldPacket& /*recvPacket*/)
{
    //recvPacket.read_skip<uint64>();

    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_ACCEPT");
    //recvPacket.read_skip<uint64>();

    // Player cannot be in guild
    if (!GetPlayer()->GetGuildId())
        // Guild where player was invited must exist
        if (Guild* guild = sGuildMgr->GetGuildById(GetPlayer()->GetGuildIdInvited()))
            guild->HandleAcceptMember(this);
}

void WorldSession::HandleGuildDeclineOpcode(WorldPacket& recvPacket)
{
    recvPacket.read_skip<uint64>();
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_DECLINE");

    GetPlayer()->SetGuildIdInvited(0);
    GetPlayer()->SetInGuild(0);
}

void WorldSession::HandleGuildInfoOpcode(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_INFO");

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->SendInfo(this);
}

void WorldSession::HandleGuildRosterOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_ROSTER");

    uint64 guildGUID, playerGUID;

    recvPacket >> guildGUID >> playerGUID;

    if (Guild* guild = _GetPlayerGuild(this))
        guild->HandleRoster(this);
}

void WorldSession::HandleGuildPromoteOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_PROMOTE");

    uint64 guid;
    recvPacket >> guid; // target guid
    recvPacket.read_skip<uint64>(); // command issuer's guid?

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleUpdateMemberRank(this, guid, false);
}

void WorldSession::HandleGuildDemoteOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_DEMOTE");

    uint64 guid;
    recvPacket >> guid;                  // target guid
    recvPacket.read_skip<uint64>();      // command issuer's guid?

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleUpdateMemberRank(this, guid, true);
}

void WorldSession::HandleGuildLeaveOpcode(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_LEAVE");

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleLeaveMember(this);
}

void WorldSession::HandleGuildDisbandOpcode(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_DISBAND");

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleDisband(this);
}

void WorldSession::HandleGuildLeaderOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_LEADER");

    std::string name;
    recvPacket.read_skip<uint64>(); // guild GUID
    recvPacket.read_skip<uint64>(); // user's guid?
    recvPacket >> name;

    if (normalizePlayerName(name))
        if (Guild* guild = _GetPlayerGuild(this, true))
            guild->HandleSetLeader(this, name);
}

void WorldSession::HandleGuildChangeInfoTextOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_INFO_TEXT");

    recvPacket.read_skip<uint64>(); // issuer's guid
    recvPacket.read_skip<uint64>(); // guild's guid
    std::string info;
    recvPacket >> info;

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleSetInfo(this, info);
}

void WorldSession::HandleGuildMOTDOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_MOTD");

    recvPacket.read_skip<uint64>();
    recvPacket.read_skip<uint64>();

    std::string motd;
    recvPacket >> motd;

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleSetMOTD(this, motd);
}

void WorldSession::HandleGuildExperienceOpcode(WorldPacket& recvPacket)
{
    recvPacket.read_skip<uint64>();

    if (Guild* guild = sGuildMgr->GetGuildById(_player->GetGuildId()))
    {
        WorldPacket data(SMSG_GUILD_XP_UPDATE, 8*5);
        data << uint64(guild->GetXPCap());                                  // max daily xp
        data << uint64(guild->GetNextLevelXP() - guild->GetCurrentXP());    // next level XP
        data << uint64(guild->GetXPCap());                                  // weekly xp
        data << uint64(guild->GetCurrentXP());                              // Curr exp
        data << uint64(guild->GetTodayXP());                                // Today exp
        SendPacket(&data);
    }
}

void WorldSession::HandleGuildMaxExperienceOpcode(WorldPacket& recvPacket)
{
    recvPacket.read_skip<uint64>();

    if (Guild* guild = sGuildMgr->GetGuildById(_player->GetGuildId()))
    {
        WorldPacket data(SMSG_GUILD_MAX_DAILY_XP, 8);
        data << uint64(guild->GetXPCap());
        SendPacket(&data);
    }
}

void WorldSession::HandleGuildRewardsOpcode(WorldPacket& recvPacket)
{
    if (!_player->GetGuildId() || !sWorld->getBoolConfig(CONFIG_GUILD_ADVANCEMENT_ENABLED))
        return;

    recvPacket.read_skip<uint64>();

    GuildRewardsVector const& vec = sGuildMgr->GetGuildRewards();
    if (vec.empty())
        return;

    WorldPacket data(SMSG_GUILD_REWARDS_LIST, 4 + 4 + ((4 + 4 + 8 + 4 + 4 + 4) * vec.size()));
    data << uint32(_player->GetGuildId()) ;
    data << uint32(vec.size()); // counter

    for (uint32 i = 0; i < vec.size(); ++i)
        data << uint32(0); // unk (only found 0 in retail logs)

    for (uint32 i = 0; i < vec.size(); ++i)
        data << uint32(0); // unk

    for (uint32 i = 0; i < vec.size(); ++i)
        data << uint64(vec[i].price); // money price

    for (uint32 i = 0; i < vec.size(); ++i)
        data << uint32(vec[i].achievement); // Achievement requirement

    for (uint32 i = 0; i < vec.size(); ++i)
        data << uint32(vec[i].standing); // Reputation level (REP_HONORED, REP_FRIENDLY, etc)

    for (uint32 i = 0; i < vec.size(); ++i)
        data << uint32(vec[i].item); // item entry
    SendPacket(&data);
}

void WorldSession::HandleGuildSetNoteOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_SET_NOTE");

    uint8 ispublic;
    uint64 guid;
    recvPacket >> ispublic;
    recvPacket >> guid;             // target guid
    recvPacket.read_skip<uint64>(); // issuer's guid (?)
    recvPacket.read_skip<uint64>(); // guild guid (not using it)

    std::string Note;
    recvPacket >> Note;

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleSetMemberNote(this, guid, Note, !ispublic);
}

void WorldSession::HandleGuildRankOpcode(WorldPacket& recvPacket)
{
    uint32 BankStacks[GUILD_BANK_MAX_TABS];
    for (uint32 i = 0; i < GUILD_BANK_MAX_TABS; i++)
        recvPacket >> BankStacks[i];

    uint32 new_rights;
    recvPacket >> new_rights;

    uint32 new_rankId;
    recvPacket >> new_rankId;

    uint32 old_rankId;
    recvPacket >> old_rankId;

    uint32 BankRights[GUILD_BANK_MAX_TABS];
    for (uint32 i = 0; i < GUILD_BANK_MAX_TABS; i++)
        recvPacket >> BankRights[i];

    uint64 guildId;
    recvPacket >> guildId;

    uint32 old_rights;
    recvPacket >> old_rights;

    uint32 money;
    recvPacket >> money;

    uint64 playerGuid;
    recvPacket >> playerGuid;

    std::string rankName;
    recvPacket >> rankName;

    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_RANK");

    if (GetPlayer()->GetGUID() != playerGuid)
    {
        printf("CMSG_GUILD_RANK: The playerGUID in the packet does not match the current player!\n");
        recvPacket.rpos(recvPacket.wpos());
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }

    if (GetPlayer()->GetGuildId() != GUID_LOPART(guildId))
    {
        printf("CMSG_GUILD_RANK: This player is not in the guild.\n");
        recvPacket.rpos(recvPacket.wpos());
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }

    Guild* guild = _GetPlayerGuild(this, true);
    if (!guild)
    {
        recvPacket.rpos(recvPacket.wpos());
        return;
    }

    GuildBankRightsAndSlotsVec rightsAndSlots(GUILD_BANK_MAX_TABS);
    if (old_rankId != GR_GUILDMASTER)
    {
        for (uint8 tabId = 0; tabId < GUILD_BANK_MAX_TABS; ++tabId)
        {
            rightsAndSlots[tabId] = GuildBankRightsAndSlots(BankRights[tabId], BankStacks[tabId]);
        }

        money *= GOLD; // In game is in gold, in core set in bronze
        guild->HandleSetRankInfo(this, new_rankId, rankName, new_rights, money, rightsAndSlots);
    }

    if (old_rankId != new_rankId && old_rankId != GR_GUILDMASTER && new_rankId != GR_GUILDMASTER)
        guild->ChangeMemberRank(old_rankId, new_rankId);
}

void WorldSession::HandleGuildRanksOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_RANKS");

    uint64 guildGUID;

    recvPacket >> guildGUID;

    Guild* guild = _GetPlayerGuild(this, true);
    if (!guild)
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }

    guild->SendGuildRankInfo(this);
}

void WorldSession::HandleGuildAddRankOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_ADD_RANK");

    std::string rankName;
    recvPacket >> rankName;

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleAddNewRank(this, rankName);
}

void WorldSession::HandleGuildDelRankOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_DEL_RANK");

    uint32 rankid;
    recvPacket >> rankid;

    if (Guild* guild = _GetPlayerGuild(this, true))
        guild->HandleRemoveRank(this, rankid);
}

// TODO!!! Doesn't update tabard, guild tab until relog
void WorldSession::HandleSaveGuildEmblemOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received MSG_SAVE_GUILD_EMBLEM");

    uint64 vendorGuid;
    recvPacket >> vendorGuid;

    EmblemInfo emblemInfo;
    emblemInfo.ReadPacket(recvPacket);

    if (GetPlayer()->GetNPCIfCanInteractWith(vendorGuid, UNIT_NPC_FLAG_TABARDDESIGNER))
    {
        // Remove fake death
        if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
            GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

        if (Guild* guild = _GetPlayerGuild(this))
            guild->HandleSetEmblem(this, emblemInfo);
        else
            // "You are not part of a guild!";
            Guild::SendSaveEmblemResult(this, ERR_GUILDEMBLEM_NOGUILD);
    }
    else
    {
        // "That's not an emblem vendor!"
        Guild::SendSaveEmblemResult(this, ERR_GUILDEMBLEM_INVALIDVENDOR);
        sLog->outDebug(LOG_FILTER_GUILD, "WORLD: HandleSaveGuildEmblemOpcode - Unit (GUID: %u) not found or you can't interact with him.", GUID_LOPART(vendorGuid));
    }
}

void WorldSession::HandleGuildEventLogQueryOpcode(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (MSG_GUILD_EVENT_LOG_QUERY)");

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SendEventLog(this);
}

void WorldSession::HandleGuildBankMoneyWithdrawn(WorldPacket& /*recvData*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (MSG_GUILD_BANK_MONEY_WITHDRAWN)");

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SendMoneyInfo(this);
}

void WorldSession::HandleGuildPermissions(WorldPacket& /*recvData*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (MSG_GUILD_PERMISSIONS)");

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SendPermissions(this);
}

// Called when clicking on Guild bank gameobject
void WorldSession::HandleGuildBankerActivate(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANKER_ACTIVATE)");

    uint64 GoGuid;
    recvData >> GoGuid;

    uint8 unk;
    recvData >> unk;

    if (GetPlayer()->GetGameObjectIfCanInteractWith(GoGuid, GAMEOBJECT_TYPE_GUILD_BANK))
    {
        if (Guild* guild = _GetPlayerGuild(this))
            guild->SendBankTabsInfo(this);
        else
            Guild::SendCommandResult(this, GUILD_UNK1, ERR_GUILD_PLAYER_NOT_IN_GUILD);
    }
}

// Called when opening guild bank tab only (first one)
void WorldSession::HandleGuildBankQueryTab(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANK_QUERY_TAB)");

    uint64 GoGuid;
    recvData >> GoGuid;

    uint8 tabId;
    recvData >> tabId;

    uint8 unk1;
    recvData >> unk1;

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SendBankTabData(this, tabId);
}

void WorldSession::HandleGuildBankDepositMoney(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANK_DEPOSIT_MONEY)");

    uint64 GoGuid;
    recvData >> GoGuid;

    uint64 money;
    recvData >> money;

    if (GetPlayer()->GetGameObjectIfCanInteractWith(GoGuid, GAMEOBJECT_TYPE_GUILD_BANK))
        if (money && GetPlayer()->HasEnoughMoney(money))
            if (Guild* guild = _GetPlayerGuild(this))
                guild->HandleMemberDepositMoney(this, money);
}

void WorldSession::HandleGuildBankWithdrawMoney(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANK_WITHDRAW_MONEY)");

    uint64 GoGuid;
    recvData >> GoGuid;

    uint64 money;
    recvData >> money;

    if (money)
        if (GetPlayer()->GetGameObjectIfCanInteractWith(GoGuid, GAMEOBJECT_TYPE_GUILD_BANK))
            if (Guild* guild = _GetPlayerGuild(this))
                guild->HandleMemberWithdrawMoney(this, money);
}

void WorldSession::HandleGuildBankSwapItems(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANK_SWAP_ITEMS)");

    uint64 GoGuid;
    recvData >> GoGuid;

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(GoGuid, GAMEOBJECT_TYPE_GUILD_BANK))
    {
        recvData.rpos(recvData.wpos());                   // Prevent additional spam at rejected packet
        return;
    }

    Guild* guild = _GetPlayerGuild(this);
    if (!guild)
    {
        recvData.rpos(recvData.wpos());                   // Prevent additional spam at rejected packet
        return;
    }

    uint8 bankToBank;
    recvData >> bankToBank;

    uint8 tabId;
    uint8 slotId;
    uint32 itemEntry;
    uint32 splitedAmount = 0;

    if (bankToBank)
    {
        uint8 destTabId;
        recvData >> destTabId;

        uint8 destSlotId;
        recvData >> destSlotId;
        recvData.read_skip<uint32>();                      // Always 0

        recvData >> tabId;
        recvData >> slotId;
        recvData >> itemEntry;
        recvData.read_skip<uint8>();                       // Always 0

        recvData >> splitedAmount;

        guild->SwapItems(GetPlayer(), tabId, slotId, destTabId, destSlotId, splitedAmount);
    }
    else
    {
        uint8 playerBag = NULL_BAG;
        uint8 playerSlotId = NULL_SLOT;
        uint8 toChar = 1;

        recvData >> tabId;
        recvData >> slotId;
        recvData >> itemEntry;

        uint8 autoStore;
        recvData >> autoStore;
        if (autoStore)
        {
            recvData.read_skip<uint32>();                  // autoStoreCount
            recvData.read_skip<uint8>();                   // ToChar (?), always and expected to be 1 (autostore only triggered in Bank -> Char)
            recvData.read_skip<uint32>();                  // Always 0
        }
        else
        {
            recvData >> playerBag;
            recvData >> playerSlotId;
            recvData >> toChar;
            recvData >> splitedAmount;
        }

        // Player <-> Bank
        // Allow to work with inventory only
        if (!Player::IsInventoryPos(playerBag, playerSlotId) && !(playerBag == NULL_BAG && playerSlotId == NULL_SLOT))
            GetPlayer()->SendEquipError(EQUIP_ERR_NONE, NULL);
        else
            guild->SwapItemsWithInventory(GetPlayer(), toChar, tabId, slotId, playerBag, playerSlotId, splitedAmount);
    }
}

void WorldSession::HandleGuildBankBuyTab(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANK_BUY_TAB)");

    uint64 GoGuid;
    recvData >> GoGuid;

    uint8 tabId;
    recvData >> tabId;

    if (GetPlayer()->GetGameObjectIfCanInteractWith(GoGuid, GAMEOBJECT_TYPE_GUILD_BANK))
       if (Guild* guild = _GetPlayerGuild(this))
           guild->HandleBuyBankTab(this, tabId);
}

void WorldSession::HandleGuildBankUpdateTab(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (CMSG_GUILD_BANK_UPDATE_TAB)");

    uint64 GoGuid;
    recvData >> GoGuid;

    uint8 tabId;
    recvData >> tabId;

    std::string name;
    recvData >> name;

    std::string icon;
    recvData >> icon;

    if (!name.empty() && !icon.empty())
        if (GetPlayer()->GetGameObjectIfCanInteractWith(GoGuid, GAMEOBJECT_TYPE_GUILD_BANK))
            if (Guild* guild = _GetPlayerGuild(this))
                guild->HandleSetBankTabInfo(this, tabId, name, icon);
}

void WorldSession::HandleGuildBankLogQuery(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received (MSG_GUILD_BANK_LOG_QUERY)");

    uint8 tabId;
    recvData >> tabId;

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SendBankLog(this, tabId);
}

void WorldSession::HandleQueryGuildBankTabText(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received MSG_QUERY_GUILD_BANK_TEXT");

    uint8 tabId;
    recvData >> tabId;

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SendBankTabText(this, tabId);
}

void WorldSession::HandleSetGuildBankTabText(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_SET_GUILD_BANK_TEXT");

    uint8 tabId;
    recvData >> tabId;

    std::string text;
    recvData >> text;

    if (Guild* guild = _GetPlayerGuild(this))
        guild->SetBankTabText(tabId, text);
}

void WorldSession::HandleGuildQueryTradeSkill(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_QUERY_TRADESKILL");

    if (Guild* guild = _GetPlayerGuild(this))
    {
        WorldPacket data(SMSG_GUILD_TRADESKILL_UPDATE, 4);
        data << uint32(0);

        SendPacket(&data);
    }
}

void WorldSession::HandleGuildQueryNews(WorldPacket& /*recvData*/)
{
    sLog->outDebug(LOG_FILTER_GUILD, "WORLD: Received CMSG_GUILD_QUERY_NEWS");

    // Sending guild news
    if (Guild* guild = _GetPlayerGuild(this))
    {
        WorldPacket data(SMSG_GUILD_NEWS_UPDATE, 4);
        guild->SetGuildNews(data);
        SendPacket(&data);
    }
}
