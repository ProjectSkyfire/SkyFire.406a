/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
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

#include "PathCommon.h"
#include "MapBuilder.h"

using namespace Pathfinding;

bool checkDirectories(bool debugOutput)
{
    vector<string> dirFiles;

    if (getDirContents(dirFiles, "maps") == LISTFILE_DIRECTORY_NOT_FOUND || !dirFiles.size())
    {
        printf("'maps' directory is empty or does not exist\n");
        return false;
    }

    dirFiles.clear();
    if (getDirContents(dirFiles, "vmaps", "*.vmtree") == LISTFILE_DIRECTORY_NOT_FOUND || !dirFiles.size())
    {
        printf("'vmaps' directory is empty or does not exist\n");
        return false;
    }

    dirFiles.clear();
    if (getDirContents(dirFiles, "mmaps") == LISTFILE_DIRECTORY_NOT_FOUND)
    {
        printf("'mmaps' directory does not exist\n");
        return false;
    }

    dirFiles.clear();
    if (debugOutput)
        if (getDirContents(dirFiles, "meshes") == LISTFILE_DIRECTORY_NOT_FOUND)
        {
            printf("'meshes' directory does not exist (no place to put debugOutput files)\n");
            return false;
        }

    return true;
}

void handleArgs(int argc, char** argv,
               int &mapnum,
               int &tileX,
               int &tileY,
               float &maxAngle,
               bool &skipLiquid,
               bool &skipContinents,
               bool &skipJunkMaps,
               bool &skipBattlegrounds,
               bool &hiResHeightmaps,
               bool &debugOutput,
               bool &badParam)
{
    char zero[2] = "0";
    int i;
    char* param;
    for (i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--maxAngle") == 0)
        {
            param = argv[++i];
            if(!param)
            {
                badParam = true;
                return;
            }

            float maxangle = atof(param);
            if (maxangle <= 90.f && maxangle >= 45.f)
                maxAngle = maxangle;
            else
                printf("invalid option for '--maxAngle', using default\n");
        }
        else if (strcmp(argv[i], "--tile") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            char* stileX = strtok(param, ",");
            char* stileY = strtok(NULL, ",");
            int tilex = atoi(stileX);
            int tiley = atoi(stileY);

            if ((tilex > 0 && tilex < 64) || (tilex == 0 && strcmp(stileX, zero) == 0))
                tileX = tilex;
            if ((tiley > 0 && tiley < 64) || (tiley == 0 && strcmp(stileY, zero) == 0))
                tileY = tiley;

            if (tileX < 0 || tileY < 0)
            {
                printf("invalid tile coords.\n");
                badParam = true;
            }
        }
        else if (strcmp(argv[i], "--skipLiquid") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            if (strcmp(param, "true") == 0)
                skipLiquid = true;
            else if (strcmp(param, "false") == 0)
                skipLiquid = false;
            else
                printf("invalid option for '--skipLiquid', using default\n");
        }
        else if (strcmp(argv[i], "--skipContinents") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            if (strcmp(param, "true") == 0)
                skipContinents = true;
            else if (strcmp(param, "false") == 0)
                skipContinents = false;
            else
                printf("invalid option for '--skipContinents', using default\n");
        }
        else if (strcmp(argv[i], "--skipJunkMaps") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            if (strcmp(param, "true") == 0)
                skipJunkMaps = true;
            else if (strcmp(param, "false") == 0)
                skipJunkMaps = false;
            else
                printf("invalid option for '--skipJunkMaps', using default\n");
        }
        else if (strcmp(argv[i], "--skipBattlegrounds") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            if (strcmp(param, "true") == 0)
                skipBattlegrounds = true;
            else if(strcmp(param, "false") == 0)
                skipBattlegrounds = false;
            else
                printf("invalid option for '--skipBattlegrounds', using default\n");
        }
        else if (strcmp(argv[i], "--hiResHeightmaps") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            if (strcmp(param, "true") == 0)
                hiResHeightmaps = true;
            else if(strcmp(param, "false") == 0)
                hiResHeightmaps = false;
            else
                printf("invalid option for '--hiResHeightmaps', using default\n");
        }
        else if (strcmp(argv[i], "--debugOutput") == 0)
        {
            param = argv[++i];
            if (!param)
            {
                badParam = true;
                return;
            }

            if (strcmp(param, "true") == 0)
                debugOutput = true;
            else if (strcmp(param, "false") == 0)
                debugOutput = false;
            else
                printf("invalid option for '--debugOutput', using default true\n");
        }
        else
        {
            int map = atoi(argv[i]);
            if (map > 0 || (map == 0 && (strcmp(argv[i], zero) == 0)))
                mapnum = map;
            else
            {
                printf("bad parameter\n");
                badParam = true;
            }
        }
    }
}

int finish(const char* message, int returnValue)
{
    printf("%s", message);
    getchar();
    return returnValue;
}

int main(int argc, char** argv)
{
    int mapnum = -1;
    float maxAngle = 60.f;
    int tileX = -1, tileY = -1;
    bool skipLiquid = false,
         skipContinents = false,
         skipJunkMaps = true,
         skipBattlegrounds = false,
         hiResHeightmaps = true,
         debugOutput = false,
         badParam = false;

    handleArgs(argc,
              argv,
              mapnum,
              tileX,
              tileY,
              maxAngle,
              skipLiquid,
              skipContinents,
              skipJunkMaps,
              skipBattlegrounds,
              hiResHeightmaps,
              debugOutput,
              badParam);

    if (badParam)
        return finish("You have specified invalid parameters", -1);

    if (mapnum == -1 && debugOutput)
    {
        printf("You have specified debug output, but didn't specify a map to generate.\n");
        printf("This will generate debug output for ALL maps.\n");
        printf("Are you sure you want to continue? (y/n) ");
        if(getchar() != 'y')
            return 0;
    }

    if (!checkDirectories(debugOutput))
        return finish("Press any key to close...", -1);

    MapBuilder builder(maxAngle,
                       skipLiquid,
                       skipContinents,
                       skipJunkMaps,
                       skipBattlegrounds,
                       hiResHeightmaps,
                       debugOutput);

    if (tileX > -1 && tileY > -1 && mapnum >= 0)
        builder.buildTile(mapnum, tileX, tileY);
    else if (mapnum >= 0)
        builder.build(uint32(mapnum));
    else
        builder.buildAll();

    return finish("mMaps Generating is done!", 1);
}

