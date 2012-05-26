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

#include "Player.h"
#include "ObjectMgr.h"
#include "ArenaTeamMgr.h"
#include "World.h"
#include "WorldPacket.h"
#include "ArenaTeam.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "Creature.h"
#include "Formulas.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Language.h"
#include "MapManager.h"
#include "Object.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Util.h"

namespace SkyFire
{
    class BattlegroundChatBuilder
    {
        public:
            BattlegroundChatBuilder(ChatMsg msgtype, int32 textId, Player const* source, va_list* args = NULL)
                : _msgtype(msgtype), _textId(textId), _source(source), _args(args) { }

            void operator()(WorldPacket& data, LocaleConstant loc_idx)
            {
                char const* text = sObjectMgr->GetSkyFireString(_textId, loc_idx);
                if (_args)
                {
                    // we need copy va_list before use or original va_list will corrupted
                    va_list ap;
                    va_copy(ap, *_args);

                    char str[2048];
                    vsnprintf(str, 2048, text, ap);
                    va_end(ap);

                    do_helper(data, &str[0]);
                }
                else
                    do_helper(data, text);
            }

        private:
            void do_helper(WorldPacket& data, char const* text)
            {
                uint64 target_guid = _source  ? _source ->GetGUID() : 0;

                data << uint8 (_msgtype);
                data << uint32(LANG_UNIVERSAL);
                data << uint64(target_guid);                // there 0 for BG messages
                data << uint32(0);                          // can be chat msg group or something
                data << uint64(target_guid);
                data << uint32(strlen(text) + 1);
                data << text;
                data << uint8 (_source ? _source->GetChatTag() : 0);
            }

            ChatMsg _msgtype;
            int32 _textId;
            Player const* _source;
            va_list* _args;
    };

    class Battleground2ChatBuilder
    {
        public:
            Battleground2ChatBuilder(ChatMsg msgtype, int32 textId, Player const* source, int32 arg1, int32 arg2)
                : _msgtype(msgtype), _textId(textId), _source(source), _arg1(arg1), _arg2(arg2) {}

            void operator()(WorldPacket& data, LocaleConstant loc_idx)
            {
                char const* text = sObjectMgr->GetSkyFireString(_textId, loc_idx);
                char const* arg1str = _arg1 ? sObjectMgr->GetSkyFireString(_arg1, loc_idx) : "";
                char const* arg2str = _arg2 ? sObjectMgr->GetSkyFireString(_arg2, loc_idx) : "";

                char str[2048];
                snprintf(str, 2048, text, arg1str, arg2str);

                uint64 target_guid = _source  ? _source->GetGUID() : 0;

                data << uint8 (_msgtype);
                data << uint32(LANG_UNIVERSAL);
                data << uint64(target_guid);                // there 0 for BG messages
                data << uint32(0);                          // can be chat msg group or something
                data << uint64(target_guid);
                data << uint32(strlen(str) + 1);
                data << str;
                data << uint8 (_source ? _source->GetChatTag() : uint8(0));
            }

        private:
            ChatMsg _msgtype;
            int32 _textId;
            Player const* _source;
            int32 _arg1;
            int32 _arg2;
    };
}                                                           // namespace SkyFire

template<class Do>
void Battleground::BroadcastWorker(Do& _do)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(MAKE_NEW_GUID(itr->first, 0, HIGHGUID_PLAYER)))
            _do(player);
}

Battleground::Battleground()
{
    _TypeID            = BATTLEGROUND_TYPE_NONE;
    _RandomTypeID      = BATTLEGROUND_TYPE_NONE;
    _InstanceID        = 0;
    _Status            = STATUS_NONE;
    _ClientInstanceID  = 0;
    _EndTime           = 0;
    _LastResurrectTime = 0;
    _BracketId         = BG_BRACKET_ID_FIRST;
    _InvitedAlliance   = 0;
    _InvitedHorde      = 0;
    _ArenaType         = 0;
    _IsArena           = false;
    _Winner            = 2;
    _StartTime         = 0;
    _ResetStatTimer    = 0;
    _Events            = 0;
    _IsRated           = false;
    _BuffChange        = false;
    _IsRandom          = false;
    _Name              = "";
    _LevelMin          = 0;
    _LevelMax          = 0;
    _InBGFreeSlotQueue = false;
    _SetDeleteThis     = false;

    _MaxPlayersPerTeam = 0;
    _MaxPlayers        = 0;
    _MinPlayersPerTeam = 0;
    _MinPlayers        = 0;

    _MapId             = 0;
    _Map               = NULL;

    _TeamStartLocX[BG_TEAM_ALLIANCE]   = 0;
    _TeamStartLocX[BG_TEAM_HORDE]      = 0;

    _TeamStartLocY[BG_TEAM_ALLIANCE]   = 0;
    _TeamStartLocY[BG_TEAM_HORDE]      = 0;

    _TeamStartLocZ[BG_TEAM_ALLIANCE]   = 0;
    _TeamStartLocZ[BG_TEAM_HORDE]      = 0;

    _TeamStartLocO[BG_TEAM_ALLIANCE]   = 0;
    _TeamStartLocO[BG_TEAM_HORDE]      = 0;

    _ArenaTeamIds[BG_TEAM_ALLIANCE]   = 0;
    _ArenaTeamIds[BG_TEAM_HORDE]      = 0;

    _ArenaTeamRatingChanges[BG_TEAM_ALLIANCE]   = 0;
    _ArenaTeamRatingChanges[BG_TEAM_HORDE]      = 0;

    _BgRaids[BG_TEAM_ALLIANCE]         = NULL;
    _BgRaids[BG_TEAM_HORDE]            = NULL;

    _PlayersCount[BG_TEAM_ALLIANCE]    = 0;
    _PlayersCount[BG_TEAM_HORDE]       = 0;

    _TeamScores[BG_TEAM_ALLIANCE]      = 0;
    _TeamScores[BG_TEAM_HORDE]         = 0;

    _PrematureCountDown = false;

    _HonorMode = BG_NORMAL;

    StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_2M;
    StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_1M;
    StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_30S;
    StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;
    //we must set to some default existing values
    StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_BG_WS_START_TWO_MINUTES;
    StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_WS_START_ONE_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_BG_WS_START_HALF_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_WS_HAS_BEGUN;
}

Battleground::~Battleground()
{
    // remove objects and creatures
    // (this is done automatically in mapmanager update, when the instance is reset after the reset time)
    uint32 size = uint32(BgCreatures.size());
    for (uint32 i = 0; i < size; ++i)
        DelCreature(i);

    size = uint32(BgObjects.size());
    for (uint32 i = 0; i < size; ++i)
        DelObject(i);

    sBattlegroundMgr->RemoveBattleground(GetInstanceID(), GetTypeID());
    // unload map
    if (_Map)
    {
        _Map->SetUnload();
        //unlink to prevent crash, always unlink all pointer reference before destruction
        _Map->SetBG(NULL);
        _Map = NULL;
    }
    // remove from bg free slot queue
    RemoveFromBGFreeSlotQueue();

    for (BattlegroundScoreMap::const_iterator itr = PlayerScores.begin(); itr != PlayerScores.end(); ++itr)
        delete itr->second;
}

void Battleground::Update(uint32 diff)
{
    if (!PreUpdateImpl(diff))
        return;

    if (!GetPlayersSize())
    {
        //BG is empty
        // if there are no players invited, delete BG
        // this will delete arena or bg object, where any player entered
        // [[   but if you use battleground object again (more battles possible to be played on 1 instance)
        //      then this condition should be removed and code:
        //      if (!GetInvitedCount(HORDE) && !GetInvitedCount(ALLIANCE))
        //          this->AddToFreeBGObjectsQueue(); // not yet implemented
        //      should be used instead of current
        // ]]
        // Battleground Template instance cannot be updated, because it would be deleted
        if (!GetInvitedCount(HORDE) && !GetInvitedCount(ALLIANCE))
            _SetDeleteThis = true;
        return;
    }

    switch (GetStatus())
    {
        case STATUS_WAIT_JOIN:
            if (GetPlayersSize())
                _ProcessJoin(diff);
            break;
        case STATUS_IN_PROGRESS:
            _ProcessOfflineQueue();
            // after 47 minutes without one team losing, the arena closes with no winner and no rating change
            if (isArena())
            {
                if (GetStartTime() >= 47*MINUTE*IN_MILLISECONDS)
                {
                    UpdateArenaWorldState();
                    CheckArenaAfterTimerConditions();
                    return;
                }

                if ((GetAlivePlayersCountByTeam(ALLIANCE) && !GetAlivePlayersCountByTeam(HORDE)) || (GetAlivePlayersCountByTeam(HORDE) && !GetAlivePlayersCountByTeam(ALLIANCE)))
                {
                    // No player is alive, decrease the time
                    _arenaEndTimer -= diff;
                    // Determine winner team
                    if (_arenaEndTimer < 100)
                    {
                        if (!GetAlivePlayersCountByTeam(ALLIANCE))
                            EndBattleground(HORDE);
                        else
                            EndBattleground(ALLIANCE);
                    }
                }
            }
            else
            {
                _ProcessRessurect(diff);
                if (sBattlegroundMgr->GetPrematureFinishTime() && (GetPlayersCountByTeam(ALLIANCE) < GetMinPlayersPerTeam() || GetPlayersCountByTeam(HORDE) < GetMinPlayersPerTeam()))
                    _ProcessProgress(diff);
                else if (_PrematureCountDown)
                    _PrematureCountDown = false;
            }
            break;
        case STATUS_WAIT_LEAVE:
            _ProcessLeave(diff);
            break;
        default:
            break;
    }

    // Update start time and reset stats timer
    _StartTime += diff;
    _ResetStatTimer += diff;

    PostUpdateImpl(diff);
}

