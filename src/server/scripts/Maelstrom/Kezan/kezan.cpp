/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
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
#include "ScriptedFollowerAI.h"
#include "kezan.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Group.h"
#include "Map.h"

// npc_deffiant_troll
enum NPC_DeffiantTroll
{
    DEFFIANT_KILL_CREDIT               = 34830,
    SPELL_LIGHTNING_VISUAL             = 45870,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND    = 14069,
    GO_DEPOSIT                         = 195489,
};

#define SAY_WORK_1 "Oops, break's over."
#define SAY_WORK_2 "Don't tase me, mon!"
#define SAY_WORK_3 "I report you to HR!"
#define SAY_WORK_4 "Work was bettah in da Undermine!"
#define SAY_WORK_5 "I'm going. I'm going!"
#define SAY_WORK_6 "Sorry, mon. It won't happen again."
#define SAY_WORK_7 "What I doin' wrong? Don't I get a lunch and two breaks a day, mon?"
#define SAY_WORK_8 "Ouch! Dat hurt!"

class npc_defiant_troll : public CreatureScript
{
    public:
    npc_defiant_troll() : CreatureScript("npc_defiant_troll") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_defiant_trollAI(creature);
    }

    struct npc_defiant_trollAI : public ScriptedAI
    {
        npc_defiant_trollAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 rebuffTimer;
        bool work;

        void Reset ()
        {
            rebuffTimer = 0;
            work = false;
        }

        void MovementInform(uint32 /*type*/, uint32 id)
        {
            if (id == 1)
                work = true;
        }

        void SpellHit(Unit* caster, const SpellEntry* spell)
        {
            if (spell->Id == SPELL_LIGHTNING_VISUAL && caster->GetTypeId() == TYPEID_PLAYER
                && caster->ToPlayer()->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_INCOMPLETE && work == false)
            {
                caster->ToPlayer()->KilledMonsterCredit(DEFFIANT_KILL_CREDIT, me->GetGUID());
                switch (urand(0, 7))
                {
                    case 0:
                        me->MonsterYell(SAY_WORK_1, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 1:
                        me->MonsterYell(SAY_WORK_2, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 2:
                        me->MonsterYell(SAY_WORK_3, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 3:
                        me->MonsterYell(SAY_WORK_4, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 4:
                        me->MonsterYell(SAY_WORK_5, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 5:
                        me->MonsterYell(SAY_WORK_6, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 6:
                        me->MonsterYell(SAY_WORK_7, LANGUAGE_UNIVERSAL, 0);
                        break;
                    case 7:
                        me->MonsterYell(SAY_WORK_8, LANGUAGE_UNIVERSAL, 0);
                        break;
                }
                me->RemoveAllAuras();
                if (GameObject* Deposit = me->FindNearestGameObject(GO_DEPOSIT, 20))
                    me->GetMotionMaster()->MovePoint(1, Deposit->GetPositionX()-1, Deposit->GetPositionY(), Deposit->GetPositionZ());
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (work == true)
                me->HandleEmoteCommand(467);

            if (rebuffTimer <= diff)
            {
                switch (urand(0, 2))
                {
                    case 0:
                        me->HandleEmoteCommand(412);
                        break;
                    case 1:
                        me->HandleEmoteCommand(10);
                        break;
                    case 2:
                        me->HandleEmoteCommand(0);
                        break;
                }
                rebuffTimer = 120000;                 //Rebuff agian in 2 minutes
            }
            else
                rebuffTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(creature, SPELL_LIGHTNING_VISUAL, true);
            SpellEntry const* spell = sSpellStore.LookupEntry(SPELL_LIGHTNING_VISUAL);
            CAST_AI(npc_defiant_troll::npc_defiant_trollAI, creature->AI())->SpellHit(player, spell);
            return true;
        }
        return false;
    }
};

// this can be moved to SAI.
// npc_fourth_and_goal_target - http://www.wowhead.com/npc=37203/fourth-and-goal-target
class npc_fourth_and_goal_target : public CreatureScript
{
public:
    npc_fourth_and_goal_target() : CreatureScript("npc_fourth_and_goal_target") { }

    struct npc_fourth_and_goal_targetAI : public ScriptedAI
    {
        npc_fourth_and_goal_targetAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() {}

        void UpdateAI(const uint32 /*diff*/)
        {
            Unit* target = NULL;
            target = me->SelectNearestTarget(5.0f);
            if (target && target->GetTypeId() == TYPEID_PLAYER)
                if (target->ToPlayer()->GetQuestStatus(28414) == QUEST_STATUS_INCOMPLETE)
                    target->ToPlayer()->KilledMonsterCredit(37203, 0);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fourth_and_goal_targetAI(creature);
    }
};

enum Hotrod
{
    SPELL_KNOCKBACK         = 66301,
    NPC_ACE                 = 34957,
    NPC_IZZY                = 34959,
    NPC_GOBBLER             = 34958,
    NPC_CITIZEN             = 35075
};

class npc_hotrod : public CreatureScript
{
public:
    npc_hotrod() : CreatureScript("npc_hotrod") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hotrodAI(creature);
    }

    struct npc_hotrodAI : public ScriptedAI
    {
        npc_hotrodAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
        }

        void UpdateAI(uint32 const diff)
        {
            if (me->GetCreatorGUID() != 0)
                return;

            if (Player* player = me->FindNearestPlayer(10.0f, true))
            {
                if (player->GetQuestStatus(14071) == QUEST_STATUS_INCOMPLETE && player->HasAura(66392))
                {
                    if (player->GetVehicle())
                    {
                        int8 seat = 0;
                        for (int8 i = 1; i < 4; i++)
                        {
                            if (player->GetVehicle()->HasEmptySeat(i))
                                seat = i;
                            else
                                if (player->GetVehicle()->GetPassenger(i)->GetEntry() == me->GetEntry())
                                    return;
                        }

                        if (seat > 0)
                            me->EnterVehicle(player, seat);
                            player->KilledMonsterCredit(me->GetEntry(), NULL);

                            if (!me->IsMounted())
                            {
                                me->GetMotionMaster()->MoveFollow(player, 5.0f,1.86f);
                            }
                    }
                }
            }
        }
    };
};

class npc_trio : public CreatureScript
{
public:

    npc_trio() : CreatureScript("npc_trio") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_trioAI(creature);
    }

    struct npc_trioAI : public ScriptedAI
    {
        npc_trioAI(Creature* creature) : ScriptedAI(creature){}

        uint32 TrioTimer;

        void Reset()
        {
            TrioTimer = 2000;
        }

        void UpdateAI(uint32 const diff)
        {
            if (TrioTimer <= diff)
            {
                if (Creature* Auto = me->FindNearestCreature(34840, 10.0f, true))
                {
                    if ((Auto->GetOwner()) && (Auto->GetOwner()->GetTypeId() == TYPEID_PLAYER) && (Auto->GetOwner()->ToPlayer()->GetQuestStatus(14071) == QUEST_STATUS_INCOMPLETE))
                    {
                        switch (me->GetEntry())
                        {
                            case 34954:
                            {
                                if (me->FindNearestCreature(34958, 10.0f, true))
                                return;

                                me->SummonCreature(34958, -8180.56f, 1317.45f, 27.53f, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
                                break;
                            }
                            case 34892:
                            {
                                if (me->FindNearestCreature(34957, 10.0f, true))
                                return;

                                me->SummonCreature(34957, -8076.68f, 1476.48f, 8.84f, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
                                break;
                            }
                            case 34890:
                            {
                                if (me->FindNearestCreature(34959, 10.0f, true))
                                return;

                                me->SummonCreature(34959, -8503.83f, 1338.88f, 101.69f, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
                                break;
                            }
                        }
                    }
                }
            }
            else
                TrioTimer -= diff;
        }
    };
};

enum Bilgewater_Death
{
    SPELL_KICK_FOOTBOMB                 = 70051,
    SPELL_CATS_MARK_AURA_INVIS          = 70086,
    SPELL_EARTHQUAKE                    = 90615,
    SPELL_SOUND_DEATHWING               = 69988,
    SPELL_DEATHWING_ATTACK              = 66858,
    SPELL_PANICKED_CITIZEN_INVIS        = 90636,
    SPELL_SUMMON_DEATHWING              = 66322,
    QUEST_FOURTH_GOAL                   = 24503
};
class npc_bilgewater_deathwing : public CreatureScript
{
public:

    npc_bilgewater_deathwing() : CreatureScript("npc_bilgewater") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bilgewater_deathwingAI(creature);
    }

    struct npc_bilgewater_deathwingAI : public ScriptedAI
    {
        npc_bilgewater_deathwingAI(Creature* creature) : ScriptedAI(creature){}

        void Reset()
        {
        }

        void UpdateAI()
        {
        }
    };
};

enum RobbingHoods
{
    SPELL_CREATE_ROBBING    = 67041,
    NPC_HIRED_LOOTER        = 35234,
    //knockback spell 66301
};

class npc_robbing_hoods : public CreatureScript
{
public:

    npc_robbing_hoods() : CreatureScript("npc_robbing_hoods") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_robbing_hoodsAI(creature);
    }

    struct npc_robbing_hoodsAI : public ScriptedAI
    {
        npc_robbing_hoodsAI(Creature* creature) : ScriptedAI(creature){}

        bool bCasted;
        uint32 GetHitTimer;

        void Reset()
        {
            bCasted = false;
            GetHitTimer = 1000;
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() == TYPEID_UNIT)
            {
                if (who->GetEntry() == 34840 && me->IsWithinDistInMap(who, 3.0f))
                {
                    me->CastSpell(me, SPELL_KNOCKBACK, false);
                    bCasted = true;

                    if (Unit* owner = who->GetCharmerOrOwnerOrSelf())
                    {
                        owner->CastSpell(owner, SPELL_CREATE_ROBBING, true);
                    }
                }
            }
        }

        void UpdateAI(uint32 const diff)
        {
            if (bCasted == true)
            {
                if (GetHitTimer <= diff)
                {
                    me->Kill(me);
                }
                GetHitTimer -= diff;
            }
        }
    };
};

enum eTres
{
    SPELL_CREATE_SHINY_BLING    = 66780,
    SPELL_CREATE_NEW_OUTFIT     = 66781,
    SPELL_CREATE_COOL_SHADES    = 66782,
};

#define GOSSIP_SZABO "Szabo, I need a hip, new outfit for the party. I'm throwing!"
#define GOSSIP_MISSA "I need some cool shades. What will two stacks of macaroons get me?"
#define GOSSIP_GAPPY "Set me up with the phattest, shiniest bling you got!"

class npc_new_you : public CreatureScript
{
public:

    npc_new_you() : CreatureScript("npc_new_you") {}

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (Action)
        {
            case GOSSIP_ACTION_INFO_DEF: player->CastSpell(player, SPELL_CREATE_SHINY_BLING, true);   player->CLOSE_GOSSIP_MENU(); break;
            case GOSSIP_ACTION_INFO_DEF+1: player->CastSpell(player, SPELL_CREATE_COOL_SHADES, true); player->CLOSE_GOSSIP_MENU(); break;
            case GOSSIP_ACTION_INFO_DEF+2: player->CastSpell(player, SPELL_CREATE_NEW_OUTFIT, true);  player->CLOSE_GOSSIP_MENU(); break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(14109) == QUEST_STATUS_INCOMPLETE && creature->GetEntry()== 35126)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GAPPY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        }

        if (player->GetQuestStatus(14109) == QUEST_STATUS_INCOMPLETE && creature->GetEntry()== 35130)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_MISSA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        }

        if (player->GetQuestStatus(14109) == QUEST_STATUS_INCOMPLETE && creature->GetEntry()== 35128)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SZABO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }
};

class npc_four_yourself : public CreatureScript
{
public:

    npc_four_yourself() : CreatureScript("npc_four_yourself") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_four_yourselfAI(creature);
    }

    struct npc_four_yourselfAI : public ScriptedAI
    {
        npc_four_yourselfAI(Creature* creature) : ScriptedAI(creature){}

        bool credit;
        uint32 RespawnTimer;
        uint32 DespawnTimer;
        uint64 PlayerGUID;

        void Reset()
        {
            RespawnTimer = 2000;
            DespawnTimer = 4000;
            PlayerGUID = 0;
            me->SetVisible(true);
            me->RestoreFaction();
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* killer)
        {
            me->Respawn(true);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!me->IsVisible())
            {
                if (RespawnTimer <= diff)
                    Reset();
                else
                    RespawnTimer -= diff;
            }
            else
            {
                if (me->GetHealth() <= 1)
                {
                    if (DespawnTimer <= diff)
                    {
                        me->setFaction(35);
                        me->SetVisible(false);
                        me->CombatStop(true);
                        me->AttackStop();
                        me->ClearAllReactives();
                        me->DeleteThreatList();
                        me->SetHealth(me->GetMaxHealth());

                        Player* player = me->GetPlayer(*me, PlayerGUID);
                        if (player->IsInWorld())
                        {
                            player->KilledMonsterCredit(me->GetEntry(), 0);
                        }
                    }
                    else
                        DespawnTimer -= diff;
                }
            }
            DoMeleeAttackIfReady();
        }

        void DamageTaken(Unit* done_by, uint32 & damage)
        {
            if (PlayerGUID == 0)
            {
                if (Player* player = done_by->ToPlayer())
                {
                    PlayerGUID = player->GetGUID();
                }
            }

            if (me->GetHealth() <= damage)
            {
                damage = me->GetHealth() - 1; //

                if (credit == false)
                {
                    me->RemoveAllAuras();
                    me->CombatStop(true);
                    me->AttackStop();
                    me->ClearAllReactives();
                    me->DeleteThreatList();
                }
                credit = true;
            }
        }
    };
};

