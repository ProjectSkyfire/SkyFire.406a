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
#include "SharedDefines.h"

#include <map>
#include <set>
#include <vector>

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
    uint32     ID;                                           // 0
    uint32     Quality;                                      // 1
    uint32     Flags;                                        // 2
    uint32     Flags2;                                       // 3
    uint32     BuyPrice;                                     // 4
    uint32     SellPrice;                                    // 5
    uint32     InventoryType;                                // 6
    int32      AllowableClass;                               // 7
    int32      AllowableRace;                                // 8
    uint32     ItemLevel;                                    // 9
    int32      RequiredLevel;                                // 10
    uint32     RequiredSkill;                                // 11
    uint32     RequiredSkillRank;                            // 12
    uint32     RequiredSpell;                                // 13
    uint32     RequiredHonorRank;                            // 14
    uint32     RequiredCityRank;                             // 15
    uint32     RequiredReputationFaction;                    // 16
    uint32     RequiredReputationRank;                       // 17
    uint32     MaxCount;                                     // 18
    uint32     Stackable;                                    // 19
    uint32     ContainerSlots;                               // 20
    int32      ItemStatType[MAX_ITEM_PROTO_STATS];           // 21 - 31
    uint32     ItemStatValue[MAX_ITEM_PROTO_STATS];          // 32 - 42
    uint32     ScalingStatDistribution;                      // 43
    uint32     DamageType;                                   // 44
    uint32     Delay;                                        // 45
    float      RangedModRange;                               // 46
    int32      SpellId[MAX_ITEM_PROTO_SPELLS];               // 47 - 52
    int32      SpellTrigger[MAX_ITEM_PROTO_SPELLS];          // 53 - 58
    int32      SpellCharges[MAX_ITEM_PROTO_SPELLS];          // 59 - 64
    int32      SpellCooldown[MAX_ITEM_PROTO_SPELLS];         // 65 - 70
    int32      SpellCategory[MAX_ITEM_PROTO_SPELLS];         // 71 - 76
    int32      SpellCategoryCooldown[MAX_ITEM_PROTO_SPELLS]; // 77 - 82
    uint32     Bonding;                                      // 83
    DB2String  Name;                                         // 84
    DB2String  Name2;                                        // 85
    DB2String  Name3;                                        // 86
    DB2String  Name4;                                        // 87
    DB2String  Description;                                  // 88
    uint32     PageText;                                     // 89
    uint32     LanguageID;                                   // 90
    uint32     PageMaterial;                                 // 91
    uint32     StartQuest;                                   // 92
    uint32     LockID;                                       // 93
    int32      Material;                                     // 94
    uint32     Sheath;                                       // 95
    uint32     RandomProperty;                               // 96
    uint32     RandomSuffix;                                 // 97
    uint32     ItemSet;                                      // 98
    uint32     MaxDurability;                                // 99
    uint32     Area;                                         // 100
    uint32     Map;                                          // 111
    uint32     BagFamily;                                    // 112
    uint32     TotemCategory;                                // 113
    uint32     Color[MAX_ITEM_PROTO_SOCKETS];                // 114 - 117
    uint32     Content[MAX_ITEM_PROTO_SOCKETS];              // 118 - 121
    int32      SocketBonus;                                  // 122
    uint32     GemProperties;                                // 123
    float      ArmorDamageModifier;                          // 124
    uint32     Duration;                                     // 125
    uint32     ItemLimitCategory;                            // 126
    uint32     HolidayId;                                    // 127
    float      StatScalingFactor;                            // 128
    int32      Field130;                                     // 129
    int32      Field131;                                     // 130
};

#endif