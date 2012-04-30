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

#ifndef SKYFIRE_ITEMINFOMGR_H
#define SKYFIRE_ITEMINFOMGR_H

#include "ItemInfo.h"

class ItemInfoMgr
{
    friend class ACE_Singleton<ItemInfoMgr, ACE_Null_Mutex>;
private:
    ItemInfoMgr();
    ~ItemInfoMgr();

public:
    typedef std::vector<ItemInfo*> ItemInfoMap;

    ItemInfo const* GetItemInfo(uint32 ItemId) const;
    uint32 GetItemInfoStoreSize() const;

    void LoadItemInfo();
    void UnloadItemInfoStore();

private:
    ItemInfoMap mItemInfoMap;
};

#define sItemInfoMgr ACE_Singleton<ItemInfoMgr, ACE_Null_Mutex>::instance()

#endif
