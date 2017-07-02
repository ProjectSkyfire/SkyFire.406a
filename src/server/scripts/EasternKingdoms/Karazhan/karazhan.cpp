/*
 * Copyright (C) 2011-2017 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2014 ScriptDev2 <https://github.com/scriptdev2/scriptdev2/>
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
SDName: Karazhan
SD%Complete: 100
SDComment: Support for Barnes (Opera controller) and Berthold (Doorman), Support for Quest 9645.
SDCategory: Karazhan
EndScriptData */

/* ContentData
npc_barnes
npc_berthold
npc_image_of_medivh
EndContentData */

#include "ScriptPCH.h"
#include "karazhan.h"
#include "ScriptedEscortAI.h"

/*######
# npc_barnesAI
######*/

#define GOSSIP_READY        "I'm not an actor."

#define SAY_READY           "Splendid, I'm going to get the audience ready. Break a leg!"
#define SAY_OZ_INTRO1       "Finally, everything is in place. Are you ready for your big stage debut?"
#define OZ_GOSSIP1          "I'm not an actor."
#define SAY_OZ_INTRO2       "Don't worry, you'll be fine. You look like a natural!"
#define OZ_GOSSIP2          "Ok, I'll give it a try, then."

#define SAY_RAJ_INTRO1      "The romantic plays are really tough, but you'll do better this time. You have TALENT. Ready?"
#define RAJ_GOSSIP1         "I've never been more ready."

#define OZ_GM_GOSSIP1       "[GM] Change event to EVENT_OZ"
#define OZ_GM_GOSSIP2       "[GM] Change event to EVENT_HOOD"
#define OZ_GM_GOSSIP3       "[GM] Change event to EVENT_RAJ"

struct Dialogue
{
    int32 textid;
    uint32 timer;
};

static Dialogue OzDialogue[]=
{
    {-1532103, 6000},
    {-1532104, 18000},
    {-1532105, 9000},
    {-1532106, 15000}
};

static Dialogue HoodDialogue[]=
{
    {-1532107, 6000},
    {-1532108, 10000},
    {-1532109, 14000},
    {-1532110, 15000}
};

static Dialogue RAJDialogue[]=
{
    {-1532111, 5000},
    {-1532112, 7000},
    {-1532113, 14000},
    {-1532114, 14000}
};

// Entries and spawn locations for creatures in Oz event
float Spawns[6][2]=
{
    {17535, -10896},                                       // Dorothee
    {17546, -10891},                                       // Roar
    {17547, -10884},                                       // Tinhead
    {17543, -10902},                                       // Strawman
    {17603, -10892},                                       // Grandmother
    {17534, -10900},                                       // Julianne
};

#define CREATURE_SPOTLIGHT  19525

#define SPELL_SPOTLIGHT     25824
#define SPELL_TUXEDO        32616

#define SPAWN_Z             90.5f
#define SPAWN_Y             -1758
#define SPAWN_O             4.738f

class npc_barnes : public CreatureScript
{
public:
    npc_barnes() : CreatureScript("npc_barnes") { }

