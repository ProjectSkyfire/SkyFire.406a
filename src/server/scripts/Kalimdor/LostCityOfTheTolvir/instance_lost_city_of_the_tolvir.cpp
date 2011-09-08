/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
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

#include "ScriptPCH.h"
#include "lost_city_of_the_tolvir.h"

#define ENCOUNTERS 5

/* Boss Encounters
   General Husam
   High Prophet Barim
   Lockmaw
   Augh
   Siamat
 */

class instance_lost_city_of_the_tolvir : public InstanceMapScript
{
public:
    instance_lost_city_of_the_tolvir() : InstanceMapScript("instance_lost_city_of_the_tolvir", 755) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_lost_city_of_the_tolvir_InstanceMapScript(map);
    }

    struct instance_lost_city_of_the_tolvir_InstanceMapScript: public InstanceScript
    {
        instance_lost_city_of_the_tolvir_InstanceMapScript(InstanceMap* map) : InstanceScript(map) {}

        uint32 uiEncounter[ENCOUNTERS];

        uint64 uiGeneralHusam;
        uint64 uiHighProphetBarim;
        uint64 uiLockmaw;
        uint64 uiAugh;
        uint64 uiSiamat;
        uint64 uiTeamInInstance;

        void Initialize()
        {
            uiGeneralHusam = 0;
            uiHighProphetBarim = 0;
            uiLockmaw = 0;
            uiAugh = 0;
            uiSiamat = 0;

            for(uint8 i=0 ; i<ENCOUNTERS; ++i)
                uiEncounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i=0; i<ENCOUNTERS; ++i)
            {
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;
            }
            return false;
        }

        void OnCreatureCreate(Creature* pCreature, bool )
        {
            switch(pCreature->GetEntry())
            {
                 case BOSS_GENERAL_HUSAM:
                     uiGeneralHusam = pCreature->GetGUID();
                     break;
                 case BOSS_HIGH_PROPHET_BARIM:
                     uiHighProphetBarim = pCreature->GetGUID();
                     break;
                 case BOSS_LOCKMAW:
                     uiLockmaw = pCreature->GetGUID();
                     break;
                 case BOSS_AUGH:
                     uiAugh = pCreature->GetGUID();
                     break;
                 case BOSS_SIAMAT:
                     uiSiamat = pCreature->GetGUID();
                     break;
            }
        }

        uint64 getData64(uint32 identifier)
        {
            switch(identifier)
            {
                case DATA_GENERAL_HUSAM:
                    return uiGeneralHusam;
                case DATA_HIGH_PROPHET_BARIM:
                    return uiHighProphetBarim;
                case DATA_LOCKMAW:
                    return uiLockmaw;
                case DATA_AUGH:
                    return uiAugh;
                case DATA_SIAMAT:
                    return uiSiamat;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
                case DATA_GENERAL_HUSAM_EVENT:
                    uiEncounter[0] = data;
                    break;
                case DATA_HIGH_PROPHET_BARIM_EVENT:
                    uiEncounter[1] = data;
                    break;
                case DATA_LOCKMAW_EVENT:
                    uiEncounter[2] = data;
                    break;
                case DATA_AUGH_EVENT:
                    uiEncounter[3] = data;
                    break;
                case DATA_SIAMAT_EVENT:
                    uiEncounter[4] = data;
                    break;
            }

           if (data == DONE)
               SaveToDB();
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case DATA_GENERAL_HUSAM_EVENT:
                    return uiEncounter[0];
                case DATA_HIGH_PROPHET_BARIM_EVENT:
                    return uiEncounter[1];
                case DATA_LOCKMAW_EVENT:
                    return uiEncounter[2];
                case DATA_AUGH_EVENT:
                    return uiEncounter[3];
                case DATA_SIAMAT_EVENT:
                    return uiEncounter[4];
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "L V" << uiEncounter[0] << " " << uiEncounter[1]  << " " << uiEncounter[2]  << " " << uiEncounter[3] << " " << uiEncounter[4];
            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;
            uint16 data0, data1, data2, data3, data4;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4;

            if (dataHead1 == 'L' && dataHead2 == 'V')
            {
                uiEncounter[0] = data0;
                uiEncounter[1] = data1;
                uiEncounter[2] = data2;
                uiEncounter[3] = data3;
                uiEncounter[4] = data4;

                for(uint8 i=0; i<ENCOUNTERS; ++i)
                    if (uiEncounter[i] == IN_PROGRESS)
                        uiEncounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_lost_city_of_the_tolvir()
{
    new instance_lost_city_of_the_tolvir();
}