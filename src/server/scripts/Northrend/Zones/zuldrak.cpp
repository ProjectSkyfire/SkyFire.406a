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
#include "ScriptedEscortAI.h"

/*####
## npc_drakuru_shackles
####*/

enum eDrakuruShackles
{
    SPELL_LEFT_CHAIN           = 59951,
    SPELL_RIGHT_CHAIN          = 59952,
    SPELL_UNLOCK_SHACKLE       = 55083,
    SPELL_FREE_RAGECLAW        = 55223,

    NPC_RAGECLAW               = 29686,
    QUEST_TROLLS_IS_GONE_CRAZY = 12861,
};

class npc_drakuru_shackles : public CreatureScript
{
public:
    npc_drakuru_shackles() : CreatureScript("npc_drakuru_shackles") { }

    struct npc_drakuru_shacklesAI : public ScriptedAI
    {
        npc_drakuru_shacklesAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 RageclawGUID;

        void Reset()
        {
            RageclawGUID = 0;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            float x, y, z;
            me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 0.1f);

            if (Unit* summon = me->SummonCreature(NPC_RAGECLAW, x, y, z,
                0, TEMPSUMMON_DEAD_DESPAWN, 1000))
            {
                RageclawGUID = summon->GetGUID();
                LockRageclaw();
            }
        }

        void LockRageclaw()
        {
            Unit* Rageclaw = Unit::GetCreature(*me, RageclawGUID);
            // pointer check not needed
            me->SetInFront(Rageclaw);
            Rageclaw->SetInFront(me);

            DoCast(Rageclaw, SPELL_LEFT_CHAIN, true);
            DoCast(Rageclaw, SPELL_RIGHT_CHAIN, true);
        }

        void UnlockRageclaw(Unit* who)
        {
            if (!who)
                return;

            Creature* Rageclaw = Unit::GetCreature(*me, RageclawGUID);
            // pointer check not needed
            DoCast(Rageclaw, SPELL_FREE_RAGECLAW, true);

            me->setDeathState(DEAD);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_UNLOCK_SHACKLE)
            {
                if (caster->ToPlayer()->GetQuestStatus(QUEST_TROLLS_IS_GONE_CRAZY) == QUEST_STATUS_INCOMPLETE)
                {
                    if (Creature* rageclaw = Unit::GetCreature(*me, RageclawGUID))
                    {
                        UnlockRageclaw(caster);
                        caster->ToPlayer()->KilledMonster(rageclaw->GetCreatureTemplate(), RageclawGUID);
                        me->DisappearAndDie();
                    }
                    else
                        me->setDeathState(JUST_DIED);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_drakuru_shacklesAI(creature);
    }
};

/*####
## npc_captured_rageclaw
####*/

enum eRageclaw
{
    SPELL_UNSHACKLED           = 55085,
    SPELL_KNEEL                = 39656
};

const char * SAY_RAGECLAW_1 =      "I poop on you, trollses!";
const char * SAY_RAGECLAW_2 =      "ARRRROOOOGGGGAAAA!";
const char * SAY_RAGECLAW_3 =      "No more mister nice wolvar!";

#define SAY_RAGECLAW RAND(SAY_RAGECLAW_1, SAY_RAGECLAW_2, SAY_RAGECLAW_3)

class npc_captured_rageclaw : public CreatureScript
{
public:
    npc_captured_rageclaw() : CreatureScript("npc_captured_rageclaw") { }

    struct npc_captured_rageclawAI : public ScriptedAI
    {
        npc_captured_rageclawAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 DespawnTimer;
        bool Despawn;

        void Reset()
        {
            Despawn = false;
            DespawnTimer = 0;
            me->setFaction(35);
            DoCast(me, SPELL_KNEEL, true); // Little Hack for kneel - Thanks Illy :P
        }

        void MoveInLineOfSight(Unit* /*who*/){}

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FREE_RAGECLAW)
            {
                me->RemoveAurasDueToSpell(SPELL_LEFT_CHAIN);

                me->RemoveAurasDueToSpell(SPELL_RIGHT_CHAIN);

                me->RemoveAurasDueToSpell(SPELL_KNEEL);

                me->setFaction(me->GetCreatureTemplate()->faction_H);

                DoCast(me, SPELL_UNSHACKLED, true);
                me->MonsterSay(SAY_RAGECLAW, LANG_UNIVERSAL, 0);
                me->GetMotionMaster()->MoveRandom(10);

                DespawnTimer = 10000;
                Despawn = true;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (UpdateVictim())
            {
                DoMeleeAttackIfReady();
                return;
            }

            if (!Despawn)
                return;

            if (DespawnTimer <= diff)
                me->DisappearAndDie();
            else DespawnTimer -= diff;
       }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_rageclawAI(creature);
    }
};

/*####
## npc_gymer
####*/

#define    GOSSIP_ITEM_G "I'm ready, Gymer. Let's go!"

enum eGymer
{
    QUEST_STORM_KING_VENGEANCE    = 12919,
    SPELL_GYMER                   = 55568
};

