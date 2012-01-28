/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "CalendarMgr.h"

#include "InstanceSaveMgr.h"
#include "Log.h"
#include "Opcodes.h"
#include "Player.h"
#include "LFGMgr.h"

void WorldSession::HandleCalendarGetCalendar(WorldPacket & /*recv_data*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_GET_CALENDAR");     // empty
    time_t cur_time = time(NULL);
    // we can't really get the real size of this packet...
    WorldPacket data(SMSG_CALENDAR_SEND_CALENDAR, 4+4*0+4+4*0+4+4);
    size_t p_counter = data.wpos();

    uint32 invite_count = 0 ;
    data << uint32(invite_count);  // invite count

    //Load invite
    for (CalendarInviteList::const_iterator itr = sCalendarMgr->m_inviteList.begin(); itr !=sCalendarMgr->m_inviteList.end(); ++itr)
    {
        if ((*itr)->target_guid == GetPlayer()->GetGUIDLow())
        {
            data << uint64((*itr)->inviteID);			// Invite ID
            data << uint64((*itr)->eventID);			// Event ID
            data << uint8((*itr)->rank);				// rank
            data << uint8(0);				// unk - TODO: Figure out what this is
            data << uint8(0);				// unk
            data.appendPackGUID((*itr)->creator_guid);	// Event creator id
            invite_count++;
        }
    }

    data.put<uint32>(p_counter, invite_count);

    uint32 event_count=0;
    p_counter = data.wpos();
    data << uint32(event_count);

    for (CalendarInviteList::const_iterator itr = sCalendarMgr->m_inviteList.begin(); itr !=sCalendarMgr->m_inviteList.end(); ++itr)
    {
        if ((*itr))
        {
            for (CalendarEventList::const_iterator i = sCalendarMgr->m_eventList.begin(); i != sCalendarMgr->m_eventList.end(); ++i)
            {
                if ((*i)->eventID ==(*itr)->eventID)
                {
                    data << uint64((*i)->eventID);           // event ID
                    data << (*i)->name;                      // event title
                    data << uint32((*i)->type);              // event type
                    data << uint32((*i)->time);              // event time as time bit field
                    data << uint32((*i)->flags);             // event flags
                    data << uint32((*i)->dungeonID);         // dungeon ID
                    data.appendPackGUID((*i)->creator_guid); // creator guid

                    event_count++;
                }
            }
        }
    }

    data.put<uint32>(p_counter, event_count);

    //data << uint32(0);                                      // unk
    //data << uint32(secsToTimeBitFields(cur_time));          // current time

    InstanceSave *save = NULL;
    uint32 counter = 0;
    p_counter = data.wpos();
    data << uint32(counter);                                // instance save count

    for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
    {
        for (Player::BoundInstancesMap::const_iterator itr = _player->_boundInstances[i].begin(); itr != _player->_boundInstances[i].end(); ++itr)
        {
            if (itr->second.perm)
            {
                save = itr->second.save;
                data << uint32(save->GetMapId());
                data << uint32(save->GetDifficulty());
                data << uint32(save->GetResetTime() - cur_time);
                data << uint64(save->GetInstanceId());      // instance save id as unique instance copy id
                ++counter;
            }
        }
    }

    data.put<uint32>(p_counter, counter);

    data << uint32(1135753200);                             // unk (28.12.2005 07:00)

    uint32 mapid = 0;
    MapEntry const* mapEnt;
    counter = 0;
    p_counter = data.wpos();
    data << uint32(counter);                                // raid reset count

    ResetTimeByMapDifficultyMap const& resets = sInstanceSaveMgr->GetResetTimeMap();
    for (ResetTimeByMapDifficultyMap::const_iterator itr = resets.begin(); itr != resets.end(); ++itr)
    {
        mapid = PAIR32_LOPART(itr->first);
        mapEnt = sMapStore.LookupEntry(mapid);
        if (!mapEnt || !mapEnt->IsRaid())
            continue;

        data << uint32(mapid);
        data << uint32(itr->second - cur_time);
        data << uint32(mapEnt->unk_time);
        ++counter;
    }

    data.put<uint32>(p_counter, counter);

    // TODO: Fix this -- read from DBC?
    std::string holidayName = "TestHolidayName";
    p_counter = data.wpos();
    counter = 0;
    data << uint32(counter);                           // holiday count

    //TODO: Fix dbc
    //   for (uint32 i = 0; i < sHolidaysStore.GetNumRows(); ++i)           // areaflag numbered from 0
    //   {
    //       if (HolidaysEntry const* holidays = sHolidaysStore.LookupEntry(i))
    //       {
    //           data << holidays->ID;                                  // Unk
    //           data << holidays->unk1;                                  // Unk
    //           data << holidays->unk2;                                  // Unk
    //           data << holidays->unk3;                                  // Unk
    //           data << holidays->unk4;                                  // Unk
    //           for (uint8 j = 0; j < 26; ++j)
    //               data << holidays->unk10[j];                              // Unk
    //           for (uint8 j = 0; j < 10; ++j)
    //               data << holidays->unk36[j];                              // Unk
    //           for (uint8 j = 0; j < 10; ++j)
    //               data << holidays->unk46[j];                              // Unk
    //           data << holidayName.c_str();                        // holiday name
    //           ++counter;
    //       }
    //}

    data.put<uint32>(p_counter, counter);
    sLog->outDebug(LOG_FILTER_NETWORKIO, ">> Sending calendar");
    data.hexlike();
    SendPacket(&data);
}

void WorldSession::HandleCalendarGetEvent(WorldPacket &recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_GET_EVENT");

    uint64 eventId;

    recv_data.hexlike();
    recv_data >> eventId;
    if (!eventId)
        return;

    SendCalendarEvent(eventId, true);
}

void WorldSession::HandleCalendarGuildFilter(WorldPacket &recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_GUILD_FILTER");
    recv_data.hexlike();
    uint32 unk1;
    uint32 unk2;
    uint32 unk3;
    recv_data >> unk1;
    recv_data >> unk2;
    recv_data >> unk3;
}

void WorldSession::HandleCalendarArenaTeam(WorldPacket &recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_ARENA_TEAM");
    recv_data.hexlike();
    uint32 unk1;
    recv_data >> unk1;
}

void WorldSession::HandleCalendarAddEvent(WorldPacket& recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_ADD_EVENT");
    uint64 eventID = sCalendarMgr->GetCurrentEventID();
    std::string eventName = "";
    std::string eventDescription = "";
    int8 type;
    int8 unk1;
    uint32 maxInvites ;
    uint32 dungeonId = 0;
    uint32 time;
    uint32 unkTime;
    uint32 flags;
    uint32 inviteCount;
    uint64 targetGuid;
    uint8 status;
    uint8 rank;

    recv_data >> eventName;
    recv_data >> eventDescription;
    recv_data >> type;
    recv_data >> unk1;
    recv_data >> maxInvites;
    recv_data >> dungeonId;
    recv_data >> time;
    recv_data >> unkTime;
    recv_data >> flags;
    recv_data >> inviteCount;

    Calendar_Event *f_event = sCalendarMgr->GetEvent(eventID);
    if (!f_event)
    {
        Calendar_Event *c_event = new Calendar_Event;
        eventID =  sCalendarMgr->GenerateNextEventID();
        c_event->eventID = eventID;
        c_event->creator_guid = GetPlayer()->GetGUIDLow();
        c_event->name = eventName;
        c_event->description = eventDescription;
        c_event->type = type;
        c_event->unk1 = unk1;
        c_event->dungeonID = dungeonId;
        c_event->time =time;
        c_event->unkTime = unkTime;
        c_event->flags = flags;
        c_event->guildID = 0;

        sCalendarMgr->AddOrUpdateCalendarEvent(*c_event, true);
    }
    if (((flags >> 6) & 1))
        return;

    if (!inviteCount)
        return;

    recv_data.readPackGUID(targetGuid);
    recv_data >> status;
    recv_data >> rank;
    // Find From calendar_event_invite table = target Guild and eventid, update oder create new invite
    Calendar_Invite *t_invite = sCalendarMgr->GetInviteFromTeargetGuid(targetGuid,eventID);
    if (!t_invite)
    {
        uint64 newInviteID = sCalendarMgr->GenerateNextInviteID();
        Calendar_Invite *c_invite = new Calendar_Invite;
        c_invite->inviteID = newInviteID;
        c_invite->eventID = eventID;
        c_invite->rank = rank;
        c_invite->status = status;
        c_invite->unk1 = 0;
        c_invite->unk2 = 0;
        c_invite->creator_guid = GetPlayer()->GetGUIDLow();
        c_invite->time =time;
        c_invite->target_guid=targetGuid;
        c_invite->text="Nothing";

        sCalendarMgr->AddOrUpdateCalendarInvite(*c_invite, true);
    }
    else
    {
        /*t_invite->status = status;
        t_invite->rank = rank;
        sCalendarMgr->AddOrUpdateCalendarInvite(*t_invite,false);
        */
    }

    SendCalendarEvent(eventID, true);
}

