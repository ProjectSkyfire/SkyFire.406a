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

#include <sstream>

#include "TerrainBuilder.h"
#include "Map.h"

static char const* MAP_VERSION_MAGIC = "v1.2";

namespace Pathfinding
{
    TerrainBuilder::TerrainBuilder(bool skipLiquid, bool hiRes) :
        m_hiResHeightMaps   (hiRes),
        m_skipLiquid        (skipLiquid)
    {
    }

    TerrainBuilder::~TerrainBuilder()
    {
    }

    void TerrainBuilder::getLoopVars(Spot portion, int &loopStart, int &loopEnd, int &loopInc)
    {
        switch(portion)
        {
            case ENTIRE:
                loopStart = 0;
                loopEnd = V8_SIZE_SQ;
                loopInc = 1;
                break;
            case TOP:
                loopStart = 0;
                loopEnd = V8_SIZE;
                loopInc = 1;
                break;
            case LEFT:
                loopStart = 0;
                loopEnd = V8_SIZE_SQ - V8_SIZE + 1;
                loopInc = V8_SIZE;
                break;
            case RIGHT:
                loopStart = V8_SIZE - 1;
                loopEnd = V8_SIZE_SQ;
                loopInc = V8_SIZE;
                break;
            case BOTTOM:
                loopStart = V8_SIZE_SQ - V8_SIZE;
                loopEnd = V8_SIZE_SQ;
                loopInc = 1;
                break;
        }
    }

    void TerrainBuilder::loadMap(uint32 mapID, uint32 tileX, uint32 tileY, MeshData &meshData)
    {
        if (loadMap(mapID, tileX, tileY, meshData, ENTIRE))
        {
            loadMap(mapID, tileX+1, tileY, meshData, LEFT);
            loadMap(mapID, tileX-1, tileY, meshData, RIGHT);
            loadMap(mapID, tileX, tileY+1, meshData, TOP);
            loadMap(mapID, tileX, tileY-1, meshData, BOTTOM);
        }
    }