class npc_gymer : public CreatureScript
{
public:
    npc_gymer() : CreatureScript("npc_gymer") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        if (player->GetQuestStatus(QUEST_STORM_KING_VENGEANCE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_G, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(13640, creature->GetGUID());
        }

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, SPELL_GYMER, true);
        }

        return true;
    }
};

/*####
## npc_gurgthock
####*/

enum eGurgthock
{
    QUEST_AMPHITHEATER_ANGUISH_TUSKARRMAGEDDON    = 12935,
    QUEST_AMPHITHEATER_ANGUISH_KORRAK_BLOODRAGER  = 12936,
    QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_2          = 12954,
    QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_1          = 12932,
    QUEST_AMPHITHEATER_ANGUISH_MAGNATAUR          = 12933,
    QUEST_AMPHITHEATER_ANGUISH_FROM_BEYOND        = 12934,
    QUEST_AMPHITHEATER_ANGUISH_CHAMPION           = 12948,

    NPC_ORINOKO_TUSKBREAKER                       = 30020,
    NPC_KORRAK_BLOODRAGER                         = 30023,
    NPC_YGGDRAS                                   = 30014,
    NPC_STINKBEARD                                = 30017,
    NPC_AZ_BARIN                                  = 30026, // air
    NPC_DUKE_SINGEN                               = 30019, // fire
    NPC_ERATHIUS                                  = 30025, // earth
    NPC_GARGORAL                                  = 30024, // water
    NPC_FIEND_WATER                               = 30044,
    NPC_FIEND_AIR                                 = 30045,
    NPC_FIEND_FIRE                                = 30042,
    NPC_FIEND_EARTH                               = 30043,
    NPC_VLADOF_BUTCHER                            = 30022,

    SAY_QUEST_ACCEPT_TUSKARRMAGEDON               = -1571031,
    SAY_QUEST_ACCEPT_KORRAK_1                     = -1571033,
    SAY_QUEST_ACCEPT_KORRAK_2                     = -1571034,
    SAY_QUEST_ACCEPT_MAGNATAUR                    = -1571035,
    //SAY_QUEST_ACCEPT_VLADOF_BUTCHER         = 0, // Text

    EMOTE_YGGDRAS_SPAWN                           = -1571039,
    SAY_STINKBEARD_SPAWN                          = -1571040,
    SAY_GURGTHOCK_ELEMENTAL_SPAWN                 = -1571041,

    SPELL_CRASHING_WAVE                           = 55909, // water
    SPELL_SHOCKWAVE                               = 55918, // earth
    SPELL_BLAST_OF_AIR                            = 55912, // air
    SPELL_MAGMA_WAVE                              = 55916, // fire

    SPELL_ORB_OF_WATER                            = 55888, // fiend of water spell
    SPELL_ORB_OF_STORMS                           = 55882, // fiend of air spell
    SPELL_BOULDER                                 = 55886, // fiend of earth spell
    SPELL_ORB_OF_FLAME                            = 55872  // fiend of fire spell
};

struct BossAndAdd
{
    uint32 Boss;
    uint32 Add;
    uint32 Spell;
    uint32 AddSpell;
};

static BossAndAdd Boss[]=
{
    {NPC_GARGORAL, NPC_FIEND_WATER, SPELL_CRASHING_WAVE, SPELL_ORB_OF_WATER},
    {NPC_AZ_BARIN, NPC_FIEND_AIR, SPELL_BLAST_OF_AIR, SPELL_ORB_OF_STORMS},
    {NPC_DUKE_SINGEN, NPC_FIEND_FIRE, SPELL_MAGMA_WAVE, SPELL_ORB_OF_FLAME},
    {NPC_ERATHIUS, NPC_FIEND_EARTH, SPELL_SHOCKWAVE, SPELL_BOULDER}
};

const Position SpawnPosition[] =
{
    {5754.692f, -2939.46f, 286.276123f, 5.156380f},        // stinkbeard || orinoko || korrak
    {5762.054199f, -2954.385010f, 273.826955f, 5.108289f}, // yggdras
    {5776.855f, -2989.77979f, 272.96814f, 5.194f},         // elementals
    {5774.388672f, -2980.124756f, 273.078613f, 5.156132f}   // vladof butcher
};

const Position AddSpawnPosition[] =
{
    {5722.487f, -3010.75f, 312.751648f, 0.478f},           // caster location
    {5724.983f, -2969.89551f, 286.359619f, 0.478f},
    {5733.76025f, -3000.34644f, 286.359619f, 0.478f},
    {5739.8125f, -2981.524f, 290.7671f, 0.478f},           // caster location
    {5742.101f, -2950.75586f, 286.2643f, 5.21f},
    {5743.305f, -3011.29736f, 290.7671f, 0.478f},          // caster location
    {5744.417f, -3025.528f, 286.35965f, 0.478f},
    {5763.189f, -3029.67529f, 290.7671f, 0.478f},
    {5769.401f, -2935.121f, 286.335754f, 5.21f},
    {5793.061f, -2934.593f, 286.359619f, 3.53f},
    {5797.32129f, -2955.26855f, 290.7671f, 3.53f},         // caster location
    {5813.94531f, -2956.74683f, 286.359619f, 3.53f},
    {5816.85547f, -2974.476f, 290.7671f, 3.53f},           // caster location
    {5820.30859f, -3002.83716f, 290.7671f, 3.53f},         // caster location
    {5828.50244f, -2981.737f, 286.359619f, 3.53f},
    {5828.899f, -2960.15479f, 312.751648f, 3.53f}           // caster location
};