enum LifeOfTheParty
{
    QUEST_LIFE_OF_THE_PARTY     = 14113,
    QUEST_PIRATE_PARTY          = 14115,
    SPELL_OUTFIT_MALE           = 66928,
    SPELL_OUTFIT_FEMALE         = 66927,
    SPELL_OUTFIT_SECONDARY      = 66985,
    SPELL_AWESOME_PARTY         = 66908,
    SPELL_PHASE_2               = 59073,
    SPELL_PHASE_4               = 59074
};

class npc_party_rock : public CreatureScript
{
public:
    npc_party_rock() : CreatureScript("npc_party_rock") {}

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_LIFE_OF_THE_PARTY)
        {
            if (player->getGender() == GENDER_MALE)
            {
                player->CastSpell(player, SPELL_AWESOME_PARTY, false);
                player->CastSpell(player, SPELL_OUTFIT_MALE, false);
                player->CastSpell(player, SPELL_OUTFIT_SECONDARY, false);
                player->CastSpell(player, SPELL_PHASE_2, false);
                player->MonsterTextEmote("You're dressed to impress! Use your new powers below to make your party guests happy!", 0, true);
            }
            else
            if (player->getGender() == GENDER_FEMALE)
            {
                player->CastSpell(player, SPELL_AWESOME_PARTY, false);
                player->CastSpell(player, SPELL_OUTFIT_FEMALE, false);
                player->CastSpell(player, SPELL_OUTFIT_SECONDARY, false);
                player->CastSpell(player, SPELL_PHASE_2, false);
                player->MonsterTextEmote("You're dressed to impress! Use your new powers below to make your party guests happy!", 0, true);
            }
        }
        return true;
    }
};

