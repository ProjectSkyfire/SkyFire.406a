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

#include "gamePCH.h"
#include "CalendarMgr.h"
#include "LFGMgr.h"
#include "Player.h"

CalendarMgr::CalendarMgr()
{
    m_EventID = 0;
    m_InviteID = 0;
}

/*
void CalendarMgr::AppendInvitesToCalendarPacketForPlayer(WorldPacket &data, Player *player)
{
    size_t p_counter = data.wpos();
    data << uint32(0);
    uint32 counter = 0;
    for (CalendarInviteMap::iterator itr = _inviteMap.begin(); itr != _inviteMap.end(); ++itr)
    {
        CalendarInvite invite = itr->second;
        //"if (invite.target_guid == GetGUID())" was not correct getGUID was not identified
        if (invite.target_guid)
        {
            data << uint64(invite.id);                // Invite ID
            data << uint64(invite.c_event);           // Event ID
            data << uint8(invite.rank);               // rank
            data << uint8(0);                         // unk - TODO: Figure out what this is
            data << uint8(0);                         // unk
            data.appendPackGUID(invite.creator_guid); // creator's guid
            counter++;
        }
    }
    data.put<uint32>(p_counter, counter);             // update number of invites
}

void CalendarMgr::AppendEventsToCalendarPacketForPlayer(WorldPacket &data, Player *player)
{
    // TODO: There's gotta be a better way to do this
    size_t p_counter = data.wpos();
    data << uint32(0);
    uint32 counter = 0;
    std::set<uint64> alreadyAdded;
    for (CalendarInviteMap::iterator itr = _inviteMap.begin(); itr != _inviteMap.end(); ++itr)
    {
        CalendarInvite invite = itr->second;
        //"if (invite.target_guid == getGUID())" was not correct getGUID was not identified
        if (invite.target_guid)
        {
            if (alreadyAdded.find(invite.id) == alreadyAdded.end())
            {
                CalendarEvent const* calendar_event = GetEvent(invite.id);
                data << uint64(calendar_event->id);                // event ID
                data << calendar_event->name;                      // event title
                data << uint32(calendar_event->type);              // event type
                data << uint32(calendar_event->time);              // event time as time bit field
                data << uint32(calendar_event->flags);             // event flags
                data << uint32(calendar_event->dungeonID);         // dungeon ID
                data.appendPackGUID(calendar_event->creator_guid); // creator guid
                alreadyAdded.insert(invite.id);
                counter++;
            }
        }
    }
    data.put<uint32>(p_counter, counter);             // update number of invites
}
*/

void CalendarMgr::AddOrUpdateCalendarEvent(Calendar_Event &c_event, bool create)
{
    if (create)
    {
        m_eventList.push_back(&c_event);
        //if (ticket.closed == 0)
        //    m_openTickets++;
    }

    _AddOrUpdateCalendarEvent(c_event);
}

void CalendarMgr::_AddOrUpdateCalendarEvent(Calendar_Event &c_event)
{
    std::string name(c_event.name), description(c_event.description);
    CharacterDatabase.EscapeString(name);
    CharacterDatabase.EscapeString(description);
    std::ostringstream os;
        os << "REPLACE INTO calendar_event(eventID, creatorGuid, name, description, flags, type, unk1, dungeonID, unkTime, time, guildID) VALUE (";
        os << c_event.eventID << ", ";
        os << c_event.creator_guid << ", '";
        os << c_event.name << "', '";
        os << c_event.description << "', ";
        os << int(c_event.flags) << ", ";
        os << int(c_event.type) << ", ";
        os << int(c_event.unk1) << ", ";
        os << c_event.dungeonID << ", ";
        os << c_event.unkTime << ", ";
        os << c_event.time << ", ";
        os << c_event.guildID << ");";

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    trans->Append(os.str().c_str());
    CharacterDatabase.CommitTransaction(trans);
}

void CalendarMgr::AddOrUpdateCalendarInvite(Calendar_Invite &c_invite, bool create)
{
    if (create)
    {
        m_inviteList.push_back(&c_invite);
        //if (ticket.closed == 0)
        //    m_openTickets++;
    }

    _AddOrUpdateCalendarInvite(c_invite);
}

void CalendarMgr::_AddOrUpdateCalendarInvite(Calendar_Invite &c_invite)
{
    std::string text(c_invite.text);
    CharacterDatabase.EscapeString(text);
    std::ostringstream os;
        os << "REPLACE INTO calendar_event_invite (inviteID,eventID, rank, status, unk1, unk2, creatorGuid, time, targetGuid, text) VALUES (";
        os << c_invite.inviteID << ", ";
        os << c_invite.eventID << ", ";
        os << int(c_invite.rank) << ", ";
        os << int(c_invite.status) << ", ";
        os << int(c_invite.unk1) << ", ";
        os << int(c_invite.unk2) << ", ";
        os << c_invite.creator_guid << ", ";
        os << c_invite.time << ", ";
        os << c_invite.target_guid << ", '";
        os << c_invite.text << "');";

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    trans->Append(os.str().c_str());
    CharacterDatabase.CommitTransaction(trans);
}

