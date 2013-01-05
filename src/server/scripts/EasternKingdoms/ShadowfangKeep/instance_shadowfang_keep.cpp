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
SDName: Instance_Shadowfang_Keep
SD%Complete: 90
SDComment:
SDCategory: Shadowfang Keep
EndScriptData */

#include "ScriptPCH.h"
#include "shadowfang_keep.h"

#define MAX_ENCOUNTER              4

enum eEnums
{
    SAY_BOSS_DIE_AD         = -1033007,
    SAY_BOSS_DIE_AS         = -1033008,
    SAY_ARCHMAGE            = -1033009,

    NPC_ASH                 = 3850,
    NPC_ADA                 = 3849,
    NPC_ARCHMAGE_ARUGAL     = 4275,
    NPC_ARUGAL_VOIDWALKER   = 4627,

    GO_COURTYARD_DOOR       = 18895,                        //door to open when talking to NPC's
    GO_SORCERER_DOOR        = 18972,                        //door to open when Fenrus the Devourer
    GO_ARUGAL_DOOR          = 18971,                        //door to open when Wolf Master Nandos

    SPELL_ASHCROMBE_TELEPORT    = 15742
};

const Position SpawnLocation[] =
{
    {-148.199f, 2165.647f, 128.448f, 1.026f},
    {-153.110f, 2168.620f, 128.448f, 1.026f},
    {-145.905f, 2180.520f, 128.448f, 4.183f},
    {-140.794f, 2178.037f, 128.448f, 4.090f},
    {-138.640f, 2170.159f, 136.577f, 2.737f}
};
class instance_shadowfang_keep : public InstanceMapScript
{
public:
    instance_shadowfang_keep() : InstanceMapScript("instance_shadowfang_keep", 33) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_shadowfang_keep_InstanceMapScript(map);
    }

    struct instance_shadowfang_keep_InstanceMapScript : public InstanceScript
    {
        instance_shadowfang_keep_InstanceMapScript(Map* map) : InstanceScript(map) {}

        uint32 Encounter[MAX_ENCOUNTER];
        std::string str_data;

        uint64 AshGUID;
        uint64 AdaGUID;
        uint64 ArchmageArugalGUID;

        uint64 DoorCourtyardGUID;
        uint64 DoorSorcererGUID;
        uint64 DoorArugalGUID;

        uint8 Phase;
        uint16 Timer;

        void Initialize()
        {
            memset(&Encounter, 0, sizeof(Encounter));

            AshGUID = 0;
            AdaGUID = 0;
            ArchmageArugalGUID = 0;

            DoorCourtyardGUID = 0;
            DoorSorcererGUID = 0;
            DoorArugalGUID = 0;

            Phase = 0;
            Timer = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_ASH: AshGUID = creature->GetGUID(); break;
                case NPC_ADA: AdaGUID = creature->GetGUID(); break;
                case NPC_ARCHMAGE_ARUGAL: ArchmageArugalGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_COURTYARD_DOOR:
                    DoorCourtyardGUID = go->GetGUID();
                    if (Encounter[0] == DONE)
                        HandleGameObject(0, true, go);
                    break;
                case GO_SORCERER_DOOR:
                    DoorSorcererGUID = go->GetGUID();
                    if (Encounter[2] == DONE)
                        HandleGameObject(0, true, go);
                    break;
                case GO_ARUGAL_DOOR:
                    DoorArugalGUID = go->GetGUID();
                    if (Encounter[3] == DONE)
                        HandleGameObject(0, true, go);
                    break;
            }
        }

        void DoSpeech()
        {
            Creature* ada = instance->GetCreature(AdaGUID);
            Creature* ash = instance->GetCreature(AshGUID);

            if (ada && ada->isAlive() && ash && ash->isAlive())
            {
                DoScriptText(SAY_BOSS_DIE_AD, ada);
                DoScriptText(SAY_BOSS_DIE_AS, ash);
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case TYPE_FREE_NPC:
                    if (data == DONE)
                        DoUseDoorOrButton(DoorCourtyardGUID);
                    Encounter[0] = data;
                    break;
                case TYPE_RETHILGORE:
                    if (data == DONE)
                        DoSpeech();
                    Encounter[1] = data;
                    break;
                case TYPE_FENRUS:
                    switch (data)
                    {
                        case DONE:
                            Timer = 1000;
                            Phase = 1;
                            break;
                        case 7:
                            DoUseDoorOrButton(DoorSorcererGUID);
                            break;
                    }
                    Encounter[2] = data;
                    break;
                case TYPE_NANDOS:
                    if (data == DONE)
                        DoUseDoorOrButton(DoorArugalGUID);
                    Encounter[3] = data;
                    break;
            }

            if (data == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << Encounter[0] << ' ' << Encounter[1] << ' ' << Encounter[2] << ' ' << Encounter[3];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type)
        {
            switch (type)
            {
                case TYPE_FREE_NPC:
                    return Encounter[0];
                case TYPE_RETHILGORE:
                    return Encounter[1];
                case TYPE_FENRUS:
                    return Encounter[2];
                case TYPE_NANDOS:
                    return Encounter[3];
            }
            return 0;
        }

        std::string GetSaveData()
        {
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

            std::istringstream loadStream(in);
            loadStream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3];

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (Encounter[i] == IN_PROGRESS)
                    Encounter[i] = NOT_STARTED;
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void Update(uint32 Diff)
        {
            if (GetData(TYPE_FENRUS) != DONE)
                return;

            Creature* archmage = instance->GetCreature(ArchmageArugalGUID);
            Creature* summon = NULL;

            if (!archmage || !archmage->isAlive())
                return;

            if (Phase)
            {
                if (Timer <= Diff)
                {
                    switch (Phase)
                    {
                        case 1:
                            summon = archmage->SummonCreature(archmage->GetEntry(), SpawnLocation[4], TEMPSUMMON_TIMED_DESPAWN, 10000);
                            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            summon->SetReactState(REACT_DEFENSIVE);
                            summon->CastSpell(summon, SPELL_ASHCROMBE_TELEPORT, true);
                            DoScriptText(SAY_ARCHMAGE, summon);
                            Timer = 2000;
                            Phase = 2;
                            break;
                        case 2:
                            archmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[0], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            archmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            archmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[2], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            archmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            Phase = 0;
                            break;
                    }
                } else Timer -= Diff;
            }
        }
    };
};

void AddSC_instance_shadowfang_keep()
{
    new instance_shadowfang_keep();
}
