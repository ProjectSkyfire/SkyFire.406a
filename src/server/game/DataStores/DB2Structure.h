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

#ifndef TRINITY_DB2STRUCTURE_H
#define TRINITY_DB2STRUCTURE_H

#include "Common.h"
#include "DBCEnums.h"
#include "Define.h"
#include "Path.h"
#include "Util.h"
#include "Vehicle.h"

#include <map>
#include <set>
#include <vector>
#include "SharedDefines.h"

// Structures using to access raw DB2 data and required packing to portability
struct ItemEntry
{
   uint32   ID;                                             // 0
   uint32   Class;                                          // 1
   uint32   SubClass;                                       // 2 some items have strange subclasses
   int32    Unk0;                                           // 3
   int32    Material;                                       // 4
   uint32   DisplayId;                                      // 5
   uint32   InventoryType;                                  // 6
   uint32   Sheath;                                         // 7
};

struct ItemSparseEntry
{
    int32 ID;
    int32 Quality;
    uint32 Flags;
    uint32 Flags2;
    int32 BuyPrice;
    int32 SellPrice;
    int32 InventoryType;
    int32 AllowableClass;
    int32 AllowableRace;
    int32 ItemLevel;
    int32 RequiredLevel;
    int32 RequiredSkill;
    int32 RequiredSkillRank;
    int32 RequiredSpell;
    int32 RequiredHonorRank;
    int32 RequiredCityRank;
    int32 RequiredReputationFaction;
    int32 RequiredReputationRank;
    int32 Maxcount;
    int32 Stackable;
    int32 ContainerSlots;
    int32 stat_type1;
    int32 stat_type2;
    int32 stat_type3;
    int32 stat_type4;
    int32 stat_type5;
    int32 stat_type6;
    int32 stat_type7;
    int32 stat_type8;
    int32 stat_type9;
    int32 stat_type10;
    int32 stat_value1;
    int32 stat_value2;
    int32 stat_value3;
    int32 stat_value4;
    int32 stat_value5;
    int32 stat_value6;
    int32 stat_value7;
    int32 stat_value8;
    int32 stat_value9;
    int32 stat_value10;
    int32 stat_unk1_1;
    int32 stat_unk1_2;
    int32 stat_unk1_3;
    int32 stat_unk1_4;
    int32 stat_unk1_5;
    int32 stat_unk1_6;
    int32 stat_unk1_7;
    int32 stat_unk1_8;
    int32 stat_unk1_9;
    int32 stat_unk1_10;
    int32 stat_unk2_1;
    int32 stat_unk2_2;
    int32 stat_unk2_3;
    int32 stat_unk2_4;
    int32 stat_unk2_5;
    int32 stat_unk2_6;
    int32 stat_unk2_7;
    int32 stat_unk2_8;
    int32 stat_unk2_9;
    int32 stat_unk2_10;
    int32 ScalingStatDistribution;
    int32 DamageType;
    int32 Delay;
    float RangedModRange;
    int32 spellid_1;
    int32 spellid_2;
    int32 spellid_3;
    int32 spellid_4;
    int32 spellid_5;
    int32 spelltrigger_1;
    int32 spelltrigger_2;
    int32 spelltrigger_3;
    int32 spelltrigger_4;
    int32 spelltrigger_5;
    int32 spellcharges_1;
    int32 spellcharges_2;
    int32 spellcharges_3;
    int32 spellcharges_4;
    int32 spellcharges_5;
    int32 spellcooldown_1;
    int32 spellcooldown_2;
    int32 spellcooldown_3;
    int32 spellcooldown_4;
    int32 spellcooldown_5;
    int32 spellcategory_1;
    int32 spellcategory_2;
    int32 spellcategory_3;
    int32 spellcategory_4;
    int32 spellcategory_5;
    int32 spellcategorycooldown_1;
    int32 spellcategorycooldown_2;
    int32 spellcategorycooldown_3;
    int32 spellcategorycooldown_4;
    int32 spellcategorycooldown_5;
    int32 Bonding;
    DBCString Name;
    DBCString Name2;
    DBCString Name3;
    DBCString Name4;
    DBCString Description;
    int32 PageText;
    int32 Languageid;
    int32 PageMaterial;
    int32 StartQuest;
    int32 LockID;
    int32 Material;
    int32 Sheath;
    int32 RandomProperty;
    int32 RandomSuffix;
    int32 ItemSet;
    int32 MaxDurability;
    int32 Area;
    int32 Map;
    int32 BagFamily;
    int32 TotemCategory;
    int32 SocketColor_1;
    int32 SocketColor_2;
    int32 SocketColor_3;
    int32 SocketContent_1;
    int32 SocketContent_2;
    int32 SocketContent_3;
    int32 SocketBonus;
    int32 GemProperties;
    float ArmorDamageModifier;
    int32 Duration;
    int32 ItemLimitCategory;
    int32 HolidayID;
    float StatScalingFactor;
    int32 Field130;
    int32 Field131;
};

#endif