inline void Battleground::_ProcessOfflineQueue()
{
    // remove offline players from bg after 5 minutes
    if (!_OfflineQueue.empty())
    {
        BattlegroundPlayerMap::iterator itr = _Players.find(*(_OfflineQueue.begin()));
        if (itr != _Players.end())
        {
            if (itr->second.OfflineRemoveTime <= sWorld->GetGameTime())
            {
                RemovePlayerAtLeave(itr->first, true, true);// remove player from BG
                _OfflineQueue.pop_front();                 // remove from offline queue
                //do not use itr for anything, because it is erased in RemovePlayerAtLeave()
            }
        }
    }
}

inline void Battleground::_ProcessRessurect(uint32 diff)
{
    // *********************************************************
    // ***       BATTLEGROUND RESSURECTION SYSTEM            ***
    // *********************************************************
    // this should be handled by spell system
    _LastResurrectTime += diff;
    if (_LastResurrectTime >= RESURRECTION_INTERVAL)
    {
        if (GetReviveQueueSize())
        {
            for (std::map<uint64, std::vector<uint64> >::iterator itr = _ReviveQueue.begin(); itr != _ReviveQueue.end(); ++itr)
            {
                Creature* sh = NULL;
                for (std::vector<uint64>::const_iterator itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
                {
                    Player* player = ObjectAccessor::FindPlayer(*itr2);
                    if (!player)
                        continue;

                    if (!sh && player->IsInWorld())
                    {
                        sh = player->GetMap()->GetCreature(itr->first);
                        // only for visual effect
                        if (sh)
                            // Spirit Heal, effect 117
                            sh->CastSpell(sh, SPELL_SPIRIT_HEAL, true);
                    }

                    // Resurrection visual
                    player->CastSpell(player, SPELL_RESURRECTION_VISUAL, true);
                    _ResurrectQueue.push_back(*itr2);
                }
                (itr->second).clear();
            }

            _ReviveQueue.clear();
            _LastResurrectTime = 0;
        }
        else
            // queue is clear and time passed, just update last resurrection time
            _LastResurrectTime = 0;
    }
    else if (_LastResurrectTime > 500)    // Resurrect players only half a second later, to see spirit heal effect on NPC
    {
        for (std::vector<uint64>::const_iterator itr = _ResurrectQueue.begin(); itr != _ResurrectQueue.end(); ++itr)
        {
            Player* player = ObjectAccessor::FindPlayer(*itr);
            if (!player)
                continue;
            player->ResurrectPlayer(1.0f);
            player->CastSpell(player, 6962, true);
            player->CastSpell(player, SPELL_SPIRIT_HEAL_MANA, true);
            sObjectAccessor->ConvertCorpseForPlayer(*itr);
        }
        _ResurrectQueue.clear();
    }
}

inline void Battleground::_ProcessProgress(uint32 diff)
{
    // *********************************************************
    // ***          BATTLEGROUND BALLANCE SYSTEM             ***
    // *********************************************************
    // if less then minimum players are in on one side, then start premature finish timer
    if (!_PrematureCountDown)
    {
        _PrematureCountDown = true;
        _PrematureCountDownTimer = sBattlegroundMgr->GetPrematureFinishTime();
    }
    else if (_PrematureCountDownTimer < diff)
    {
        // time's up!
        uint32 winner = 0;
        if (GetPlayersCountByTeam(ALLIANCE) >= GetMinPlayersPerTeam())
            winner = ALLIANCE;
        else if (GetPlayersCountByTeam(HORDE) >= GetMinPlayersPerTeam())
            winner = HORDE;

        EndBattleground(winner);
        _PrematureCountDown = false;
    }
    else if (!sBattlegroundMgr->isTesting())
    {
        uint32 newtime = _PrematureCountDownTimer - diff;
        // announce every minute
        if (newtime > (MINUTE * IN_MILLISECONDS))
        {
            if (newtime / (MINUTE * IN_MILLISECONDS) != _PrematureCountDownTimer / (MINUTE * IN_MILLISECONDS))
                PSendMessageToAll(LANG_BATTLEGROUND_PREMATURE_FINISH_WARNING, CHAT_MSG_SYSTEM, NULL, (uint32)(_PrematureCountDownTimer / (MINUTE * IN_MILLISECONDS)));
        }
        else
        {
            //announce every 15 seconds
            if (newtime / (15 * IN_MILLISECONDS) != _PrematureCountDownTimer / (15 * IN_MILLISECONDS))
                PSendMessageToAll(LANG_BATTLEGROUND_PREMATURE_FINISH_WARNING_SECS, CHAT_MSG_SYSTEM, NULL, (uint32)(_PrematureCountDownTimer / IN_MILLISECONDS));
        }
        _PrematureCountDownTimer = newtime;
    }
}

inline void Battleground::_ProcessJoin(uint32 diff)
{
    // *********************************************************
    // ***          BATTLEGROUND STARTING SYSTEM             ***
    // *********************************************************
    ModifyStartDelayTime(diff);

    if (_ResetStatTimer > 5000)
    {
        _ResetStatTimer = 0;
        for (BattlegroundPlayerMap::const_iterator itr = GetPlayers().begin(); itr != GetPlayers().end(); ++itr)
            if (Player* player = ObjectAccessor::FindPlayer(itr->first))
                player->ResetAllPowers();
    }

    if (!(_Events & BG_STARTING_EVENT_1))
    {
        _Events |= BG_STARTING_EVENT_1;

        if (!FindBgMap())
        {
            sLog->outError("Battleground::_ProcessJoin: map (map id: %u, instance id: %u) is not created!", _MapId, _InstanceID);
            EndNow();
            return;
        }

        // Setup here, only when at least one player has ported to the map
        if (!SetupBattleground())
        {
            EndNow();
            return;
        }

        StartingEventCloseDoors();
        SetStartDelayTime(StartDelayTimes[BG_STARTING_EVENT_FIRST]);
        // First start warning - 2 or 1 minute
        SendMessageToAll(StartMessageIds[BG_STARTING_EVENT_FIRST], CHAT_MSG_BG_SYSTEM_NEUTRAL);
    }
    // After 1 minute or 30 seconds, warning is signalled
    else if (GetStartDelayTime() <= StartDelayTimes[BG_STARTING_EVENT_SECOND] && !(_Events & BG_STARTING_EVENT_2))
    {
        _Events |= BG_STARTING_EVENT_2;
        SendMessageToAll(StartMessageIds[BG_STARTING_EVENT_SECOND], CHAT_MSG_BG_SYSTEM_NEUTRAL);
    }
    // After 30 or 15 seconds, warning is signalled
    else if (GetStartDelayTime() <= StartDelayTimes[BG_STARTING_EVENT_THIRD] && !(_Events & BG_STARTING_EVENT_3))
    {
        _Events |= BG_STARTING_EVENT_3;
        SendMessageToAll(StartMessageIds[BG_STARTING_EVENT_THIRD], CHAT_MSG_BG_SYSTEM_NEUTRAL);
    }
    // Delay expired (atfer 2 or 1 minute)
    else if (GetStartDelayTime() <= 0 && !(_Events & BG_STARTING_EVENT_4))
    {
        _Events |= BG_STARTING_EVENT_4;

        StartingEventOpenDoors();

        SendWarningToAll(StartMessageIds[BG_STARTING_EVENT_FOURTH]);
        SetStatus(STATUS_IN_PROGRESS);
        SetStartDelayTime(StartDelayTimes[BG_STARTING_EVENT_FOURTH]);

        // Remove preparation
        if (isArena())
        {
            // TODO : add arena sound PlaySoundToAll(SOUND_ARENA_START);
            for (BattlegroundPlayerMap::const_iterator itr = GetPlayers().begin(); itr != GetPlayers().end(); ++itr)
                if (Player* player = ObjectAccessor::FindPlayer(itr->first))
                {
                    // BG Status packet
                    WorldPacket status;
                    BattlegroundQueueTypeId bgQueueTypeId = sBattlegroundMgr->BGQueueTypeId(_TypeID, GetArenaType());
                    uint32 queueSlot = player->GetBattlegroundQueueIndex(bgQueueTypeId);
                    sBattlegroundMgr->BuildBattlegroundStatusPacket(&status, this, queueSlot, STATUS_IN_PROGRESS, 0, GetStartTime(), GetArenaType());
                    player->GetSession()->SendPacket(&status);

                    player->RemoveAurasDueToSpell(SPELL_ARENA_PREPARATION);
                    player->ResetAllPowers();
                    // remove auras with duration lower than 30s
                    Unit::AuraApplicationMap & auraMap = player->GetAppliedAuras();
                    for (Unit::AuraApplicationMap::iterator iter = auraMap.begin(); iter != auraMap.end();)
                    {
                        AuraApplication * aurApp = iter->second;
                        Aura * aura = aurApp->GetBase();
                        if (!aura->IsPermanent()
                            && aura->GetDuration() <= 30*IN_MILLISECONDS
                            && aurApp->IsPositive()
                            && (!(aura->GetSpellInfo()->Attributes & SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY))
                            && (!aura->HasEffectType(SPELL_AURA_MOD_INVISIBILITY)))
                            player->RemoveAura(iter);
                        else
                            ++iter;
                    }
                }

            CheckArenaWinConditions();
        }
        else
        {
            PlaySoundToAll(SOUND_BG_START);

            for (BattlegroundPlayerMap::const_iterator itr = GetPlayers().begin(); itr != GetPlayers().end(); ++itr)
                if (Player* player = ObjectAccessor::FindPlayer(itr->first))
                {
                    player->RemoveAurasDueToSpell(SPELL_PREPARATION);
                    player->ResetAllPowers();
                }
            // Announce BG starting
            if (sWorld->getBoolConfig(CONFIG_BATTLEGROUND_QUEUE_ANNOUNCER_ENABLE))
                sWorld->SendWorldText(LANG_BG_STARTED_ANNOUNCE_WORLD, GetName(), GetMinLevel(), GetMaxLevel());
        }
    }
}

inline void Battleground::_ProcessLeave(uint32 diff)
{
    // *********************************************************
    // ***          BATTLEGROUND ENDING SYSTEM               ***
    // *********************************************************
    // remove all players from battleground after 2 minutes
    _EndTime -= diff;
    if (_EndTime <= 0)
    {
        _EndTime = 0;
        BattlegroundPlayerMap::iterator itr, next;
        for (itr = _Players.begin(); itr != _Players.end(); itr = next)
        {
            next = itr;
            ++next;
            //itr is erased here!
            RemovePlayerAtLeave(itr->first, true, true);// remove player from BG
            // do not change any battleground's private variables
        }
    }
}

inline Player* Battleground::_GetPlayer(uint64 guid, bool offlineRemove, const char* context) const
{
    Player* player = NULL;
    if (!offlineRemove)
    {
        player = ObjectAccessor::FindPlayer(guid);
        if (!player)
            sLog->outError("Battleground::%s: player (GUID: %u) not found for BG (map: %u, instance id: %u)!",
                context, GUID_LOPART(guid), _MapId, _InstanceID);
    }
    return player;
}

inline Player* Battleground::_GetPlayer(BattlegroundPlayerMap::iterator itr, const char* context)
{
    return _GetPlayer(itr->first, itr->second.OfflineRemoveTime, context);
}

inline Player* Battleground::_GetPlayer(BattlegroundPlayerMap::const_iterator itr, const char* context) const
{
    return _GetPlayer(itr->first, itr->second.OfflineRemoveTime, context);
}

inline Player* Battleground::_GetPlayerForTeam(uint32 teamId, BattlegroundPlayerMap::const_iterator itr, const char* context) const
{
    Player* player = _GetPlayer(itr, context);
    if (player)
    {
        uint32 team = itr->second.Team;
        if (!team)
            team = player->GetTeam();
        if (team != teamId)
            player = NULL;
    }
    return player;
}

void Battleground::SetTeamStartLoc(uint32 TeamID, float X, float Y, float Z, float O)
{
    BattlegroundTeamId idx = GetTeamIndexByTeamId(TeamID);
    _TeamStartLocX[idx] = X;
    _TeamStartLocY[idx] = Y;
    _TeamStartLocZ[idx] = Z;
    _TeamStartLocO[idx] = O;
}

void Battleground::SendPacketToAll(WorldPacket* packet)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayer(itr, "SendPacketToAll"))
            player->GetSession()->SendPacket(packet);
}

