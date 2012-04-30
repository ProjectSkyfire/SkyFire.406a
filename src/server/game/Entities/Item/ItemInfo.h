/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
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

#ifndef _ITEMINFO_H
#define _ITEMINFO_H

#include "Define.h"
#include "SharedDefines.h"
#include "DB2Structure.h"
#include "DB2Stores.h"

class ItemInfoMgr;
class ItemInfo;
struct ItemEntry;
struct ItemSparseEntry;

class ItemInfo
{
public:
    uint32   Id;
    uint32   Class;
    uint32   SubClass;
    int32    Unk0;
    int32    Material;
    uint32   DisplayId;
    uint32   InventoryType;
    uint32   Sheath;

    // Functions
    ItemInfo(ItemSparseEntry const* itemSparse);
};

class ItemSparseInfo
{
public:
    uint32 Id;
    uint32 Quality;
    uint32 Flags;
    uint32 Flags2;
    int32 BuyPrice;
    int32 SellPrice;
    uint32 InventoryType;
    int32 AllowableClass;
    int32 AllowableRace;
    uint32 ItemLevel;
    uint32 RequiredLevel;
    uint32 RequiredSkill;
    uint32 RequiredSkillRank;
    uint32 RequiredSpell;
    uint32 RequiredHonorRank;
    uint32 RequiredCityRank;
    uint32 RequiredReputationFaction;
    uint32 RequiredReputationRank;
    int32 MaxCount;
    int32 Stackable;
    int32 ContainerSlots;
    int32 ItemStatType[MAX_ITEM_PROTO_STATS];
    int32 ItemStatValue[MAX_ITEM_PROTO_STATS];
    int32 ItemStatUnk1[MAX_ITEM_PROTO_STATS];
    int32 ItemStatUnk2[MAX_ITEM_PROTO_STATS];
    int32 ScalingStatDistribution;
    int32 DamageType;
    int32 Delay;
    float RangedModRange;
    int32 SpellId[MAX_ITEM_PROTO_SPELLS];
    int32 SpellTrigger[MAX_ITEM_PROTO_SPELLS];
    int32 SpellCharges[MAX_ITEM_PROTO_SPELLS];
    int32 SpellCooldown[MAX_ITEM_PROTO_SPELLS];
    int32 SpellCategory[MAX_ITEM_PROTO_SPELLS];
    int32 SpellCategoryCooldown[MAX_ITEM_PROTO_SPELLS];
    int32 Bonding;
    std::string name;
    std::string name2;
    std::string name3;
    std::string name4;
    std::string description;
    int32 PageText;
    int32 LanguageId;
    int32 PageMaterial;
    int32 StartQuest;
    int32 LockID;
    int32 Material;
    int32 Sheath;
    int32 RandomProperty;
    int32 RandomSuffix;
    int32 ItemSet;
    uint32 MaxDurability;
    int32 Area;
    int32 Map;
    int32 BagFamily;
    int32 TotemCategory;
    int32 SocketColor[MAX_ITEM_PROTO_SOCKETS];
    int32 SocketContent[MAX_ITEM_PROTO_SOCKETS];
    int32 SocketBonus;
    int32 GemProperties;
    float ArmorDamageModifier;
    int32 Duration;
    int32 ItemLimitCategory;
    int32 HolidayId;
    float StatScalingFactor;
    uint32 archaeologyUnk; // related to archeology
    uint32 FindingsCount;

    ItemSparseInfo(ItemEntry const* itemEntry);
    ItemSparseEntry const* GetSparseInfo() const;
};

#endif // _ITEMINFO_H