class npc_party_pirate : public CreatureScript
{
public:
    npc_party_pirate() : CreatureScript("npc_party_pirate") {}

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_PIRATE_PARTY)
        {
            if (player->getGender() == GENDER_MALE)
            {
                player->RemoveAurasDueToSpell(SPELL_AWESOME_PARTY);
                player->RemoveAurasDueToSpell(SPELL_OUTFIT_MALE);
                player->RemoveAurasDueToSpell(SPELL_OUTFIT_SECONDARY);
                player->CastSpell(player,SPELL_PHASE_4, false);
            }
            else
            if (player->getGender() == GENDER_FEMALE)
            {
                player->RemoveAurasDueToSpell(SPELL_AWESOME_PARTY);
                player->RemoveAurasDueToSpell(SPELL_OUTFIT_FEMALE);
                player->RemoveAurasDueToSpell(SPELL_OUTFIT_SECONDARY);
                player->CastSpell(player,SPELL_PHASE_4, false);
            }
        }
        return true;
    }
};

enum Guest
{
    SPELL_COSMETIC_STUN = 46957,
    SPELL_DRUNKEN_STATE = 55664,
    SPELL_BUBBLY        = 75042,
    SPELL_BUCKET        = 75044,
    SPELL_DANCE         = 75046,
    SPELL_FIREWORKS     = 75048,
    SPELL_HORS_DEV      = 75050,
    SPELL_HAPPY_GUEST   = 66916,

