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

#include "Common.h"
#include "DBCFileLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DBCFileLoader::DBCFileLoader()
{
    data = NULL;
    fieldsOffset = NULL;
}

bool DBCFileLoader::Load(const char* filename, const char* fmt)
{
    uint32 header;
    if (data)
    {
        delete [] data;
        data = NULL;
    }

    FILE* f = fopen(filename, "rb");
    if (!f)
        return false;

    if (fread(&header, 4, 1, f) != 1)                           // Number of records
    {
        fclose(f);
        return false;
    }

    EndianConvert(header);

    if (header != 0x43424457)                                //'WDBC'
    {
        fclose(f);
        return false;
    }

    if (fread(&recordCount, 4, 1, f) != 1)                      // Number of records
    {
        fclose(f);
        return false;
    }

    EndianConvert(recordCount);

    if (fread(&fieldCount, 4, 1, f) != 1)                       // Number of fields
    {
        fclose(f);
        return false;
    }

    EndianConvert(fieldCount);

    if (fread(&recordSize, 4, 1, f) != 1)                       // Size of a record
    {
        fclose(f);
        return false;
    }

    EndianConvert(recordSize);

    if (fread(&stringSize, 4, 1, f) != 1)                       // String size
    {
        fclose(f);
        return false;
    }

    EndianConvert(stringSize);

    fieldsOffset = new uint32[fieldCount];
    fieldsOffset[0] = 0;
    for (uint32 i = 1; i < fieldCount; i++)
    {
        fieldsOffset[i] = fieldsOffset[i - 1];
        if (fmt[i - 1] == 'b' || fmt[i - 1] == 'X')         // byte fields
            fieldsOffset[i] += 1;
        else                                                // 4 byte fields (int32/float/strings)
            fieldsOffset[i] += 4;
    }

    data = new unsigned char[recordSize*recordCount+stringSize];
    stringTable = data + recordSize*recordCount;

    if (fread(data, recordSize*recordCount+stringSize, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    fclose(f);

    return true;
}

DBCFileLoader::~DBCFileLoader()
{
    if (data)
        delete [] data;

    if (fieldsOffset)
        delete [] fieldsOffset;
}

DBCFileLoader::Record DBCFileLoader::getRecord(size_t id)
{
    ASSERT(data);
    return Record(*this, data + id*recordSize);
}

uint32 DBCFileLoader::GetFormatRecordSize(const char * format, int32* index_pos)
{
    uint32 recordsize = 0;
    int32 i = -1;
    for (uint32 x=0; format[x]; ++x)
    {
        switch (format[x])
        {
            case FT_FLOAT:
            case FT_INT:
                recordsize+=4;
                break;
            case FT_STRING:
                recordsize+=sizeof(char*);
                break;
            case FT_SORT:
                i=x;
                break;
            case FT_IND:
                i=x;
                recordsize+=4;
                break;
            case FT_BYTE:
                recordsize += 1;
                break;
        }
    }

    if (index_pos)
        *index_pos = i;

    return recordsize;
}

uint32 DBCFileLoader::GetFormatStringsFields(const char * format)
{
    uint32 stringfields = 0;
    for (uint32 x=0; format[x]; ++x)
        if (format[x] == FT_STRING)
            ++stringfields;

    return stringfields;
}

char* DBCFileLoader::AutoProduceData(const char* format, uint32& records, char**& indexTable, uint32 sqlRecordCount, uint32 sqlHighestIndex, char*& sqlDataTable)
{
    /*
    format STRING, NA, FLOAT, NA, INT <=>
    struct{
    char* field0,
    float field1,
    int field2
    }entry;

    this func will generate  entry[rows] data;
    */

    typedef char* ptr;
    if (strlen(format) != fieldCount)
        return NULL;

    //get struct size and index pos
    int32 i;
    uint32 recordsize=GetFormatRecordSize(format, &i);

    if (i>=0)
    {
        uint32 maxi=0;
        //find max index
        for (uint32 y=0; y<recordCount; y++)
        {
            uint32 ind=getRecord(y).getUInt (i);
            if (ind>maxi)maxi=ind;
        }

        // If higher index avalible from sql - use it instead of dbcs
        if (sqlHighestIndex > maxi)
            maxi = sqlHighestIndex;

        ++maxi;
        records=maxi;
        indexTable=new ptr[maxi];
        memset(indexTable, 0, maxi*sizeof(ptr));
    }
    else
    {
        records = recordCount + sqlRecordCount;
        indexTable = new ptr[recordCount+ sqlRecordCount];
    }

    char* dataTable= new char[(recordCount + sqlRecordCount)*recordsize];

    uint32 offset=0;

    for (uint32 y =0; y<recordCount; ++y)
    {
        if (i>=0)
            indexTable[getRecord(y).getUInt(i)]=&dataTable[offset];
        else
            indexTable[y]=&dataTable[offset];

        for (uint32 x=0; x<fieldCount; x++)
        {
            switch (format[x])
            {
                case FT_FLOAT:
                    *((float*)(&dataTable[offset]))=getRecord(y).getFloat(x);
                    offset+=4;
                    break;
                case FT_IND:
                case FT_INT:
                    *((uint32*)(&dataTable[offset]))=getRecord(y).getUInt(x);
                    offset+=4;
                    break;
                case FT_BYTE:
                    *((uint8*)(&dataTable[offset]))=getRecord(y).getUInt8(x);
                    offset+=1;
                    break;
                case FT_STRING:
                    *((char**)(&dataTable[offset]))=NULL;   // will be replaces non-empty or "" strings in AutoProduceStrings
                    offset+=sizeof(char*);
                    break;
            }
        }
    }

    sqlDataTable = dataTable + offset;

    return dataTable;
}

char* DBCFileLoader::AutoProduceStringsArrayHolders(const char* format, char* dataTable)
{
    if (strlen(format) != fieldCount)
        return NULL;

    // we store flat holders pool as single memory block
    size_t stringFields = GetFormatStringsFields(format);
    // each string field at load have array of string for each locale
    size_t stringHolderSize = sizeof(char*) * TOTAL_LOCALES;
    size_t stringHoldersRecordPoolSize = stringFields * stringHolderSize;
    size_t stringHoldersPoolSize = stringHoldersRecordPoolSize * recordCount;

    char* stringHoldersPool = new char[stringHoldersPoolSize];

    for (size_t i = 0; i < stringHoldersPoolSize / sizeof(char*); ++i)
        ((char const**)stringHoldersPool)[i] = NULL;

    uint32 offset=0;

    // assign string holders to string field slots
    for (uint32 y = 0; y < recordCount; y++)
    {
        uint32 stringFieldNum = 0;

        for (uint32 x = 0; x < fieldCount; x++)
            switch (format[x])
        {
            case FT_FLOAT:
            case FT_IND:
            case FT_INT:
                offset += 4;
                break;
            case FT_BYTE:
                offset += 1;
                break;
            case FT_STRING:
                {
                    // init dbc string field slots by pointers to string holders
                    char const*** slot = (char const***)(&dataTable[offset]);
                    *slot = (char const**)(&stringHoldersPool[stringHoldersRecordPoolSize * y + stringHolderSize*stringFieldNum]);
                    ++stringFieldNum;
                    offset += sizeof(char*);
                    break;
                }
            case FT_NA:
            case FT_NA_BYTE:
            case FT_SORT:
                break;
            default:
                assert(false && "unknown format character");
        }
    }

    //send as char* for store in char* pool list for free at unload
    return stringHoldersPool;
}

char* DBCFileLoader::AutoProduceStrings(const char* format, char* dataTable, uint8 locale)
{
    if (strlen(format)!=fieldCount)
        return NULL;

    struct DBCStringHolder
    {
        char const* Strings[TOTAL_LOCALES];
    };

    char* stringPool = new char[stringSize];
    memcpy(stringPool, stringTable, stringSize);

    uint32 offset=0;

    for (uint32 y =0; y<recordCount; y++)
    {
        for (uint32 x=0; x<fieldCount; x++)
            switch (format[x])
        {
            case FT_FLOAT:
            case FT_IND:
            case FT_INT:
                offset+=4;
                break;
            case FT_BYTE:
                offset+=1;
                break;
            case FT_STRING:
                DBCStringHolder** slot = (DBCStringHolder**)(&dataTable[offset]);
                if (*slot) // ensure the strings array holder is filled
                {
                    const char * st = getRecord(y).getString(x);
                    if (locale == 0)
                    {
                        // default locale, fill all unfilled locale entries
                        for (uint8 loc = 0; loc < TOTAL_LOCALES; loc++)
                            if (!(*slot)->Strings[loc])
                                (*slot)->Strings[loc] = stringPool+(st-(const char*)stringTable);
                    }
                    else // specific locale, overwrite locale entry
                        (*slot)->Strings[locale] = stringPool+(st-(const char*)stringTable);
                }
                offset+=sizeof(char*);
                break;
        }
    }

    return stringPool;
}