class npc_gurgthock : public CreatureScript
{
public:
    npc_gurgthock() : CreatureScript("npc_gurgthock") { }

    struct npc_gurgthockAI : public ScriptedAI
    {
        npc_gurgthockAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 SummonGUID;
        uint64 playerGUID;

        uint32 Timer;
        uint32 Phase;
        uint32 RemoveFlagTimer;
        uint32 Quest;
        uint8 BossRandom;

        bool bRemoveFlag;

        void Reset()
        {
            SummonGUID = 0;
            playerGUID = 0;

            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            Timer = 0;
            Phase = 0;
            Quest = 0;
            RemoveFlagTimer = 5000;

            BossRandom = 0;

            bRemoveFlag = false;
        }

        void SetGUID(uint64 guid, int32 /*id*/)
        {
            playerGUID = guid;
        }

        void SetData(uint32 Id, uint32 value)
        {
            bRemoveFlag = true;
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

            switch (Id)
            {
                case 1:
                    switch (value)
                    {
                        case QUEST_AMPHITHEATER_ANGUISH_TUSKARRMAGEDDON:
                            DoScriptText(SAY_QUEST_ACCEPT_TUSKARRMAGEDON, me);
                            Phase = 1;
                            Timer = 4000;
                            break;
                        case QUEST_AMPHITHEATER_ANGUISH_KORRAK_BLOODRAGER:
                            DoScriptText(SAY_QUEST_ACCEPT_KORRAK_1, me);
                            Phase = 3;
                            Timer = 3000;
                            break;
                        case QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_2:
                        case QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_1:
                            Phase = 6;
                            Timer = 3000;
                            break;
                        case QUEST_AMPHITHEATER_ANGUISH_MAGNATAUR:
                            Timer = 5000;
                            Phase = 7;
                            break;
                        case QUEST_AMPHITHEATER_ANGUISH_FROM_BEYOND:
                            Timer = 2000;
                            Phase = 12;
                            break;
                        case QUEST_AMPHITHEATER_ANGUISH_CHAMPION:
                            Timer = 3000;
                            Phase = 15;
                            break;
                   }
                        break;
                }
        }

        void UpdateAI(const uint32 diff)
        {
            ScriptedAI::UpdateAI(diff);

            if (bRemoveFlag)
            {
                if (RemoveFlagTimer <= diff)
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    bRemoveFlag = false;

                    RemoveFlagTimer = 10000;
                } else RemoveFlagTimer -= diff;
            }