    SPELL_U_FIREWORKS   = 66912,
    SPELL_U_BUBBLY      = 66909,
    SPELL_U_BUCKET      = 66910,
    SPELL_U_DANCE       = 66911,
    SPELL_U_HORS        = 66913
};

const uint32 spellId[5] = {75042, 75044, 75046, 75048, 75050};

class npc_partygoer : public CreatureScript
{
public:

    npc_partygoer() : CreatureScript("npc_partygoer") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_partygoerAI(creature);
    }

    struct npc_partygoerAI : public ScriptedAI
    {
        npc_partygoerAI(Creature* creature) : ScriptedAI(creature){}

        bool spellHit;
        uint32 ResetTimer;
        uint32 BucketTimer;
        uint32 FireWorkTimer;
        uint32 BubblyTimer;
        uint32 DanceTimer;
        uint32 HorsTimer;

        void Reset()
        {
            me->SetVisible(true);
            ResetTimer      = 5000;
            BucketTimer     = 20000;
            BubblyTimer     = 13000;
            FireWorkTimer   = 16000;
            DanceTimer      = 19000;
            HorsTimer       = 14000;
            spellHit        = false;
            me->CastSpell(me, spellId[urand(0, 4)], false);
        }

        void UpdateAI(uint32 const diff)
        {
            if (me->HasAura(SPELL_HAPPY_GUEST))
            {
                if (ResetTimer <= diff)
                {
                    me->RemoveAurasDueToSpell(SPELL_HAPPY_GUEST);
                    me->SetVisible(false);
                    Reset();
                }
                else
                    ResetTimer -= diff;
            }

            if (me->HasAura(SPELL_BUCKET))
            {
                me->CastSpell(me, SPELL_COSMETIC_STUN, false);
                me->CastSpell(me, SPELL_DRUNKEN_STATE, false);

                if (BucketTimer <= diff)
                {
                    me->MonsterSay("Ugh... I need a bucket!", 0, 0);
                    BucketTimer = 20000;
                }
                else
                    BucketTimer -= diff;
            }

            if (me->HasAura(SPELL_FIREWORKS))
            {
                if (FireWorkTimer <= diff)
                {
                    me->CastSpell(me,66918,false);
                    me->MonsterSay("I love fireworks!", 0, 0);
                    FireWorkTimer = 17000;
                }
                else
                    FireWorkTimer -= diff;
            }

            if (me->HasAura(SPELL_U_BUBBLY))
            {
                if (BubblyTimer <= diff)
                {
                    me->MonsterSay("I could really use a refill on my drink here.", 0, 0);
                    BubblyTimer = 14000;
                }
                else
                    BubblyTimer -= diff;
            }

            if (me->HasAura(SPELL_DANCE))
            {
                if (DanceTimer <= diff)
                {
                    me->MonsterSay("If only I had someone to dance with.", 0, 0);
                    DanceTimer = 15000;
                }
                else
                    DanceTimer -= diff;
            }

            if (me->HasAura(SPELL_HORS_DEV))
            {
                if (HorsTimer <= diff)
                {
                    me->MonsterSay("This is delicious! Are there more hors d'oeuvres?", 0, 0);
                    HorsTimer = 21000;
                }
                else
                    HorsTimer -= diff;
            }
        }

        void SpellHit(Unit* caster, const SpellEntry* Spellkind)
        {
            if (me->HasAura(SPELL_FIREWORKS) && Spellkind->Id == 66912  &&  !spellHit)
            {
                me->RemoveAurasDueToSpell(SPELL_FIREWORKS);
                me->CastSpell(me, SPELL_HAPPY_GUEST, false);
                spellHit = true;
                caster->CastSpell(caster, 66917, false);
                caster->ToPlayer()->KilledMonsterCredit(35175, 0);
                me->MonsterSay("Woo, hoo, fireworks! More, more!", 0, 0);
            }

            if (me->HasAura(SPELL_HORS_DEV) && Spellkind->Id == 66913 && !spellHit)
            {
                me->RemoveAurasDueToSpell(SPELL_HORS_DEV);
                me->CastSpell(me, SPELL_HAPPY_GUEST, false);
                spellHit = true;
                me->CastSpell(me, 75124, false);
                caster->ToPlayer()->KilledMonsterCredit(35175, 0);
                me->MonsterSay("Nom, nom, nom!", 0, 0);
            }

            if (me->HasAura(SPELL_DANCE) && Spellkind->Id == 66911 && !spellHit)
            {
                me->RemoveAurasDueToSpell(SPELL_DANCE);
                me->CastSpell(me, SPELL_HAPPY_GUEST, false);
                spellHit = true;
                me->CastSpell(me, 75123, false);
                caster->ToPlayer()->KilledMonsterCredit(35175, 0);
                me->MonsterSay("Shake it like goblinoid picture.", 0, 0);
            }

            if (me->HasAura(SPELL_BUCKET) && Spellkind->Id == 66910 && !spellHit)
            {
                me->RemoveAurasDueToSpell(SPELL_BUCKET);
                me->CastSpell(me, SPELL_HAPPY_GUEST, false);
                spellHit = true;
                me->CastSpell(me, 66931, false);
                caster->ToPlayer()->KilledMonsterCredit(35175, 0);
                me->MonsterSay("Shorry about your shoes.", 0, 0);
            }

            if (me->HasAura(SPELL_BUBBLY) && Spellkind->Id == 66909 && !spellHit)
            {
                me->RemoveAurasDueToSpell(SPELL_BUBBLY);
                me->CastSpell(me, SPELL_HAPPY_GUEST, false);
                spellHit = true;
                me->CastSpell(me, 75122, false);
                caster->ToPlayer()->KilledMonsterCredit(35175, 0);
                me->MonsterSay("Thanks for the refill, sir!", 0, 0);
            }
        }
    };
};