    bool TerrainBuilder::loadMap(uint32 mapID, uint32 tileX, uint32 tileY, MeshData &meshData, Spot portion)
    {
        char mapFileName[255];
        sprintf(mapFileName, "maps/%03u%02u%02u.map", mapID, tileY, tileX);

        FILE* mapFile = fopen(mapFileName, "rb");
        if (!mapFile)
            return false;

        map_fileheader fheader;
        fread(&fheader, sizeof(map_fileheader), 1, mapFile);

        if (fheader.versionMagic != *((uint32 const*)(MAP_VERSION_MAGIC)))
        {
            fclose(mapFile);
            printf("%s is the wrong version, please extract new .map files\n", mapFileName);
            return false;
        }

        map_heightHeader hheader;
        fseek(mapFile, fheader.heightMapOffset, SEEK_SET);
        fread(&hheader, sizeof(map_heightHeader), 1, mapFile);

        bool haveTerrain = !(hheader.flags & MAP_HEIGHT_NO_HEIGHT);
        bool haveLiquid = fheader.liquidMapOffset && !m_skipLiquid;

        // no data in this map file
        if (!haveTerrain && !haveLiquid)
        {
            fclose(mapFile);
            return false;
        }

        // data used later
        uint16 holes[16][16];
        memset(holes, 0, sizeof(holes));
        uint8 liquid_type[16][16];
        memset(liquid_type, 0, sizeof(liquid_type));

        G3D::Array<int> ltriangles;
        G3D::Array<int> ttriangles;

        // terrain data
        if (haveTerrain)
        {
            int i;
            float heightMultiplier;
            float V9[V9_SIZE_SQ], V8[V8_SIZE_SQ];

            if (hheader.flags & MAP_HEIGHT_AS_INT8)
            {
                uint8 v9[V9_SIZE_SQ];
                uint8 v8[V8_SIZE_SQ];
                fread(v9, sizeof(uint8), V9_SIZE_SQ, mapFile);
                fread(v8, sizeof(uint8), V8_SIZE_SQ, mapFile);
                heightMultiplier = (hheader.gridMaxHeight - hheader.gridHeight) / 255;

                for (i = 0; i < V9_SIZE_SQ; ++i)
                    V9[i] = (float)v9[i]*heightMultiplier + hheader.gridHeight;

                if (m_hiResHeightMaps)
                    for (i = 0; i < V8_SIZE_SQ; ++i)
                        V8[i] = (float)v8[i]*heightMultiplier + hheader.gridHeight;
            }
            else if (hheader.flags & MAP_HEIGHT_AS_INT16)
            {
                uint16 v9[V9_SIZE_SQ];
                uint16 v8[V8_SIZE_SQ];
                fread(v9, sizeof(uint16), V9_SIZE_SQ, mapFile);
                fread(v8, sizeof(uint16), V8_SIZE_SQ, mapFile);
                heightMultiplier = (hheader.gridMaxHeight - hheader.gridHeight) / 65535;

                for (i = 0; i < V9_SIZE_SQ; ++i)
                    V9[i] = (float)v9[i]*heightMultiplier + hheader.gridHeight;

                if (m_hiResHeightMaps)
                    for (i = 0; i < V8_SIZE_SQ; ++i)
                        V8[i] = (float)v8[i]*heightMultiplier + hheader.gridHeight;
            }
            else
            {
                fread(V9, sizeof(float), V9_SIZE_SQ, mapFile);
                if (m_hiResHeightMaps)
                    fread(V8, sizeof(float), V8_SIZE_SQ, mapFile);
            }

            // hole data
            memset(holes, 0, sizeof(fheader.holesSize));
            fseek(mapFile, fheader.holesOffset, SEEK_SET);
            fread(holes, fheader.holesSize, 1, mapFile);

            int count = meshData.solidVerts.size() / 3;
            float xoffset = (float(tileX)-32)*GRID_SIZE;
            float yoffset = (float(tileY)-32)*GRID_SIZE;

            float coord[3];

            for (i = 0; i < V9_SIZE_SQ; ++i)
            {
                getHeightCoord(i, GRID_V9, xoffset, yoffset, coord, V9);
                meshData.solidVerts.append(coord[0]);
                meshData.solidVerts.append(coord[2]);
                meshData.solidVerts.append(coord[1]);
            }

            if (m_hiResHeightMaps)
                for (i = 0; i < V8_SIZE_SQ; ++i)
                {
                    getHeightCoord(i, GRID_V8, xoffset, yoffset, coord, V8);
                    meshData.solidVerts.append(coord[0]);
                    meshData.solidVerts.append(coord[2]);
                    meshData.solidVerts.append(coord[1]);
                }

            int triInc, j, indices[3], loopStart, loopEnd, loopInc;
            getLoopVars(portion, loopStart, loopEnd, loopInc);

            triInc = m_hiResHeightMaps ? 1 : BOTTOM-TOP;

            for (i = loopStart; i < loopEnd; i+=loopInc)
                    for (j = TOP; j <= BOTTOM; j+=triInc)
                    {
                        getHeightTriangle(i, Spot(j), indices);
                        ttriangles.append(indices[2] + count);
                        ttriangles.append(indices[1] + count);
                        ttriangles.append(indices[0] + count);
                    }
        }

        // liquid data
        if (haveLiquid)
        {
            do
            {
                map_liquidHeader lheader;
                fseek(mapFile, fheader.liquidMapOffset, SEEK_SET);
                fread(&lheader, sizeof(map_liquidHeader), 1, mapFile);

                float* liquid_map = 0;

                if (!(lheader.flags & MAP_LIQUID_NO_TYPE))
                    fread(liquid_type, sizeof(liquid_type), 1, mapFile);

                if (!(lheader.flags & MAP_LIQUID_NO_HEIGHT))
                {
                    liquid_map = new float [lheader.width*lheader.height];
                    fread(liquid_map, sizeof(float), lheader.width*lheader.height, mapFile);
                }

                if (!liquid_type && !liquid_map)
                    break;

                int count = meshData.liquidVerts.size() / 3;
                float xoffset = (float(tileX)-32)*GRID_SIZE;
                float yoffset = (float(tileY)-32)*GRID_SIZE;

                float coord[3];
                int row, col;

                // generate coordinates
                if (!(lheader.flags & MAP_LIQUID_NO_HEIGHT))
                {
                    int j = 0;
                    for (int i = 0; i < V9_SIZE_SQ; ++i)
                    {
                        row = i / V9_SIZE;
                        col = i % V9_SIZE;
                        if ((row < (lheader.offsetY) || row >= (lheader.offsetY + lheader.height)) ||
                           (col < (lheader.offsetX) || col >= (lheader.offsetX + lheader.width)))
                        {
                            // dummy vert using invalid height
                            meshData.liquidVerts.append((xoffset+col*GRID_PART_SIZE)*-1, INVALID_MAP_LIQ_HEIGHT, (yoffset+row*GRID_PART_SIZE)*-1);
                            continue;
                        }

                        getLiquidCoord(i, j, xoffset, yoffset, coord, liquid_map);
                        meshData.liquidVerts.append(coord[0]);
                        meshData.liquidVerts.append(coord[2]);
                        meshData.liquidVerts.append(coord[1]);
                        j++;
                    }
                }
                else
                {
                    for (int i = 0; i < V9_SIZE_SQ; ++i)
                    {
                        row = i / V9_SIZE;
                        col = i % V9_SIZE;
                        meshData.liquidVerts.append((xoffset+col*GRID_PART_SIZE)*-1, lheader.liquidLevel, (yoffset+row*GRID_PART_SIZE)*-1);
                    }
                }

                delete [] liquid_map;

                int indices[3], loopStart, loopEnd, loopInc, triInc;
                getLoopVars(portion, loopStart, loopEnd, loopInc);
                triInc = BOTTOM-TOP;

                // generate triangles
                for (int i = loopStart; i < loopEnd; i+=loopInc)
                    for (int j = TOP; j <= BOTTOM; j+= triInc)
                    {
                        getHeightTriangle(i, Spot(j), indices, true);
                        ltriangles.append(indices[2] + count);
                        ltriangles.append(indices[1] + count);
                        ltriangles.append(indices[0] + count);
                    }
            }while(0);
        }

        fclose(mapFile);

        // now that we have gathered the data, we can figure out which parts to keep:
        // liquid above ground
        // ground above any liquid type
        // ground below <1.5 yard of water

        int loopStart, loopEnd, loopInc, tTriCount;
        bool useTerrain, useLiquid;

        float* lverts = meshData.liquidVerts.getCArray();
        float* tverts = meshData.solidVerts.getCArray();
        int* ltris = ltriangles.getCArray();
        int* ttris = ttriangles.getCArray();

        getLoopVars(portion, loopStart, loopEnd, loopInc);
        tTriCount = m_hiResHeightMaps ? 4 : 2;

        if (ltriangles.size() || ttriangles.size())
        {
            for (int i = loopStart; i < loopEnd; i+=loopInc)
            {
                for (int j = 0; j < 2; ++j)
                {
                    // default is true, will change to false if needed
                    useTerrain = true;
                    useLiquid = true;
                    uint8 liquidType;

                    // if there is no liquid, don't use liquid
                    if (!liquid_type ||
                       !meshData.liquidVerts.size() ||
                       !ltriangles.size())
                        useLiquid = false;
                    else
                    {
                        liquidType = getLiquidType(i, liquid_type);
                        switch(liquidType)
                        {
                            default:
                                useLiquid = false;
                                break;
                            case MAP_LIQUID_TYPE_WATER:
                            case MAP_LIQUID_TYPE_OCEAN:
                                // merge different types of water
                                liquidType = NAV_WATER;
                                break;
                            case MAP_LIQUID_TYPE_MAGMA:
                                liquidType = NAV_MAGMA;
                                break;
                            case MAP_LIQUID_TYPE_SLIME:
                                liquidType = NAV_SLIME;
                                break;
                            case MAP_LIQUID_TYPE_DARK_WATER:
                                // players should not be here, so logically neither should creatures
                                useTerrain = false;
                                useLiquid = false;
                                break;
                        }
                    }

                    // if there is no terrain, don't use terrain
                    if (!ttriangles.size())
                        useTerrain = false;

                    // liquid is rendered as quads.  If any triangle has invalid height,
                    // don't render any of the triangles in that quad
                    if (useLiquid)
                        if((&lverts[ltris[0]*3])[1] == INVALID_MAP_LIQ_HEIGHT ||
                           (&lverts[ltris[1]*3])[1] == INVALID_MAP_LIQ_HEIGHT ||
                           (&lverts[ltris[2]*3])[1] == INVALID_MAP_LIQ_HEIGHT)
                        {
                            useLiquid = false;
                        }

                    // if there is a hole here, don't use the terrain
                    if (useTerrain)
                        useTerrain = !isHole(i, holes);

                    if (useTerrain && useLiquid)
                    {
                        // get the indexes of the corners of the quad
                        int idx1, idx2, idx3;
                        if (j == 0)
                        {
                            idx1 = 0;
                            idx2 = 1;
                            idx3 = tTriCount;   // accesses index from next triangle on low res
                        }
                        else
                        {
                            idx1 = 0;
                            idx2 = 3*tTriCount/2-2;
                            idx3 = 3*tTriCount/2-1;
                        }

                        if (useTerrain &&
                            (&lverts[ltris[0]*3])[1] - 1.5f > (&tverts[ttris[idx1]*3])[1] &&
                            (&lverts[ltris[1]*3])[1] - 1.5f > (&tverts[ttris[idx2]*3])[1] &&
                            (&lverts[ltris[2]*3])[1] - 1.5f > (&tverts[ttris[idx3]*3])[1])
                            useTerrain = false; // if the whole terrain triangle is 1.5yds under liquid, don't use it
                        else if (useLiquid &&
                                (&lverts[ltris[0]*3])[1] < (&tverts[ttris[idx1]*3])[1] &&
                                (&lverts[ltris[1]*3])[1] < (&tverts[ttris[idx2]*3])[1] &&
                                (&lverts[ltris[2]*3])[1] < (&tverts[ttris[idx3]*3])[1])
                            useLiquid = false;  // if the whole liquid triangle is under terrain, don't use it
                    }

                    if (useLiquid)
                    {
                        meshData.liquidType.append(liquidType);
                        for(int k = 0; k < 3; ++k)
                            meshData.liquidTris.append(ltris[k]);
                    }

                    if (useTerrain)
                        for(int k = 0; k < 3*tTriCount/2; ++k)
                            meshData.solidTris.append(ttris[k]);

                    // advance to next set of triangles
                    ltris += 3;
                    ttris += 3*tTriCount/2;
                }
            }
        }

        return meshData.solidTris.size() || meshData.liquidTris.size();
    }