            if (Phase)
            {
                Player* player = me->GetPlayer(*me, playerGUID);

                if (Timer <= diff)
                {
                    switch (Phase)
                    {
                        case 1:
                            if (Creature* summon = me->SummonCreature(NPC_ORINOKO_TUSKBREAKER, SpawnPosition[0], TEMPSUMMON_CORPSE_DESPAWN, 1000))
                                SummonGUID = summon->GetGUID();
                            Phase = 2;
                            Timer = 4000;
                            break;
                         case 2:
                            if (Creature* summon = Unit::GetCreature(*me, SummonGUID))
                                summon->GetMotionMaster()->MoveJump(5776.319824f, -2981.005371f, 273.100037f, 10.0f, 20.0f);
                            Phase = 0;
                            SummonGUID = 0;
                            break;
                        case 3:
                            DoScriptText(SAY_QUEST_ACCEPT_KORRAK_2, me);
                            Timer = 3000;
                            Phase = 4;
                            break;
                        case 4:
                            if (Creature* summon = me->SummonCreature(NPC_KORRAK_BLOODRAGER, SpawnPosition[0], TEMPSUMMON_CORPSE_DESPAWN, 1000))
                                SummonGUID = summon->GetGUID();
                            Timer = 3000;
                            Phase = 0;
                            break;
                        case 6:
                            {
                                if (!player)
                                    return;

                                std::string sText = ("The grand Amphitheater of Anguish awaits, " + std::string(player->GetName()) + ". Remember, once a battle starts you have to stay in the area. WIN OR DIE!");

                                me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
                                Timer = 5000;
                                Phase = 9;
                            }
                            break;
                        case 7:
                            {
                               if (!player)
                                   return;

                                std::string sText = ("Prepare to make you stand, " + std::string(player->GetName()) + "! Get in the Amphitheater and stand ready! Remember, you and your opponent must stay in the arena at all times or you will be disqualified!");
                                me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
                                Timer = 3000;
                                Phase = 8;
                            }
                            break;
                        case 8:
                            DoScriptText(SAY_QUEST_ACCEPT_MAGNATAUR, me);
                            Timer = 5000;
                            Phase = 11;
                            break;
                        case 9:
                            {
                                if (!player)
                                    return;

                                std::string sText = ("Here we are once again, ladies and gentlemen. The epic struggle between life and death in the Amphitheater of Anguish! For this round we have " + std::string(player->GetName()) + " versus the hulking jormungar, Yg... Yggd? Yggdoze? Who comes up with these names?! " + std::string(player->GetName()) + " versus big worm!");
                                me->MonsterYell(sText.c_str(), LANG_UNIVERSAL, 0);
                                Timer = 10000;
                                Phase = 10;
                            }
                            break;
                        case 10:
                            me->SummonCreature(NPC_YGGDRAS, SpawnPosition[1], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                            DoScriptText(EMOTE_YGGDRAS_SPAWN, me);
                            Phase = 0;
                            break;
                        case 11:
                            if (Creature* creature = me->SummonCreature(NPC_STINKBEARD, SpawnPosition[0], TEMPSUMMON_CORPSE_DESPAWN, 1000))
                                DoScriptText(SAY_STINKBEARD_SPAWN, creature);
                            Phase = 0;
                            break;
                        case 12:
                        {
                            if (!player)
                                return;

                            std::string sText = ("Prepare to make you stand, " + std::string(player->GetName()) + "! Get in the Amphitheater and stand ready! Remember, you and your opponent must stay in the arena at all times or you will be disqualified!");
                            me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
                            Timer = 5000;
                            Phase = 13;
                        }
                        break;
                        case 13:
                            DoScriptText(SAY_GURGTHOCK_ELEMENTAL_SPAWN, me);
                            Timer = 3000;
                            Phase = 14;
                            break;
                        case 14:
                            BossRandom = urand(0, 3);
                            if (Creature* creature = me->SummonCreature(Boss[BossRandom].Boss, SpawnPosition[2], TEMPSUMMON_CORPSE_DESPAWN, 1000))
                                creature->AI()->SetData(1, BossRandom);
                            Phase = 0;
                            break;
                        // NPC_VLADOF_BUTCHER
                        case 15:
                            {
                                if (!player)
                                    return;

                                std::string sText = ("Prepare to make you stand, " + std::string(player->GetName()) + "! Get in the Amphitheater and stand ready! Remember, you and your opponent must stay in the arena at all times or you will be disqualified!");
                                me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
                                Timer = 5000;
                                Phase = 16;
                            }
                            break;
                        case 16:
                            //DoScriptText(SAY_QUEST_ACCEPT_VLADOF_BUTCHER, me);
                            Timer = 0;
                            Phase = 17;
                            break;
                        case 17:
                            if (Creature * spawn = me->SummonCreature(NPC_VLADOF_BUTCHER, SpawnPosition[3], TEMPSUMMON_CORPSE_DESPAWN, 3000))
                                spawn->AI()->AttackStart(player->ToUnit());
                            Phase = 0;
                            break;
                    }
                }
                else Timer -= diff;
            }
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
            case QUEST_AMPHITHEATER_ANGUISH_TUSKARRMAGEDDON:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_AMPHITHEATER_ANGUISH_KORRAK_BLOODRAGER:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_2:
            case QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_1:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_AMPHITHEATER_ANGUISH_MAGNATAUR:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            case QUEST_AMPHITHEATER_ANGUISH_FROM_BEYOND:
            case QUEST_AMPHITHEATER_ANGUISH_CHAMPION:
                creature->AI()->SetData(1, quest->GetQuestId());
                break;
            default:
                break;
        }

        creature->AI()->SetGUID(player->GetGUID());

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gurgthockAI(creature);
    }
};

enum eVladofButcherSpells
{
    // NPC_VLADOF_BUTCHER Spells
    SPELL_DEFLECTION        = 55976, // even
    SPELL_WHIRLWIND         = 55977, // even
    SPELL_BLOOD_BOIL        = 55974, // even
    SPELL_HYSTERIA          = 55975, // aggro add
    SPELL_BLOOD_PLAGUE      = 55973, // on aggro target
    SPELL_BLOOD_PRESENCE    = 50689  // even
};

enum eVladofButcherEvents
{
    EVENT_WHIRLWIND = 1,
    EVENT_BLOOD_BOIL,
    EVENT_BLOOD_PLAGUE
};

class npc_vladof_butcher : public CreatureScript
{
public:
    npc_vladof_butcher() : CreatureScript("npc_vladof_butcher") { }

    struct npc_vladof_butcherAI : public ScriptedAI
    {
        npc_vladof_butcherAI(Creature* creature) : ScriptedAI(creature) { }

private:
        EventMap events;
        bool bZauberabwehr;

public:
        void Reset()
        {
            events.Reset();
            bZauberabwehr = false;
        }

        void EnterCombat(Unit* who)
        {
            if (!who)
                return;

            DoCast(me, SPELL_BLOOD_PRESENCE, true);

            events.ScheduleEvent(EVENT_BLOOD_PLAGUE, 3000);
            events.ScheduleEvent(EVENT_BLOOD_BOIL, urand(5000, 8000));
            events.ScheduleEvent(EVENT_WHIRLWIND, 10000);
        }