enum Vault
{
    SPELL_ENTER_VAULT       = 67476,
    SPELL_VAULT_CRACKED     = 67492,
    SPELL_VAULT_INTERACT    = 67555,
    SPELL_POWER_CORRECT     = 67493,
    SPELL_POWER_INCORRECT   = 67494,
    SPELL_SUMMON_BUNNY_VEH  = 67488,
    SPELL_EMTEC_VEHICLE     = 67579,
    SPELL_DRILL             = 67495,
    SPELL_EXPLOSIVE         = 67496,
    SPELL_GRAY              = 67499,
    SPELL_LISTEN            = 67497,
    SPELL_LOCKPICK          = 67498,
    SPELL_TIMER             = 67502,

    //VEHICLE SPELLS
    SPELL_GRAY_VEH          = 67526,
    SPELL_LOCKPICK_VEH      = 67525,
    SPELL_LISTEN_VEH        = 67524,
    SPELL_DRILL_VEH         = 67522,
    SPELL_EXPLOSIVE_VEH     = 67508
};

class npc_bank_vault : public CreatureScript
{
public:
    npc_bank_vault() : CreatureScript("npc_bank_vault") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bank_vaultAI(creature);
    }

    struct npc_bank_vaultAI : public ScriptedAI
    {
        npc_bank_vaultAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 PlayerGuid;
        uint32 Timer, PresureTimer, SpellToClick, SelectedSpell;
        uint8 Phase;

        bool IsInCorrectPhase, WasClicked;

        void Reset()
        {
            PlayerGuid = me->GetOwnerGUID();

            Timer           = 2000;
            PresureTimer    = 2000;
            Phase           = 0;
            me->MonsterSay("dupa", 0, 0);
            IsInCorrectPhase = WasClicked = false;
            SpellToClick = SelectedSpell = 0;
            /*
            1 - Button 1 - 67526
            2 - Button 2 - 67508
            3 - Button 3 - 67524
            4 - Button 4 - 67525
            5 - Button 5 - 67522
            */
        }

        void SpellHit(Unit* caster, SpellEntry const* spell)
        {
            if (((caster->GetGUID() != PlayerGuid) || !caster->HasAura(67476)) || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (!WasClicked)
            {
                switch (spell->Id)
                {
                    case 67526: CheckClickedSpell(1);
                    case 67508: CheckClickedSpell(2);
                    case 67524: CheckClickedSpell(3);
                    case 67525: CheckClickedSpell(4);
                    case 67522: CheckClickedSpell(5);
                    default: sLog->outStaticDebug("[!WARNING!]Unhandled Spell In Goblin Bank Quest[!WARNING!] Spell Id: " + spell->Id);
                }
            }
        }

        bool CheckClickedSpell(uint32 SS)
        {
            WasClicked = true;
            Timer = 2000;

            if (SS == SpellToClick)
            {
                me->MonsterTextEmote("Correct!", PlayerGuid, true);
                PresureTimer = 2000;

                if (me->GetPower(me->getPowerType()) > 90)
                {
                    int32 diff = 100 - me->GetPower(me->getPowerType());
                    AddPower(diff);
                }
                else
                    AddPower(10);

                return true;
            }
            else
            {
                AddPower(-10);
                return false;
            }
        }

        void AddPower(int32 dVal)
        {
            if (dVal > 0)
                me->SetPower(me->getPowerType(), me->GetPower(me->getPowerType()) + dVal);
            else
                me->SetPower(me->getPowerType(), me->GetPower(me->getPowerType()) - dVal);
        }

        void SayEventText(uint32 TextIdentifier, Unit* unit)
        {
            switch (TextIdentifier)
            {
                case 1: me->MonsterTextEmote("Spell 1", unit->GetGUID(), true); break;
                case 2: me->MonsterTextEmote("Spell 2", unit->GetGUID(), true); break;
                case 3: me->MonsterTextEmote("Spell 3", unit->GetGUID(), true); break;
                case 4: me->MonsterTextEmote("Spell 4", unit->GetGUID(), true); break;
                case 5: me->MonsterTextEmote("Spell 5", unit->GetGUID(), true); break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 const diff)
        {
            if (Player* player = me->GetPlayer(*me, PlayerGuid))
            {
                if (!IsInCorrectPhase)
                {
                    if (Timer < diff)
                    {
                        switch (Phase)
                        {
                            case 0:
                            {
                                me->MonsterTextEmote("You are about to break into the First Bank of Kezan's vault to retrieve your Personal Riches!", PlayerGuid, true);
                                Phase++;
                                Timer = 8000;
                            }
                            break;
                            // The Vault will be cracked once the Vault Breaking progress bar reaches 100 percent!
                            // Doing the wrong thing at the wrong time will reduce the progress of the bar.
                            case 1: me->MonsterTextEmote("hello World 1", PlayerGuid, true); Phase++;  Timer = 10000; break;
                            case 2: me->MonsterTextEmote("hello World 2", PlayerGuid, true); Phase++;  Timer = 10000; break;
                            case 3: me->MonsterTextEmote("Good luck!", PlayerGuid, true);    Phase++;  Timer = 5000;  break;
                            case 4: IsInCorrectPhase = true; Phase = 0; Timer = 1000; break;
                            default:
                                break;
                        }
                    }
                    else
                        Timer -= diff;
                }

                if (IsInCorrectPhase)
                {
                    if (Aura* pAuraTimer = player->GetAura(67502))
                    {
                        if (PresureTimer < diff)    // Removing 5 Pressure every interval
                        {
                            AddPower(-5);
                            PresureTimer = 2000;
                        }
                        else
                            PresureTimer -= diff;

                        if (pAuraTimer->IsExpired())
                        {
                            if (me->GetPower(me->getPowerType()) > 0)
                            {
                                int32 PowerVal = me->GetPower(me->getPowerType());
                                AddPower(-PowerVal);
                            }
                        }
                    }

                    if (WasClicked)
                    {
                        if (Timer < diff)
                        {
                            if (me->GetPower(me->getPowerType()) < 100)
                            {
                                SpellToClick = urand(1, 5);
                                SayEventText(SpellToClick, player);
                                WasClicked = false;
                                //Timer Spell
                                player->CastSpell(player, 67502, true);
                            }

                            if (me->GetPower(me->getPowerType()) == 100)
                            {
                                player->CastSpell(player, 67492, true);
                                me->MonsterTextEmote("Success! You have your Personal Riches!", PlayerGuid, true);
                                me->ForcedDespawn();
                            }
                        }
                        else
                            Timer -= diff;
                    }
                }
            }
            else
                me->ForcedDespawn();
        }
    };
};

class npc_liberate_chunk : public CreatureScript
{
public:
    npc_liberate_chunk() : CreatureScript("npc_liberate_chunk") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_liberate_chunkAI(creature);
    }

    struct npc_liberate_chunkAI : public ScriptedAI
    {
        npc_liberate_chunkAI(Creature* creature) : ScriptedAI(creature){}

        uint32 BoomTimer;
        uint32 RespawnTimer;
        bool spellHit;

        void Reset()
        {
            RespawnTimer    = 4000;
            BoomTimer       = 1000;
            spellHit        = false;
            me->SetRespawnTime(30);
        }

        void UpdateAI(uint32 const diff)
        {
            if (spellHit == true)
            {
                if (BoomTimer <= diff)
                {
                     me->ForcedDespawn(5000);
                }
                else
                    BoomTimer -= diff;

                if (RespawnTimer <= diff)
                {
                    Reset();
                }
                else
                    RespawnTimer -= diff;
            }
        }

        void SpellHit(Unit* caster, const SpellEntry* Spellkind)
        {
            if (Spellkind->Id == 67682 && !spellHit)
            {
                spellHit = true;
            }
        }
    };
};