void Battleground::SendPacketToTeam(uint32 TeamID, WorldPacket* packet, Player* sender, bool self)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayerForTeam(TeamID, itr, "SendPacketToTeam"))
            if (self || sender != player)
                player->GetSession()->SendPacket(packet);
}

void Battleground::PlaySoundToAll(uint32 SoundID)
{
    WorldPacket data;
    sBattlegroundMgr->BuildPlaySoundPacket(&data, SoundID);
    SendPacketToAll(&data);
}

void Battleground::PlaySoundToTeam(uint32 SoundID, uint32 TeamID)
{
    WorldPacket data;
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayerForTeam(TeamID, itr, "PlaySoundToTeam"))
        {
            sBattlegroundMgr->BuildPlaySoundPacket(&data, SoundID);
            player->GetSession()->SendPacket(&data);
        }
}

void Battleground::CastSpellOnTeam(uint32 SpellID, uint32 TeamID)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayerForTeam(TeamID, itr, "CastSpellOnTeam"))
            player->CastSpell(player, SpellID, true);
}

void Battleground::RemoveAuraOnTeam(uint32 SpellID, uint32 TeamID)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayerForTeam(TeamID, itr, "RemoveAuraOnTeam"))
            player->RemoveAura(SpellID);
}

void Battleground::YellToAll(Creature* creature, const char* text, uint32 language)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayer(itr, "YellToAll"))
        {
            WorldPacket data(SMSG_MESSAGECHAT, 200);
            creature->BuildMonsterChat(&data, CHAT_MSG_MONSTER_YELL, text, language, creature->GetName(), itr->first);
            player->GetSession()->SendPacket(&data);
        }
}

void Battleground::RewardHonorToTeam(uint32 Honor, uint32 TeamID)
{
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = _GetPlayerForTeam(TeamID, itr, "RewardHonorToTeam"))
            UpdatePlayerScore(player, SCORE_BONUS_HONOR, Honor);
}

void Battleground::RewardReputationToTeam(uint32 faction_id, uint32 Reputation, uint32 TeamID)
{
    if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(faction_id))
        for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
            if (Player* player = _GetPlayerForTeam(TeamID, itr, "RewardReputationToTeam"))
                player->GetReputationMgr().ModifyReputation(factionEntry, Reputation);
}

void Battleground::UpdateWorldState(uint32 Field, uint32 Value)
{
    WorldPacket data;
    sBattlegroundMgr->BuildUpdateWorldStatePacket(&data, Field, Value);
    SendPacketToAll(&data);
}

void Battleground::UpdateWorldStateForPlayer(uint32 Field, uint32 Value, Player* Source)
{
    WorldPacket data;
    sBattlegroundMgr->BuildUpdateWorldStatePacket(&data, Field, Value);
    Source->GetSession()->SendPacket(&data);
}

