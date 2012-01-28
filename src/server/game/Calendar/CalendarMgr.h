/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _CALENDARMGR_H
#define _CALENDARMGR_H

#include <string>
#include <ace/Singleton.h>
#include "Player.h"
#include "Common.h"

// TODO - Get correct values
enum CalendarEventType
{
    CALENDARTYPE_RAID		= 0,
    CALENDARTYPE_DUNGEON	= 1,
    CALENDARTYPE_PVP		= 2,
    CALENDARTYPE_MEETING	= 3,
    CALENDARTYPE_OTHER		= 4,
};

// TODO - Get correct values
enum CalendarInviteStatus
{
    CALENDARSTATUS_INVITED		= 0,
    CALENDARSTATUS_ACCEPTED		= 1,
    CALENDARSTATUS_DECLINED		= 2,
    CALENDARSTATUS_CONFIRMED	= 3,
    CALENDARSTATUS_TENTATIVE	= 4,
    CALENDARSTATUS_OUT			= 5,
    CALENDARSTATUS_STANDBY		= 6,
};

enum CalendarFlag
{
    CALENDAR_NONE			= 0,
    CALENDAR_NORMAL			= 1,
    CALENDAR_INVITES_LOCED	= 16,
    CALENDAR_WITHOUT_INVITE	= 64,
    CALENDAR_GUILD_EVENT	= 1024,
};

enum CalendarModerationRank
{
    CALENDAR_PLAYER = 0,
    CALENDAR_MODERATOR = 1,
    CALENDAR_OVNER = 2,
};
enum  CalendarSendEventType
{
    CALENDAR_GET = 0,
    CALENDAR_ADD = 1,
    CALENDAR_COPY = 2,
};

enum CalendarCommandError
{
    CALENDAR_ERROR_INTERNAL = 0,
    CALENDAR_ERROR_PERMISSIONS,
    CALENDAR_ERROR_ALREADY_INVITED_TO_EVENT,
    CALENDAR_ERROR_NOT_ALLIED,
    CALENDAR_ERROR_INVITES_EXCEEDED,
    CALENDAR_ERROR_SELF_INVITES_EXCEEDED,
    CALENDAR_ERROR_OTHER_INVITES_EXCEEDED,
    CALENDAR_ERROR_EVENTS_EXCEEDED,
    CALENDAR_ERROR_GUILD_EVENTS_EXCEEDED,
    CALENDAR_ERROR_ARENA_EVENTS_EXCEEDED,
    CALENDAR_ERROR_INVALID_TIME,
    CALENDAR_ERROR_INVALID_DATE,
    CALENDAR_ERROR_NEEDS_TITLE,
    CALENDAR_ERROR_EVENT_INVALID,
    CALENDAR_ERROR_NOT_INVITED,
    CALENDAR_ERROR_NO_INVITE,
    CALENDAR_ERROR_EVENT_PASSED,
    CALENDAR_ERROR_EVENT_LOCKED,
    CALENDAR_ERROR_DELETE_CREATOR_FAILED,
    CALENDAR_ERROR_RESTRICTED_LEVEL,
    CALENDAR_ERROR_EVENT_WRONG_SERVER,
    CALENDAR_ERROR_INVITE_WRONG_SERVER,
    CALENDAR_ERROR_NO_GUILD_INVITES,
    CALENDAR_ERROR_INVALID_SIGNUP,
    CALENDAR_ERROR_NO_MODERATOR
};

struct Calendar_Event
{
    uint64 eventID;
    uint64 creator_guid;
    std::string name;
    std::string description;
    uint8 type;
    uint8 unk1;
    uint32 dungeonID;
    uint32 unkTime;
    uint32 time;
    uint32 flags;
    uint32 guildID;
};

struct Calendar_Invite
{
    uint64 inviteID;
    uint64 eventID;
    uint8 rank;
    uint8 status;
    uint8 unk1;
    uint8 unk2;
    uint64 creator_guid;
    uint32 time;
    uint64 target_guid;
    std::string text;
};

typedef std::list<Calendar_Invite*> CalendarInviteList;
typedef std::list<Calendar_Event*> CalendarEventList;

class CalendarMgr
{
        CalendarMgr();
        friend class ACE_Singleton<CalendarMgr, ACE_Null_Mutex>;
    public:
        void LoadHolidayData();
        void LoadCalendarData();