    struct npc_barnesAI : public npc_escortAI
    {
        npc_barnesAI(Creature* creature) : npc_escortAI(creature)
        {
            RaidWiped = false;
            EventId = 0;
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint64 SpotlightGUID;

        uint32 TalkCount;
        uint32 TalkTimer;
        uint32 WipeTimer;
        uint32 EventId;

        bool PerformanceReady;
        bool RaidWiped;

        void Reset()
        {
            SpotlightGUID = 0;

            TalkCount = 0;
            TalkTimer = 2000;
            WipeTimer = 5000;

            PerformanceReady = false;

            if (instance)
                EventId = instance->GetData(DATA_OPERA_PERFORMANCE);
        }

        void StartEvent()
        {
            if (!instance)
                return;

            instance->SetData(TYPE_OPERA, IN_PROGRESS);

            //resets count for this event, in case earlier failed
            if (EventId == EVENT_OZ)
                instance->SetData(DATA_OPERA_OZ_DEATHCOUNT, IN_PROGRESS);

            Start(false, false);
        }

        void EnterCombat(Unit* /*who*/) {}

        void WaypointReached(uint32 i)
        {
            if (!instance)
                return;

            switch (i)
            {
                case 0:
                    DoCast(me, SPELL_TUXEDO, false);
                    instance->DoUseDoorOrButton(instance->GetData64(DATA_GO_STAGEDOORLEFT));
                    break;
                case 4:
                    TalkCount = 0;
                    SetEscortPaused(true);

                    if (Creature* spotlight = me->SummonCreature(CREATURE_SPOTLIGHT,
                        me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f,
                        TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                    {
                        spotlight->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        spotlight->CastSpell(spotlight, SPELL_SPOTLIGHT, false);
                        SpotlightGUID = spotlight->GetGUID();
                    }
                    break;
                case 8:
                    instance->DoUseDoorOrButton(instance->GetData64(DATA_GO_STAGEDOORLEFT));
                    PerformanceReady = true;
                    break;
                case 9:
                    PrepareEncounter();
                    instance->DoUseDoorOrButton(instance->GetData64(DATA_GO_CURTAINS));
                    break;
            }
        }

        void Talk(uint32 count)
        {
            int32 text = 0;

            switch (EventId)
            {
                case EVENT_OZ:
                    if (OzDialogue[count].textid)
                         text = OzDialogue[count].textid;
                    if (OzDialogue[count].timer)
                        TalkTimer = OzDialogue[count].timer;
                    break;

                case EVENT_HOOD:
                    if (HoodDialogue[count].textid)
                        text = HoodDialogue[count].textid;
                    if (HoodDialogue[count].timer)
                        TalkTimer = HoodDialogue[count].timer;
                    break;

                case EVENT_RAJ:
                     if (RAJDialogue[count].textid)
                         text = RAJDialogue[count].textid;
                    if (RAJDialogue[count].timer)
                        TalkTimer = RAJDialogue[count].timer;
                    break;
            }

            if (text)
                 DoScriptText(text, me);
        }

        void PrepareEncounter()
        {
            sLog->outDebug(LOG_FILTER_TSCR, "TSCR: Barnes Opera Event - Introduction complete - preparing encounter %d", EventId);
            uint8 index = 0;
            uint8 count = 0;

            switch (EventId)
            {
                case EVENT_OZ:
                    index = 0;
                    count = 4;
                    break;
                case EVENT_HOOD:
                    index = 4;
                    count = index+1;
                    break;
                case EVENT_RAJ:
                    index = 5;
                    count = index+1;
                    break;
            }

            for (; index < count; ++index)
            {
                uint32 entry = ((uint32)Spawns[index][0]);
                float PosX = Spawns[index][1];

                if (Creature* creature = me->SummonCreature(entry, PosX, SPAWN_Y, SPAWN_Z, SPAWN_O, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, HOUR*2*IN_MILLISECONDS))
                {
                    // In case database has bad flags
                    creature->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
                    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }

            RaidWiped = false;
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (TalkTimer <= diff)
                {
                    if (TalkCount > 3)
                    {
                        if (Creature* spotlight = Unit::GetCreature(*me, SpotlightGUID))
                            spotlight->DespawnOrUnsummon();

                        SetEscortPaused(false);
                        return;
                    }

                    Talk(TalkCount);
                    ++TalkCount;
                } else TalkTimer -= diff;
            }

            if (PerformanceReady)
            {
                if (!RaidWiped)
                {
                    if (WipeTimer <= diff)
                    {
                        Map* map = me->GetMap();
                        if (!map->IsDungeon())
                            return;

                        Map::PlayerList const &PlayerList = map->GetPlayers();
                        if (PlayerList.isEmpty())
                            return;

                        RaidWiped = true;
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->getSource()->isAlive() && !i->getSource()->isGameMaster())
                            {
                                RaidWiped = false;
                                break;
                            }
                        }

                        if (RaidWiped)
                        {
                            RaidWiped = true;
                            EnterEvadeMode();
                            return;
                        }

                        WipeTimer = 15000;
                    } else WipeTimer -= diff;
                }
            }
        }
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Action)
    {
        player->PlayerTalkClass->ClearMenus();
        npc_barnesAI* barnesAI = CAST_AI(npc_barnes::npc_barnesAI, creature->AI());

        switch (Action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OZ_GOSSIP2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(8971, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->CLOSE_GOSSIP_MENU();
                barnesAI->StartEvent();
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->CLOSE_GOSSIP_MENU();
                barnesAI->EventId = EVENT_OZ;
                sLog->outString("TSCR: player (GUID " UI64FMTD ") manually set Opera event to EVENT_OZ", player->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->CLOSE_GOSSIP_MENU();
                barnesAI->EventId = EVENT_HOOD;
                sLog->outString("TSCR: player (GUID " UI64FMTD ") manually set Opera event to EVENT_HOOD", player->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->CLOSE_GOSSIP_MENU();
                barnesAI->EventId = EVENT_RAJ;
                sLog->outString("TSCR: player (GUID " UI64FMTD ") manually set Opera event to EVENT_RAJ", player->GetGUID());
                break;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            // Check for death of Moroes and if opera event is not done already
            if (instance->GetData(TYPE_MOROES) == DONE && instance->GetData(TYPE_OPERA) != DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OZ_GOSSIP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                if (player->isGameMaster())
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, OZ_GM_GOSSIP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, OZ_GM_GOSSIP2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, OZ_GM_GOSSIP3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                }

                if (npc_barnesAI* barnesAI = CAST_AI(npc_barnes::npc_barnesAI, creature->AI()))
                {
                    if (!barnesAI->RaidWiped)
                        player->SEND_GOSSIP_MENU(8970, creature->GetGUID());
                    else
                        player->SEND_GOSSIP_MENU(8975, creature->GetGUID());

                    return true;
                }
            }
        }

        player->SEND_GOSSIP_MENU(8978, creature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_barnesAI(creature);
    }
};

/*###
# npc_berthold
####*/

enum eBerthold
{
    SPELL_TELEPORT           = 39567
};

#define GOSSIP_ITEM_TELEPORT    "Teleport me to the Guardian's Library"

class npc_berthold : public CreatureScript
{
public:
    npc_berthold() : CreatureScript("npc_berthold") { }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (Action == GOSSIP_ACTION_INFO_DEF + 1)
            player->CastSpell(player, SPELL_TELEPORT, true);

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            // Check if Shade of Aran event is done
            if (instance->GetData(TYPE_ARAN) == DONE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELEPORT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }
};

/*###
# npc_image_of_medivh
####*/

#define SAY_DIALOG_MEDIVH_1         "You've got my attention, dragon. You'll find I'm not as easily scared as the villagers below."
#define SAY_DIALOG_ARCANAGOS_2      "Your dabbling in the arcane has gone too far, Medivh. You've attracted the attention of powers beyond your understanding. You must leave Karazhan at once!"
#define SAY_DIALOG_MEDIVH_3         "You dare challenge me at my own dwelling? Your arrogance is astounding, even for a dragon!"
#define SAY_DIALOG_ARCANAGOS_4      "A dark power seeks to use you, Medivh! If you stay, dire days will follow. You must hurry, we don't have much time!"
#define SAY_DIALOG_MEDIVH_5         "I do not know what you speak of, dragon... but I will not be bullied by this display of insolence. I'll leave Karazhan when it suits me!"
#define SAY_DIALOG_ARCANAGOS_6      "You leave me no alternative. I will stop you by force if you won't listen to reason!"
#define EMOTE_DIALOG_MEDIVH_7       "begins to cast a spell of great power, weaving his own essence into the magic."
#define SAY_DIALOG_ARCANAGOS_8      "What have you done, wizard? This cannot be! I'm burning from... within!"
#define SAY_DIALOG_MEDIVH_9         "He should not have angered me. I must go... recover my strength now..."

#define MOB_ARCANAGOS               17652
#define SPELL_FIRE_BALL             30967
#define SPELL_UBER_FIREBALL         30971
#define SPELL_CONFLAGRATION_BLAST   30977
#define SPELL_MANA_SHIELD           31635

static float MedivPos[4] = {-11161.49f, -1902.24f, 91.48f, 1.94f};
static float ArcanagosPos[4] = {-11169.75f, -1881.48f, 95.39f, 4.83f};

class npc_image_of_medivh : public CreatureScript
{
public:
    npc_image_of_medivh() : CreatureScript("npc_image_of_medivh") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_image_of_medivhAI(creature);
    }

    struct npc_image_of_medivhAI : public ScriptedAI
    {
        npc_image_of_medivhAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint64 ArcanagosGUID;

        uint32 YellTimer;
        uint32 Step;
        uint32 FireMedivhTimer;
        uint32 FireArcanagosTimer;

        bool EventStarted;

        void Reset()
        {
            ArcanagosGUID = 0;

            if (instance && instance->GetData64(DATA_IMAGE_OF_MEDIVH) == 0)
            {
                instance->SetData64(DATA_IMAGE_OF_MEDIVH, me->GetGUID());
                (*me).GetMotionMaster()->MovePoint(1, MedivPos[0], MedivPos[1], MedivPos[2]);
                Step = 0;
            }else
            {
                me->DealDamage(me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                me->RemoveCorpse();
            }
        }
        void EnterCombat(Unit* /*who*/) {}

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;
            if (id == 1)
            {
                StartEvent();
                me->SetOrientation(MedivPos[3]);
                me->SetOrientation(MedivPos[3]);
            }
        }

        void StartEvent()
        {
            Step = 1;
            EventStarted = true;
            Creature* Arcanagos = me->SummonCreature(MOB_ARCANAGOS, ArcanagosPos[0], ArcanagosPos[1], ArcanagosPos[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 20000);
            if (!Arcanagos)
                return;
            ArcanagosGUID = Arcanagos->GetGUID();
            Arcanagos->SetLevitate(true);
            (*Arcanagos).GetMotionMaster()->MovePoint(0, ArcanagosPos[0], ArcanagosPos[1], ArcanagosPos[2]);
            Arcanagos->SetOrientation(ArcanagosPos[3]);
            me->SetOrientation(MedivPos[3]);
            YellTimer = 10000;
        }

        uint32 NextStep(uint32 Step)
        {
            Unit* arca = Unit::GetUnit(*me, ArcanagosGUID);
            Map* map = me->GetMap();
            switch (Step)
            {
            case 0: return 9999999;
            case 1:
                me->MonsterYell(SAY_DIALOG_MEDIVH_1, LANGUAGE_UNIVERSAL, 0);
                return 10000;
            case 2:
                if (arca)
                    CAST_CRE(arca)->MonsterYell(SAY_DIALOG_ARCANAGOS_2, LANGUAGE_UNIVERSAL, 0);
                return 20000;
            case 3:
                me->MonsterYell(SAY_DIALOG_MEDIVH_3, LANGUAGE_UNIVERSAL, 0);
                return 10000;
            case 4:
                if (arca)
                    CAST_CRE(arca)->MonsterYell(SAY_DIALOG_ARCANAGOS_4, LANGUAGE_UNIVERSAL, 0);
                return 20000;
            case 5:
                me->MonsterYell(SAY_DIALOG_MEDIVH_5, LANGUAGE_UNIVERSAL, 0);
                return 20000;
            case 6:
                if (arca)
                    CAST_CRE(arca)->MonsterYell(SAY_DIALOG_ARCANAGOS_6, LANGUAGE_UNIVERSAL, 0);
                return 10000;
            case 7:
                FireArcanagosTimer = 500;
                return 5000;
            case 8:
                FireMedivhTimer = 500;
                DoCast(me, SPELL_MANA_SHIELD);
                return 10000;
            case 9:
                me->MonsterTextEmote(EMOTE_DIALOG_MEDIVH_7, 0, false);
                return 10000;
            case 10:
                if (arca)
                    DoCast(arca, SPELL_CONFLAGRATION_BLAST, false);
                return 1000;
            case 11:
                if (arca)
                    CAST_CRE(arca)->MonsterYell(SAY_DIALOG_ARCANAGOS_8, LANGUAGE_UNIVERSAL, 0);
                return 5000;
            case 12:
                arca->GetMotionMaster()->MovePoint(0, -11010.82f, -1761.18f, 156.47f);
                arca->setActive(true);
                arca->InterruptNonMeleeSpells(true);
                arca->SetSpeed(MOVE_FLIGHT, 2.0f);
                return 10000;
            case 13:
                me->MonsterYell(SAY_DIALOG_MEDIVH_9, LANGUAGE_UNIVERSAL, 0);
                return 10000;
            case 14:
                me->SetVisible(false);
                me->ClearInCombat();

                if (map->IsDungeon())
                {
                    InstanceMap::PlayerList const &PlayerList = map->GetPlayers();
                    for (InstanceMap::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (i->getSource()->isAlive())
                        {
                            if (i->getSource()->GetQuestStatus(9645) == QUEST_STATUS_INCOMPLETE)
                                i->getSource()->CompleteQuest(9645);
                        }
                    }
                }
                return 50000;
            case 15:
                arca->DealDamage(arca, arca->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                return 5000;
            default : return 9999999;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (YellTimer <= diff)
            {
                if (EventStarted)
                    YellTimer = NextStep(Step++);
            } else YellTimer -= diff;

            if (Step >= 7 && Step <= 12)
            {
                Unit* arca = Unit::GetUnit(*me, ArcanagosGUID);

                if (FireArcanagosTimer <= diff)
                {
                    if (arca)
                        arca->CastSpell(me, SPELL_FIRE_BALL, false);
                    FireArcanagosTimer = 6000;
                } else FireArcanagosTimer -= diff;

                if (FireMedivhTimer <= diff)
                {
                    if (arca)
                        DoCast(arca, SPELL_FIRE_BALL);
                    FireMedivhTimer = 5000;
                } else FireMedivhTimer -= diff;
            }
        }
    };
};

void AddSC_karazhan()
{
    new npc_barnes();
    new npc_berthold();
    new npc_image_of_medivh();
}