void Battleground::EndBattleground(uint32 winner)
{
    RemoveFromBGFreeSlotQueue();

    ArenaTeam* winner_arena_team   = NULL;
    ArenaTeam* loser_arena_team    = NULL;
    uint32 loser_team_rating       = 0;
    uint32 loser_matchmaker_rating = 0;
    int32  loser_change            = 0;
    int32  loser_matchmaker_change = 0;
    uint32 winner_team_rating      = 0;
    uint32 winner_matchmaker_rating = 0;
    int32  winner_change           = 0;
    int32  winner_matchmaker_change = 0;
    WorldPacket data;
    int32 winmsg_id                = 0;

    if (winner == ALLIANCE)
    {
        winmsg_id = isBattleground() ? LANG_BG_A_WINS : LANG_ARENA_GOLD_WINS;

        PlaySoundToAll(SOUND_ALLIANCE_WINS);                // alliance wins sound

        SetWinner(WINNER_ALLIANCE);
    }
    else if (winner == HORDE)
    {
        winmsg_id = isBattleground() ? LANG_BG_H_WINS : LANG_ARENA_GREEN_WINS;

        PlaySoundToAll(SOUND_HORDE_WINS);                   // horde wins sound

        SetWinner(WINNER_HORDE);
    }
    else
    {
        SetWinner(3);
    }

    SetStatus(STATUS_WAIT_LEAVE);
    //we must set it this way, because end time is sent in packet!
    _EndTime = TIME_TO_AUTOREMOVE;

    // arena rating calculation
    if (isArena() && isRated())
    {
        winner_arena_team = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(winner));
        loser_arena_team = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(GetOtherTeam(winner)));
        if (winner_arena_team && loser_arena_team && winner_arena_team != loser_arena_team)
        {
            if (winner != WINNER_NONE)
            {
                loser_team_rating = loser_arena_team->GetRating();
                loser_matchmaker_rating = GetArenaMatchmakerRating(GetOtherTeam(winner));
                winner_team_rating = winner_arena_team->GetRating();
                winner_matchmaker_rating = GetArenaMatchmakerRating(winner);
                winner_matchmaker_change = winner_arena_team->WonAgainst(winner_matchmaker_rating, loser_matchmaker_rating, winner_change);
                loser_matchmaker_change = loser_arena_team->LostAgainst(loser_matchmaker_rating, winner_matchmaker_rating, loser_change);
                sLog->outArena("--- Winner: old rating: %u, rating gain: %d, old MMR: %u, MMR gain: %d --- Loser: old rating: %u, rating loss: %d, old MMR: %u, MMR loss: %d ---", winner_team_rating, winner_change, winner_matchmaker_rating,
                    winner_matchmaker_change, loser_team_rating, loser_change, loser_matchmaker_rating, loser_matchmaker_change);
                SetArenaMatchmakerRating(winner, winner_matchmaker_rating + winner_matchmaker_change);
                SetArenaMatchmakerRating(GetOtherTeam(winner), loser_matchmaker_rating + loser_matchmaker_change);
                SetArenaTeamRatingChangeForTeam(winner, winner_change);
                SetArenaTeamRatingChangeForTeam(GetOtherTeam(winner), loser_change);
                sLog->outArena("Arena match Type: %u for Team1Id: %u - Team2Id: %u ended. WinnerTeamId: %u. Winner rating: +%d, Loser rating: %d", _ArenaType, _ArenaTeamIds[BG_TEAM_ALLIANCE], _ArenaTeamIds[BG_TEAM_HORDE], winner_arena_team->GetId(), winner_change, loser_change);
                if (sWorld->getBoolConfig(CONFIG_ARENA_LOG_EXTENDED_INFO))
                    for (Battleground::BattlegroundScoreMap::const_iterator itr = GetPlayerScoresBegin(); itr != GetPlayerScoresEnd(); ++itr)
                        if (Player* player = ObjectAccessor::FindPlayer(itr->first))
                            sLog->outArena("Statistics for %s (GUID: " UI64FMTD ", Team: %d, IP: %s): %u damage, %u healing, %u killing blows", player->GetName(), itr->first, player->GetArenaTeamId(_ArenaType == 5 ? 2 : _ArenaType == 3), player->GetSession()->GetRemoteAddress().c_str(), itr->second->DamageDone, itr->second->HealingDone, itr->second->KillingBlows);
            }
            // Deduct 16 points from each teams arena-rating if there are no winners after 45+2 minutes
            else
            {
                SetArenaTeamRatingChangeForTeam(ALLIANCE, ARENA_TIMELIMIT_POINTS_LOSS);
                SetArenaTeamRatingChangeForTeam(HORDE, ARENA_TIMELIMIT_POINTS_LOSS);
                winner_arena_team->FinishGame(ARENA_TIMELIMIT_POINTS_LOSS);
                loser_arena_team->FinishGame(ARENA_TIMELIMIT_POINTS_LOSS);
            }
        }
        else
        {
            SetArenaTeamRatingChangeForTeam(ALLIANCE, 0);
            SetArenaTeamRatingChangeForTeam(HORDE, 0);
        }
    }

    uint8 aliveWinners = GetAlivePlayersCountByTeam(winner);
    for (BattlegroundPlayerMap::iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
    {
        uint32 team = itr->second.Team;

        if (itr->second.OfflineRemoveTime)
        {
            //if rated arena match - make member lost!
            if (isArena() && isRated() && winner_arena_team && loser_arena_team && winner_arena_team != loser_arena_team)
            {
                if (team == winner)
                    winner_arena_team->OfflineMemberLost(itr->first, loser_matchmaker_rating, winner_matchmaker_change);
                else
                    loser_arena_team->OfflineMemberLost(itr->first, winner_matchmaker_rating, loser_matchmaker_change);
            }
            continue;
        }

        Player* player = _GetPlayer(itr, "EndBattleground");
        if (!player)
            continue;

        // should remove spirit of redemption
        if (player->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
            player->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

        // Last standing - Rated 5v5 arena & be solely alive player
        if (team == winner && isArena() && isRated() && GetArenaType() == ARENA_TYPE_5v5 && aliveWinners == 1 && player->isAlive())
            player->CastSpell(player, SPELL_THE_LAST_STANDING, true);

        if (!player->isAlive())
        {
            player->ResurrectPlayer(1.0f);
            player->SpawnCorpseBones();
        }
        else
        {
            //needed cause else in av some creatures will kill the players at the end
            player->CombatStop();
            player->getHostileRefManager().deleteReferences();
        }

        //this line is obsolete - team is set ALWAYS
        //if (!team) team = player->GetTeam();

        // per player calculation
        if (isArena() && isRated() && winner_arena_team && loser_arena_team && winner_arena_team != loser_arena_team)
        {
            if (team == winner)
            {
                // update achievement BEFORE personal rating update
                ArenaTeamMember* member = winner_arena_team->GetMember(player->GetGUID());
                if (member)
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA, 1);

                winner_arena_team->MemberWon(player, loser_matchmaker_rating, winner_matchmaker_change);
            }
            else
            {
                loser_arena_team->MemberLost(player, winner_matchmaker_rating, loser_matchmaker_change);

                // Arena lost => reset the win_rated_arena having the "no_lose" condition
                player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA, player, ACHIEVEMENT_CRITERIA_CONDITION_NO_LOSE);
            }
        }

        uint32 winner_kills = player->GetRandomWinner() ? BG_REWARD_WINNER_HONOR_LAST : BG_REWARD_WINNER_HONOR_FIRST;
        uint32 loser_kills = player->GetRandomWinner() ? BG_REWARD_LOSER_HONOR_LAST : BG_REWARD_LOSER_HONOR_FIRST;
        uint32 winner_arena = player->GetRandomWinner() ? BG_REWARD_WINNER_ARENA_LAST : BG_REWARD_WINNER_ARENA_FIRST;

        // Reward winner team
        if (team == winner)
        {
            if (IsRandom() || BattlegroundMgr::IsBGWeekend(GetTypeID()))
            {
                UpdatePlayerScore(player, SCORE_BONUS_HONOR, GetBonusHonorFromKill(winner_kills));
                if (!player->GetRandomWinner())
                    player->SetRandomWinner(true);
            }

            player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_BG, 1);
        }
        else
        {
            if (IsRandom() || BattlegroundMgr::IsBGWeekend(GetTypeID()))
                UpdatePlayerScore(player, SCORE_BONUS_HONOR, GetBonusHonorFromKill(loser_kills));
        }

        player->ResetAllPowers();
        player->CombatStopWithPets(true);

        BlockMovement(player);

        sBattlegroundMgr->BuildPvpLogDataPacket(&data, this);
        player->GetSession()->SendPacket(&data);

        BattlegroundQueueTypeId bgQueueTypeId = BattlegroundMgr::BGQueueTypeId(GetTypeID(), GetArenaType());
        sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, this, player->GetBattlegroundQueueIndex(bgQueueTypeId), STATUS_IN_PROGRESS, TIME_TO_AUTOREMOVE, GetStartTime(), GetArenaType());
        player->GetSession()->SendPacket(&data);
        player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND, 1);
    }

    if (isArena() && isRated() && winner_arena_team && loser_arena_team && winner_arena_team != loser_arena_team)
    {
        // update arena points only after increasing the player's match count!
        //obsolete: winner_arena_team->UpdateArenaPointsHelper();
        //obsolete: loser_arena_team->UpdateArenaPointsHelper();
        // save the stat changes
        winner_arena_team->SaveToDB();
        loser_arena_team->SaveToDB();
        // send updated arena team stats to players
        // this way all arena team members will get notified, not only the ones who participated in this match
        winner_arena_team->NotifyStatsChanged();
        loser_arena_team->NotifyStatsChanged();
    }

    if (winmsg_id)
        SendMessageToAll(winmsg_id, CHAT_MSG_BG_SYSTEM_NEUTRAL);
}

uint32 Battleground::GetBonusHonorFromKill(uint32 kills) const
{
    //variable kills means how many honorable kills you scored (so we need kills * honor_for_one_kill)
    uint32 maxLevel = std::min(GetMaxLevel(), 80U);
    return SkyFire::Honor::hk_honor_at_level(maxLevel, float(kills));
}

void Battleground::BlockMovement(Player* player)
{
    player->SetClientControl(player, 0);                          // movement disabled NOTE: the effect will be automatically removed by client when the player is teleported from the battleground, so no need to send with uint8(1) in RemovePlayerAtLeave()
}