//void CalendarMgr::SendCommandResult(WorldSession* session, CalendarSendEventType type, CalendarCommandError errCode, const std::string& param)
void CalendarMgr::SendCommandResult(WorldSession* session, uint32 type, uint32 errocode, const std::string& param)
{
    WorldPacket data(SMSG_CALENDAR_COMMAND_RESULT, 8 + param.size() + 1);
    data << uint32(type);
    data << param;
    data << uint32(errocode);
    session->SendPacket(&data);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent (SMSG_CALENDAR_COMMAND_RESULT)");
}

void CalendarMgr::LoadHolidayData()
{
    uint32 oldMSTime = getMSTime();
    uint32 count = 0;
    for (uint32 i = 0; i < sHolidaysStore.GetNumRows(); ++i)           // areaflag numbered from 0
    {
         if (HolidaysEntry const* holidays = sHolidaysStore.LookupEntry(i))
             count++;
    }
    m_HolidayCount = count;

    sLog->outString(">> Loaded %u Holidays definitions in %u ms", m_HolidayCount, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void CalendarMgr::LoadCalendarData()
{
    uint32 oldMSTime = getMSTime();
    uint32 count = 0;
    //Load Invire Map fro m database
    if (!m_inviteList.empty())
        for (CalendarInviteList::const_iterator itr = m_inviteList.begin(); itr !=m_inviteList.end(); ++itr)
            delete *itr;

    m_inviteList.clear();
    m_InviteID = 0;
    m_CalendaInviteCount = 0;

    QueryResult result = CharacterDatabase.Query("SELECT inviteID, eventID, rank, status ,unk1, unk2, creatorGuid, targetGuid, time, text FROM calendar_event_invite");
    if (!result)
    {
        sLog->outErrorDb(">> Loaded 0 calendar_event_invite, table is empty!");
        sLog->outString();
        return;
    }

    count = 0; //reset count
    do
    {
        Field* fields = result->Fetch();

        Calendar_Invite *invite = new Calendar_Invite;

        invite->inviteID = fields[0].GetUInt64();
        invite->eventID = fields[1].GetUInt64();
        invite->rank = fields[2].GetUInt8();
        invite->status = fields[3].GetInt32();
        invite->unk1 = fields[4].GetInt8();
        invite->unk2 = fields[5].GetInt32();
        invite->creator_guid = fields[6].GetInt64();
        invite->target_guid = fields[7].GetInt64();
        invite->time = fields[8].GetInt32();
        invite->text = fields[9].GetCString();

        m_inviteList.push_back(invite);
        count++;
    } while (result->NextRow());

    m_CalendaInviteCount = count;

     result = CharacterDatabase.Query("SELECT MAX(inviteID) FROM calendar_event_invite");

    if (result)
    {
        Field *fields = result->Fetch();
        m_InviteID = fields[0].GetUInt64();
    }

    sLog->outString(">> Loaded %u calendar_event_invite in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();

    /*
    * Load Event Map from database
    */

    if (!m_eventList.empty())
        for (CalendarEventList::const_iterator itr = m_eventList.begin(); itr !=m_eventList.end(); ++itr)
            delete *itr;

    m_eventList.clear();
    m_EventID = 0;
    m_CalendatEventCount = 0;
    count = 0; //reset count

    result = CharacterDatabase.Query("SELECT eventID, creatorGuid, name, description, type, unk1, dungeonID, unkTime, time, flags, guildID FROM calendar_event");
    if (!result)
    {
        sLog->outErrorDb(">> Loaded 0 calendar_event, table is empty!");
        sLog->outString();
        return;
    }

    do
    {
        Field* fields = result->Fetch();
        Calendar_Event* c_event = new Calendar_Event;
        c_event->eventID = fields[0].GetUInt64();
        c_event->creator_guid = fields[1].GetUInt64();
        c_event->name = fields[2].GetString();
        c_event->description = fields[3].GetString();
        c_event->type = fields[4].GetUInt8();
        c_event->unk1 = fields[5].GetUInt8();
        c_event->dungeonID = fields[6].GetUInt32();
        c_event->unkTime = fields[7].GetUInt32();
        c_event->time = fields[8].GetUInt32();
        c_event->flags = fields[9].GetUInt8();
        c_event->guildID = fields[10].GetUInt64();

        m_eventList.push_back(c_event);
        count++;
    } while (result->NextRow());

    m_CalendatEventCount = count;

    result = CharacterDatabase.Query("SELECT MAX(eventID) from calendar_event");

    if (result)
    {
        Field *fields = result->Fetch();
        m_EventID = fields[0].GetUInt64();
    }

    sLog->outString(">> Loaded %u calendar_event in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}