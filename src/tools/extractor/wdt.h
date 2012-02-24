/*
 * Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef WDT_H
#define WDT_H

#include "headers.h"
#include "FileLoader.h"

//**************************************************************************************
// WDT file class and structures
//**************************************************************************************
#define WDT_MAP_SIZE 64

class wdt_MPHD
{
    union
    {
        uint32 fcc;
        char   fcc_txt[4];
    };
public:
    uint32 size;

    uint32 data1;
    uint32 data2;
    uint32 data3;
    uint32 data4;
    uint32 data5;
    uint32 data6;
    uint32 data7;
    uint32 data8;
    bool   prepareLoadedData();
};

class wdt_MAIN
{
    union
    {
        uint32 fcc;
        char   fcc_txt[4];
    };
public:
    uint32 size;

    struct adtData
    {
        uint32 exist;
        uint32 data1;
    } adt_list[64][64];

    bool   prepareLoadedData();
};

class wdt_MWMO
{
    union
    {
        uint32 fcc;
        char   fcc_txt[4];
    };
public:
    uint32 size;
    bool prepareLoadedData();
};

class WDT_file : public FileLoader
{
public:
    bool   prepareLoadedData();

    WDT_file(const char * filename, HANDLE _handle);

    wdt_MPHD *mphd;
    wdt_MAIN *main;
    wdt_MWMO *wmo;
};

#endif