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
#include "DatabaseEnv.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "ObjectMgr.h"
#include "ArenaTeamMgr.h"
#include "GuildMgr.h"
#include "AuctionHouseMgr.h"
#include "AccountMgr.h"
#include "PlayerDump.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Opcodes.h"
#include "GameObject.h"
#include "Chat.h"
#include "Log.h"
#include "Guild.h"
#include "ObjectAccessor.h"
#include "MapManager.h"
#include "Language.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "Weather.h"
#include "PointMovementGenerator.h"
#include "TargetedMovementGenerator.h"
#include "SkillDiscovery.h"
#include "SkillExtraItems.h"
#include "SystemConfig.h"
#include "Config.h"
#include "Util.h"
#include "ItemEnchantmentMgr.h"
#include "BattlegroundMgr.h"
#include "InstanceSaveMgr.h"
#include "InstanceScript.h"
#include "CreatureEventAIMgr.h"
#include "SpellAuraEffects.h"
#include "DBCEnums.h"
#include "ConditionMgr.h"
#include "DisableMgr.h"
#include "Transport.h"
#include "WeatherMgr.h"
#include "ScriptMgr.h"
#include "CreatureTextMgr.h"
#include "SmartAI.h"
#include "Group.h"
#include "ChannelMgr.h"

bool ChatHandler::HandleMapSetInfoCommand(const char* args)
{
   return true;
}
bool ChatHandler::HandleMapInfoCommand(const char* args)
{
return true;
}
bool ChatHandler::HandleMaxSkillCommand(const char* /*args*/)
{
    Player* SelectedPlayer = getSelectedPlayer();
    if (!SelectedPlayer)
    {
        SendSysMessage(LANGUAGE_NO_CHARACTER_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    // each skills that have max skill value dependent from level seted to current level max skill value
    SelectedPlayer->UpdateSkillsToMaxSkillsForLevel();
    return true;
}

bool ChatHandler::HandleSetSkillCommand(const char *args)
{
    // number or [name] Shift-click form |color|Hskill:skill_id|h[name]|h|r
    char* skill_p = extractKeyFromLink((char*)args, "Hskill");
    if (!skill_p)
        return false;

    char *level_p = strtok (NULL, " ");

    if (!level_p)
        return false;

    char *max_p   = strtok (NULL, " ");

    int32 skill = atoi(skill_p);
    if (skill <= 0)
    {
        PSendSysMessage(LANGUAGE_INVALID_SKILL_ID, skill);
        SetSentErrorMessage(true);
        return false;
    }

    int32 level = atol (level_p);

    Player* target = getSelectedPlayer();
    if (!target)
    {
        SendSysMessage(LANGUAGE_NO_CHARACTER_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    SkillLineEntry const* sl = sSkillLineStore.LookupEntry(skill);
    if (!sl)
    {
        PSendSysMessage(LANGUAGE_INVALID_SKILL_ID, skill);
        SetSentErrorMessage(true);
        return false;
    }

    std::string tNameLink = GetNameLink(target);

    if (!target->GetSkillValue(skill))
    {
        PSendSysMessage(LANGUAGE_SET_SKILL_ERROR, tNameLink.c_str(), skill, sl->name);
        SetSentErrorMessage(true);
        return false;
    }

    int32 max   = max_p ? atol (max_p) : target->GetPureMaxSkillValue(skill);

    if (level <= 0 || level > max || max <= 0)
        return false;

    target->SetSkill(skill, target->GetSkillStep(skill), level, max);
    PSendSysMessage(LANGUAGE_SET_SKILL, skill, sl->name, tNameLink.c_str(), level, max);

    return true;
}

bool ChatHandler::HandleUnLearnCommand(const char *args)
{
    if (!*args)
        return false;

    // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r
    uint32 spell_id = extractSpellIdFromLink((char*)args);
    if (!spell_id)
        return false;

    char const* allStr = strtok(NULL, " ");
    bool allRanks = allStr ? (strncmp(allStr, "all", strlen(allStr)) == 0) : false;

    Player* target = getSelectedPlayer();
    if (!target)
    {
        SendSysMessage(LANGUAGE_NO_CHARACTER_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (allRanks)
        spell_id = sSpellMgr->GetFirstSpellInChain (spell_id);

    if (target->HasSpell(spell_id))
        target->removeSpell(spell_id, false, !allRanks);
    else
        SendSysMessage(LANGUAGE_FORGET_SPELL);

    if (GetTalentSpellCost(spell_id))
        target->SendTalentsInfoData(false);

    return true;
}

bool ChatHandler::HandleCooldownCommand(const char *args)
{
    Player* target = getSelectedPlayer();
    if (!target)
    {
        SendSysMessage(LANGUAGE_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }

    std::string tNameLink = GetNameLink(target);

    if (!*args)
    {
        target->RemoveAllSpellCooldown();
        PSendSysMessage(LANGUAGE_REMOVEALL_COOLDOWN, tNameLink.c_str());
    }
    else
    {
        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spell_id = extractSpellIdFromLink((char*)args);
        if (!spell_id)
            return false;

        if (!sSpellMgr->GetSpellInfo(spell_id))
        {
            PSendSysMessage(LANGUAGE_UNKNOWN_SPELL, target == m_session->GetPlayer() ? GetSkyFireString(LANGUAGE_YOU) : tNameLink.c_str());
            SetSentErrorMessage(true);
            return false;
        }

        target->RemoveSpellCooldown(spell_id, true);
        PSendSysMessage(LANGUAGE_REMOVE_COOLDOWN, spell_id, target == m_session->GetPlayer() ? GetSkyFireString(LANGUAGE_YOU) : tNameLink.c_str());
   }
    return true;
}

bool ChatHandler::HandleAddItemCommand(const char *args)
{
    if (!*args)
        return false;

    uint32 itemId = 0;

    if (args[0] == '[')                                        // [name] manual form
    {
        char* citemName = strtok((char*)args, "]");

        if (citemName && citemName[0])
        {
            std::string itemName = citemName+1;
            WorldDatabase.EscapeString(itemName);

            PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_ITEM_TEMPLATE_BY_NAME);
            stmt->setString(0, itemName);
            PreparedQueryResult result = WorldDatabase.Query(stmt);

            if (!result)
            {
                PSendSysMessage(LANGUAGE_COMMAND_COULDNOTFIND, citemName+1);
                SetSentErrorMessage(true);
                return false;
            }
            itemId = result->Fetch()->GetUInt16();
        }
        else
            return false;
    }
    else                                                    // item_id or [name] Shift-click form |color|Hitem:item_id:0:0:0|h[name]|h|r
    {
        char* cId = extractKeyFromLink((char*)args, "Hitem");
        if (!cId)
            return false;
        itemId = atol(cId);
    }

    char* ccount = strtok(NULL, " ");

    int32 count = 1;

    if (ccount)
        count = strtol(ccount, NULL, 10);

    if (count == 0)
        count = 1;

    Player* player = m_session->GetPlayer();
    Player* plTarget = getSelectedPlayer();
    if (!plTarget)
        plTarget = player;

    sLog->outDetail(GetSkyFireString(LANGUAGE_ADDITEM), itemId, count);

    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
    if (!proto)
    {
        PSendSysMessage(LANGUAGE_COMMAND_ITEMIDINVALID, itemId);
        SetSentErrorMessage(true);
        return false;
    }

    //Subtract
    if (count < 0)
    {
        plTarget->DestroyItemCount(itemId, -count, true, false);
        PSendSysMessage(LANGUAGE_REMOVEITEM, itemId, -count, GetNameLink(plTarget).c_str());
        return true;
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
        PSendSysMessage(LANGUAGE_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
        SetSentErrorMessage(true);
        return false;
    }

    Item* item = plTarget->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

    // remove binding (let GM give it to another player later)
    if (player == plTarget)
        for (ItemPosCountVec::const_iterator itr = dest.begin(); itr != dest.end(); ++itr)
            if (Item* item1 = player->GetItemByPos(itr->pos))
                item1->SetBinding(false);

    if (count > 0 && item)
    {
        player->SendNewItem(item, count, false, true);
        if (player != plTarget)
            plTarget->SendNewItem(item, count, true, false);
    }

    if (noSpaceForCount > 0)
        PSendSysMessage(LANGUAGE_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

    return true;
}

bool ChatHandler::HandleAddItemSetCommand(const char *args)
{
    if (!*args)
        return false;

    char* cId = extractKeyFromLink((char*)args, "Hitemset"); // number or [name] Shift-click form |color|Hitemset:itemset_id|h[name]|h|r
    if (!cId)
        return false;

    uint32 itemsetId = atol(cId);

    // prevent generation all items with itemset field value '0'
    if (itemsetId == 0)
    {
        PSendSysMessage(LANGUAGE_NO_ITEMS_FROM_ITEMSET_FOUND, itemsetId);
        SetSentErrorMessage(true);
        return false;
    }

    Player* player = m_session->GetPlayer();
    Player* playerTarget = getSelectedPlayer();
    if (!playerTarget)
        playerTarget = player;

    sLog->outDetail(GetSkyFireString(LANGUAGE_ADDITEMSET), itemsetId);

    bool found = false;
    ItemTemplateContainer const* its = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator itr = its->begin(); itr != its->end(); ++itr)
    {
        if (itr->second.ItemSet == itemsetId)
        {
            found = true;
            ItemPosCountVec dest;
            InventoryResult msg = playerTarget->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itr->second.ItemId, 1);
            if (msg == EQUIP_ERR_OK)
            {
                Item* item = playerTarget->StoreNewItem(dest, itr->second.ItemId, true);

                // remove binding (let GM give it to another player later)
                if (player == playerTarget)
                    item->SetBinding(false);

                player->SendNewItem(item, 1, false, true);
                if (player != playerTarget)
                    playerTarget->SendNewItem(item, 1, true, false);
            }
            else
            {
                player->SendEquipError(msg, NULL, NULL, itr->second.ItemId);
                PSendSysMessage(LANGUAGE_ITEM_CANNOT_CREATE, itr->second.ItemId, 1);
            }
        }
    }

    if (!found)
    {
        PSendSysMessage(LANGUAGE_NO_ITEMS_FROM_ITEMSET_FOUND, itemsetId);

        SetSentErrorMessage(true);
        return false;
    }

    return true;
}

/** \brief GM command level 3 - Create a guild.
 *
 * This command allows a GM (level 3) to create a guild.
 *
 * The "args" parameter contains the name of the guild leader
 * and then the name of the guild.
 *
 */
bool ChatHandler::HandleGuildCreateCommand(const char *args)
{
    if (!*args)
        return false;

    // if not guild name only (in "") then player name
    Player* target;
    if (!extractPlayerTarget(*args != '"' ? (char*)args : NULL, &target))
        return false;

    char* tailStr = *args != '"' ? strtok(NULL, "") : (char*)args;
    if (!tailStr)
        return false;

    char* guildStr = extractQuotedArg(tailStr);
    if (!guildStr)
        return false;

    std::string guildname = guildStr;

    if (target->GetGuildId())
    {
        SendSysMessage (LANGUAGE_PLAYER_IN_GUILD);
        return true;
    }

    Guild* guild = new Guild;
    if (!guild->Create (target, guildname))
    {
        delete guild;
        SendSysMessage (LANGUAGE_GUILD_NOT_CREATED);
        SetSentErrorMessage (true);
        return false;
    }

    sGuildMgr->AddGuild(guild);
    return true;
}

bool ChatHandler::HandleGuildInviteCommand(const char *args)
{
    if (!*args)
        return false;

    // if not guild name only (in "") then player name
    uint64 target_guid;
    if (!extractPlayerTarget(*args != '"' ? (char*)args : NULL, NULL, &target_guid))
        return false;

    char* tailStr = *args != '"' ? strtok(NULL, "") : (char*)args;
    if (!tailStr)
        return false;

    char* guildStr = extractQuotedArg(tailStr);
    if (!guildStr)
        return false;

    std::string glName = guildStr;
    Guild* targetGuild = sGuildMgr->GetGuildByName (glName);
    if (!targetGuild)
        return false;

    // player's guild membership checked in AddMember before add
    return targetGuild->AddMember(target_guid);
}

bool ChatHandler::HandleGuildUninviteCommand(const char *args)
{
    Player* target;
    uint64 target_guid;
    if (!extractPlayerTarget((char*)args, &target, &target_guid))
        return false;

    uint32 glId   = target ? target->GetGuildId () : Player::GetGuildIdFromGUID (target_guid);

    if (!glId)
        return false;

    Guild* targetGuild = sGuildMgr->GetGuildById (glId);
    if (!targetGuild)
        return false;

    targetGuild->DeleteMember(target_guid, false, true);
    return true;
}

bool ChatHandler::HandleGuildRankCommand(const char *args)
{
    char* nameStr;
    char* rankStr;
    extractOptFirstArg((char*)args, &nameStr, &rankStr);
    if (!rankStr)
        return false;

    Player* target;
    uint64 target_guid;
    std::string target_name;
    if (!extractPlayerTarget(nameStr, &target, &target_guid, &target_name))
        return false;

    uint32 glId   = target ? target->GetGuildId () : Player::GetGuildIdFromGUID (target_guid);
    if (!glId)
        return false;

    Guild* targetGuild = sGuildMgr->GetGuildById (glId);
    if (!targetGuild)
        return false;

    uint32 newrank = uint32 (atoi (rankStr));
    return targetGuild->ChangeMemberRank(target_guid, newrank);
}

bool ChatHandler::HandleGuildDeleteCommand(const char *args)
{
    if (!*args)
        return false;

    char* guildStr = extractQuotedArg((char*)args);
    if (!guildStr)
        return false;

    std::string gld = guildStr;

    Guild* targetGuild = sGuildMgr->GetGuildByName (gld);
    if (!targetGuild)
        return false;

    targetGuild->Disband ();

    return true;
}

bool ChatHandler::HandleGetDistanceCommand(const char *args)
{
    WorldObject* obj = NULL;

    if (*args)
    {
        uint64 guid = extractGuidFromLink((char*)args);
        if (guid)
            obj = (WorldObject*)ObjectAccessor::GetObjectByTypeMask(*m_session->GetPlayer(), guid, TYPEMASK_UNIT|TYPEMASK_GAMEOBJECT);

        if (!obj)
        {
            SendSysMessage(LANGUAGE_PLAYER_NOT_FOUND);
            SetSentErrorMessage(true);
            return false;
        }
    }
    else
    {
        obj = getSelectedUnit();

        if (!obj)
        {
            SendSysMessage(LANGUAGE_SELECT_CHARACTER_OR_CREATURE);
            SetSentErrorMessage(true);
            return false;
        }
    }

    PSendSysMessage(LANGUAGE_DISTANCE, m_session->GetPlayer()->GetDistance(obj), m_session->GetPlayer()->GetDistance2d(obj), m_session->GetPlayer()->GetExactDist(obj), m_session->GetPlayer()->GetExactDist2d(obj));
    return true;
}

bool ChatHandler::HandleDieCommand(const char* /*args*/)
{
    Unit* target = getSelectedUnit();

    if (!target || !m_session->GetPlayer()->GetSelection())
    {
        SendSysMessage(LANGUAGE_SELECT_CHARACTER_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    if (target->GetTypeId() == TYPEID_PLAYER)
    {
        if (HasLowerSecurity((Player*)target, 0, false))
            return false;
    }

    if (target->isAlive())
    {
        if (sWorld->getBoolConfig(CONFIG_DIE_COMMAND_MODE))
            m_session->GetPlayer()->Kill(target);
        else
            m_session->GetPlayer()->DealDamage(target, target->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
    }

    return true;
}

bool ChatHandler::HandleDamageCommand(const char * args)
{
    if (!*args)
        return false;

    Unit* target = getSelectedUnit();

    if (!target || !m_session->GetPlayer()->GetSelection())
    {
        SendSysMessage(LANGUAGE_SELECT_CHARACTER_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    if (target->GetTypeId() == TYPEID_PLAYER)
    {
        if (HasLowerSecurity((Player*)target, 0, false))
            return false;
    }

    if (!target->isAlive())
        return true;

    char* damageStr = strtok((char*)args, " ");
    if (!damageStr)
        return false;

    int32 damage_int = atoi((char*)damageStr);
    if (damage_int <= 0)
        return true;

    uint32 damage = damage_int;

    char* schoolStr = strtok((char*)NULL, " ");

    // flat melee damage without resistence/etc reduction
    if (!schoolStr)
    {
        m_session->GetPlayer()->DealDamage(target, damage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        if (target != m_session->GetPlayer())
            m_session->GetPlayer()->SendAttackStateUpdate (HITINFO_NORMALSWING2, target, 1, SPELL_SCHOOL_MASK_NORMAL, damage, 0, 0, VICTIMSTATE_HIT, 0);
        return true;
    }

    uint32 school = schoolStr ? atoi((char*)schoolStr) : SPELL_SCHOOL_NORMAL;
    if (school >= MAX_SPELL_SCHOOL)
        return false;

    SpellSchoolMask schoolmask = SpellSchoolMask(1 << school);

    if (Unit::IsDamageReducedByArmor(schoolmask))
        damage = m_session->GetPlayer()->CalcArmorReducedDamage(target, damage, NULL, BASE_ATTACK);

    char* spellStr = strtok((char*)NULL, " ");

    // melee damage by specific school
    if (!spellStr)
    {
        uint32 absorb = 0;
        uint32 resist = 0;

        m_session->GetPlayer()->CalcAbsorbResist(target, schoolmask, SPELL_DIRECT_DAMAGE, damage, &absorb, &resist);

        if (damage <= absorb + resist)
            return true;

        damage -= absorb + resist;

        m_session->GetPlayer()->DealDamageMods(target, damage, &absorb);
        m_session->GetPlayer()->DealDamage(target, damage, NULL, DIRECT_DAMAGE, schoolmask, NULL, false);
        m_session->GetPlayer()->SendAttackStateUpdate (HITINFO_NORMALSWING2, target, 1, schoolmask, damage, absorb, resist, VICTIMSTATE_HIT, 0);
        return true;
    }

    // non-melee damage

    // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
    uint32 spellid = extractSpellIdFromLink((char*)args);
    if (!spellid || !sSpellMgr->GetSpellInfo(spellid))
        return false;

    m_session->GetPlayer()->SpellNonMeleeDamageLog(target, spellid, damage);
    return true;
}

bool ChatHandler::HandleReviveCommand(const char *args)
{
    Player* target;
    uint64 target_guid;
    if (!extractPlayerTarget((char*)args, &target, &target_guid))
        return false;

    if (target)
    {
        target->ResurrectPlayer(!AccountMgr::IsPlayerAccount(target->GetSession()->GetSecurity()) ? 1.0f : 0.5f);
        target->SpawnCorpseBones();
        target->SaveToDB();
    }
    else
        // will resurrected at login without corpse
        sObjectAccessor->ConvertCorpseForPlayer(target_guid);

    return true;
}

bool ChatHandler::HandleAuraCommand(const char *args)
{
    Unit* target = getSelectedUnit();
    if (!target)
    {
        SendSysMessage(LANGUAGE_SELECT_CHARACTER_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
    uint32 spellID = extractSpellIdFromLink((char*)args);

    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellID))
        Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, target, target);

    return true;
}

bool ChatHandler::HandleUnAuraCommand(const char *args)
{
    Unit* target = getSelectedUnit();
    if (!target)
    {
        SendSysMessage(LANGUAGE_SELECT_CHARACTER_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    std::string argstr = args;
    if (argstr == "all")
    {
        target->RemoveAllAuras();
        return true;
    }

    // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
    uint32 spellID = extractSpellIdFromLink((char*)args);
    if (!spellID)
        return false;

    target->RemoveAurasDueToSpell(spellID);

    return true;
}

bool ChatHandler::HandleLinkGraveCommand(const char *args)
{
    if (!*args)
        return false;

    char* px = strtok((char*)args, " ");
    if (!px)
        return false;

    uint32 g_id = (uint32)atoi(px);

    uint32 g_team;

    char* px2 = strtok(NULL, " ");

    if (!px2)
        g_team = 0;
    else if (strncmp(px2, "horde", 6) == 0)
        g_team = HORDE;
    else if (strncmp(px2, "alliance", 9) == 0)
        g_team = ALLIANCE;
    else
        return false;

    WorldSafeLocsEntry const* graveyard =  sWorldSafeLocsStore.LookupEntry(g_id);

    if (!graveyard)
    {
        PSendSysMessage(LANGUAGE_COMMAND_GRAVEYARDNOEXIST, g_id);
        SetSentErrorMessage(true);
        return false;
    }

    Player* player = m_session->GetPlayer();

    uint32 zoneId = player->GetZoneId();

    AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(zoneId);
    if (!areaEntry || areaEntry->zone !=0)
    {
        PSendSysMessage(LANGUAGE_COMMAND_GRAVEYARDWRONGZONE, g_id, zoneId);
        SetSentErrorMessage(true);
        return false;
    }

    if (sObjectMgr->AddGraveYardLink(g_id, zoneId, g_team))
        PSendSysMessage(LANGUAGE_COMMAND_GRAVEYARDLINKED, g_id, zoneId);
    else
        PSendSysMessage(LANGUAGE_COMMAND_GRAVEYARDALRLINKED, g_id, zoneId);

    return true;
}

bool ChatHandler::HandleNearGraveCommand(const char *args)
{
    uint32 g_team;

    size_t argslen = strlen(args);

    if (!*args)
        g_team = 0;
    else if (strncmp((char*)args, "horde", argslen) == 0)
        g_team = HORDE;
    else if (strncmp((char*)args, "alliance", argslen) == 0)
        g_team = ALLIANCE;
    else
        return false;

    Player* player = m_session->GetPlayer();
    uint32 zone_id = player->GetZoneId();

    WorldSafeLocsEntry const* graveyard = sObjectMgr->GetClosestGraveYard(
        player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), g_team);

    if (graveyard)
    {
        uint32 g_id = graveyard->ID;

        GraveYardData const* data = sObjectMgr->FindGraveYardData(g_id, zone_id);
        if (!data)
        {
            PSendSysMessage(LANGUAGE_COMMAND_GRAVEYARDERROR, g_id);
            SetSentErrorMessage(true);
            return false;
        }

        g_team = data->team;

        std::string team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_NOTEAM);

        if (g_team == 0)
            team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_ANY);
        else if (g_team == HORDE)
            team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_HORDE);
        else if (g_team == ALLIANCE)
            team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_ALLIANCE);

        PSendSysMessage(LANGUAGE_COMMAND_GRAVEYARDNEAREST, g_id, team_name.c_str(), zone_id);
    }
    else
    {
        std::string team_name;

        if (g_team == 0)
            team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_ANY);
        else if (g_team == HORDE)
            team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_HORDE);
        else if (g_team == ALLIANCE)
            team_name = GetSkyFireString(LANGUAGE_COMMAND_GRAVEYARD_ALLIANCE);

        if (g_team == ~uint32(0))
            PSendSysMessage(LANGUAGE_COMMAND_ZONENOGRAVEYARDS, zone_id);
        else
            PSendSysMessage(LANGUAGE_COMMAND_ZONENOGRAFACTION, zone_id, team_name.c_str());
    }

    return true;
}

bool ChatHandler::HandleExploreCheatCommand(const char *args)
{
    if (!*args)
        return false;

    int flag = atoi((char*)args);

    Player* chr = getSelectedPlayer();
    if (chr == NULL)
    {
        SendSysMessage(LANGUAGE_NO_CHARACTER_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (flag != 0)
    {
        PSendSysMessage(LANGUAGE_YOU_SET_EXPLORE_ALL, GetNameLink(chr).c_str());
        if (needReportToTarget(chr))
            ChatHandler(chr).PSendSysMessage(LANGUAGE_YOURS_EXPLORE_SET_ALL, GetNameLink().c_str());
    }
    else
    {
        PSendSysMessage(LANGUAGE_YOU_SET_EXPLORE_NOTHING, GetNameLink(chr).c_str());
        if (needReportToTarget(chr))
            ChatHandler(chr).PSendSysMessage(LANGUAGE_YOURS_EXPLORE_SET_NOTHING, GetNameLink().c_str());
    }

    for (uint8 i = 0; i < PLAYER_EXPLORED_ZONES_SIZE; ++i)
    {
        if (flag != 0)
            m_session->GetPlayer()->SetFlag(PLAYER_EXPLORED_ZONES_1+i, 0xFFFFFFFF);
        else
            m_session->GetPlayer()->SetFlag(PLAYER_EXPLORED_ZONES_1+i, 0);
    }

    return true;
}

bool ChatHandler::HandleHoverCommand(const char *args)
{
    char* px = strtok((char*)args, " ");
    uint32 flag;
    if (!px)
        flag = 1;
    else
        flag = atoi(px);

    m_session->GetPlayer()->SetHover(flag);

    if (flag)
        SendSysMessage(LANGUAGE_HOVER_ENABLED);
    else
        SendSysMessage(LANGUAGE_HOVER_DISABLED);

    return true;
}

void ChatHandler::HandleCharacterLevel(Player* player, uint64 playerGuid, uint32 oldLevel, uint32 newLevel)
{
    if (player)
    {
        player->GiveLevel(newLevel);
        player->InitTalentForLevel();
        player->SetUInt32Value(PLAYER_XP, 0);

        if (needReportToTarget(player))
        {
            if (oldLevel == newLevel)
                ChatHandler(player).PSendSysMessage(LANGUAGE_YOURS_LEVEL_PROGRESS_RESET, GetNameLink().c_str());
            else if (oldLevel < newLevel)
                ChatHandler(player).PSendSysMessage(LANGUAGE_YOURS_LEVEL_UP, GetNameLink().c_str(), newLevel);
            else                                                // if (oldlevel > newlevel)
                ChatHandler(player).PSendSysMessage(LANGUAGE_YOURS_LEVEL_DOWN, GetNameLink().c_str(), newLevel);
        }
    }
    else
    {
        // Update level and reset XP, everything else will be updated at login
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHARACTER_UPDATE_LEVEL);

        stmt->setUInt8(0, uint8(newLevel));
        stmt->setUInt32(1, GUID_LOPART(playerGuid));

        CharacterDatabase.Execute(stmt);
    }
}

bool ChatHandler::HandleShowAreaCommand(const char *args)
{
    if (!*args)
        return false;

    Player* chr = getSelectedPlayer();
    if (chr == NULL)
    {
        SendSysMessage(LANGUAGE_NO_CHARACTER_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    int area = GetAreaFlagByAreaID(atoi((char*)args));
    int offset = area / 32;
    uint32 val = (uint32)(1 << (area % 32));

    if (area<0 || offset >= PLAYER_EXPLORED_ZONES_SIZE)
    {
        SendSysMessage(LANGUAGE_BAD_VALUE);
        SetSentErrorMessage(true);
        return false;
    }

    uint32 currFields = chr->GetUInt32Value(PLAYER_EXPLORED_ZONES_1 + offset);
    chr->SetUInt32Value(PLAYER_EXPLORED_ZONES_1 + offset, (uint32)(currFields | val));

    SendSysMessage(LANGUAGE_EXPLORE_AREA);
    return true;
}

bool ChatHandler::HandleHideAreaCommand(const char *args)
{
    if (!*args)
        return false;

    Player* chr = getSelectedPlayer();
    if (chr == NULL)
    {
        SendSysMessage(LANGUAGE_NO_CHARACTER_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    int area = GetAreaFlagByAreaID(atoi((char*)args));
    int offset = area / 32;
    uint32 val = (uint32)(1 << (area % 32));

    if (area<0 || offset >= PLAYER_EXPLORED_ZONES_SIZE)
    {
        SendSysMessage(LANGUAGE_BAD_VALUE);
        SetSentErrorMessage(true);
        return false;
    }

    uint32 currFields = chr->GetUInt32Value(PLAYER_EXPLORED_ZONES_1 + offset);
    chr->SetUInt32Value(PLAYER_EXPLORED_ZONES_1 + offset, (uint32)(currFields ^ val));

    SendSysMessage(LANGUAGE_UNEXPLORE_AREA);
    return true;
}

bool ChatHandler::HandleBankCommand(const char* /*args*/)
{
    m_session->SendShowBank(m_session->GetPlayer()->GetGUID());

    return true;
}

bool ChatHandler::HandleChangeWeather(const char *args)
{
    if (!*args)
        return false;

    //Weather is OFF
    if (!sWorld->getBoolConfig(CONFIG_WEATHER))
    {
        SendSysMessage(LANGUAGE_WEATHER_DISABLED);
        SetSentErrorMessage(true);
        return false;
    }

    // *Change the weather of a cell
    char* px = strtok((char*)args, " ");
    char* py = strtok(NULL, " ");

    if (!px || !py)
        return false;

    uint32 type = (uint32)atoi(px);                         //0 to 3, 0: fine, 1: rain, 2: snow, 3: sand
    float grade = (float)atof(py);                          //0 to 1, sending -1 is instand good weather

    Player* player = m_session->GetPlayer();
    uint32 zoneid = player->GetZoneId();

    Weather* wth = WeatherMgr::FindWeather(zoneid);

    if (!wth)
        wth = WeatherMgr::AddWeather(zoneid);
    if (!wth)
    {
        SendSysMessage(LANGUAGE_NO_WEATHER);
        SetSentErrorMessage(true);
        return false;
    }

    wth->SetWeather(WeatherType(type), grade);

    return true;
}

bool ChatHandler::HandleRespawnCommand(const char* /*args*/)
{
    Player* player = m_session->GetPlayer();

    // accept only explicitly selected target (not implicitly self targeting case)
    Unit* target = getSelectedUnit();
    if (player->GetSelection() && target)
    {
        if (target->GetTypeId() != TYPEID_UNIT || target->isPet())
        {
            SendSysMessage(LANGUAGE_SELECT_CREATURE);
            SetSentErrorMessage(true);
            return false;
        }

        if (target->isDead())
            target->ToCreature()->Respawn();
        return true;
    }

    CellCoord p(SkyFire::ComputeCellCoord(player->GetPositionX(), player->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    SkyFire::RespawnDo u_do;
    SkyFire::WorldObjectWorker<SkyFire::RespawnDo> worker(player, u_do);

    TypeContainerVisitor<SkyFire::WorldObjectWorker<SkyFire::RespawnDo>, GridTypeMapContainer > obj_worker(worker);
    cell.Visit(p, obj_worker, *player->GetMap(), *player, player->GetGridActivationRange());

    return true;
}

bool ChatHandler::HandleMovegensCommand(const char* /*args*/)
{
    Unit* unit = getSelectedUnit();
    if (!unit)
    {
        SendSysMessage(LANGUAGE_SELECT_CHARACTER_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    PSendSysMessage(LANGUAGE_MOVEGENS_LIST, (unit->GetTypeId() == TYPEID_PLAYER ? "Player" : "Creature"), unit->GetGUIDLow());

    MotionMaster* mm = unit->GetMotionMaster();
    float x, y, z;
    mm->GetDestination(x, y, z);

    for (uint8 i = 0; i < MAX_MOTION_SLOT; ++i)
    {
        MovementGenerator* mg = mm->GetMotionSlot(i);
        if (!mg)
        {
            SendSysMessage("Empty");
            continue;
        }
        switch (mg->GetMovementGeneratorType())
        {
            case IDLE_MOTION_TYPE:          SendSysMessage(LANGUAGE_MOVEGENS_IDLE);          break;
            case RANDOM_MOTION_TYPE:        SendSysMessage(LANGUAGE_MOVEGENS_RANDOM);        break;
            case WAYPOINT_MOTION_TYPE:      SendSysMessage(LANGUAGE_MOVEGENS_WAYPOINT);      break;
            case ANIMAL_RANDOM_MOTION_TYPE: SendSysMessage(LANGUAGE_MOVEGENS_ANIMAL_RANDOM); break;
            case CONFUSED_MOTION_TYPE:      SendSysMessage(LANGUAGE_MOVEGENS_CONFUSED);      break;
            case CHASE_MOTION_TYPE:
            {
                Unit* target = NULL;
                if (unit->GetTypeId() == TYPEID_PLAYER)
                    target = static_cast<ChaseMovementGenerator<Player> const*>(mg)->GetTarget();
                else
                    target = static_cast<ChaseMovementGenerator<Creature> const*>(mg)->GetTarget();

                if (!target)
                    SendSysMessage(LANGUAGE_MOVEGENS_CHASE_NULL);
                else if (target->GetTypeId() == TYPEID_PLAYER)
                    PSendSysMessage(LANGUAGE_MOVEGENS_CHASE_PLAYER, target->GetName(), target->GetGUIDLow());
                else
                    PSendSysMessage(LANGUAGE_MOVEGENS_CHASE_CREATURE, target->GetName(), target->GetGUIDLow());
                break;
            }
            case FOLLOW_MOTION_TYPE:
            {
                Unit* target = NULL;
                if (unit->GetTypeId() == TYPEID_PLAYER)
                    target = static_cast<FollowMovementGenerator<Player> const*>(mg)->GetTarget();
                else
                    target = static_cast<FollowMovementGenerator<Creature> const*>(mg)->GetTarget();

                if (!target)
                    SendSysMessage(LANGUAGE_MOVEGENS_FOLLOW_NULL);
                else if (target->GetTypeId() == TYPEID_PLAYER)
                    PSendSysMessage(LANGUAGE_MOVEGENS_FOLLOW_PLAYER, target->GetName(), target->GetGUIDLow());
                else
                    PSendSysMessage(LANGUAGE_MOVEGENS_FOLLOW_CREATURE, target->GetName(), target->GetGUIDLow());
                 break;
             }
            case HOME_MOTION_TYPE:
            {
                if (unit->GetTypeId() == TYPEID_UNIT)
                    PSendSysMessage(LANGUAGE_MOVEGENS_HOME_CREATURE, x, y, z);
                else
                    SendSysMessage(LANGUAGE_MOVEGENS_HOME_PLAYER);
                break;
            }
            case FLIGHT_MOTION_TYPE:   SendSysMessage(LANGUAGE_MOVEGENS_FLIGHT);  break;
            case POINT_MOTION_TYPE:
            {
                PSendSysMessage(LANGUAGE_MOVEGENS_POINT, x, y, z);
                break;
            }
            case FLEEING_MOTION_TYPE:  SendSysMessage(LANGUAGE_MOVEGENS_FEAR);    break;
            case DISTRACT_MOTION_TYPE: SendSysMessage(LANGUAGE_MOVEGENS_DISTRACT);  break;
            case EFFECT_MOTION_TYPE: SendSysMessage(LANGUAGE_MOVEGENS_EFFECT);  break;
            default:
                PSendSysMessage(LANGUAGE_MOVEGENS_UNKNOWN, mg->GetMovementGeneratorType());
                break;
        }
    }
    return true;
}

/*
ComeToMe command REQUIRED for 3rd party scripting library to have access to PointMovementGenerator
Without this function 3rd party scripting library will get linking errors (unresolved external)
when attempting to use the PointMovementGenerator
*/
bool ChatHandler::HandleComeToMeCommand(const char *args)
{
    char* newFlagStr = strtok((char*)args, " ");

    if (!newFlagStr)
        return false;

    Creature* caster = getSelectedCreature();
    if (!caster)
    {
        SendSysMessage(LANGUAGE_SELECT_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    Player* player = m_session->GetPlayer();

    caster->GetMotionMaster()->MovePoint(0, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ());
    return true;
}

std::string GetTimeString(uint64 time)
{
    uint64 days = time / DAY, hours = (time % DAY) / HOUR, minute = (time % HOUR) / MINUTE;
    std::ostringstream ss;
    if (days) ss << days << "d ";
    if (hours) ss << hours << "h ";
    ss << minute << 'm';
    return ss.str();
}

//Send items by mail
bool ChatHandler::HandleSendItemsCommand(const char *args)
{
    // format: name "subject text" "mail text" item1[:count1] item2[:count2] ... item12[:count12]
    Player* receiver;
    uint64 receiver_guid;
    std::string receiver_name;
    if (!extractPlayerTarget((char*)args, &receiver, &receiver_guid, &receiver_name))
        return false;

    char* tail1 = strtok(NULL, "");
    if (!tail1)
        return false;

    char* msgSubject = extractQuotedArg(tail1);
    if (!msgSubject)
        return false;

    char* tail2 = strtok(NULL, "");
    if (!tail2)
        return false;

    char* msgText = extractQuotedArg(tail2);
    if (!msgText)
        return false;

    // msgSubject, msgText isn't NUL after prev. check
    std::string subject = msgSubject;
    std::string text    = msgText;

    // extract items
    typedef std::pair<uint32, uint32> ItemPair;
    typedef std::list< ItemPair > ItemPairs;
    ItemPairs items;

    // get all tail string
    char* tail = strtok(NULL, "");

    // get from tail next item str
    while (char* itemStr = strtok(tail, " "))
    {
        // and get new tail
        tail = strtok(NULL, "");

        // parse item str
        char* itemIdStr = strtok(itemStr, ":");
        char* itemCountStr = strtok(NULL, " ");

        uint32 item_id = atoi(itemIdStr);
        if (!item_id)
            return false;

        ItemTemplate const* item_proto = sObjectMgr->GetItemTemplate(item_id);
        if (!item_proto)
        {
            PSendSysMessage(LANGUAGE_COMMAND_ITEMIDINVALID, item_id);
            SetSentErrorMessage(true);
            return false;
        }

        uint32 item_count = itemCountStr ? atoi(itemCountStr) : 1;
        if (item_count < 1 || (item_proto->MaxCount > 0 && item_count > uint32(item_proto->MaxCount)))
        {
            PSendSysMessage(LANGUAGE_COMMAND_INVALID_ITEM_COUNT, item_count, item_id);
            SetSentErrorMessage(true);
            return false;
        }

        while (item_count > item_proto->GetMaxStackSize())
        {
            items.push_back(ItemPair(item_id, item_proto->GetMaxStackSize()));
            item_count -= item_proto->GetMaxStackSize();
        }

        items.push_back(ItemPair(item_id, item_count));

        if (items.size() > MAX_MAIL_ITEMS)
        {
            PSendSysMessage(LANGUAGE_COMMAND_MAIL_ITEMS_LIMIT, MAX_MAIL_ITEMS);
            SetSentErrorMessage(true);
            return false;
        }
    }

    // from console show not existed sender
    MailSender sender(MAIL_NORMAL, m_session ? m_session->GetPlayer()->GetGUIDLow() : 0, MAIL_STATIONERY_GM);

    // fill mail
    MailDraft draft(subject, text);

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    for (ItemPairs::const_iterator itr = items.begin(); itr != items.end(); ++itr)
    {
        if (Item* item = Item::CreateItem(itr->first, itr->second, m_session ? m_session->GetPlayer() : 0))
        {
            item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
            draft.AddItem(item);
        }
    }

    draft.SendMailTo(trans, MailReceiver(receiver, GUID_LOPART(receiver_guid)), sender);
    CharacterDatabase.CommitTransaction(trans);

    std::string nameLink = playerLink(receiver_name);
    PSendSysMessage(LANGUAGE_MAIL_SENT, nameLink.c_str());
    return true;
}

///Send money by mail
bool ChatHandler::HandleSendMoneyCommand(const char *args)
{
    /// format: name "subject text" "mail text" money

    Player* receiver;
    uint64 receiver_guid;
    std::string receiver_name;
    if (!extractPlayerTarget((char*)args, &receiver, &receiver_guid, &receiver_name))
        return false;

    char* tail1 = strtok(NULL, "");
    if (!tail1)
        return false;

    char* msgSubject = extractQuotedArg(tail1);
    if (!msgSubject)
        return false;

    char* tail2 = strtok(NULL, "");
    if (!tail2)
        return false;

    char* msgText = extractQuotedArg(tail2);
    if (!msgText)
        return false;

    char* money_str = strtok(NULL, "");
    int32 money = money_str ? atoi(money_str) : 0;
    if (money <= 0)
        return false;

    // msgSubject, msgText isn't NUL after prev. check
    std::string subject = msgSubject;
    std::string text    = msgText;

    // from console show not existed sender
    MailSender sender(MAIL_NORMAL, m_session ? m_session->GetPlayer()->GetGUIDLow() : 0, MAIL_STATIONERY_GM);

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    MailDraft(subject, text)
        .AddMoney(money)
        .SendMailTo(trans, MailReceiver(receiver, GUID_LOPART(receiver_guid)), sender);

    CharacterDatabase.CommitTransaction(trans);

    std::string nameLink = playerLink(receiver_name);
    PSendSysMessage(LANGUAGE_MAIL_SENT, nameLink.c_str());
    return true;
}

/// Send a message to a player in game
bool ChatHandler::HandleSendMessageCommand(const char *args)
{
    ///- Find the player
    Player* rPlayer;
    if (!extractPlayerTarget((char*)args, &rPlayer))
        return false;

    char* msg_str = strtok(NULL, "");
    if (!msg_str)
        return false;

    ///- Check that he is not logging out.
    if (rPlayer->GetSession()->isLogingOut())
    {
        SendSysMessage(LANGUAGE_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }

    ///- Send the message
    //Use SendAreaTriggerMessage for fastest delivery.
    rPlayer->GetSession()->SendAreaTriggerMessage("%s", msg_str);
    rPlayer->GetSession()->SendAreaTriggerMessage("|cffff0000[Message from administrator]:|r");

    //Confirmation message
    std::string nameLink = GetNameLink(rPlayer);
    PSendSysMessage(LANGUAGE_SENDMESSAGE, nameLink.c_str(), msg_str);
    return true;
}

bool ChatHandler::HandleFlushArenaPointsCommand(const char * /*args*/)
{
    sArenaTeamMgr->DistributeArenaPoints();
    return true;
}

bool ChatHandler::HandleChannelSetOwnership(const char *args)
{
    if (!*args)
        return false;
    char *channel = strtok((char*)args, " ");
    char *argstr =  strtok(NULL, "");

    if (!channel || !argstr)
        return false;

    Player* player = m_session->GetPlayer();
    Channel* chn = NULL;

    if (ChannelMgr* cMgr = channelMgr(player->GetTeam()))
        chn = cMgr->GetChannel(channel, player);

    if (strcmp(argstr, "on") == 0)
    {
        if (chn)
            chn->SetOwnership(true);
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHARACTER_UPDATE_CHANNEL_OWNERSHIP);
        stmt->setUInt8 (0, 1);
        stmt->setString(1, channel);
        CharacterDatabase.Execute(stmt);
        PSendSysMessage(LANGUAGE_CHANNEL_ENABLE_OWNERSHIP, channel);
    }
    else if (strcmp(argstr, "off") == 0)
    {
        if (chn)
            chn->SetOwnership(false);
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHARACTER_UPDATE_CHANNEL_OWNERSHIP);
        stmt->setUInt8 (0, 0);
        stmt->setString(1, channel);
        CharacterDatabase.Execute(stmt);
        PSendSysMessage(LANGUAGE_CHANNEL_DISABLE_OWNERSHIP, channel);
    }
    else
        return false;

    return true;
}

bool ChatHandler::HandlePlayAllCommand(const char *args)
{
    if (!*args)
        return false;

    uint32 soundId = atoi((char*)args);

    if (!sSoundEntriesStore.LookupEntry(soundId))
    {
        PSendSysMessage(LANGUAGE_SOUND_NOT_EXIST, soundId);
        SetSentErrorMessage(true);
        return false;
    }

    WorldPacket data(SMSG_PLAY_SOUND, 4);
    data << uint32(soundId) << m_session->GetPlayer()->GetGUID();
    sWorld->SendGlobalMessage(&data);

    PSendSysMessage(LANGUAGE_COMMAND_PLAYED_TO_ALL, soundId);
    return true;
}

bool ChatHandler::HandleFreezeCommand(const char *args)
{
    std::string name;
    Player* player;
    char *TargetName = strtok((char*)args, " "); //get entered name
    if (!TargetName) //if no name entered use target
    {
        player = getSelectedPlayer();
        if (player) //prevent crash with creature as target
        {
            name = player->GetName();
            normalizePlayerName(name);
        }
    }
    else // if name entered
    {
        name = TargetName;
        normalizePlayerName(name);
        player = sObjectAccessor->FindPlayerByName(name.c_str());
    }

    if (!player)
    {
        SendSysMessage(LANGUAGE_COMMAND_FREEZE_WRONG);
        return true;
    }

    if (player == m_session->GetPlayer())
    {
        SendSysMessage(LANGUAGE_COMMAND_FREEZE_ERROR);
        return true;
    }

    //effect
    if (player && player != m_session->GetPlayer())
    {
        PSendSysMessage(LANGUAGE_COMMAND_FREEZE, name.c_str());

        //stop combat + make player unattackable + duel stop + stop some spells
        player->setFaction(35);
        player->CombatStop();
        if (player->IsNonMeleeSpellCasted(true))
            player->InterruptNonMeleeSpells(true);
        player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        //if player class = hunter || warlock remove pet if alive
        if ((player->getClass() == CLASS_HUNTER) || (player->getClass() == CLASS_WARLOCK))
        {
            if (Pet* pet = player->GetPet())
            {
                pet->SavePetToDB(PET_SAVE_AS_CURRENT);
                 // not let dismiss dead pet
                 if (pet && pet->isAlive())
                    player->RemovePet(pet, PET_SLOT_OTHER_PET);
            }
        }

        //m_session->GetPlayer()->CastSpell(player, spellID, false);
        if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(9454))
            Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, player, player);

        //save player
        player->SaveToDB();
    }
    return true;
}

bool ChatHandler::HandleUnFreezeCommand(const char *args)
{
    std::string name;
    Player* player;
    char *TargetName = strtok((char*)args, " "); //get entered name
    if (!TargetName) //if no name entered use target
    {
        player = getSelectedPlayer();
        if (player) //prevent crash with creature as target
            name = player->GetName();
    }

    else // if name entered
    {
        name = TargetName;
        normalizePlayerName(name);
        player = sObjectAccessor->FindPlayerByName(name.c_str());
    }

    //effect
    if (player)
    {
        PSendSysMessage(LANGUAGE_COMMAND_UNFREEZE, name.c_str());

        //Reset player faction + allow combat + allow duels
        player->setFactionForRace(player->getRace());
        player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        //allow movement and spells
        player->RemoveAurasDueToSpell(9454);

        //save player
        player->SaveToDB();
    }

    if (!player)
    {
        if (TargetName)
        {
            //check for offline players
            QueryResult result = CharacterDatabase.PQuery("SELECT characters.guid FROM characters WHERE characters.name = '%s'", name.c_str());
            if (!result)
            {
                SendSysMessage(LANGUAGE_COMMAND_FREEZE_WRONG);
                return true;
            }
            //if player found: delete his freeze aura
            Field* fields=result->Fetch();
            uint64 pguid = fields[0].GetUInt64();

            CharacterDatabase.PQuery("DELETE FROM character_aura WHERE character_aura.spell = 9454 AND character_aura.guid = '%u'", pguid);
            PSendSysMessage(LANGUAGE_COMMAND_UNFREEZE, name.c_str());
            return true;
        }
        else
        {
            SendSysMessage(LANGUAGE_COMMAND_FREEZE_WRONG);
            return true;
        }
    }

    return true;
}

bool ChatHandler::HandleListFreezeCommand(const char * /*args*/)
{
    //Get names from DB
    QueryResult result = CharacterDatabase.Query("SELECT characters.name FROM characters LEFT JOIN character_aura ON (characters.guid = character_aura.guid) WHERE character_aura.spell = 9454");
    if (!result)
    {
        SendSysMessage(LANGUAGE_COMMAND_NO_FROZEN_PLAYERS);
        return true;
    }
    //Header of the names
    PSendSysMessage(LANGUAGE_COMMAND_LIST_FREEZE);

    //Output of the results
    do
    {
        Field* fields = result->Fetch();
        std::string fplayers = fields[0].GetString();
        PSendSysMessage(LANGUAGE_COMMAND_FROZEN_PLAYERS, fplayers.c_str());
    } while (result->NextRow());

    return true;
}

bool ChatHandler::HandleGroupLeaderCommand(const char *args)
{
    Player* player  = NULL;
    Group* group = NULL;
    uint64 guid  = 0;
    char* cname  = strtok((char*)args, " ");

    if (GetPlayerGroupAndGUIDByName(cname, player, group, guid))
        if (group && group->GetLeaderGUID() != guid)
        {
            group->ChangeLeader(guid);
            group->SendUpdate();
        }

    return true;
}

bool ChatHandler::HandleGroupDisbandCommand(const char *args)
{
    Player* player  = NULL;
    Group* group = NULL;
    uint64 guid  = 0;
    char* cname  = strtok((char*)args, " ");

    if (GetPlayerGroupAndGUIDByName(cname, player, group, guid))
        if (group)
            group->Disband();

    return true;
}

bool ChatHandler::HandleGroupRemoveCommand(const char *args)
{
    Player* player  = NULL;
    Group* group = NULL;
    uint64 guid  = 0;
    char* cname  = strtok((char*)args, " ");

    if (GetPlayerGroupAndGUIDByName(cname, player, group, guid, true))
        if (group)
            group->RemoveMember(guid);

    return true;
}

bool ChatHandler::HandlePossessCommand(const char * /*args*/)
{
    Unit* unit = getSelectedUnit();
    if (!unit)
        return false;

    m_session->GetPlayer()->CastSpell(unit, 530, true);
    return true;
}

bool ChatHandler::HandleUnPossessCommand(const char * /*args*/)
{
    Unit* unit = getSelectedUnit();
    if (!unit)
        unit = m_session->GetPlayer();

    unit->RemoveCharmAuras();

    return true;
}

bool ChatHandler::HandleBindSightCommand(const char * /*args*/)
{
    Unit* unit = getSelectedUnit();
    if (!unit)
        return false;

    m_session->GetPlayer()->CastSpell(unit, 6277, true);
    return true;
}

bool ChatHandler::HandleUnbindSightCommand(const char * /*args*/)
{
    if (m_session->GetPlayer()->isPossessing())
        return false;

    m_session->GetPlayer()->StopCastingBindSight();
    return true;
}