        Calendar_Event* GetEvent(uint64 eventID)
        {
            for (CalendarEventList::const_iterator i = m_eventList.begin(); i != m_eventList.end(); ++i)
                if ((*i) && (*i)->eventID == eventID)
                    return (*i);

            return NULL;
        }

        Calendar_Invite* GetInvite(uint64 inviteID)
        {
            for (CalendarInviteList::const_iterator i = m_inviteList.begin(); i != m_inviteList.end(); ++i)
                if ((*i) && (*i)->inviteID == inviteID)
                    return (*i);

            return NULL;
        }

        Calendar_Invite* GetInviteFromPlayer(uint64 playerGuild, uint8 status)
        {
            for (CalendarInviteList::const_iterator i = m_inviteList.begin(); i != m_inviteList.end(); ++i)
                if ((*i) && (*i)->target_guid == playerGuild && (*i)->status == status)
                    return (*i);

            return NULL;
        }

        Calendar_Invite* GetInviteFromTeargetGuid(uint64 targetGuid,uint64 eventID)
        {
            for (CalendarInviteList::const_iterator i = m_inviteList.begin(); i != m_inviteList.end(); ++i)
                if ((*i) && (*i)->target_guid == targetGuid)
                    return (*i);

            return NULL;
        }

        /*void AddInvite(CalendarInvite invite) { m_inviteList. = invite; }
        void RemoveInvite(uint64 inviteID) { m_inviteList.erase(inviteID); }

        CalendarEvent const* GetEvent(uint64 eventID)
        {
            CalendarEventMap::const_iterator itr = _eventMap.find(eventID);
            if(itr == _eventMap.end())
                return NULL;
            return &itr->second;
        }

        void AddEvent(CalendarEvent calendar_event) { _eventMap[calendar_event.id] = calendar_event; }
        void RemoveEvent(uint64 eventID) { _eventMap.erase(eventID); }

        void AppendInvitesToCalendarPacketForPlayer(WorldPacket &data, Player *player);
        void AppendEventsToCalendarPacketForPlayer(WorldPacket &data, Player *player);
        */
        bool GetInviteStatus(uint64 playerGuild)
        {
            for (CalendarInviteList::iterator itr = m_inviteList.begin(); itr != m_inviteList.end(); ++itr)
            {
                if((*itr)->status == CALENDARSTATUS_INVITED && (*itr)->target_guid == playerGuild)
                    return true;
            }
            return false;
        }

        uint64 GenerateNextEventID() { return ++m_EventID; }
        uint64 GenerateNextInviteID() { return ++m_InviteID; }
        uint64 GetCurrentEventID() {return m_EventID;}
        uint64 GetCurrentInviteID() {return m_InviteID;}

        uint32 GetHolidayCount() {return m_HolidayCount;}
        uint32 GetInviteCount() {return m_CalendaInviteCount;}
        uint32 GetEventCount() {return m_CalendatEventCount;}

        void AddOrUpdateCalendarEvent(Calendar_Event &c_event, bool create = false);
        void _AddOrUpdateCalendarEvent(Calendar_Event &c_event);

        void AddOrUpdateCalendarInvite(Calendar_Invite &c_invite, bool create = false);
        void _AddOrUpdateCalendarInvite(Calendar_Invite &c_invite);
        void SendCommandResult(WorldSession* session, uint32 type, uint32 errocode, const std::string& param);
        /*Calendar_Invite* GetInviteStatus(uint64 player)
        {
            for (CalendarInviteList::const_iterator i = m_inviteList.begin(); i != m_inviteList.end(); ++i)
                if ((*i) && (*i)->status == 1 && (*i)->target_guid == player)
                    return true;

                return false;
        }
        */

        CalendarInviteList m_inviteList;
        CalendarEventList m_eventList;

    protected:
        uint32 m_HolidayCount;
        uint32 m_CalendaInviteCount;
        uint32 m_CalendatEventCount;
        uint64 m_EventID;
        uint64 m_InviteID;
        bool m_invitePlayerStatus;
};

#define sCalendarMgr ACE_Singleton<CalendarMgr, ACE_Null_Mutex>::instance()

#endif