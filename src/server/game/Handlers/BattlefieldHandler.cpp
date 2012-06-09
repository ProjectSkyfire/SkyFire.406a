/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "WorldSession.h"

#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "Opcodes.h"

//This send to player windows for invite player to join the war
//Param1:(BattleId) the BattleId of Bf
//Param2:(ZoneId) the zone where the battle is (4197 for wg)
//Param3:(time) Time in second that the player have for accept
void WorldSession::SendBfInvitePlayerToWar(uint32 BattleId, uint32 ZoneId, uint64 p_time)
{
    //Send packet
    WorldPacket data(SMSG_BATTLEFIELD_MGR_ENTRY_INVITE, 16);
    data << uint32(0);
    data << uint32(ZoneId);
    data << uint64(BattleId | 0x20000);

    //Sending the packet to player
    SendPacket(&data);
}

//This send invitation to player to join the queue
//Param1:(BattleId) the BattleId of Bf
void WorldSession::SendBfInvitePlayerToQueue(uint32 BattleId)
{
    WorldPacket data(SMSG_BATTLEFIELD_MGR_QUEUE_INVITE, 5);

    data << uint8(0);
    data << uint8(1); // warmup
    data << uint32(0);
    data << uint32(0);
    data << uint32(0);
    data << uint32(0);
    data << uint32(0);
    data << uint64(BattleId); // BattleId                                   //warmup ? used ?

    //Sending packet to player
    SendPacket(&data);
}

//This send packet for inform player that he join queue
//Param1:(BattleId) the BattleId of Bf
//Param2:(ZoneId) the zone where the battle is (4197 for wg)
void WorldSession::SendBfQueueInviteResponse(uint32 BattleId, uint32 ZoneId)
{
    WorldPacket data(SMSG_BATTLEFIELD_MGR_QUEUE_REQUEST_RESPONSE, 11);
    data << uint8(0); // unk, Logging In???
    data << uint64(BattleId);
    data << uint32(ZoneId);
    data << uint64(GetPlayer()->GetGUID());
    data << uint8(1); // 1 = accepted, 0 = You cant join queue right now
    data << uint8(1); // 1 = queued for next battle, 0 = you are queued, please wait...

    SendPacket(&data);
}

//This is call when player accept to join war
//Param1:(BattleId) the BattleId of Bf
void WorldSession::SendBfEntered(uint32 BattleId)
{
    WorldPacket data(SMSG_BATTLEFIELD_MGR_ENTERED, 7);
    data << uint32(BattleId);
    data << uint8(1);   //unk
    data << uint8(1);   //unk
    data << uint8(_player->isAFK()?1:0);  //Clear AFK

    SendPacket(&data);
}

//Send when player is kick from Battlefield
void WorldSession::SendBfLeaveMessage(uint32 BattleId)
{
    WorldPacket data(SMSG_BATTLEFIELD_MGR_EJECTED, 7);
    data << uint8(8);  //byte Reason
    data << uint8(2);  //byte BattleStatus
    data << uint64(BattleId);
    data << uint8(0);  //bool Relocated

    SendPacket(&data);
}

//Send by client when he click on accept for queue
void WorldSession::HandleBfQueueInviteResponse(WorldPacket& recv_data)
{
    uint64 data;
    uint8 Accepted;

    recv_data >> Accepted >> data;

    uint64 BattleId = data &~ 0x20000;

    Battlefield* Bf= sBattlefieldMgr->GetBattlefieldByBattleId((uint32)BattleId);
    if (!Bf)
        return;

    if (Accepted)
        Bf->PlayerAcceptInviteToQueue(_player);
}

//Send by client on clicking in accept or refuse of invitation windows for join game
void WorldSession::HandleBfEntryInviteResponse(WorldPacket& recv_data)
{
    uint64 data;
    uint8 Accepted;

    recv_data >> Accepted >> data;

    uint64 BattleId = data &~ 0x20000;

    Battlefield* Bf= sBattlefieldMgr->GetBattlefieldByBattleId((uint32)BattleId);
    if (!Bf)
        return;

    //If player accept invitation
    if (Accepted)
    {
        Bf->PlayerAcceptInviteToWar(_player);
    }
    else
    {
        if (_player->GetZoneId() == Bf->GetZoneId())
            Bf->KickPlayerFromBf(_player->GetGUID());
    }
}

void WorldSession::HandleBfExitRequest(WorldPacket& recv_data)
{
    uint64 BattleId;

    recv_data >> BattleId;
    uint32 bId = BattleId & 0xFFFF;
    sLog->outError("HandleBfExitRequest: BattleID:%u ",bId);
    Battlefield* Bf= sBattlefieldMgr->GetBattlefieldByBattleId(bId);
    if (!Bf)
        return;

    Bf->AskToLeaveQueue(_player);
}

//Send by client when he click on join the queue
void WorldSession::HandleBfJoinQueue(WorldPacket& recv_data)
{
    uint64 data;

    recv_data >> data;

    uint64 BattleId = data &~ 0x20000;

    Battlefield* Bf= sBattlefieldMgr->GetBattlefieldByBattleId(BattleId);
    if (!Bf)
        return;

    Bf->InvitePlayerToQueue(_player);
}