    void TerrainBuilder::getHeightCoord(int index, Grid grid, float xOffset, float yOffset, float* coord, float* v)
    {
        // wow coords: x, y, height
        // coord is mirroed about the horizontal axes
        switch(grid)
        {
            case GRID_V9:
                coord[0] = (xOffset + index%(V9_SIZE)*GRID_PART_SIZE) * -1.f;
                coord[1] = (yOffset + (int)(index/(V9_SIZE))*GRID_PART_SIZE) * -1.f;
                coord[2] = v[index];
                break;
            case GRID_V8:
                coord[0] = (xOffset + index%(V8_SIZE)*GRID_PART_SIZE + GRID_PART_SIZE/2.f) * -1.f;
                coord[1] = (yOffset + (int)(index/(V8_SIZE))*GRID_PART_SIZE + GRID_PART_SIZE/2.f) * -1.f;
                coord[2] = v[index];
                break;
        }
    }

    void TerrainBuilder::getHeightTriangle(int square, Spot triangle, int* indices, bool liquid/* = false*/)
    {
        int rowOffset = square/V8_SIZE;
        if (m_hiResHeightMaps && !liquid)
            switch(triangle)
            {
                case TOP:
                    indices[0] = square+rowOffset;                  //           0-----1 .... 128
                    indices[1] = square+1+rowOffset;                //           |\ T /|
                    indices[2] = (V9_SIZE_SQ)+square;               //           | \ / |
                    break;                                          //           |L 0 R| .. 127
                case LEFT:                                          //           | / \ |
                    indices[0] = square+rowOffset;                  //           |/ B \|
                    indices[1] = (V9_SIZE_SQ)+square;               //          129---130 ... 386
                    indices[2] = square+V9_SIZE+rowOffset;          //           |\   /|
                    break;                                          //           | \ / |
                case RIGHT:                                         //           | 128 | .. 255
                    indices[0] = square+1+rowOffset;                //           | / \ |
                    indices[1] = square+V9_SIZE+1+rowOffset;        //           |/   \|
                    indices[2] = (V9_SIZE_SQ)+square;               //          258---259 ... 515
                    break;
                case BOTTOM:
                    indices[0] = (V9_SIZE_SQ)+square;
                    indices[1] = square+V9_SIZE+1+rowOffset;
                    indices[2] = square+V9_SIZE+rowOffset;
                    break;
                default: break;
            }
        else
            switch(triangle)
            {                                                           //           0-----1 .... 128
                case TOP:                                               //           |\    |
                    indices[0] = square+rowOffset;                      //           | \ T |
                    indices[1] = square+1+rowOffset;                    //           |  \  |
                    indices[2] = square+V9_SIZE+1+rowOffset;            //           | B \ |
                    break;                                              //           |    \|
                case BOTTOM:                                            //          129---130 ... 386
                    indices[0] = square+rowOffset;                      //           |\    |
                    indices[1] = square+V9_SIZE+1+rowOffset;            //           | \   |
                    indices[2] = square+V9_SIZE+rowOffset;              //           |  \  |
                    break;                                              //           |   \ |
                default: break;
            }                                                           //           |    \|
                                                                        //          258---259 ... 515
    }