        void JustDied(Unit* killer)
        {
            if (killer)
                killer->GetCharmerOrOwnerPlayerOrPlayerItself()->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_CHAMPION, killer);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!bZauberabwehr && me->HealthBelowPct(50))
            {
                DoCast(me, SPELL_DEFLECTION, true);
                bZauberabwehr = true;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BLOOD_PLAGUE:
                        DoCastVictim(SPELL_BLOOD_PLAGUE);
                        events.RescheduleEvent(EVENT_BLOOD_PLAGUE, 10000);
                        break;
                    case EVENT_BLOOD_BOIL:
                        DoCast(me, SPELL_BLOOD_BOIL, true);
                        events.RescheduleEvent(EVENT_BLOOD_PLAGUE, 10000);
                        break;
                    case EVENT_WHIRLWIND:
                        DoCast(me, SPELL_WHIRLWIND, true);
                        events.RescheduleEvent(EVENT_BLOOD_PLAGUE, 10000);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI * GetAI(Creature* creature) const
    {
        return new npc_vladof_butcherAI(creature);
    }
};

/*####
## npc_orinoko_tuskbreaker
####*/

enum eOrinokoTuskbreaker
{
    SPELL_BATTLE_SHOUT      = 32064,
    SPELL_FISHY_SCENT       = 55937,
    SPELL_IMPALE            = 55929,
    SPELL_SUMMON_WHISKER    = 55946,

    NPC_WHISKER             = 30113,
    NPC_HUNGRY_PENGUIN      = 30110,

    SAY_CALL_FOR_HELP       = -1571032
};

class npc_orinoko_tuskbreaker : public CreatureScript
{
public:
    npc_orinoko_tuskbreaker() : CreatureScript("npc_orinoko_tuskbreaker") { }

    struct npc_orinoko_tuskbreakerAI : public ScriptedAI
    {
        npc_orinoko_tuskbreakerAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_PASSIVE);
        }

        bool bSummoned;
        bool bBattleShout;
        bool bFishyScent;

        uint32 battleShoutTimer;
        uint32 fishyScentTimer;

        uint64 AffectedGUID;
        uint64 Whisker;

        void Reset()
        {
            bSummoned           = false;
            bBattleShout        = false;
            bFishyScent         = false;
            battleShoutTimer  = 0;
            fishyScentTimer   = 20000;
            Whisker           = 0;
            AffectedGUID        = 0;
        }

        void EnterEvadeMode()
        {
            if (Creature* whisker = me->GetCreature(*me, Whisker))
                whisker->RemoveFromWorld();
        }

        void MovementInform(uint32 Type, uint32 /*Id*/)
        {
            if (Type != POINT_MOTION_TYPE)
                return;

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
            battleShoutTimer  = 7000;
        }

        void EnterCombat(Unit* who)
        {
            DoCast(who, SPELL_IMPALE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!bBattleShout && battleShoutTimer <= diff)
            {
                DoCast(me, SPELL_BATTLE_SHOUT);
                bBattleShout = true;
            } else battleShoutTimer -= diff;

            if (fishyScentTimer <= diff)
            {
                if (Unit* affected = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    DoCast(affected, SPELL_FISHY_SCENT);
                    AffectedGUID = affected->GetGUID();
                }
                fishyScentTimer = 20000;
            } else fishyScentTimer -= diff;

            if (!bSummoned && !HealthAbovePct(50))
            {
                DoScriptText(SAY_CALL_FOR_HELP , me);
                //DoCast(me->getVictim(), SPELL_SUMMON_WHISKER); petai is not working correctly???

                if (Creature* whisker = me->SummonCreature(NPC_WHISKER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0))
                    Whisker = whisker->GetGUID();
                bSummoned = true;
            }

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_WHISKER:
                    summon->AI()->AttackStart(me->getVictim());
                    break;
                case NPC_HUNGRY_PENGUIN:
                    if (Unit* affected = Unit::GetUnit(*me, AffectedGUID))
                    {
                        if (affected->isAlive())
                            summon->AI()->AttackStart(affected);
                    }
                    break;
            }
        }

        void JustDied(Unit* killer)
        {
            if (Whisker)
                if (Creature* whisker = me->GetCreature(*me, Whisker))
                    whisker->RemoveFromWorld();

            if (killer->GetTypeId() == TYPEID_PLAYER)
                killer->GetCharmerOrOwnerPlayerOrPlayerItself()->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_TUSKARRMAGEDDON, killer);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_orinoko_tuskbreakerAI(creature);
    }
};

/*####
## npc_korrak_bloodrager
####*/

enum eKorrakBloodrager
{
    SPELL_GROW     = 55948,
    SPELL_CHARGE   = 24193,
    SPELL_UPPERCUT = 30471,
    SPELL_ENRAGE   = 42745
};

class npc_korrak_bloodrager : public CreatureScript
{
public:
    npc_korrak_bloodrager() : CreatureScript("npc_korrak_bloodrager") { }

