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
SFName: Stormwind_City
SF%Complete: 100
SFComment: Quest support: 1640, 1447, 4185, 11223, 434.
SFCategory: Stormwind City
EndScriptData */

/* ContentData
npc_archmage_malin
npc_bartleby
npc_dashel_stonefist
npc_lady_katrana_prestor
npc_tyrion
npc_tyrion_spybot
npc_marzon_silent_blade
npc_lord_gregor_lescovar
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

/*######
## npc_archmage_malin
######*/

#define GOSSIP_ITEM_MALIN "Can you send me to Theramore? I have an urgent message for Lady Jaina from Highlord Bolvar."

class npc_archmage_malin : public CreatureScript
{
public:
    npc_archmage_malin() : CreatureScript("npc_archmage_malin") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->CastSpell(player, 42711, true);
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(11223) == QUEST_STATUS_COMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MALIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

/*######
## npc_bartleby
######*/

enum eBartleby
{
    FACTION_ENEMY       = 168,
    QUEST_BEAT          = 1640
};

class npc_bartleby : public CreatureScript
{
public:
    npc_bartleby() : CreatureScript("npc_bartleby") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BEAT)
        {
            creature->setFaction(FACTION_ENEMY);
            creature->AI()->AttackStart(player);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bartlebyAI(creature);
    }

    struct npc_bartlebyAI : public ScriptedAI
    {
        npc_bartlebyAI(Creature* creature) : ScriptedAI(creature)
        {
            NormalFaction = creature->getFaction();
        }

        uint32 NormalFaction;

        void Reset()
        {
            if (me->getFaction() != NormalFaction)
                me->setFaction(NormalFaction);
        }

        void AttackedBy(Unit* attacker)
        {
            if (me->getVictim())
                return;

            if (me->IsFriendlyTo(attacker))
                return;

            AttackStart(attacker);
        }

        void DamageTaken(Unit* doneBy, uint32 &Damage)
        {
            if (Damage > me->GetHealth() || me->HealthBelowPctDamaged(15, Damage))
            {
                //Take 0 damage
                Damage = 0;

                if (doneBy->GetTypeId() == TYPEID_PLAYER)
                    CAST_PLR(doneBy)->AreaExploredOrEventHappens(QUEST_BEAT);
                EnterEvadeMode();
            }
        }
    };
};

/*######
## npc_dashel_stonefist
######*/

enum eDashel
{
    QUEST_MISSING_DIPLO_PT8     = 1447,
    FACTION_HOSTILE             = 168
};

class npc_dashel_stonefist : public CreatureScript
{
public:
    npc_dashel_stonefist() : CreatureScript("npc_dashel_stonefist") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_MISSING_DIPLO_PT8)
        {
            creature->setFaction(FACTION_HOSTILE);
            CAST_AI(npc_dashel_stonefist::npc_dashel_stonefistAI, creature->AI())->AttackStart(player);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dashel_stonefistAI(creature);
    }

    struct npc_dashel_stonefistAI : public ScriptedAI
    {
        npc_dashel_stonefistAI(Creature* creature) : ScriptedAI(creature)
        {
            NormalFaction = creature->getFaction();
        }

        uint32 NormalFaction;

        void Reset()
        {
            if (me->getFaction() != NormalFaction)
                me->setFaction(NormalFaction);
        }

        void AttackedBy(Unit* attacker)
        {
            if (me->getVictim())
                return;

            if (me->IsFriendlyTo(attacker))
                return;

            AttackStart(attacker);
        }

        void DamageTaken(Unit* doneBy, uint32 &Damage)
        {
            if (Damage > me->GetHealth() || me->HealthBelowPctDamaged(15, Damage))
            {
                Damage = 0;

                if (doneBy->GetTypeId() == TYPEID_PLAYER)
                    CAST_PLR(doneBy)->AreaExploredOrEventHappens(QUEST_MISSING_DIPLO_PT8);

                EnterEvadeMode();
            }
        }
    };
};

/*######
## npc_lady_katrana_prestor
######*/

#define GOSSIP_ITEM_KAT_1 "Pardon the intrusion, Lady Prestor, but Highlord Bolvar suggested that I seek your advice."
#define GOSSIP_ITEM_KAT_2 "My apologies, Lady Prestor."
#define GOSSIP_ITEM_KAT_3 "Begging your pardon, Lady Prestor. That was not my intent."
#define GOSSIP_ITEM_KAT_4 "Thank you for your time, Lady Prestor."