void Battleground::RemovePlayerAtLeave(uint64 guid, bool Transport, bool SendPacket)
{
    uint32 team = GetPlayerTeam(guid);
    bool participant = false;
    // Remove from lists/maps
    BattlegroundPlayerMap::iterator itr = _Players.find(guid);
    if (itr != _Players.end())
    {
        UpdatePlayersCountByTeam(team, true);               // -1 player
        _Players.erase(itr);
        // check if the player was a participant of the match, or only entered through gm command (goname)
        participant = true;
    }

    BattlegroundScoreMap::iterator itr2 = PlayerScores.find(guid);
    if (itr2 != PlayerScores.end())
    {
        delete itr2->second;                                // delete player's score
        PlayerScores.erase(itr2);
    }

    RemovePlayerFromResurrectQueue(guid);

    Player* player = ObjectAccessor::FindPlayer(guid);

    // should remove spirit of redemption
    if (player)
    {
        if (player->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
            player->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

        if (!player->isAlive())                              // resurrect on exit
        {
            player->ResurrectPlayer(1.0f);
            player->SpawnCorpseBones();
        }
    }

    RemovePlayer(player, guid, team);                           // BG subclass specific code

    if (participant) // if the player was a match participant, remove auras, calc rating, update queue
    {
        BattlegroundTypeId bgTypeId = GetTypeID();
        BattlegroundQueueTypeId bgQueueTypeId = BattlegroundMgr::BGQueueTypeId(GetTypeID(), GetArenaType());
        if (player)
        {
            player->ClearAfkReports();

            if (!team) team = player->GetTeam();

            // if arena, remove the specific arena auras
            if (isArena())
            {
                bgTypeId=BATTLEGROUND_AA;                   // set the bg type to all arenas (it will be used for queue refreshing)

                // unsummon current and summon old pet if there was one and there isn't a current pet
                player->RemovePet(NULL, PET_SAVE_AS_CURRENT);
                player->ResummonPetTemporaryUnSummonedIfAny();

                if (isRated() && GetStatus() == STATUS_IN_PROGRESS)
                {
                    //left a rated match while the encounter was in progress, consider as loser
                    ArenaTeam* winner_arena_team = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(GetOtherTeam(team)));
                    ArenaTeam* loser_arena_team = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(team));
                    if (winner_arena_team && loser_arena_team && winner_arena_team != loser_arena_team)
                        loser_arena_team->MemberLost(player, GetArenaMatchmakerRating(GetOtherTeam(team)));
                }
            }
            if (SendPacket)
            {
                WorldPacket data;
                sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, this, player->GetBattlegroundQueueIndex(bgQueueTypeId), STATUS_NONE, 0, 0, 0);
                player->GetSession()->SendPacket(&data);
            }

            // this call is important, because player, when joins to battleground, this method is not called, so it must be called when leaving bg
            player->RemoveBattlegroundQueueId(bgQueueTypeId);
        }
        else
        // removing offline participant
        {
            if (isRated() && GetStatus() == STATUS_IN_PROGRESS)
            {
                //left a rated match while the encounter was in progress, consider as loser
                ArenaTeam* others_arena_team = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(GetOtherTeam(team)));
                ArenaTeam* players_arena_team = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(team));
                if (others_arena_team && players_arena_team)
                    players_arena_team->OfflineMemberLost(guid, GetArenaMatchmakerRating(GetOtherTeam(team)));
            }
        }

        // remove from raid group if player is member
        if (Group* group = GetBgRaid(team))
        {
            if (!group->RemoveMember(guid))                // group was disbanded
            {
                SetBgRaid(team, NULL);
            }
        }
        DecreaseInvitedCount(team);
        //we should update battleground queue, but only if bg isn't ending
        if (isBattleground() && GetStatus() < STATUS_WAIT_LEAVE)
        {
            // a player has left the battleground, so there are free slots -> add to queue
            AddToBGFreeSlotQueue();
            sBattlegroundMgr->ScheduleQueueUpdate(0, 0, bgQueueTypeId, bgTypeId, GetBracketId());
        }
        // Let others know
        WorldPacket data;
        sBattlegroundMgr->BuildPlayerLeftBattlegroundPacket(&data, guid);
        SendPacketToTeam(team, &data, player, false);
    }

    if (player)
    {
        // Do next only if found in battleground
        player->SetBattlegroundId(0, BATTLEGROUND_TYPE_NONE);  // We're not in BG.
        // reset destination bg team
        player->SetBGTeam(0);

        if (Transport)
            player->TeleportToBGEntryPoint();

        sLog->outDetail("BATTLEGROUND: Removed player %s from Battleground.", player->GetName());
    }

    //battleground object will be deleted next Battleground::Update() call
}

// this method is called when no players remains in battleground
void Battleground::Reset()
{
    SetWinner(WINNER_NONE);
    SetStatus(STATUS_WAIT_QUEUE);
    SetStartTime(0);
    SetEndTime(0);
    SetLastResurrectTime(0);
    SetArenaType(0);
    SetRated(false);

    _Events = 0;

    if (_InvitedAlliance > 0 || _InvitedHorde > 0)
        sLog->outError("Battleground::Reset: one of the counters is not 0 (alliance: %u, horde: %u) for BG (map: %u, instance id: %u)!",
            _InvitedAlliance, _InvitedHorde, _MapId, _InstanceID);

    _InvitedAlliance = 0;
    _InvitedHorde = 0;
    _InBGFreeSlotQueue = false;

    _Players.clear();

    for (BattlegroundScoreMap::const_iterator itr = PlayerScores.begin(); itr != PlayerScores.end(); ++itr)
        delete itr->second;
    PlayerScores.clear();

    ResetBGSubclass();
}

void Battleground::StartBattleground()
{
    SetStartTime(0);
    SetLastResurrectTime(0);
    // add BG to free slot queue
    AddToBGFreeSlotQueue();

    // add bg to update list
    // This must be done here, because we need to have already invited some players when first BG::Update() method is executed
    // and it doesn't matter if we call StartBattleground() more times, because m_Battlegrounds is a map and instance id never changes
    sBattlegroundMgr->AddBattleground(GetInstanceID(), GetTypeID(), this);
    if (_IsRated)
        sLog->outArena("Arena match type: %u for Team1Id: %u - Team2Id: %u started.", _ArenaType, _ArenaTeamIds[BG_TEAM_ALLIANCE], _ArenaTeamIds[BG_TEAM_HORDE]);
}

void Battleground::AddPlayer(Player* player)
{
    // remove afk from player
    if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_AFK))
        player->ToggleAFK();

    // score struct must be created in inherited class

    uint64 guid = player->GetGUID();
    uint32 team = player->GetBGTeam();

    BattlegroundPlayer bp;
    bp.OfflineRemoveTime = 0;
    bp.Team = team;

    // Add to list/maps
    _Players[guid] = bp;

    UpdatePlayersCountByTeam(team, false);                  // +1 player

    WorldPacket data;
    sBattlegroundMgr->BuildPlayerJoinedBattlegroundPacket(&data, player);
    SendPacketToTeam(team, &data, player, false);

    // BG Status packet
    WorldPacket status;
    BattlegroundQueueTypeId bgQueueTypeId = sBattlegroundMgr->BGQueueTypeId(_TypeID, GetArenaType());
    uint32 queueSlot = player->GetBattlegroundQueueIndex(bgQueueTypeId);
    sBattlegroundMgr->BuildBattlegroundStatusPacket(&status, this, queueSlot, STATUS_IN_PROGRESS, 0, GetStartTime(), GetArenaType(), isArena() ? 0 : 1);
    player->GetSession()->SendPacket(&status);

    player->RemoveAurasByType(SPELL_AURA_MOUNTED);

    // add arena specific auras
    if (isArena())
    {
        player->ResummonPetTemporaryUnSummonedIfAny();

        // Removing pet's buffs and debuffs which are not permanent on Arena enter
        if (Pet* pet = player->GetPet())
        {
            pet->SetHealth(pet->GetMaxHealth());

            Unit::AuraApplicationMap& appliedAuras = pet->GetAppliedAuras();
            for (Unit::AuraApplicationMap::iterator itr = appliedAuras.begin(); itr != appliedAuras.end(); ++itr)
                if (AuraApplication* aurApp = itr->second)
                    if (Aura* aura = aurApp->GetBase())
                        if (!aura->IsPermanent())
                            pet->RemoveAura(itr);
        }

        player->RemoveArenaEnchantments(TEMP_ENCHANTMENT_SLOT);
        if (team == ALLIANCE)                                // gold
        {
            if (player->GetTeam() == HORDE)
                player->CastSpell(player, SPELL_HORDE_GOLD_FLAG, true);
            else
                player->CastSpell(player, SPELL_ALLIANCE_GOLD_FLAG, true);
        }
        else                                                // green
        {
            if (player->GetTeam() == HORDE)
                player->CastSpell(player, SPELL_HORDE_GREEN_FLAG, true);
            else
                player->CastSpell(player, SPELL_ALLIANCE_GREEN_FLAG, true);
        }

        player->DestroyConjuredItems(true);
        player->UnsummonPetTemporaryIfAny();

        if (GetStatus() == STATUS_WAIT_JOIN)                 // not started yet
        {
            player->CastSpell(player, SPELL_ARENA_PREPARATION, true);
            player->ResetAllPowers();
        }
        WorldPacket teammate;
        teammate.Initialize(SMSG_ARENA_OPPONENT_UPDATE, 8);
        teammate << uint64(player->GetGUID());
        SendPacketToTeam(team, &teammate, player, false);
    }
    else
    {
        if (GetStatus() == STATUS_WAIT_JOIN)                 // not started yet
            player->CastSpell(player, SPELL_PREPARATION, true);   // reduces all mana cost of spells.
    }

    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_BG, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);
    player->GetAchievementMgr().ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL, player, ACHIEVEMENT_CRITERIA_CONDITION_BG_MAP, GetMapId(), true);

    // setup BG group membership
    PlayerAddedToBGCheckIfBGIsRunning(player);
    AddOrSetPlayerToCorrectBgGroup(player, team);

    // Log
    sLog->outDetail("BATTLEGROUND: Player %s joined the battle.", player->GetName());
}

