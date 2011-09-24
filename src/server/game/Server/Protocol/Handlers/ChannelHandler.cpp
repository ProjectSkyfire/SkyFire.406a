/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "ObjectMgr.h"                                      // for normalizePlayerName
#include "ChannelMgr.h"

void WorldSession::HandleJoinChannel(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());

    uint32 channel_id;
    uint8 unknown1, unknown2;
    std::string _password, _channelname;

    recvPacket.read_skip<uint8>();
    recvPacket.read_skip<uint8>();
    recvPacket >> channel_id;
    recvPacket >> unknown1 >> unknown2;
    recvPacket >> _password;
    recvPacket >> _channelname;

    if (channel_id)
    {
        ChatChannelsEntry const* channel = sChatChannelsStore.LookupEntry(channel_id);
        if (!channel)
            return;

        AreaTableEntry const* current_zone = GetAreaEntryByAreaID(_player->GetZoneId());
        if (!current_zone)
            return;

        if (!_player->CanJoinConstantChannelInZone(channel, current_zone))
            return;
    }

    if (_channelname.empty())
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        cMgr->team = _player->GetTeam();
        if (Channel* chn = cMgr->GetJoinChannel(_channelname, channel_id))
            chn->Join(_player->GetGUID(), _password.c_str());
    }
}

void WorldSession::HandleLeaveChannel(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    uint32 _unk;
    std::string _channelname;

    recvPacket >> _unk;                                      // channel id?
    recvPacket >> _channelname;

    if (_channelname.empty())
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->Leave(_player->GetGUID(), true);
        cMgr->LeftChannel(_channelname);
    }
}

void WorldSession::HandleChannelList(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    recvPacket >> _channelname;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->List(_player);
}

void WorldSession::HandleChannelPassword(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _password;

    recvPacket >> _channelname;
    recvPacket >> _password;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->Password(_player->GetGUID(), _password.c_str());
}

void WorldSession::HandleChannelSetOwner(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _newp;

    recvPacket >> _channelname;
    recvPacket >> _newp;

    if (!normalizePlayerName(_newp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->SetOwner(_player->GetGUID(), _newp.c_str());
}

void WorldSession::HandleChannelOwner(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    recvPacket >> _channelname;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->SendWhoOwner(_player->GetGUID());
}

void WorldSession::HandleChannelModerator(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->SetModerator(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelUnmoderator(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->UnsetModerator(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelMute(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->SetMute(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelUnmute(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->UnsetMute(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelInvite(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->Invite(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelKick(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->Kick(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelBan(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->Ban(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelUnban(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    std::string _otp;

    recvPacket >> _channelname;
    recvPacket >> _otp;

    if (!normalizePlayerName(_otp))
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->UnBan(_player->GetGUID(), _otp.c_str());
}

void WorldSession::HandleChannelAnnouncements(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    recvPacket >> _channelname;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->Announce(_player->GetGUID());
}

void WorldSession::HandleChannelDisplayListQuery(WorldPacket &recvPacket)
{
    // this should be OK because the 2 function _were_ the same
    HandleChannelList(recvPacket);
}

void WorldSession::HandleGetChannelMemberCount(WorldPacket &recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());
    std::string _channelname;
    recvPacket >> _channelname;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
        {
            WorldPacket data(SMSG_CHANNEL_MEMBER_COUNT, chn->GetName().size()+1+1+4);
            data << chn->GetName();
            data << uint8(chn->GetFlags());
            data << uint32(chn->GetNumPlayers());
            SendPacket(&data);
        }
    }
}

void WorldSession::HandleSetChannelWatch(WorldPacket &recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Opcode %u", recvPacket.GetOpcode());

    std::string _channelname;

    recvPacket >> _channelname;
    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel *chn = cMgr->GetChannel(_channelname, _player))
            chn->JoinNotify(_player->GetGUID());
}