/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011 TrilliumEMU <http://www.trilliumemu.org/>
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

#include "ItemInfo.h"

/* ItemInfoMgr */

ItemInfoMgr::ItemInfoMgr() {}

ItemInfoMgr::~ItemInfoMgr()
{
    UnloadItemInfoStore();
}

void ItemInfoMgr::UnloadItemInfoStore()
{
    for (uint32 i = 0; i < mItemInfoMap.size(); i++)
    {
        if (mItemInfoMap[i])
            delete mItemInfoMap[i];
    }
    mItemInfoMap.clear();
}

void ItemInfoMgr::LoadItemInfo()
{
    uint32 oldMSTime = getMSTime();

    UnloadItemInfoStore();
    mItemInfoMap.resize(sItemSparseStore.GetNumRows(), NULL);

    for (uint32 i = 0; i < sItemSparseStore.GetNumRows(); i++)
    {
        if (ItemSparseEntry const* _itemSparse = sItemSparseStore.LookupEntry(i))
            mItemInfoMap[i] = new ItemInfo(_itemSparse);
    }

    sLog->outString(">> Loaded %u Items Info in %u ms", mItemInfoMap.size(), GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

/* ItemInfo */

ItemInfo::ItemInfo(ItemSparseEntry const* itemSparse)
{
    // Item.db2 including Blizzard test items, so we use the Item-sparse.db2 data
    /* Item-sparse.db2 */
    ItemId                                                   = itemSparse->ID;
    Quality                                                  = itemSparse->Quality;
    Flags                                                    = itemSparse->Flags;
    Flags2                                                   = itemSparse->Flags2;
    BuyPrice                                                 = itemSparse->BuyPrice;
    SellPrice                                                = itemSparse->SellPrice;
    InventoryType                                            = itemSparse->InventoryType;
    AllowableClass                                           = itemSparse->AllowableClass;
    AllowableRace                                            = itemSparse->AllowableRace;
    ItemLevel                                                = itemSparse->ItemLevel;
    RequiredLevel                                            = itemSparse->RequiredLevel;
    RequiredSkill                                            = itemSparse->RequiredSkill;
    RequiredSkillRank                                        = itemSparse->RequiredSkillRank;
    RequiredSpell                                            = itemSparse->RequiredSpell;
    RequiredHonorRank                                        = itemSparse->RequiredHonorRank;
    RequiredCityRank                                         = itemSparse->RequiredCityRank;
    RequiredReputationFaction                                = itemSparse->RequiredReputationFaction;
    RequiredReputationRank                                   = itemSparse->RequiredReputationRank;
    MaxCount                                                 = itemSparse->MaxCount;
    Stackable                                                = itemSparse->Stackable;
    ContainerSlots                                           = itemSparse->ContainerSlots;
    for (uint8 i = 0; i < MAX_ITEM_PROTO_STATS; i++)
    {
        ItemStatType[i]          = itemSparse->ItemStatType[i];
        ItemStatValue[i]         = itemSparse->ItemStatValue[i];
    }
    ScalingStatDistribution                                  = itemSparse->ScalingStatDistribution;
    DamageType                                               = itemSparse->DamageType;
    Delay                                                    = itemSparse->Delay;
    RangedModRange                                           = itemSparse->RangedModRange;
    for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; i++)
    {
         SpellId[i]               = itemSparse->SpellId[i];
         SpellTrigger[i]          = itemSparse->SpellTrigger[i];
         SpellCharges[i]          = itemSparse->SpellCharges[i];
         SpellCooldown[i]         = itemSparse->SpellCooldown[i];
         SpellCategory[i]         = itemSparse->SpellCategory[i];
         SpellCategoryCooldown[i] = itemSparse->SpellCategoryCooldown[i];
    }
    Bonding                                                 = itemSparse->Bonding;
    Name                                                    = itemSparse->Name;
    Description                                             = itemSparse->Description;
    PageText                                                = itemSparse->PageText;
    LanguageID                                              = itemSparse->LanguageID;
    PageMaterial                                            = itemSparse->PageMaterial;
    StartQuest                                              = itemSparse->StartQuest;
    LockID                                                  = itemSparse->LockID;
    Material                                                = itemSparse->Material;
    Sheath                                                  = itemSparse->Sheath;
    RandomProperty                                          = itemSparse->RandomProperty;
    RandomSuffix                                            = itemSparse->RandomSuffix;
    ItemSet                                                 = itemSparse->ItemSet;
    MaxDurability                                           = itemSparse->MaxDurability;
    Area                                                    = itemSparse->Area;
    Map                                                     = itemSparse->Map;
    BagFamily                                               = itemSparse->BagFamily;
    TotemCategory                                           = itemSparse->TotemCategory;
    for (uint8 i = 0; i < MAX_ITEM_PROTO_SOCKETS; i++)
    {
        Color[i]     = itemSparse->Color[i];
        Content[i]   = itemSparse->Content[i];
    }
    SocketBonus                                             = itemSparse->SocketBonus;
    GemProperties                                           = itemSparse->GemProperties;
    ArmorDamageModifier                                     = itemSparse->ArmorDamageModifier;
    Duration                                                = itemSparse->Duration;
    ItemLimitCategory                                       = itemSparse->ItemLimitCategory;
    HolidayId                                               = itemSparse->HolidayId;
    StatScalingFactor                                       = itemSparse->StatScalingFactor;

    /* Item.db2 */
    ItemEntry const* _itemEntry = GetItemEntry();
    Class          = _itemEntry ? _itemEntry->Class : 0;
    SubClass       = _itemEntry ? _itemEntry->SubClass : 0;
    Unk0           = _itemEntry ? _itemEntry->Unk0 : 0;
    DisplayId      = _itemEntry ? _itemEntry->DisplayId : 0;

     /* item_template */
    ItemTemplate const* _proto = sObjectMgr->GetItemTemplate(ItemId);
    BuyCount          = _proto ? _proto->BuyCount : 0;
    Block             = _proto ? _proto->Block : 0;
    RequiredDisenchantSkill = _proto ? _proto->RequiredDisenchantSkill : 0;
    ScriptId          = _proto ? _proto->ScriptId : 0;
    DisenchantID      = _proto ? _proto->DisenchantID : 0;
    FoodType          = _proto ? _proto->FoodType : 0;
    MinMoneyLoot      = _proto ? _proto->MinMoneyLoot : 0;
    MaxMoneyLoot      = _proto ? _proto->MaxMoneyLoot : 0;
}

ItemEntry const* ItemInfo::GetItemEntry() const
{
    return ItemId ? sItemStore.LookupEntry(ItemId) : NULL;
}