enum e477
{
    SPELL_SUMMON_GASBOT = 70252, // http://www.wowhead.com/spell=70252/447-summon-gasbot
};

class npc_447 : public CreatureScript
{
public:
    npc_447() : CreatureScript("npc_447") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_447AI(creature);
    }

    struct npc_447AI : public ScriptedAI
    {
        npc_447AI(Creature* creature) : ScriptedAI(creature){}

        uint8 Phase;
        uint32 MoveTimer;
        uint32 FireTimer;

        void Reset()
        {
            Phase       = 0;
            MoveTimer   = 1500;
            me->CastSpell(me, 69813, false);
            FireTimer   = 15000;
        }

        void UpdateAI(uint32 const diff)
        {
            if (MoveTimer <= diff)
            {
                    switch (Phase)
                    {
                        case 0: me->GetMotionMaster()->MovePoint(1, -8423.04f, 1363.70f, 104.67f); MoveTimer = 11000; Phase++;  break;
                        case 1: me->CastSpell(me, 70259, false); MoveTimer = 1000; Phase++; break;
                        case 2:
                        {
                            std::list<Creature*> fire;
                            me->GetCreatureListWithEntryInGrid(fire, 37682, 40.0f);
                            fire.sort(SkyFire::ObjectDistanceOrderPred(me));
                            for (std::list<Creature*>::iterator itr = fire.begin(); itr != fire.end(); itr++)
                            {
                                if ((*itr)->isAlive() && (*itr)->GetTypeId() == TYPEID_UNIT)
                                {
                                    (*itr)->CastSpell((*itr), 70262, true);
                                    if (FireTimer <= diff)
                                    {
                                        (*itr)->RemoveAurasDueToSpell(70262);
                                    }
                                    else
                                        FireTimer -= diff;
                                }
                            }
                            MoveTimer = 15000;
                            Phase++;
                        }
                        break;
                        case 3: me->ForcedDespawn(); break;
                        default:
                            break;
                    }
            }
            else
                MoveTimer -= diff;
        }
    };
};

