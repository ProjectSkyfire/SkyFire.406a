/*
 * Copyright (C) 2010-2011 SkyFire <http://www.projectskyfire.org/>
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
#include "throne_of_the_tides.h"

#define ENCOUNTERS 4

/*Boss Encounters
-----------------
  Lady Naz'jar
  Commander Ulthok
  Erunak Stoneshaper & Mindbender Ghur'sha - TODO: These two will be treated like a single DATA_EVENT
  Ozumat
*/

class instance_throne_of_the_tides : public InstanceMapScript
{
public:
    instance_throne_of_the_tides() : InstanceMapScript("instance_throne_of_the_tides", 643) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_throne_of_the_tides_InstanceMapScript(map);
    }

    struct instance_throne_of_the_tides_InstanceMapScript: public InstanceScript
    {
        instance_throne_of_the_tides_InstanceMapScript(InstanceMap* map): InstanceScript(map) { }

        uint32 uiEncounter[ENCOUNTERS];

        uint64 uiLadyNazjar;
        uint64 uiCommanderUlthok;
        uint64 uiErunakStonespeaker;
        uint64 uiMindbenderGhrusha;
        uint64 uiOzumat;

        void Initialize()
        {
            uiLadyNazjar = 0;
            uiCommanderUlthok = 0;
            uiErunakStonespeaker = 0;
            uiMindbenderGhrusha = 0;
            uiOzumat = 0;

            for(uint8 i=0; i < ENCOUNTERS; ++i)
                uiEncounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i=0; i < ENCOUNTERS; ++i)
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
                 case BOSS_LADY_NAZJAR:
                     uiLadyNazjar = pCreature->GetGUID();
                     break;
                 case BOSS_COMMANDER_ULTHOK:
                     uiCommanderUlthok = pCreature->GetGUID();
                     break;
                 case BOSS_ERUNAK_STONESPEAKER:
                     uiErunakStonespeaker = pCreature->GetGUID();
                     break;
                 case BOSS_MINDBENDER_GHURSHA:
                     uiMindbenderGhrusha = pCreature->GetGUID();
                     break;
                 case BOSS_OZUMAT:
                     uiOzumat = pCreature->GetGUID();
                     break;
            }
        }

        uint64 getData64(uint32 identifier)
        {
            switch(identifier)
            {
                case DATA_LADY_NAZJAR:
                    return uiLadyNazjar;
                case DATA_COMMANDER_ULTHOK:
                    return uiCommanderUlthok;
                case DATA_ERUNAK_STONESPEAKER:
                    return uiErunakStonespeaker;
                case DATA_MINDBENDER_GHURSHA:
                    return uiMindbenderGhrusha;
                case DATA_OZUMAT:
                    return uiOzumat;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
                case DATA_LADY_NAZJAR:
                    uiEncounter[0] = data;
                    break;
                case DATA_COMMANDER_ULTHOK:
                    uiEncounter[1] = data;
                    break;
                case DATA_ERUNAK_STONESPEAKER:
                    uiEncounter[2] = data;
                    break;
                case DATA_MINDBENDER_GHURSHA:
                    uiEncounter[3] = data;
                    break;
                case DATA_OZUMAT:
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
                case DATA_LADY_NAZJAR_EVENT:
                    return uiEncounter[0];
                case DATA_COMMANDER_ULTHOK_EVENT:
                    return uiEncounter[1];
                case DATA_ERUNAK_STONESPEAKER_EVENT:
                    return uiEncounter[2];
                case DATA_MINDBENDER_GHURSHA_EVENT:
                    return uiEncounter[3];
                case DATA_OZUMAT_EVENT:
                    return uiEncounter[4];
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "T H" << uiEncounter[0] << " " << uiEncounter[1]  << " " << uiEncounter[2]  << " " << uiEncounter[3] << " " << uiEncounter[4];
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

            if (dataHead1 == 'T' && dataHead2 == 'H')
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

void AddSC_instance_throne_of_the_tides()
{
    new instance_throne_of_the_tides();
}