// this method adds player to his team's bg group, or sets his correct group if player is already in bg group
void Battleground::AddOrSetPlayerToCorrectBgGroup(Player* player, uint32 team)
{
    uint64 playerGuid = player->GetGUID();
    Group* group = GetBgRaid(team);
    if (!group)                                      // first player joined
    {
        group = new Group;
        SetBgRaid(team, group);
        group->Create(player);
    }
    else                                            // raid already exist
    {
        if (group->IsMember(playerGuid))
        {
            uint8 subgroup = group->GetMemberGroup(playerGuid);
            player->SetBattlegroundOrBattlefieldRaid(group, subgroup);
        }
        else
        {
            group->AddMember(player);
            if (Group* originalGroup = player->GetOriginalGroup())
                if (originalGroup->IsLeader(playerGuid))
                {
                    group->ChangeLeader(playerGuid);
                    group->SendUpdate();
                }
        }
    }
}

// This method should be called when player logs into running battleground
void Battleground::EventPlayerLoggedIn(Player* player)
{
    uint64 guid = player->GetGUID();
    // player is correct pointer
    for (std::deque<uint64>::iterator itr = _OfflineQueue.begin(); itr != _OfflineQueue.end(); ++itr)
    {
        if (*itr == guid)
        {
            _OfflineQueue.erase(itr);
            break;
        }
    }
    _Players[guid].OfflineRemoveTime = 0;
    PlayerAddedToBGCheckIfBGIsRunning(player);
    // if battleground is starting, then add preparation aura
    // we don't have to do that, because preparation aura isn't removed when player logs out
}

// This method should be called when player logs out from running battleground
void Battleground::EventPlayerLoggedOut(Player* player)
{
    uint64 guid = player->GetGUID();
    // player is correct pointer, it is checked in WorldSession::LogoutPlayer()
    _OfflineQueue.push_back(player->GetGUID());
    _Players[guid].OfflineRemoveTime = sWorld->GetGameTime() + MAX_OFFLINE_TIME;
    if (GetStatus() == STATUS_IN_PROGRESS)
    {
        // drop flag and handle other cleanups
        RemovePlayer(player, guid, GetPlayerTeam(guid));

        // 1 player is logging out, if it is the last, then end arena!
        if (isArena())
            if (GetAlivePlayersCountByTeam(player->GetTeam()) <= 1 && GetPlayersCountByTeam(GetOtherTeam(player->GetTeam())))
                EndBattleground(GetOtherTeam(player->GetTeam()));
    }
}

// This method should be called only once ... it adds pointer to queue
void Battleground::AddToBGFreeSlotQueue()
{
    // make sure to add only once
    if (!_InBGFreeSlotQueue && isBattleground())
    {
        sBattlegroundMgr->BGFreeSlotQueue[_TypeID].push_front(this);
        _InBGFreeSlotQueue = true;
    }
}

// This method removes this battleground from free queue - it must be called when deleting battleground - not used now
void Battleground::RemoveFromBGFreeSlotQueue()
{
    // set to be able to re-add if needed
    _InBGFreeSlotQueue = false;
    // uncomment this code when battlegrounds will work like instances
    for (BGFreeSlotQueueType::iterator itr = sBattlegroundMgr->BGFreeSlotQueue[_TypeID].begin(); itr != sBattlegroundMgr->BGFreeSlotQueue[_TypeID].end(); ++itr)
    {
        if ((*itr)->GetInstanceID() == _InstanceID)
        {
            sBattlegroundMgr->BGFreeSlotQueue[_TypeID].erase(itr);
            return;
        }
    }
}

// get the number of free slots for team
// returns the number how many players can join battleground to MaxPlayersPerTeam
uint32 Battleground::GetFreeSlotsForTeam(uint32 Team) const
{
    // if BG is starting ... invite anyone
    if (GetStatus() == STATUS_WAIT_JOIN)
        return (GetInvitedCount(Team) < GetMaxPlayersPerTeam()) ? GetMaxPlayersPerTeam() - GetInvitedCount(Team) : 0;
    // if BG is already started .. do not allow to join too much players of one faction
    uint32 otherTeam;
    uint32 otherIn;
    if (Team == ALLIANCE)
    {
        otherTeam = GetInvitedCount(HORDE);
        otherIn = GetPlayersCountByTeam(HORDE);
    }
    else
    {
        otherTeam = GetInvitedCount(ALLIANCE);
        otherIn = GetPlayersCountByTeam(ALLIANCE);
    }
    if (GetStatus() == STATUS_IN_PROGRESS)
    {
        // difference based on ppl invited (not necessarily entered battle)
        // default: allow 0
        uint32 diff = 0;
        // allow join one person if the sides are equal (to fill up bg to minplayersperteam)
        if (otherTeam == GetInvitedCount(Team))
            diff = 1;
        // allow join more ppl if the other side has more players
        else if (otherTeam > GetInvitedCount(Team))
            diff = otherTeam - GetInvitedCount(Team);

        // difference based on max players per team (don't allow inviting more)
        uint32 diff2 = (GetInvitedCount(Team) < GetMaxPlayersPerTeam()) ? GetMaxPlayersPerTeam() - GetInvitedCount(Team) : 0;
        // difference based on players who already entered
        // default: allow 0
        uint32 diff3 = 0;
        // allow join one person if the sides are equal (to fill up bg minplayersperteam)
        if (otherIn == GetPlayersCountByTeam(Team))
            diff3 = 1;
        // allow join more ppl if the other side has more players
        else if (otherIn > GetPlayersCountByTeam(Team))
            diff3 = otherIn - GetPlayersCountByTeam(Team);
        // or other side has less than minPlayersPerTeam
        else if (GetInvitedCount(Team) <= GetMinPlayersPerTeam())
            diff3 = GetMinPlayersPerTeam() - GetInvitedCount(Team) + 1;

        // return the minimum of the 3 differences

        // min of diff and diff 2
        diff = std::min(diff, diff2);
        // min of diff, diff2 and diff3
        return std::min(diff, diff3);
    }
    return 0;
}

bool Battleground::HasFreeSlots() const
{
    return GetPlayersSize() < GetMaxPlayers();
}

void Battleground::UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor)
{
    //this procedure is called from virtual function implemented in bg subclass
    BattlegroundScoreMap::const_iterator itr = PlayerScores.find(Source->GetGUID());
    if (itr == PlayerScores.end())                         // player not found...
        return;

    switch (type)
    {
        case SCORE_KILLING_BLOWS:                           // Killing blows
            itr->second->KillingBlows += value;
            break;
        case SCORE_DEATHS:                                  // Deaths
            itr->second->Deaths += value;
            break;
        case SCORE_HONORABLE_KILLS:                         // Honorable kills
            itr->second->HonorableKills += value;
            break;
        case SCORE_BONUS_HONOR:                             // Honor bonus
            // do not add honor in arenas
            if (isBattleground())
            {
                // reward honor instantly
                if (doAddHonor)
                    Source->RewardHonor(NULL, 1, value);    // RewardHonor calls UpdatePlayerScore with doAddHonor = false
                else
                    itr->second->BonusHonor += value;
            }
            break;
            // used only in EY, but in MSG_PVP_LOG_DATA opcode
        case SCORE_DAMAGE_DONE:                             // Damage Done
            itr->second->DamageDone += value;
            break;
        case SCORE_HEALING_DONE:                            // Healing Done
            itr->second->HealingDone += value;
            break;
        default:
            sLog->outError("Battleground::UpdatePlayerScore: unknown score type (%u) for BG (map: %u, instance id: %u)!",
                type, _MapId, _InstanceID);
            break;
    }
}

void Battleground::AddPlayerToResurrectQueue(uint64 npc_guid, uint64 player_guid)
{
    _ReviveQueue[npc_guid].push_back(player_guid);

    Player* player = ObjectAccessor::FindPlayer(player_guid);
    if (!player)
        return;

    player->CastSpell(player, SPELL_WAITING_FOR_RESURRECT, true);
}

void Battleground::RemovePlayerFromResurrectQueue(uint64 player_guid)
{
    for (std::map<uint64, std::vector<uint64> >::iterator itr = _ReviveQueue.begin(); itr != _ReviveQueue.end(); ++itr)
    {
        for (std::vector<uint64>::iterator itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
        {
            if (*itr2 == player_guid)
            {
                (itr->second).erase(itr2);
                if (Player* player = ObjectAccessor::FindPlayer(player_guid))
                    player->RemoveAurasDueToSpell(SPELL_WAITING_FOR_RESURRECT);
                return;
            }
        }
    }
}

bool Battleground::AddObject(uint32 type, uint32 entry, float x, float y, float z, float o, float rotation0, float rotation1, float rotation2, float rotation3, uint32 /*respawnTime*/)
{
    // If the assert is called, means that _BgObjects must be resized!
    ASSERT(type < BgObjects.size());

    Map* map = FindBgMap();
    if (!map)
        return false;
    // Must be created this way, adding to godatamap would add it to the base map of the instance
    // and when loading it (in go::LoadFromDB()), a new guid would be assigned to the object, and a new object would be created
    // So we must create it specific for this instance
    GameObject* go = new GameObject;
    if (!go->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), entry, GetBgMap(),
        PHASEMASK_NORMAL, x, y, z, o, rotation0, rotation1, rotation2, rotation3, 100, GO_STATE_READY))
    {
        sLog->outErrorDb("Battleground::AddObject: cannot create gameobject (entry: %u) for BG (map: %u, instance id: %u)!",
                entry, _MapId, _InstanceID);
        sLog->outError("Battleground::AddObject: cannot create gameobject (entry: %u) for BG (map: %u, instance id: %u)!",
                entry, _MapId, _InstanceID);
        delete go;
        return false;
    }
