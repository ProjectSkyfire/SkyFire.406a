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

#include "ItemInfo.h"

ItemInfo::ItemInfo(ItemSparseEntry const* itemSparse)
{
    Id = itemSparse->ID;
    Class = itemSparse->AllowableClass;
    SubClass = itemSparse->AllowableClass;
    Unk0;
    Material = itemSparse->Material;
    DisplayId;
    InventoryType = itemSparse->InventoryType;
    Sheath = itemSparse->Sheath;
}

ItemSparseInfo::ItemSparseInfo(ItemEntry const* itemEntry)
{
    Id;
    Quality;
    Flags;
    Flags2;
    BuyPrice;
    SellPrice;
    InventoryType;
    AllowableClass;
    AllowableRace;
    ItemLevel;
    RequiredLevel;
    RequiredSkill;
    RequiredSkillRank;
    RequiredSpell;
    RequiredHonorRank;
    RequiredCityRank;
    RequiredReputationFaction;
    RequiredReputationRank;
    MaxCount;
    Stackable;
    ContainerSlots;
    ItemStatType[MAX_ITEM_PROTO_STATS];
    ItemStatValue[MAX_ITEM_PROTO_STATS];
    ItemStatUnk1[MAX_ITEM_PROTO_STATS];
    ItemStatUnk2[MAX_ITEM_PROTO_STATS];
    ScalingStatDistribution;
    DamageType;
    Delay;
    RangedModRange;
    SpellId[MAX_ITEM_PROTO_SPELLS];
    SpellTrigger[MAX_ITEM_PROTO_SPELLS];
    SpellCharges[MAX_ITEM_PROTO_SPELLS];
    SpellCooldown[MAX_ITEM_PROTO_SPELLS];
    SpellCategory[MAX_ITEM_PROTO_SPELLS];
    SpellCategoryCooldown[MAX_ITEM_PROTO_SPELLS];
    Bonding;
    name;
    name2;
    name3;
    name4;
    description;
    PageText;
    LanguageId;
    PageMaterial;
    StartQuest;
    LockID;
    Material;
    Sheath;
    RandomProperty;
    RandomSuffix;
    ItemSet;
    MaxDurability;
    Area;
    Map;
    BagFamily;
    TotemCategory;
    SocketColor[MAX_ITEM_PROTO_SOCKETS];
    SocketContent[MAX_ITEM_PROTO_SOCKETS];
    SocketBonus;
    GemProperties;
    ArmorDamageModifier;
    Duration;
    ItemLimitCategory;
    HolidayId;
    StatScalingFactor;
    archaeologyUnk; // related to archeology (?)
    FindingsCount; // related to archeology
}

ItemSparseEntry const* ItemSparseInfo::GetSparseInfo() const
{
    return sItemSparseStore.LookupEntry(Id);
}
