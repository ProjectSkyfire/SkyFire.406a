/*
 * Copyright (C) 2010 CactusEMU <http://www.cactusemu.com/>
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

#include "headers.h"

#include "map.h"
#include "adt.h"
#include "wdt.h"

#include "dbc.h"

#include "MPQ.h"
#include "MPQFile.h"
#include "FileLoader.h"
#include "DBCFile.h"

#include "misc.h"

HANDLE localeMPQ[PATCH_REV_COUNT+1];
HANDLE WorldMPQ;
HANDLE ExpansionsMPQ[3];
map_id *map_ids;
uint16 *areas;
uint16 *LiqType;
uint32 maxAreaId;

#define ARG_MAP "--map"
#define ARG_NOMAP "--nomap"
#define ARG_DBC "--dbc"
#define ARG_NODBC "--nodbc"

int main(int argc, char * arg[])
{
    printf("DBC/Map Extractor\n");
    printf("===================\n\n");

    bool extractDBC = true;
    bool extractMap = true;

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(arg[i], ARG_MAP) == 0)
            extractMap = true;
        if (strcmp(arg[i], ARG_NOMAP) == 0)
            extractMap = false;
        if (strcmp(arg[i], ARG_DBC) == 0)
            extractDBC = true;
        if (strcmp(arg[i], ARG_NODBC) == 0)
            extractDBC = false;
    }

    int FirstLocale = -1;
    int build = 0;

    for (int i = 0; i < LANG_COUNT; i++)
    {
        char tmp1[512];
        sprintf(tmp1, "%s/Data/%s/locale-%s.MPQ", input_path, langs[i], langs[i]);
        if (FileExists(tmp1))
        {
            printf("Detected locale: %s\n", langs[i]);

            //Open MPQs
            LoadLocaleMPQFiles(i);

            //Extract DBC files
            if (FirstLocale < 0)
            {
                FirstLocale = i;
                build = ReadBuild(FirstLocale);
                printf("Detected base client build: %u\n", build);
                if (build != CLIENT_BUILD)
                {
                    printf("ERROR: your client is not up-to-date. Client build should be %u", CLIENT_BUILD);
                    return 0;
                }
                if (extractDBC)
                    ExtractDBCFiles(i, true);
            }
            else if (extractDBC)
                ExtractDBCFiles(i, false);
        }
    }

    if (FirstLocale < 0)
    {
        printf("No locales detected\n");
        return 0;
    }

    if (extractMap)
        ExtractMapsFromMpq(build);

    return 0;
}