class npc_run_away : public CreatureScript
{
public:
    npc_run_away() : CreatureScript("npc_run_away") {}

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == 14126)
        {
            player->SendMovieStart(22);
            player->CastSpell(player, 74100, true);
            player->CastSpell(player, 69010, true);
            player->CastSpell(player, 59043, true);

            WorldLocation loc;
            loc.m_mapId       = 648;
            loc.m_positionX   = -534.62f;
            loc.m_positionY   = 3273.43f;
            loc.m_positionZ   = 0.23f;
            loc._orientation = 4.71f;
            player->SetHomebind(loc, 4721);
        }
        return true;
    }
};

class go_mortar : public GameObjectScript
{
public:
    go_mortar() : GameObjectScript("go_mortar") {}

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->Use(player);

        if (player->GetQuestStatus(14126) ==  QUEST_STATUS_COMPLETE)
        {
            if (Creature* pTarget = go->FindNearestCreature(24288, 50.0f, true))
            {
                player->CastSpell(pTarget, 92633, true);
            }
        }
        return true;
    }
};

void AddSC_kezan()
{
    new npc_fourth_and_goal_target();
    new npc_defiant_troll();
    new npc_hotrod();
    new npc_trio();
    new npc_bilgewater_deathwing();
    new npc_robbing_hoods();
    new npc_new_you();
    new npc_four_yourself();
    new npc_party_rock();
    new npc_party_pirate();
    new npc_partygoer();
    new npc_bank_vault();
    new npc_liberate_chunk();
    new npc_447();
    //new npc_run_away();
    new go_mortar();
}