    struct npc_korrak_bloodragerAI : public npc_escortAI
    {
        npc_korrak_bloodragerAI(Creature* creature) : npc_escortAI(creature)
        {
            Start(true, true, 0, NULL);
            SetDespawnAtEnd(false);
        }

        uint32 ChargeTimer;
        uint32 UppercutTimer;

        bool bEnrage;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_PASSIVE);
            ChargeTimer = 15000;
            UppercutTimer = 12000;
            bEnrage = false;
        }

        void WaypointReached(uint32 uiI)
        {
            switch (uiI)
            {
                case 6:
                    me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(me, SPELL_GROW);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (UppercutTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0))
                    DoCast(target, SPELL_UPPERCUT);
                UppercutTimer = 12000;
            } else UppercutTimer -= diff;

            if (ChargeTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0))
                    DoCast(target, SPELL_CHARGE);
                ChargeTimer = 15000;
            } else ChargeTimer -= diff;

            if (!bEnrage && !HealthAbovePct(20))
            {
                DoCast(me, SPELL_ENRAGE);
                bEnrage = true;
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
                player->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_KORRAK_BLOODRAGER, killer);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_korrak_bloodragerAI(creature);
    }
};

/*####
## npc_yggdras
####*/

enum eYggdras
{
    SPELL_CLEAVE            = 40504,
    SPELL_CORRODE_FLESH     = 57076,
    SPELL_JORMUNGAR_SPAWN   = 55859
};

class npc_yggdras : public CreatureScript
{
public:
    npc_yggdras() : CreatureScript("npc_yggdras") { }

    struct npc_yggdrasAI : public ScriptedAI
    {
        npc_yggdrasAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 CleaveTimer ;
        uint32 CorrodeFleshTimer;

        void Reset()
        {
            CleaveTimer  = 9000;
            CorrodeFleshTimer = 6000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->getVictim()->GetPositionZ() >= 286.276f)
            {
                std::list<HostileReference*> t_list = me->getThreatManager().getThreatList();
                for (std::list<HostileReference*>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                {
                    if (Unit* unit = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                    {
                        if (unit->GetPositionZ() <= 286.276f)
                        {
                            me->getThreatManager().resetAllAggro();
                            me->AddThreat(unit, 5.0f);
                            break;
                        }
                        EnterEvadeMode();
                    }
                }
            }

            if (CleaveTimer  <= diff)
            {
                DoCast(me->getVictim(), SPELL_CLEAVE);
                CleaveTimer = 9000;
            } else CleaveTimer -= diff;

            if (CorrodeFleshTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_CORRODE_FLESH);
                CorrodeFleshTimer = 6000;
            } else CorrodeFleshTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
            {
                std::string sText = (std::string(killer->GetName()) + " has defeated Yg.. Yggg-really big worm!");
                summoner->MonsterYell(sText.c_str(), LANG_UNIVERSAL, 0);
            }

            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                player->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_1, killer);
                player->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_YGGDRAS_2, killer);
            }

            for (uint8 i = 0; i < 3; ++i)
                DoCast(killer, SPELL_JORMUNGAR_SPAWN, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_yggdrasAI(creature);
    }
};

/*####
## npc_stinkbeard
####*/

enum eStinkbeard
{
    SPELL_ENRAGE_STINKBEARD = 50420,
    SPELL_KNOCK_AWAY        = 31389,
    SPELL_STINKY_BEARD      = 55867,
    SPELL_THUNDERBLADE      = 55866,
    SPELL_THUNDERCLAP       = 15588
};

class npc_stinkbeard : public CreatureScript
{
public:
    npc_stinkbeard() : CreatureScript("npc_stinkbeard") { }

    struct npc_stinkbeardAI : public npc_escortAI
    {
        npc_stinkbeardAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_PASSIVE);
            Start(true, true, 0, NULL);
            SetDespawnAtEnd(false);
        }

        uint32 KnockAwayTimer;
        uint32 StinkyBeardTimer;

        bool bEnrage;
        bool bThunderClap;

        void Reset()
        {
            me->AddAura(SPELL_THUNDERBLADE, me);
            KnockAwayTimer   = 10000;
            StinkyBeardTimer = 15000;
            bEnrage = false;
            bThunderClap = false;
        }

        void WaypointReached(uint32 uiI)
        {
            switch (uiI)
            {
                case 7:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (Unit* victim = me->getVictim())
            {
                if (victim->GetPositionZ() >= 286.276f)
                {
                    std::list<HostileReference*> t_list = me->getThreatManager().getThreatList();
                    for (std::list<HostileReference*>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                    {
                        if (Unit* unit = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                        {
                            if (unit->GetPositionZ() <= 286.276f)
                            {
                                me->getThreatManager().resetAllAggro();
                                me->AddThreat(unit, 5.0f);
                                break;
                            }
                            EnterEvadeMode();
                        }
                    }
                }
            }

            if (bThunderClap && !HealthAbovePct(10))
            {
                DoCastAOE(SPELL_THUNDERCLAP);
                bThunderClap = true;
            }

            if (KnockAwayTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    if (target && target->isAlive())
                        DoCast(target, SPELL_KNOCK_AWAY);
                }
                KnockAwayTimer = 10000;
            } else KnockAwayTimer -= diff;

            if (StinkyBeardTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    if (target && target->isAlive())
                        DoCast(target, SPELL_STINKY_BEARD);
                }
                StinkyBeardTimer = 15000;
            } else StinkyBeardTimer -= diff;

            if (!bEnrage && !HealthAbovePct(20))
            {
                DoCast(me, SPELL_ENRAGE_STINKBEARD);
                bEnrage = true;
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
                player->GetCharmerOrOwnerPlayerOrPlayerItself()->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_MAGNATAUR, killer);

            std::string sText = ("And with AUTHORITY, " + std::string(killer->GetName()) + " dominates the magnataur lord! Stinkbeard's clan is gonna miss him back home in the Dragonblight!");
            me->MonsterYell(sText.c_str(), LANG_UNIVERSAL, 0);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stinkbeardAI(creature);
    }
};

