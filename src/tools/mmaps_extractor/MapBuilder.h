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

#ifndef _MAP_BUILDER_H
#define _MAP_BUILDER_H

#include <vector>
#include <set>
#include <map>

#include "TerrainBuilder.h"
#include "IVMapManager.h"
#include "WorldModel.h"
#include "Recast.h"
#include "DetourNavMesh.h"

using namespace std;
using namespace VMAP;
// G3D namespace typedefs conflicts with ACE typedefs

namespace Pathfinding
{
    typedef map<uint32,set<uint32>*> TileList;

    struct IntermediateValues
    {
        rcHeightfield* heightfield;
        unsigned char* triFlags;
        rcCompactHeightfield* compactHeightfield;
        rcContourSet* contours;
        rcPolyMesh* polyMesh;
        rcPolyMeshDetail* polyMeshDetail;
    };

    class MapBuilder
    {
        public:
            MapBuilder(float maxWalkableAngle   = 60.f,
                       bool skipLiquid          = false,
                       bool skipContinents      = false,
                       bool skipJunkMaps        = true,
                       bool skipBattlegrounds   = true,
                       bool hiResHeightmaps     = true,
                       bool debugOutput         = true);

            ~MapBuilder();

            // builds all mmap tiles for the specified map id (ignores skip settings)
            void build(uint32 mapID);

            // builds an mmap tile for the specified map tile (ignores skip settings)
            void buildTile(uint32 mapID, uint32 tileX, uint32 tileY);

            // builds list of maps, then builds all of mmap tiles (based on the skip settings)
            void buildAll();

        private:
            // detect maps and tiles
            void discoverTiles();
            set<uint32>* getTileList(uint32 mapID);

            // load and unload models
            bool loadVMap(uint32 mapID, uint32 tileX, uint32 tileY, MeshData &meshData);
            void unloadVMap(uint32 mapID, uint32 tileX, uint32 tileY);

            // vert and triangle methods
            void transform(vector<Vector3> original, vector<Vector3> &transformed,
                           float scale, G3D::Matrix3 rotation, Vector3 position);
            void copyVertices(vector<Vector3> source, G3D::Array<float> &dest);
            void copyIndices(vector<MeshTriangle> source, G3D::Array<int> &dest, int offest, bool flip);
            void copyIndices(G3D::Array<int> &dest, G3D::Array<int> src, int offset);
            void cleanVertices(G3D::Array<float> &verts, G3D::Array<int> &tris);

            // move map building
            void buildMoveMap(uint32 mapID);
            void buildNavMesh(uint32 mapID, dtNavMesh* &navMesh);
            void buildMoveMapTile(uint32 mapID,
                                  uint32 tileX,
                                  uint32 tileY,
                                  MeshData meshData,
                                  float* bmin,
                                  float* bmax,
                                  dtNavMesh* navMesh);

            void getTileBounds(uint32 tileX, uint32 tileY,
                               float* verts, int vertCount,
                               float* bmin, float* bmax);

            void initIntermediateValues(IntermediateValues &iv);
            void clearIntermediateValues(IntermediateValues &iv);

            bool shouldSkipMap(uint32 mapID);
            bool isTransportMap(uint32 mapID);

            // debug output
            void generateObjFile(uint32 mapID, uint32 tileX, uint32 tileY, MeshData meshData);
            void generateRealObj(uint32 mapID, uint32 tileX, uint32 tileY, MeshData meshData);
            void writeIV(uint32 mapID, uint32 tileX, uint32 tileY, IntermediateValues iv);
            void debugWrite(FILE* file, const rcHeightfield* hf);
            void debugWrite(FILE* file, const rcSpan* span);
            void debugWrite(FILE* file, const rcCompactHeightfield* chf);
            void debugWrite(FILE* file, const rcContourSet* cs);
            void debugWrite(FILE* file, const rcPolyMesh* mesh);
            void debugWrite(FILE* file, const rcPolyMeshDetail* mesh);

            IVMapManager* m_vmapManager;
            TerrainBuilder* m_terrainBuilder;

            TileList m_tiles;

            bool m_debugOutput;

            bool m_skipContinents;
            bool m_skipJunkMaps;
            bool m_skipBattlegrounds;

            float m_maxWalkableAngle;
    };
}

#endif