/*
    uint32 guid = go->GetGUIDLow();

    // without this, UseButtonOrDoor caused the crash, since it tried to get go info from godata
    // iirc that was changed, so adding to go data map is no longer required if that was the only function using godata from GameObject without checking if it existed
    GameObjectData& data = sObjectMgr->NewGOData(guid);

    data.id             = entry;
    data.mapid          = GetMapId();
    data.posX           = x;
    data.posY           = y;
    data.posZ           = z;
    data.orientation    = o;
    data.rotation0      = rotation0;
    data.rotation1      = rotation1;
    data.rotation2      = rotation2;
    data.rotation3      = rotation3;
    data.spawntimesecs  = respawnTime;
    data.spawnMask      = 1;
    data.animprogress   = 100;
    data.go_state       = 1;
*/
    // Add to world, so it can be later looked up from HashMapHolder
    if (!map->AddToMap(go))
    {
        delete go;
        return false;
    }
    BgObjects[type] = go->GetGUID();
    return true;
}

// Some doors aren't despawned so we cannot handle their closing in gameobject::update()
// It would be nice to correctly implement GO_ACTIVATED state and open/close doors in gameobject code
void Battleground::DoorClose(uint32 type)
{
    if (GameObject* obj = GetBgMap()->GetGameObject(BgObjects[type]))
    {
        // If doors are open, close it
        if (obj->getLootState() == GO_ACTIVATED && obj->GetGoState() != GO_STATE_READY)
        {
            // Change state to allow door to be closed
            obj->SetLootState(GO_READY);
            obj->UseDoorOrButton(RESPAWN_ONE_DAY);
        }
    }
    else
        sLog->outError("Battleground::DoorClose: door gameobject (type: %u, GUID: %u) not found for BG (map: %u, instance id: %u)!",
            type, GUID_LOPART(BgObjects[type]), _MapId, _InstanceID);
}

void Battleground::DoorOpen(uint32 type)
{
    if (GameObject* obj = GetBgMap()->GetGameObject(BgObjects[type]))
    {
        // Change state to be sure they will be opened
        obj->SetLootState(GO_READY);
        obj->UseDoorOrButton(RESPAWN_ONE_DAY);
    }
    else
        sLog->outError("Battleground::DoorOpen: door gameobject (type: %u, GUID: %u) not found for BG (map: %u, instance id: %u)!",
            type, GUID_LOPART(BgObjects[type]), _MapId, _InstanceID);
}

GameObject* Battleground::GetBGObject(uint32 type)
{
    GameObject* obj = GetBgMap()->GetGameObject(BgObjects[type]);
    if (!obj)
        sLog->outError("Battleground::GetBGObject: gameobject (type: %u, GUID: %u) not found for BG (map: %u, instance id: %u)!",
            type, GUID_LOPART(BgObjects[type]), _MapId, _InstanceID);
    return obj;
}

Creature* Battleground::GetBGCreature(uint32 type)
{
    Creature* creature = GetBgMap()->GetCreature(BgCreatures[type]);
    if (!creature)
        sLog->outError("Battleground::GetBGCreature: creature (type: %u, GUID: %u) not found for BG (map: %u, instance id: %u)!",
            type, GUID_LOPART(BgCreatures[type]), _MapId, _InstanceID);
    return creature;
}

void Battleground::SpawnBGObject(uint32 type, uint32 respawntime)
{
    if (Map* map = FindBgMap())
        if (GameObject* obj = map->GetGameObject(BgObjects[type]))
        {
            if (respawntime)
                obj->SetLootState(GO_JUST_DEACTIVATED);
            else
                if (obj->getLootState() == GO_JUST_DEACTIVATED)
                    // Change state from GO_JUST_DEACTIVATED to GO_READY in case battleground is starting again
                    obj->SetLootState(GO_READY);
            obj->SetRespawnTime(respawntime);
            map->AddToMap(obj);
        }
}

Creature* Battleground::AddCreature(uint32 entry, uint32 type, uint32 teamval, float x, float y, float z, float o, uint32 respawntime)
{
    // If the assert is called, means that BgCreatures must be resized!
    ASSERT(type < BgCreatures.size());

    Map* map = FindBgMap();
    if (!map)
        return NULL;

    Creature* creature = new Creature;
    if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), map, PHASEMASK_NORMAL, entry, 0, teamval, x, y, z, o))
    {
        sLog->outError("Battleground::AddCreature: cannot create creature (entry: %u) for BG (map: %u, instance id: %u)!",
            entry, _MapId, _InstanceID);
        delete creature;
        return NULL;
    }

    creature->SetHomePosition(x, y, z, o);

    CreatureTemplate const* cinfo = sObjectMgr->GetCreatureTemplate(entry);
    if (!cinfo)
    {
        sLog->outError("Battleground::AddCreature: creature template (entry: %u) does not exist for BG (map: %u, instance id: %u)!",
            entry, _MapId, _InstanceID);
        delete creature;
        return NULL;
    }
    // Force using DB speeds
    creature->SetSpeed(MOVE_WALK,  cinfo->speed_walk);
    creature->SetSpeed(MOVE_RUN,   cinfo->speed_run);

    if (!map->AddToMap(creature))
    {
        delete creature;
        return NULL;
    }

    BgCreatures[type] = creature->GetGUID();

    if (respawntime)
        creature->SetRespawnDelay(respawntime);

    return  creature;
}

bool Battleground::DelCreature(uint32 type)
{
    if (!BgCreatures[type])
        return true;

    if (Creature *creature = GetBgMap()->GetCreature(BgCreatures[type]))
    {
        creature->AddObjectToRemoveList();
        BgCreatures[type] = 0;
        return true;
    }

    sLog->outError("Battleground::DelCreature: creature (type: %u, GUID: %u) not found for BG (map: %u, instance id: %u)!",
        type, GUID_LOPART(BgCreatures[type]), _MapId, _InstanceID);
    BgCreatures[type] = 0;
    return false;
}

bool Battleground::DelObject(uint32 type)
{
    if (!BgObjects[type])
        return true;

    if (GameObject* obj = GetBgMap()->GetGameObject(BgObjects[type]))
    {
        obj->SetRespawnTime(0);                                 // not save respawn time
        obj->Delete();
        BgObjects[type] = 0;
        return true;
    }
    sLog->outError("Battleground::DelObject: gameobject (type: %u, GUID: %u) not found for BG (map: %u, instance id: %u)!",
        type, GUID_LOPART(BgObjects[type]), _MapId, _InstanceID);
    BgObjects[type] = 0;
    return false;
}

bool Battleground::AddSpiritGuide(uint32 type, float x, float y, float z, float o, uint32 team)
{
    uint32 entry = (team == ALLIANCE) ?
        BG_CREATURE_ENTRY_A_SPIRITGUIDE :
        BG_CREATURE_ENTRY_H_SPIRITGUIDE;

    if (Creature* creature = AddCreature(entry, type, team, x, y, z, o))
    {
        creature->setDeathState(DEAD);
        creature->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, creature->GetGUID());
        // aura
        // TODO: Fix display here
        // creature->SetVisibleAura(0, SPELL_SPIRIT_HEAL_CHANNEL);
        // casting visual effect
        creature->SetUInt32Value(UNIT_CHANNEL_SPELL, SPELL_SPIRIT_HEAL_CHANNEL);
        // correct cast speed
        creature->SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
        //creature->CastSpell(creature, SPELL_SPIRIT_HEAL_CHANNEL, true);
        return true;
    }
    sLog->outError("Battleground::AddSpiritGuide: cannot create spirit guide (type: %u, entry: %u) for BG (map: %u, instance id: %u)!",
        type, entry, _MapId, _InstanceID);
    EndNow();
    return false;
}

void Battleground::SendMessageToAll(int32 entry, ChatMsg type, Player const* source)
{
    if (!entry)
        return;

    SkyFire::BattlegroundChatBuilder bg_builder(type, entry, source);
    SkyFire::LocalizedPacketDo<SkyFire::BattlegroundChatBuilder> bg_do(bg_builder);
    BroadcastWorker(bg_do);
}

void Battleground::PSendMessageToAll(int32 entry, ChatMsg type, Player const* source, ...)
{
    if (!entry)
        return;

    va_list ap;
    va_start(ap, source);

    SkyFire::BattlegroundChatBuilder bg_builder(type, entry, source, &ap);
    SkyFire::LocalizedPacketDo<SkyFire::BattlegroundChatBuilder> bg_do(bg_builder);
    BroadcastWorker(bg_do);

    va_end(ap);
}

void Battleground::SendWarningToAll(int32 entry, ...)
{
    if (!entry)
        return;

    const char *format = sObjectMgr->GetSkyFireStringForDBCLocale(entry);

    char str[1024];
    va_list ap;
    va_start(ap, entry);
    vsnprintf(str, 1024, format, ap);
    va_end(ap);
    std::string msg(str);

    WorldPacket data(SMSG_MESSAGECHAT, 200);

    data << (uint8)CHAT_MSG_RAID_BOSS_EMOTE;
    data << (uint32)LANG_UNIVERSAL;
    data << (uint64)0;
    data << (uint32)0;                                     // 2.1.0
    data << (uint32)1;
    data << (uint8)0;
    data << (uint64)0;
    data << (uint32)(msg.length() + 1);
    data << msg.c_str();
    data << (uint8)0;
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(MAKE_NEW_GUID(itr->first, 0, HIGHGUID_PLAYER)))
            if (player->GetSession())
                player->GetSession()->SendPacket(&data);
}