/*####
## npc_elemental_lord
####*/

class npc_elemental_lord : public CreatureScript
{
public:
    npc_elemental_lord() : CreatureScript("npc_elemental_lord") { }

    struct npc_elemental_lordAI : public ScriptedAI
    {
        npc_elemental_lordAI(Creature* creature) : ScriptedAI(creature) {}

        std::list<uint64> SummonList;

        uint32 elementalSpellTimer;

        uint8 BossRandom;
        uint32 spellInfo;

        bool bAddAttack;

        void Reset()
        {
            BossRandom = 0;
            spellInfo = 0;
            elementalSpellTimer = urand(5000, 8000);

            bAddAttack = false;
        }

        void SetData(uint32 data, uint32 value)
        {
            if (data == 1)
            {
                BossRandom = value;
                SummonAdds();
            }
        }

        void SummonAdds()
        {
            if (!Boss[BossRandom].Add)
                return;

            SummonList.clear();

            for (uint8 uiI = 0; uiI < 16 ; uiI++)
            {
                if (Creature* summon = me->SummonCreature(Boss[BossRandom].Add, AddSpawnPosition[uiI]))
                {
                    summon->AI()->SetData(1, BossRandom);
                    SummonList.push_back(summon->GetGUID());
                }
            }
        }

        void EnterCombat(Unit* unit)
        {
            if (!SummonList.empty())
                for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                {
                    if (Creature* temp = Unit::GetCreature(*me, *itr))
                    {
                        temp->_CombatDistance = 100.0f; // ugly hack? we are not in a instance sorry. :(
                        temp->AI()->AttackStart(unit);
                    }
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->getVictim()->GetPositionZ() >= 286.276f)
            {
                std::list<HostileReference*> t_list = me->getThreatManager().getThreatList();
                for (std::list<HostileReference*>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                {
                    if (Unit* unit = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                    {
                        if (unit->GetPositionZ() <= 286.276f)
                        {
                            me->getThreatManager().resetAllAggro();
                            me->AddThreat(unit, 5.0f);
                            break;
                        }
                        EnterEvadeMode();
                    }
                }
            }

            if (elementalSpellTimer <= diff)
            {
                DoCastVictim(Boss[BossRandom].Spell);

                elementalSpellTimer = urand(5000, 8000);
            } else elementalSpellTimer -= diff;

            if (!bAddAttack && !HealthAbovePct(20))
            {
                if (!SummonList.empty())
                    for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                    {
                        if (Creature* temp = Unit::GetCreature(*me, *itr))
                        {
                            if (temp->GetPositionZ() >= 287.00f)
                                continue;

                            if (temp->getVictim())
                                temp->GetMotionMaster()->MoveChase(temp->getVictim());
                        }
                    }

                bAddAttack = true;
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
            if (!SummonList.empty())
                for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                    if (Creature* temp = Unit::GetCreature(*me, *itr))
                        temp->DespawnOrUnsummon();

            if (Player* player = killer->GetCharmerOrOwnerPlayerOrPlayerItself())
                player->GetCharmerOrOwnerPlayerOrPlayerItself()->GroupEventHappens(QUEST_AMPHITHEATER_ANGUISH_FROM_BEYOND, killer);

            std::string sText = (std::string(killer->GetName()) + " is victorious once more!");

            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                summoner->MonsterYell(sText.c_str(), LANG_UNIVERSAL, 0);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_elemental_lordAI(creature);
    }
};

/*####
## npc_fiend_elemental
####*/

class npc_fiend_elemental : public CreatureScript
{
public:
    npc_fiend_elemental() : CreatureScript("npc_fiend_elemental") { }

    struct npc_fiend_elementalAI : public ScriptedAI
    {
        npc_fiend_elementalAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 MissleTimer;
        uint32 Spell;

        void Reset()
        {
            if (me->GetPositionZ() >= 287.0f)
                me->GetMotionMaster()->MoveIdle();

            Spell = 0;
            MissleTimer = urand(2000, 7000);
        }

        void AttackStart(Unit* who)
        {
            if (!who)
                return;

            AttackStartNoMove(who);
        }

        void SetData(uint32 data, uint32 value)
        {
            if (data == 1)
                Spell = Boss[value].AddSpell;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->GetPositionZ() >= 287.0f)
            {
                if (MissleTimer <= diff)
                {
                    DoCast(me, Spell); // this spell is not supported ... YET!
                    MissleTimer = urand(2000, 7000);
                } else MissleTimer -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fiend_elementalAI(creature);
    }
};

/*####
## npc_released_offspring_harkoa
####*/

class npc_released_offspring_harkoa : public CreatureScript
{
public:
    npc_released_offspring_harkoa() : CreatureScript("npc_released_offspring_harkoa") { }

    struct npc_released_offspring_harkoaAI : public ScriptedAI
    {
        npc_released_offspring_harkoaAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            float x, y, z;
            me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 25.0f);
            me->GetMotionMaster()->MovePoint(0, x, y, z);
        }

        void MovementInform(uint32 Type, uint32 /*Id*/)
        {
            if (Type != POINT_MOTION_TYPE)
                return;
            me->DisappearAndDie();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_released_offspring_harkoaAI(creature);
    }
};

/*######
## npc_crusade_recruit
######*/

enum eCrusade_recruit
{
    SPELL_QUEST_CREDIT                            = 50633,

    QUEST_TROLL_PATROL_INTESTINAL_FORTITUDE       = 12509,

    GOSSIP_CRUSADE_TEXT                           = 13069,

    SAY_RECRUIT_1                                 = -1571036,
    SAY_RECRUIT_2                                 = -1571037,
    SAY_RECRUIT_3                                 = -1571038
};

#define GOSSIP_ITEM_1 "Get out there and make those Scourge wish they were never reborn!"

class npc_crusade_recruit : public CreatureScript
{
public:
    npc_crusade_recruit() : CreatureScript("npc_crusade_recruit") { }

    struct npc_crusade_recruitAI : public ScriptedAI
    {
        npc_crusade_recruitAI(Creature* creature) : ScriptedAI(creature) {}

        uint8 m_Phase;                  //The current phase we are in
        uint32 m_Timer;                 //Timer until phase transition
        float m_heading;                  //Store creature heading

        void Reset()
        {
            m_Timer = 0;
            m_Phase = 0;
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
            m_heading = me->GetOrientation();
        }

        void UpdateAI(const uint32 diff)
        {
            if (m_Phase)
            {
                if (m_Timer <= diff)
                {
                    switch (m_Phase)
                    {
                        case 1:
                            // say random text
                            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            DoScriptText(RAND(SAY_RECRUIT_1, SAY_RECRUIT_2, SAY_RECRUIT_3), me);
                            m_Timer = 3000;
                            m_Phase = 2;
                            break;
                        case 2:
                            // walk forward
                            me->SetWalk(true);
                            me->GetMotionMaster()->MovePoint(0, me->GetPositionX() + (cos(m_heading) * 10), me->GetPositionY() + (sin(m_heading) * 10), me->GetPositionZ());
                            m_Timer = 5000;
                            m_Phase = 3;
                            break;
                        case 3:
                            // despawn
                            me->DisappearAndDie();
                            m_Timer = 0;
                            m_Phase = 0;
                            break;
                    }
                }
                else
                m_Timer -= diff;
            }
            ScriptedAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crusade_recruitAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_TROLL_PATROL_INTESTINAL_FORTITUDE) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(GOSSIP_CRUSADE_TEXT, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF +1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->CastSpell(player, SPELL_QUEST_CREDIT, true);
            CAST_AI(npc_crusade_recruit::npc_crusade_recruitAI, (creature->AI()))->m_Phase = 1;
            creature->SetInFront(player);
            creature->SendMovementFlagUpdate();
        }

        return true;
    }
};

/*######
## Quest 12916: Our Only Hope!
## go_scourge_enclosure
######*/

enum eScourgeEnclosure
{
    QUEST_OUR_ONLY_HOPE                           = 12916,
    NPC_GYMER_DUMMY                               = 29928   //from quest template
};

class go_scourge_enclosure : public GameObjectScript
{
public:
    go_scourge_enclosure() : GameObjectScript("go_scourge_enclosure") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_OUR_ONLY_HOPE) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* gymerDummy = go->FindNearestCreature(NPC_GYMER_DUMMY, 20.0f);
            if (gymerDummy)
            {
                go->UseDoorOrButton();
                player->KilledMonsterCredit(gymerDummy->GetEntry(), gymerDummy->GetGUID());
                gymerDummy->CastSpell(gymerDummy, 55529, true);
                gymerDummy->DisappearAndDie();
            }
        }
        return true;
    }
};

void AddSC_zuldrak()
{
    new npc_drakuru_shackles();
    new npc_captured_rageclaw();
    new npc_gymer();
    new npc_gurgthock();
    new npc_orinoko_tuskbreaker();
    new npc_korrak_bloodrager();
    new npc_yggdras();
    new npc_stinkbeard();
    new npc_released_offspring_harkoa();
    new npc_crusade_recruit();
    new npc_elemental_lord();
    new npc_fiend_elemental();
    new npc_vladof_butcher();
    new go_scourge_enclosure();
}