    void TerrainBuilder::getLiquidCoord(int index, int index2, float xOffset, float yOffset, float* coord, float* v)
    {
        // wow coords: x, y, height
        // coord is mirroed about the horizontal axes
        coord[0] = (xOffset + index%(V9_SIZE)*GRID_PART_SIZE) * -1.f;
        coord[1] = (yOffset + (int)(index/(V9_SIZE))*GRID_PART_SIZE) * -1.f;
        coord[2] = v[index2];
    }

    static uint16 holetab_h[4] = {0x1111, 0x2222, 0x4444, 0x8888};
    static uint16 holetab_v[4] = {0x000F, 0x00F0, 0x0F00, 0xF000};

    bool TerrainBuilder::isHole(int square, const uint16 holes[16][16])
    {
        int row = square / 128;
        int col = square % 128;
        int cellRow = row / 8;     // 8 squares per cell
        int cellCol = col / 8;
        int holeRow = row % 8 / 2;
        int holeCol = (square - (row * 128 + cellCol * 8)) / 2;

        uint16 hole = holes[cellRow][cellCol];
        return (hole & holetab_h[holeCol] & holetab_v[holeRow]) != 0;
    }

    uint8 TerrainBuilder::getLiquidType(int square, const uint8 liquid_type[16][16])
    {
        int row = square / 128;
        int col = square % 128;
        int cellRow = row / 8;     // 8 squares per cell
        int cellCol = col / 8;

        return liquid_type[cellRow][cellCol];
    }
}