void WorldSession::HandleCalendarUpdateEvent(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_UPDATE_EVENT");
//
//	uint64 eventID;
//	std::string Name = "Nothing";
//    std::string Description = "No Decription";
//	int8 type;
//    int8 unk1;
//    uint32 dungeonId = 0;
//    uint32 eventPackedTime;
//    uint32 unkPackedTime;
//    uint32 flags;
//	uint32 inviteCount;
//	uint64 creatorGuid;
//
//	recv_data >> eventID;
//    recv_data >> Name;
//    recv_data >> Description;
//    recv_data >> type;
//    recv_data >> unk1;
//	recv_data >> flags;
//    recv_data >> eventPackedTime;
//    recv_data >> unkPackedTime;
//    recv_data >> inviteCount;
//    recv_data >> dungeonId;
//
//	Calendar_Event *c_event = sCalendarMgr->GetEvent(eventID);
//
//	c_event->eventID = eventID;
//	c_event->creator_guid = GetPlayer()->GetGUIDLow();
//	c_event->name = Name;
//	c_event->description = Description;
//	c_event->type = type;
//	c_event->unk1 = unk1;
//	c_event->dungeonID = dungeonId;
//	c_event->time = eventPackedTime;
//	c_event->unkTime = unkPackedTime;
//	c_event->flags = flags;
//	c_event->guildID = 0;
//
//	/*sCalendarMgr->AddOrUpdateCalendarEvent(*c_event, true);*/
}
//
void WorldSession::HandleCalendarRemoveEvent(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_REMOVE_EVENT");
//	recv_data.hexlike();
//	uint64 eventId;
//    uint64 creatorGuid;
//    uint32 unk1;
//
//    recv_data >> eventId;
//    recv_data >> creatorGuid;
//    recv_data >> unk1;
}
//
void WorldSession::HandleCalendarCopyEvent(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_COPY_EVENT");
//    recv_data.hexlike();
//    recv_data.rpos(recv_data.wpos());                       // set to end to avoid warnings spam
//
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint32
}
//
void WorldSession::HandleCalendarEventInvite(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_EVENT_INVITE");
//	recv_data.hexlike();
//
//    uint64 eventId;
//    uint64 inviteId;
//    std::string name;
//    uint8 status;
//    uint8 rank;
//
//	WorldPacket data (SMSG_CALENDAR_EVENT_INVITE, 4);
//
//	recv_data >> eventId;
//    recv_data >> inviteId;
//    recv_data >> name;
//    recv_data >> status;
//    recv_data >> rank;
//
//	uint32 errorcode = 1;
//
//	if(eventId == 0)
//		data << uint32(errorcode);
//
//	SendPacket(&data);
//
//	/*
//	if (eventId == 0)
//		eventId = sCalendarMgr->GenerateNextEventID();
//		Calendar_Event *c_event = new Calendar_Event;
//		c_event->eventID = eventId;
//		c_event->creator_guid = GetPlayer()->GetGUIDLow();
//		c_event->name = "";
//		c_event->description = "";
//		c_event->type = 0;
//		c_event->unk1 = 0;
//		c_event->dungeonID = 0;
//		c_event->time =0;
//		c_event->unkTime =0;
//		c_event->flags = 0;
//		c_event->guildID = 0;
//
//	sCalendarMgr->AddOrUpdateCalendarEvent(*c_event,true);
//
//	Calendar_Invite *t_invite = sCalendarMgr->GetInvite(inviteId);
//	if(!t_invite)
//	{
//		if (inviteId > 1)
//		inviteId == sCalendarMgr->GenerateNextInviteID();
//		Calendar_Invite *c_invite = new Calendar_Invite;
//		c_invite->inviteID = inviteId;
//		c_invite->c_eventid = eventId;
//		c_invite->rank = rank;
//		c_invite->status = status;
//		c_invite->unk1 = 0;
//		c_invite->unk2 = 0;
//		c_invite->creator_guid = GetPlayer()->GetGUIDLow();
//		c_invite->time = lastChange;
//		c_invite->target_guid=0;
//		c_invite->text=name;
//
//		sCalendarMgr->AddOrUpdateCalendarInvite(*c_invite,true);
//	*/
}
//
void WorldSession::HandleCalendarEventRsvp(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_EVENT_RSVP");
//    recv_data.hexlike();
//                        // set to end to avoid warnings spam
//
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint32
}
//
void WorldSession::HandleCalendarEventRemoveInvite(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_EVENT_REMOVE_INVITE");
//    recv_data.hexlike();
//                         // set to end to avoid warnings spam
//	uint32 unk2;
//	uint32 unk3;
//	uint32 unk4;
//	uint64 guid;
//
//	//recv_data >> unk1;
//    recv_data.readPackGUID(guid);
//   	recv_data >> unk2;
//    recv_data >> unk3;
//    recv_data >> unk4;
}
//
void WorldSession::HandleCalendarEventStatus(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_EVENT_STATUS");
//    recv_data.hexlike();
//    //recv_data.rpos(recv_data.wpos());                       // set to end to avoid warnings spam
//
//    //recv_data.readPackGUID(guid)
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint32
}
//
void WorldSession::HandleCalendarEventModeratorStatus(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_EVENT_MODERATOR_STATUS");
//    recv_data.hexlike();
//   // recv_data.rpos(recv_data.wpos());                       // set to end to avoid warnings spam
//
//    //recv_data.readPackGUID(guid)
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint32
}
//
void WorldSession::HandleCalendarComplain(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_COMPLAIN");
//    recv_data.hexlike();
//   // recv_data.rpos(recv_data.wpos());                       // set to end to avoid warnings spam
//
//    //recv_data >> uint64
//    //recv_data >> uint64
//    //recv_data >> uint64
}
//
void WorldSession::HandleCalendarGetNumPending(WorldPacket &recv_data)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CALENDAR_GET_NUM_PENDING");  // empty
//
//	recv_data.hexlike();
//
//	WorldPacket data(SMSG_CALENDAR_SEND_NUM_PENDING, 4);
//
//	// number of pending invites 0 nothig 1 ivite pendig
//
//	data << uint32(sCalendarMgr->GetInviteStatus(GetPlayer()->GetGUIDLow()));
//
//	SendPacket(&data);
}
//
void WorldSession::SendCalendarEvent(uint64 eventId, bool added)
{
//    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_CALENDAR_SEND_EVENT");
//    WorldPacket data(SMSG_CALENDAR_SEND_EVENT);
//
//	data << uint8(added);         // from add_event
//
//	Calendar_Event *c_event = sCalendarMgr->GetEvent(eventId);
//	if (c_event)
//	{
//
//		data.appendPackGUID(c_event->creator_guid);                                // creator GUID
//		data << uint64(c_event->eventID);                                      // event ID
//		data << c_event->name;                                       // event name
//		data << c_event->description;                                       // event description
//		data << uint8(c_event->type);                                       // event type
//		data << uint8(c_event->unk1);                                       // unk
//		data << uint32(100);                                    // Max invites
//		data << int32(c_event->dungeonID);                                       // dungeon ID
//		data << uint32(c_event->unkTime);                                      // unk time
//		data << uint32(c_event->time);                                      // event time
//		data << uint32(c_event->flags);                                      // event flags
//		data << uint32(c_event->guildID);									// event guild id
//	}
//
//	// Player invite this event
//	uint32 p_counter;
//	uint32 count = 0;
//	p_counter = data.wpos();
//	data << uint32(count);
//	//terest
//	uint64 guid =32;
//	uint8 unk1 = 0;
//	uint8 unk2 = 0;
//	uint8 unk3 = 0;
//	uint8 unk4 = 0;
//	uint32 unk33 = 0;
//	uint64 inID = 1;
//	uint8 text =192;
//
//	for (uint8 i = 0; i < count; ++i)
//        {
//            data << uint64(guid);                              // invite played guid
//            data << uint8(unk1);                               // unk
//            data << uint8(unk2);                               // status
//            data << uint8(unk3);                               // rank
//            data << uint8(unk4);                               // unk
//            data << uint64(inID);                              // invite ID
//            data << uint32(unk33);                              // unk
//            data << uint8(text);                               // text
//        }
//
//	/*for(CalendarInviteList::const_iterator itr = sCalendarMgr->m_inviteList.begin(); itr != sCalendarMgr->m_inviteList.end(); ++itr)
//	{
//		if((*itr)->eventID == eventId)
//		{
//			data.appendPackGUID((*itr)->target_guid);                              // invite played guid
//			data << uint8(unk1);                               // unk
//			data << uint8((*itr)->status);                               // status
//			data << uint8((*itr)->rank);                               // rank
//			data << uint8(unk2);                               // unk
//			data << uint64((*itr)->inviteID);                              // invite ID
//			data << uint32(unk3);                              // unk
//			data << uint8(0);                               // text
//			++count;
//		}
//	}
//	*/
//	data.put<uint32>(p_counter, count);
//	data.hexlike();
//  SendPacket(&data);
}

void WorldSession::SendCalendarEventInviteAlert(uint64 eventId, uint64 inviteId)
{
    /*sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_CALENDAR_EVENT_INVITE_ALERT");
    WorldPacket data(SMSG_CALENDAR_EVENT_INVITE_ALERT);

    data << uint64(0);                           // event ID
    data << uint8(0);                            // event title
    data << uint32(0);                           // event time
    uint32 unknum = 1;
    data << uint32(unknum);
    data << uint8(0);                            // event type
    data << uint32(0);                           // dungeon id
    data << uint64(0);                           // invite id
    data << uint8(0);                            // invite status
    data << uint8(0);                            // invite rank
    data.appendPackGUID(0);                      // event creator
    data.appendPackGUID(0);                      // invite sender
    SendPacket(&data);*/
}

void WorldSession::SendCalendarEventRemovedAlert(uint64 eventId)
{
    /*sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_CALENDAR_EVENT_REMOVED_ALERT");
    WorldPacket data(SMSG_CALENDAR_EVENT_REMOVED_ALERT);
    data << uint8(0);                            // unk
    data << uint64(0);                           // invite id
    data << uint32(0);                           // invite time
    SendPacket(&data);*/
}