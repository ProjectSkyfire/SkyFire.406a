/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "obsidian_sanctum.h"

#define MAX_ENCOUNTER     1

/* Obsidian Sanctum encounters:
0 - Sartharion
*/

class instance_obsidian_sanctum : public InstanceMapScript
{
public:
    instance_obsidian_sanctum() : InstanceMapScript("instance_obsidian_sanctum", 615) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_obsidian_sanctum_InstanceMapScript(map);
    }

    struct instance_obsidian_sanctum_InstanceMapScript : public InstanceScript
    {
        instance_obsidian_sanctum_InstanceMapScript(Map* map) : InstanceScript(map) {}

        uint32 Encounter[MAX_ENCOUNTER];
        uint64 SartharionGUID;
        uint64 TenebronGUID;
        uint64 ShadronGUID;
        uint64 VesperonGUID;

        bool _bTenebronKilled;
        bool _bShadronKilled;
        bool _bVesperonKilled;

        void Initialize()
        {
            memset(&Encounter, 0, sizeof(Encounter));

            SartharionGUID = 0;
            TenebronGUID   = 0;
            ShadronGUID    = 0;
            VesperonGUID   = 0;

            _bTenebronKilled = false;
            _bShadronKilled = false;
            _bVesperonKilled = false;
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (Encounter[i] == IN_PROGRESS)
                    return true;

            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_SARTHARION:
                    SartharionGUID = creature->GetGUID();
                    break;
                //three dragons below set to active state once created.
                //we must expect bigger raid to encounter main boss, and then three dragons must be active due to grid differences
                case NPC_TENEBRON:
                    TenebronGUID = creature->GetGUID();
                    creature->setActive(true);
                    break;
                case NPC_SHADRON:
                    ShadronGUID = creature->GetGUID();
                    creature->setActive(true);
                    break;
                case NPC_VESPERON:
                    VesperonGUID = creature->GetGUID();
                    creature->setActive(true);
                    break;
            }
        }

        void SetData(uint32 Type, uint32 uiData)
        {
            if (Type == TYPE_SARTHARION_EVENT)
                Encounter[0] = uiData;
            else if (Type == TYPE_TENEBRON_PREKILLED)
                _bTenebronKilled = true;
            else if (Type == TYPE_SHADRON_PREKILLED)
                _bShadronKilled = true;
            else if (Type == TYPE_VESPERON_PREKILLED)
                _bVesperonKilled = true;
        }

        uint32 GetData(uint32 Type)
        {
            if (Type == TYPE_SARTHARION_EVENT)
                return Encounter[0];
            else if (Type == TYPE_TENEBRON_PREKILLED)
                return _bTenebronKilled;
            else if (Type == TYPE_SHADRON_PREKILLED)
                return _bShadronKilled;
            else if (Type == TYPE_VESPERON_PREKILLED)
                return _bVesperonKilled;

            return 0;
        }

        uint64 GetData64(uint32 uiData)
        {
            switch (uiData)
            {
                case DATA_SARTHARION:
                    return SartharionGUID;
                case DATA_TENEBRON:
                    return TenebronGUID;
                case DATA_SHADRON:
                    return ShadronGUID;
                case DATA_VESPERON:
                    return VesperonGUID;
            }
            return 0;
        }
    };
};

void AddSC_instance_obsidian_sanctum()
{
    new instance_obsidian_sanctum();
}
