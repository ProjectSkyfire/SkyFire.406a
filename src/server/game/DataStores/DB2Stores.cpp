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

#include "DB2Stores.h"

#include "Entities/Item/ItemPrototype.h"
#include "Logging/Log.h"
#include "SharedDefines.h"
#include "SpellMgr.h"
#include "DB2fmt.h"

#include <map>

DB2Storage <ItemEntry> sItemStore(Itemfmt);
DB2Storage <ItemSparseEntry> sItemSparseStore (ItemSparsefmt);

typedef std::list<std::string> StoreProblemList1;

static bool LoadDB2_assert_print(uint32 fsize, uint32 rsize, const std::string& filename)
{
    sLog->outError("Size of '%s' setted by format string (%u) not equal size of C++ structure (%u).", filename.c_str(), fsize, rsize);

    // ASSERT must fail after function call
    return false;
}

struct LocalDB2Data
{
    LocalDB2Data(LocaleConstant loc) : defaultLocale(loc), availableDb2Locales(0xFFFFFFFF) {}

    LocaleConstant defaultLocale;

    // bitmasks for index of fullLocaleNameList
    uint32 availableDb2Locales;
};

template<class T>
inline void LoadDB2(uint32& availableDb2Locales, StoreProblemList1& errlist, DB2Storage<T>& storage, const std::string& db2_path, const std::string& filename)
{
    // compatibility format and C++ structure sizes
    ASSERT(DB2FileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDB2_assert_print(DB2FileLoader::GetFormatRecordSize(storage.GetFormat()), sizeof(T), filename));

    std::string db2_filename = db2_path + filename;
    if (storage.Load(db2_filename.c_str()))
    {
        for (uint8 loc = 1; loc < TOTAL_LOCALES; ++loc)
        {
            if (!(availableDb2Locales & (1 << loc)))
                continue;

            std::string localizedFileName = db2_path + localeNames[loc] + "/" + filename;
            if (!storage.LoadStringsFrom(localizedFileName.c_str(), loc))
                availableDb2Locales &= ~(1<<loc);             // mark locale as not available
        }
    }
    else
    {
        // sort problematic db2 to (1) non compatible and (2) nonexistent
        FILE * f = fopen(db2_filename.c_str(), "rb");
        if (f)
        {
            char buf[100];
            snprintf(buf, 100, "(exist, but have %d fields instead " SIZEFMTD ") Wrong client version DBC file?", storage.GetFieldCount(), strlen(storage.GetFormat()));
            errlist.push_back(db2_filename + buf);
            fclose(f);
        }
        else
            errlist.push_back(db2_filename);
    }
}

void LoadDB2Stores(const std::string& dataPath)
{
    std::string db2Path = dataPath + "dbc/";

    const uint32 DB2FilesCount = 1;

    StoreProblemList1 bad_db2_files;
    uint32 availableDb2Locales = 0xFFFFFFFF;

    LoadDB2(availableDb2Locales, bad_db2_files, sItemStore,                   db2Path, "Item.db2");
    LoadDB2(availableDb2Locales, bad_db2_files, sItemSparseStore,             db2Path, "Item-sparse.db2");

    for (uint32 i = 0; i < sItemStore.GetNumRows(); ++i)
    {
        const ItemEntry* itemEntry = sItemStore.LookupEntry(i);
        if (!itemEntry)
            continue;

        if (itemEntry->Class >= MAX_ITEM_CLASS)
        {
            sLog->outErrorDb("Item (Entry: %u) in Item.db2 has too high class value %u", itemEntry->ID, itemEntry->Class);
            const_cast<ItemEntry*>(itemEntry)->Class = 0;
        }
        if (itemEntry->SubClass >= MaxItemSubclassValues[itemEntry->Class])
        {
            sLog->outErrorDb("Item (Entry: %u) in Item.db2 has too high subclass value %u for class %u", itemEntry->ID, itemEntry->SubClass, itemEntry->Class);
            const_cast<ItemEntry*>(itemEntry)->SubClass = 0;
        }
    }

    // Check loaded DBC files proper version
    if (!sItemStore.LookupEntry(68815) ||                   // last client known item added in 4.0.6a
        !sItemSparseStore.LookupEntry(68815))               // last client known item added in 4.0.6a
    {
        sLog->outString("");
        sLog->outError("Please extract correct db2 files from client 4.0.6a 13623.");
        exit(1);
    }

    sLog->outString(">> Initialized %d data stores.", DB2FilesCount);
    sLog->outString();
}
