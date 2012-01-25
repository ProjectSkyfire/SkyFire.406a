/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */
/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2012 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
 
#ifndef DEF_BLACKWING_LAIR
#define DEF_BLACKWING_LAIR

enum
{
    MAX_ENCOUNTER               = 8,

    TYPE_RAZORGORE              = 0,
    TYPE_VAELASTRASZ            = 1,
    TYPE_LASHLAYER              = 2,
    TYPE_FIREMAW                = 3,
    TYPE_EBONROC                = 4,
    TYPE_FLAMEGOR               = 5,
    TYPE_CHROMAGGUS             = 6,
    TYPE_NEFARIAN               = 7,

    NPC_RAZORGORE               = 12435,
    NPC_VAELASTRASZ             = 13020,
    NPC_LASHLAYER               = 12017,
    NPC_FIREMAW                 = 11983,
    NPC_EBONROC                 = 14601,
    NPC_FLAMEGOR                = 11981,
    NPC_CHROMAGGUS              = 14020,
    NPC_NEFARIAN                = 11583,
    NPC_LORD_NEFARIAN           = 10162,
    NPC_BLACKWING_TECHNICIAN    = 13996,                    // Flees at Vael intro event

    GO_DOOR_RAZORGORE_ENTER     = 176964,
    GO_DOOR_RAZORGORE_EXIT      = 176965,
    GO_DOOR_NEFARIAN            = 176966,
    GO_DOOR_CHROMAGGUS_ENTER    = 179115,
    GO_DOOR_CHROMAGGUS_SIDE     = 179116,
    GO_DOOR_CHROMAGGUS_EXIT     = 179117,
    GO_DOOR_VAELASTRASZ         = 179364,
    GO_DOOR_LASHLAYER           = 179365,
};

// Coords used to spawn Nefarius at the throne
static const float aNefariusSpawnLoc[4] = {-7466.16f, -1040.80f, 412.053f, 2.14675f};

class MANGOS_DLL_DECL instance_blackwing_lair : public ScriptedInstance
{
    public:
        instance_blackwing_lair(Map* pMap);
        ~instance_blackwing_lair() {}

        void Initialize();
        bool IsEncounterInProgress() const;

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);

    protected:
        std::string m_strInstData;
        uint32 m_auiEncounter[MAX_ENCOUNTER];

        GUIDList m_lTechnicianGuids;
};

#endif