class npc_lady_katrana_prestor : public CreatureScript
{
public:
    npc_lady_katrana_prestor() : CreatureScript("npc_lady_katrana_prestor") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(2694, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(2695, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU(2696, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(4185);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(4185) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(2693, creature->GetGUID());

        return true;
    }
};

/*######
## npc_lord_gregor_lescovar
######*/

enum eLordGregorLescovar
{
    SAY_LESCOVAR_2 = -1000457,
    SAY_GUARD_2    = -1000458,
    SAY_LESCOVAR_3 = -1000459,
    SAY_MARZON_1   = -1000460,
    SAY_LESCOVAR_4 = -1000461,
    SAY_TYRION_2   = -1000462,
    SAY_MARZON_2   = -1000463,

    NPC_STORMWIND_ROYAL = 1756,
    NPC_MARZON_BLADE    = 1755,
    NPC_TYRION          = 7766,

    QUEST_THE_ATTACK    = 434
};

class npc_lord_gregor_lescovar : public CreatureScript
{
public:
    npc_lord_gregor_lescovar() : CreatureScript("npc_lord_gregor_lescovar") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_gregor_lescovarAI(creature);
    }

    struct npc_lord_gregor_lescovarAI : public npc_escortAI
    {
        npc_lord_gregor_lescovarAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->RestoreFaction();
        }

        uint32 Timer;
        uint32 Phase;

        uint64 MarzonGUID;

        void Reset()
        {
            Timer = 0;
            Phase = 0;

            MarzonGUID = 0;
        }

        void EnterEvadeMode()
        {
            me->DisappearAndDie();

            if (Creature* marzon = Unit::GetCreature(*me, MarzonGUID))
            {
                if (marzon->isAlive())
                    marzon->DisappearAndDie();
            }
        }

        void EnterCombat(Unit* who)
        {
            if (Creature* marzon = Unit::GetCreature(*me, MarzonGUID))
            {
                if (marzon->isAlive() && !marzon->isInCombat())
                    marzon->AI()->AttackStart(who);
            }
        }

        void WaypointReached(uint32 PointId)
        {
            switch (PointId)
            {
                case 14:
                    SetEscortPaused(true);
                    DoScriptText(SAY_LESCOVAR_2, me);
                    Timer = 3000;
                    Phase = 1;
                    break;
                case 16:
                    SetEscortPaused(true);
                    if (Creature* marzon = me->SummonCreature(NPC_MARZON_BLADE, -8411.360352f, 480.069733f, 123.760895f, 4.941504f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000))
                    {
                        marzon->GetMotionMaster()->MovePoint(0, -8408.000977f, 468.611450f, 123.759903f);
                        MarzonGUID = marzon->GetGUID();
                    }
                    Timer = 2000;
                    Phase = 4;
                    break;
            }
        }
        //TO-DO: We don't have movemaps, also we can't make 2 npcs walks to one point propperly (and we can not use escort ai, because they are 2 different spawns and with same entry), because of it we make them, disappear.
        void DoGuardsDisappearAndDie()
        {
            std::list<Creature*> GuardList;
            me->GetCreatureListWithEntryInGrid(GuardList, NPC_STORMWIND_ROYAL, 8.0f);
            if (!GuardList.empty())
            {
                for (std::list<Creature*>::const_iterator itr = GuardList.begin(); itr != GuardList.end(); ++itr)
                {
                    if (Creature* guard = *itr)
                        guard->DisappearAndDie();
                }
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            if (Phase)
            {
                if (Timer <= Diff)
                {
                    switch (Phase)
                    {
                        case 1:
                            if (Creature* guard = me->FindNearestCreature(NPC_STORMWIND_ROYAL, 8.0f, true))
                                DoScriptText(SAY_GUARD_2, guard);
                            Timer = 3000;
                            Phase = 2;
                            break;
                        case 2:
                            DoGuardsDisappearAndDie();
                            Timer = 2000;
                            Phase = 3;
                            break;
                        case 3:
                            SetEscortPaused(false);
                            Timer = 0;
                            Phase = 0;
                            break;
                        case 4:
                            DoScriptText(SAY_LESCOVAR_3, me);
                            Timer = 0;
                            Phase = 0;
                            break;
                        case 5:
                            if (Creature* marzon = Unit::GetCreature(*me, MarzonGUID))
                                DoScriptText(SAY_MARZON_1, marzon);
                            Timer = 3000;
                            Phase = 6;
                            break;
                        case 6:
                            DoScriptText(SAY_LESCOVAR_4, me);
                            if (Player* player = GetPlayerForEscort())
                                player->AreaExploredOrEventHappens(QUEST_THE_ATTACK);
                            Timer = 2000;
                            Phase = 7;
                            break;
                        case 7:
                            if (Creature* tyrion = me->FindNearestCreature(NPC_TYRION, 20.0f, true))
                                DoScriptText(SAY_TYRION_2, tyrion);
                            if (Creature* marzon = Unit::GetCreature(*me, MarzonGUID))
                                marzon->setFaction(14);
                            me->setFaction(14);
                            Timer = 0;
                            Phase = 0;
                            break;
                    }
                }
                else Timer -= Diff;
            }
            npc_escortAI::UpdateAI(Diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_marzon_silent_blade
######*/

class npc_marzon_silent_blade : public CreatureScript
{
public:
    npc_marzon_silent_blade() : CreatureScript("npc_marzon_silent_blade") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_marzon_silent_bladeAI(creature);
    }

    struct npc_marzon_silent_bladeAI : public ScriptedAI
    {
        npc_marzon_silent_bladeAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetWalk(true);
        }

        void Reset()
        {
            me->RestoreFaction();
        }

        void EnterCombat(Unit* who)
        {
            DoScriptText(SAY_MARZON_2, me);

            if (me->isSummon())
            {
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    if (summoner && summoner->GetTypeId() == TYPEID_UNIT && summoner->isAlive() && !summoner->isInCombat())
                        summoner->ToCreature()->AI()->AttackStart(who);
                }
            }
        }

        void EnterEvadeMode()
        {
            me->DisappearAndDie();

            if (me->isSummon())
            {
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    if (summoner && summoner->GetTypeId() == TYPEID_UNIT && summoner->isAlive())
                        summoner->ToCreature()->DisappearAndDie();
                }
            }
        }

        void MovementInform(uint32 Type, uint32 /*uiId*/)
        {
            if (Type != POINT_MOTION_TYPE)
                return;

            if (me->isSummon())
            {
                Unit* summoner = me->ToTempSummon()->GetSummoner();
                if (summoner && summoner->GetTypeId() == TYPEID_UNIT && summoner->IsAIEnabled)
                {
                    npc_lord_gregor_lescovar::npc_lord_gregor_lescovarAI* ai =
                        CAST_AI(npc_lord_gregor_lescovar::npc_lord_gregor_lescovarAI, summoner->GetAI());
                    if (ai)
                    {
                        ai->Timer = 2000;
                        ai->Phase = 5;
                    }
                    //me->ChangeOrient(0.0f, summoner);
                }
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_tyrion_spybot
######*/

enum eTyrionSpybot
{
    SAY_QUEST_ACCEPT_ATTACK  = -1000499,
    SAY_TYRION_1             = -1000450,
    SAY_SPYBOT_1             = -1000451,
    SAY_GUARD_1              = -1000452,
    SAY_SPYBOT_2             = -1000453,
    SAY_SPYBOT_3             = -1000454,
    SAY_LESCOVAR_1           = -1000455,
    SAY_SPYBOT_4             = -1000456,

    NPC_PRIESTESS_TYRIONA    = 7779,
    NPC_LORD_GREGOR_LESCOVAR = 1754,
};

class npc_tyrion_spybot : public CreatureScript
{
public:
    npc_tyrion_spybot() : CreatureScript("npc_tyrion_spybot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tyrion_spybotAI(creature);
    }

    struct npc_tyrion_spybotAI : public npc_escortAI
    {
        npc_tyrion_spybotAI(Creature* creature) : npc_escortAI(creature) {}

        uint32 Timer;
        uint32 Phase;

        void Reset()
        {
            Timer = 0;
            Phase = 0;
        }

        void WaypointReached(uint32 PointId)
        {
            switch (PointId)
            {
                case 1:
                    SetEscortPaused(true);
                    Timer = 2000;
                    Phase = 1;
                    break;
                case 5:
                    SetEscortPaused(true);
                    DoScriptText(SAY_SPYBOT_1, me);
                    Timer = 2000;
                    Phase = 5;
                    break;
                case 17:
                    SetEscortPaused(true);
                    DoScriptText(SAY_SPYBOT_3, me);
                    Timer = 3000;
                    Phase = 8;
                    break;
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            if (Phase)
            {
                if (Timer <= Diff)
                {
                    switch (Phase)
                    {
                        case 1:
                            DoScriptText(SAY_QUEST_ACCEPT_ATTACK, me);
                            Timer = 3000;
                            Phase = 2;
                            break;
                        case 2:
                            if (Creature* tyrion = me->FindNearestCreature(NPC_TYRION, 10.0f))
                                DoScriptText(SAY_TYRION_1, tyrion);
                            Timer = 3000;
                            Phase = 3;
                            break;
                        case 3:
                            me->UpdateEntry(NPC_PRIESTESS_TYRIONA, ALLIANCE);
                            Timer = 2000;
                            Phase = 4;
                            break;
                        case 4:
                           SetEscortPaused(false);
                           Phase = 0;
                           Timer = 0;
                           break;
                        case 5:
                            if (Creature* guard = me->FindNearestCreature(NPC_STORMWIND_ROYAL, 10.0f, true))
                                DoScriptText(SAY_GUARD_1, guard);
                            Timer = 3000;
                            Phase = 6;
                            break;
                        case 6:
                            DoScriptText(SAY_SPYBOT_2, me);
                            Timer = 3000;
                            Phase = 7;
                            break;
                        case 7:
                            SetEscortPaused(false);
                            Timer = 0;
                            Phase = 0;
                            break;
                        case 8:
                            if (Creature* lescovar = me->FindNearestCreature(NPC_LORD_GREGOR_LESCOVAR, 10.0f))
                                DoScriptText(SAY_LESCOVAR_1, lescovar);
                            Timer = 3000;
                            Phase = 9;
                            break;
                        case 9:
                            DoScriptText(SAY_SPYBOT_4, me);
                            Timer = 3000;
                            Phase = 10;
                            break;
                        case 10:
                            if (Creature* lescovar = me->FindNearestCreature(NPC_LORD_GREGOR_LESCOVAR, 10.0f))
                            {
                                if (Player* player = GetPlayerForEscort())
                                {
                                    CAST_AI(npc_lord_gregor_lescovar::npc_lord_gregor_lescovarAI, lescovar->AI())->Start(false, false, player->GetGUID());
                                    CAST_AI(npc_lord_gregor_lescovar::npc_lord_gregor_lescovarAI, lescovar->AI())->SetMaxPlayerDistance(200.0f);
                                }
                            }
                            me->DisappearAndDie();
                            Timer = 0;
                            Phase = 0;
                            break;
                    }
                }
                else Timer -= Diff;
            }
            npc_escortAI::UpdateAI(Diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_tyrion
######*/

enum eTyrion
{
    NPC_TYRION_SPYBOT = 8856
};

class npc_tyrion : public CreatureScript
{
public:
    npc_tyrion() : CreatureScript("npc_tyrion") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_ATTACK)
        {
            if (Creature* spybot = creature->FindNearestCreature(NPC_TYRION_SPYBOT, 5.0f, true))
            {
                CAST_AI(npc_tyrion_spybot::npc_tyrion_spybotAI, spybot->AI())->Start(false, false, player->GetGUID());
                CAST_AI(npc_tyrion_spybot::npc_tyrion_spybotAI, spybot->AI())->SetMaxPlayerDistance(200.0f);
            }
            return true;
        }
        return false;
    }
};

/************************************
**Stormwind Gryphon Rider
*************************************/
enum eStormwindGryphonRider
{
     SPELL_GREYMANE_RESOLVE = 96161,
     SPELL_SHOOT = 6660
};

class npc_stormwind_gryphon_rider: public CreatureScript
{
public:
    npc_stormwind_gryphon_rider() : CreatureScript("npc_stormwind_gryphon_rider") {}

    struct npc_stormwind_gryphon_rider_eventAI : public ScriptedAI
    {
        npc_stormwind_gryphon_rider_eventAI(Creature *c) : ScriptedAI(c) {}

        uint32 timer_greymane_resolve;
        uint32 timer_shoot;

        void Reset ()
        {
            timer_greymane_resolve = 360000;
            timer_shoot = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (timer_greymane_resolve<= diff)
            {
                DoCast(me, SPELL_GREYMANE_RESOLVE);
                timer_greymane_resolve = 360000;
            } else timer_greymane_resolve -= diff;

            if (timer_shoot<= diff)
            {
                DoCast(me->getVictim(), SPELL_SHOOT);
                timer_shoot = 5000;
            } else timer_shoot -= diff;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_stormwind_gryphon_rider_eventAI(pCreature);
    }
};

/*******************
**Stormwind Guard
********************/
enum eStormwindGuard
{
    SPELL_SHOOT_2 = 95826
};

class npc_stormwind_guard: public CreatureScript
{
public:
    npc_stormwind_guard() : CreatureScript("npc_stormwind_guard") {}

    struct npc_stormwind_guard_eventAI : public ScriptedAI
    {
        npc_stormwind_guard_eventAI(Creature *c) : ScriptedAI(c) {}

        uint32 shoot_2;

        void Reset()
        {
            shoot_2 = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (shoot_2<= diff)
            {
                DoCast(me->getVictim(), SPELL_SHOOT_2);
                shoot_2 = 5000;
            } else shoot_2 -= diff;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_stormwind_guard_eventAI(pCreature);
    }
};

/***************************
** Stormwind Harbor Guard
****************************/

enum eStormwindHarborGuard
{
    SPELL_SHOOT_3 = 95826
};

class npc_stormwind_harbor_guard: public CreatureScript
{
public:
    npc_stormwind_harbor_guard() : CreatureScript("npc_stormwind_harbor_guard") {}

    struct npc_stormwind_harbor_guard_eventAI : public ScriptedAI
    {
        npc_stormwind_harbor_guard_eventAI(Creature *c) : ScriptedAI(c) {}

        uint32 shoot_3;

        void Reset()
        {
            shoot_3 = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (shoot_3<= diff)
            {
                DoCast(me->getVictim(), SPELL_SHOOT_3);
                shoot_3 = 5000;
            } else shoot_3 -= diff;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_stormwind_harbor_guard_eventAI(pCreature);
    }
};

/**************************
** Stormwind City Patroller
***************************/

enum eStormwindCityPatroller
{
    SPELL_SHOOT_4 = 95826
};

class npc_stormwind_city_patroller: public CreatureScript
{
public:
    npc_stormwind_city_patroller() : CreatureScript("npc_stormwind_city_patroller") {}

    struct npc_stormwind_city_patroller_eventAI : public ScriptedAI
    {
        npc_stormwind_city_patroller_eventAI(Creature *c) : ScriptedAI(c) {}

        uint32 shoot_4;

        void Reset()
        {
            shoot_4 = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (shoot_4<= diff)
            {
                DoCast(me->getVictim(), SPELL_SHOOT_4);
                shoot_4 = 5000;
            } else shoot_4 -= diff;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_stormwind_city_patroller_eventAI(pCreature);
    }
};

/*************************
**Stormwind Royal Guard
**************************/

enum eStormwindRoyalGuard
{
    SPELL_SPIT = 58519,
    SPELL_BANNANA = 58514,
    SPELL_APPLE = 58511,
    SPELL_SHOOT_5 = 95826
};

class npc_stormwind_royal_guard: public CreatureScript
{
public:
    npc_stormwind_royal_guard() : CreatureScript("npc_stormwind_royal_guard") {}

    struct npc_stormwind_royal_guard_eventAI : public ScriptedAI
    {
        npc_stormwind_royal_guard_eventAI(Creature *c) : ScriptedAI(c) {}

        uint32 spit;
        uint32 banana;
        uint32 apple;
        uint32 shoot_5;

        void Reset ()
        {
            spit = 45000;
            banana = 45000;
            apple = 45000;
            shoot_5 = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (spit<= diff)
            {
                DoCast(me->getVictim(), SPELL_SPIT);
                spit = 45000;
            } else spit -= diff;

            if (banana<= diff)
            {
                DoCast(me->getVictim(), SPELL_BANNANA);
                banana = 45000;
            } else banana -= diff;

            if (apple<= diff)
            {
                DoCast(me->getVictim(), SPELL_APPLE);
                apple = 45000;
            }

            if (shoot_5<= diff)
            {
                DoCast(me->getVictim(), SPELL_SHOOT_5);
                shoot_5 = 5000;
            } else shoot_5 -= diff;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_stormwind_royal_guard_eventAI(pCreature);
    }
};

void AddSC_stormwind_city()
{
    new npc_archmage_malin();
    new npc_bartleby();
    new npc_dashel_stonefist();
    new npc_lady_katrana_prestor();
    new npc_tyrion();
    new npc_tyrion_spybot();
    new npc_lord_gregor_lescovar();
    new npc_marzon_silent_blade();
    new npc_stormwind_gryphon_rider();
    new npc_stormwind_guard();
    new npc_stormwind_harbor_guard();
    new npc_stormwind_city_patroller();
    new npc_stormwind_royal_guard();
}