void Battleground::SendMessage2ToAll(int32 entry, ChatMsg type, Player const* source, int32 arg1, int32 arg2)
{
    SkyFire::Battleground2ChatBuilder bg_builder(type, entry, source, arg1, arg2);
    SkyFire::LocalizedPacketDo<SkyFire::Battleground2ChatBuilder> bg_do(bg_builder);
    BroadcastWorker(bg_do);
}

void Battleground::EndNow()
{
    RemoveFromBGFreeSlotQueue();
    SetStatus(STATUS_WAIT_LEAVE);
    SetEndTime(0);
}

// To be removed
const char* Battleground::GetSkyFireString(int32 entry)
{
    // FIXME: now we have different DBC locales and need localized message for each target client
    return sObjectMgr->GetSkyFireStringForDBCLocale(entry);
}

// IMPORTANT NOTICE:
// buffs aren't spawned/despawned when players captures anything
// buffs are in their positions when battleground starts
void Battleground::HandleTriggerBuff(uint64 go_guid)
{
    GameObject* obj = GetBgMap()->GetGameObject(go_guid);
    if (!obj || obj->GetGoType() != GAMEOBJECT_TYPE_TRAP || !obj->isSpawned())
        return;

    // Change buff type, when buff is used:
    int32 index = BgObjects.size() - 1;
    while (index >= 0 && BgObjects[index] != go_guid)
        index--;
    if (index < 0)
    {
        sLog->outError("Battleground::HandleTriggerBuff: cannot find buff gameobject (GUID: %u, entry: %u, type: %u) in internal data for BG (map: %u, instance id: %u)!",
            GUID_LOPART(go_guid), obj->GetEntry(), obj->GetGoType(), _MapId, _InstanceID);
        return;
    }

    // Randomly select new buff
    uint8 buff = urand(0, 2);
    uint32 entry = obj->GetEntry();
    if (_BuffChange && entry != Buff_Entries[buff])
    {
        // Despawn current buff
        SpawnBGObject(index, RESPAWN_ONE_DAY);
        // Set index for new one
        for (uint8 currBuffTypeIndex = 0; currBuffTypeIndex < 3; ++currBuffTypeIndex)
            if (entry == Buff_Entries[currBuffTypeIndex])
            {
                index -= currBuffTypeIndex;
                index += buff;
            }
    }

    SpawnBGObject(index, BUFF_RESPAWN_TIME);
}

void Battleground::HandleKillPlayer(Player* player, Player* killer)
{
    // Keep in mind that for arena this will have to be changed a bit

    // Add +1 deaths
    UpdatePlayerScore(player, SCORE_DEATHS, 1);
    // Add +1 kills to group and +1 killing_blows to killer
    if (killer)
    {
        UpdatePlayerScore(killer, SCORE_HONORABLE_KILLS, 1);
        UpdatePlayerScore(killer, SCORE_KILLING_BLOWS, 1);

        for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
        {
            Player* creditedPlayer = ObjectAccessor::FindPlayer(itr->first);
            if (!creditedPlayer || creditedPlayer == killer)
                continue;

            if (creditedPlayer->GetTeam() == killer->GetTeam() && creditedPlayer->IsAtGroupRewardDistance(player))
                UpdatePlayerScore(creditedPlayer, SCORE_HONORABLE_KILLS, 1);
        }
    }

    if (!isArena())
    {
        // To be able to remove insignia -- ONLY IN Battlegrounds
        player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
        RewardXPAtKill(killer, player);
    }
}

// Return the player's team based on battlegroundplayer info
// Used in same faction arena matches mainly
uint32 Battleground::GetPlayerTeam(uint64 guid) const
{
    BattlegroundPlayerMap::const_iterator itr = _Players.find(guid);
    if (itr != _Players.end())
        return itr->second.Team;
    return 0;
}

uint32 Battleground::GetOtherTeam(uint32 teamId) const
{
    return teamId ? ((teamId == ALLIANCE) ? HORDE : ALLIANCE) : 0;
}

bool Battleground::IsPlayerInBattleground(uint64 guid) const
{
    BattlegroundPlayerMap::const_iterator itr = _Players.find(guid);
    if (itr != _Players.end())
        return true;
    return false;
}

void Battleground::PlayerAddedToBGCheckIfBGIsRunning(Player* player)
{
    if (GetStatus() != STATUS_WAIT_LEAVE)
        return;

    WorldPacket data;
    BattlegroundQueueTypeId bgQueueTypeId = BattlegroundMgr::BGQueueTypeId(GetTypeID(), GetArenaType());

    BlockMovement(player);

    sBattlegroundMgr->BuildPvpLogDataPacket(&data, this);
    player->GetSession()->SendPacket(&data);

    sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, this, player->GetBattlegroundQueueIndex(bgQueueTypeId), STATUS_IN_PROGRESS, GetEndTime(), GetStartTime(), GetArenaType());
    player->GetSession()->SendPacket(&data);
}

uint32 Battleground::GetAlivePlayersCountByTeam(uint32 Team) const
{
    int count = 0;
    for (BattlegroundPlayerMap::const_iterator itr = _Players.begin(); itr != _Players.end(); ++itr)
    {
        if (itr->second.Team == Team)
        {
            Player* player = ObjectAccessor::FindPlayer(itr->first);
            if (player && player->isAlive() && !player->HasByteFlag(UNIT_FIELD_BYTES_2, 3, FORM_SPIRITOFREDEMPTION))
                ++count;
        }
    }
    return count;
}

void Battleground::SetHoliday(bool is_holiday)
{
    _HonorMode = is_holiday ? BG_HOLIDAY : BG_NORMAL;
}

int32 Battleground::GetObjectType(uint64 guid)
{
    for (uint32 i = 0; i < BgObjects.size(); ++i)
        if (BgObjects[i] == guid)
            return i;
    sLog->outError("Battleground::GetObjectType: player used gameobject (GUID: %u) which is not in internal data for BG (map: %u, instance id: %u), cheating?",
        GUID_LOPART(guid), _MapId, _InstanceID);
    return -1;
}

void Battleground::HandleKillUnit(Creature* /*creature*/, Player* /*killer*/)
{
}

void Battleground::CheckArenaAfterTimerConditions()
{
    EndBattleground(WINNER_NONE);
}

void Battleground::CheckArenaWinConditions()
{
    if (!GetAlivePlayersCountByTeam(ALLIANCE) && GetPlayersCountByTeam(HORDE))
    {
        if (isArena())
            ScheduleArenaEnd(1500);
        else
            EndBattleground(HORDE);
    }
    else if (GetPlayersCountByTeam(ALLIANCE) && !GetAlivePlayersCountByTeam(HORDE))
    {
        if (isArena())
            ScheduleArenaEnd(1500);
        else
            EndBattleground(ALLIANCE);
    }
}

void Battleground::ScheduleArenaEnd(uint32 time)
{
    _arenaEndTimer = time;
}

void Battleground::UpdateArenaWorldState()
{
    UpdateWorldState(0xe10, GetAlivePlayersCountByTeam(HORDE));
    UpdateWorldState(0xe11, GetAlivePlayersCountByTeam(ALLIANCE));
}

void Battleground::SetBgRaid(uint32 TeamID, Group* bg_raid)
{
    Group*& old_raid = TeamID == ALLIANCE ? _BgRaids[BG_TEAM_ALLIANCE] : _BgRaids[BG_TEAM_HORDE];
    if (old_raid)
        old_raid->SetBattlegroundGroup(NULL);
    if (bg_raid)
        bg_raid->SetBattlegroundGroup(this);
    old_raid = bg_raid;
}

WorldSafeLocsEntry const* Battleground::GetClosestGraveYard(Player* player)
{
    return sObjectMgr->GetClosestGraveYard(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), player->GetTeam());
}

bool Battleground::IsTeamScoreInRange(uint32 team, uint32 minScore, uint32 maxScore) const
{
    BattlegroundTeamId teamIndex = GetTeamIndexByTeamId(team);
    uint32 score = std::max(_TeamScores[teamIndex], 0);
    return score >= minScore && score <= maxScore;
}

void Battleground::StartTimedAchievement(AchievementCriteriaTimedTypes type, uint32 entry)
{
    for (BattlegroundPlayerMap::const_iterator itr = GetPlayers().begin(); itr != GetPlayers().end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(itr->first))
            player->GetAchievementMgr().StartTimedAchievement(type, entry);
}

void Battleground::SetBracket(PvPDifficultyEntry const* bracketEntry)
{
    _BracketId = bracketEntry->GetBracketId();
    SetLevelRange(bracketEntry->minLevel, bracketEntry->maxLevel);
}

void Battleground::RewardXPAtKill(Player* killer, Player* victim)
{
    if (sWorld->getBoolConfig(CONFIG_BG_XP_FOR_KILL) && killer && victim)
        killer->RewardPlayerAndGroupAtKill(victim, true);
}
