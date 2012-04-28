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

#include "ItemInfoMgr.h"

/* ItemInfoMgr */

ItemInfoMgr::ItemInfoMgr() {}

ItemInfoMgr::~ItemInfoMgr()
{
    UnloadItemInfoStore();
}

void ItemInfoMgr::UnloadItemInfoStore()
{
    for (uint32 i = 0; i < mItemInfoMap.size(); ++i)
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

    for (uint32 i = 0; i < sItemSparseStore.GetNumRows(); ++i)
    {
        if (ItemSparseEntry const* _itemSparse = sItemSparseStore.LookupEntry(i))
            mItemInfoMap[i] = new ItemInfo(_itemSparse);
    }

    sLog->outString(">> Loaded %u Items Info in %u ms", mItemInfoMap.size(), GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

ItemInfo const* ItemInfoMgr::GetItemInfo(uint32 ItemId) const
{
    return ItemId < GetItemInfoStoreSize() ? mItemInfoMap[ItemId] : NULL;
}

uint32 ItemInfoMgr::GetItemInfoStoreSize() const
{
    return mItemInfoMap.size();
}
