/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2013 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Instance_ZulGurub
SD%Complete: 80
SDComment: Missing reset function after killing a boss for Ohgan, Thekal.
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

class instance_zulgurub : public InstanceMapScript
{
    public:
        instance_zulgurub()
            : InstanceMapScript("instance_zulgurub", 309) {}

        struct instance_zulgurub_InstanceMapScript : public InstanceScript
        {
            instance_zulgurub_InstanceMapScript(Map* map) : InstanceScript(map) {}

            //If all High Priest bosses were killed. Lorkhan, Zath and Ohgan are added too.
            uint32 Encounter[MAX_ENCOUNTERS];

            //Storing Lorkhan, Zath and Thekal because we need to cast on them later. Jindo is needed for healfunction too.
            uint64 LorKhanGUID;
            uint64 ZathGUID;
            uint64 ThekalGUID;
            uint64 JindoGUID;

            void Initialize()
            {
                memset(&Encounter, 0, sizeof(Encounter));

                LorKhanGUID  = 0;
                ZathGUID     = 0;
                ThekalGUID   = 0;
                JindoGUID    = 0;
            }

            bool IsEncounterInProgress() const
            {
                //not active in Zul'Gurub
                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case 11347: LorKhanGUID = creature->GetGUID(); break;
                    case 11348: ZathGUID    = creature->GetGUID(); break;
                    case 14509: ThekalGUID  = creature->GetGUID(); break;
                    case 11380: JindoGUID   = creature->GetGUID(); break;
                }
            }

            void SetData(uint32 Type, uint32 Data)
            {
                switch (Type)
                {
                    case DATA_ARLOKK:
                        Encounter[0] = Data;
                        break;

                    case DATA_JEKLIK:
                        Encounter[1] = Data;
                        break;

                    case DATA_VENOXIS:
                        Encounter[2] = Data;
                        break;

                    case DATA_MARLI:
                        Encounter[3] = Data;
                        break;

                    case DATA_THEKAL:
                        Encounter[4] = Data;
                        break;

                    case DATA_LORKHAN:
                        Encounter[5] = Data;
                        break;

                    case DATA_ZATH:
                        Encounter[6] = Data;
                        break;

                    case DATA_OHGAN:
                        Encounter[7] = Data;
                        break;
                }
            }

            uint32 GetData(uint32 Type)
            {
                switch (Type)
                {
                    case DATA_ARLOKK:
                        return Encounter[0];
                    case DATA_JEKLIK:
                        return Encounter[1];
                    case DATA_VENOXIS:
                        return Encounter[2];
                    case DATA_MARLI:
                        return Encounter[3];
                    case DATA_THEKAL:
                        return Encounter[4];
                    case DATA_LORKHAN:
                        return Encounter[5];
                    case DATA_ZATH:
                        return Encounter[6];
                    case DATA_OHGAN:
                        return Encounter[7];
                }
                return 0;
            }

            uint64 GetData64(uint32 Data)
            {
                switch (Data)
                {
                    case DATA_LORKHAN:
                        return LorKhanGUID;
                    case DATA_ZATH:
                        return ZathGUID;
                    case DATA_THEKAL:
                        return ThekalGUID;
                    case DATA_JINDO:
                        return JindoGUID;
                }
                return 0;
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_zulgurub_InstanceMapScript(map);
        }
};

void AddSC_instance_zulgurub()
{
    new instance_zulgurub();
}
