/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2012 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
Name: Orgrimmar
%Complete: 100
Comment: Quest support for 2460, 6566 are both obsolete quests for cataclysm and need properly removed.
Category: Orgrimmar
EndScriptData */

/* ContentData
npc_shenthul
npc_thrall_warchief
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_shenthul
######*/

enum Shenthul
{
    QUEST_SHATTERED_SALUTE  = 2460  // Obsolete quest for cata
};

class npc_shenthul : public CreatureScript
{
public:
    npc_shenthul() : CreatureScript("npc_shenthul") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SHATTERED_SALUTE)
        {
            CAST_AI(npc_shenthul::npc_shenthulAI, creature->AI())->CanTalk = true;
            CAST_AI(npc_shenthul::npc_shenthulAI, creature->AI())->PlayerGUID = player->GetGUID();
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shenthulAI (creature);
    }

    struct npc_shenthulAI : public ScriptedAI
    {
        npc_shenthulAI(Creature* creature) : ScriptedAI(creature) {}

        bool CanTalk;
        bool CanEmote;
        uint32 Salute_Timer;
        uint32 Reset_Timer;
        uint64 PlayerGUID;

        void Reset()
        {
            CanTalk = false;
            CanEmote = false;
            Salute_Timer = 6000;
            Reset_Timer = 0;
            PlayerGUID = 0;
        }

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (CanEmote)
            {
                if (Reset_Timer <= diff)
                {
                    if (Player* player = Unit::GetPlayer(*me, PlayerGUID))
                    {
                        if (player->GetTypeId() == TYPEID_PLAYER && player->GetQuestStatus(QUEST_SHATTERED_SALUTE) == QUEST_STATUS_INCOMPLETE)
                            player->FailQuest(QUEST_SHATTERED_SALUTE);
                    }
                    Reset();
                } else Reset_Timer -= diff;
            }

            if (CanTalk && !CanEmote)
            {
                if (Salute_Timer <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                    CanEmote = true;
                    Reset_Timer = 60000;
                } else Salute_Timer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void ReceiveEmote(Player* player, uint32 emote)
        {
            if (emote == TEXT_EMOTE_SALUTE && player->GetQuestStatus(QUEST_SHATTERED_SALUTE) == QUEST_STATUS_INCOMPLETE)
            {
                if (CanEmote)
                {
                    player->AreaExploredOrEventHappens(QUEST_SHATTERED_SALUTE);
                    Reset();
                }
            }
        }
    };
};

/*######
## npc_thrall_warchief
######*/

enum Thrall
{
    QUEST_6566              = 6566,  // obsolete quest for cata
    SPELL_CHAIN_LIGHTNING   = 16033,
    SPELL_SHOCK             = 16034
};

#define GOSSIP_HTW "Please share your wisdom with me, Warchief."
#define GOSSIP_STW1 "What discoveries?"
#define GOSSIP_STW2 "Usurper?"
#define GOSSIP_STW3 "With all due respect, Warchief - why not allow them to be destroyed? Does this not strengthen our position?"
#define GOSSIP_STW4 "I... I did not think of it that way, Warchief."
#define GOSSIP_STW5 "I live only to serve, Warchief! My life is empty and meaningless without your guidance."
#define GOSSIP_STW6 "Of course, Warchief!"

//TODO: verify abilities/timers
class npc_thrall_warchief : public CreatureScript
{
public:
    npc_thrall_warchief() : CreatureScript("npc_thrall_warchief") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(5733, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->SEND_GOSSIP_MENU(5734, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->SEND_GOSSIP_MENU(5735, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                player->SEND_GOSSIP_MENU(5736, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                player->SEND_GOSSIP_MENU(5737, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                player->SEND_GOSSIP_MENU(5738, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(QUEST_6566);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_6566) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HTW, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_thrall_warchiefAI (creature);
    }

    struct npc_thrall_warchiefAI : public ScriptedAI
    {
        npc_thrall_warchiefAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 ChainLightning_Timer;
        uint32 Shock_Timer;

        void Reset()
        {
            ChainLightning_Timer = 2000;
            Shock_Timer = 8000;
        }

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (ChainLightning_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_CHAIN_LIGHTNING);
                ChainLightning_Timer = 9000;
            } else ChainLightning_Timer -= diff;

            if (Shock_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHOCK);
                Shock_Timer = 15000;
            } else Shock_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_hellscream_demolisher
######*/

#define FIRST_ENGINEER_SAY_1 "Ready for inspection, sir!"
#define FIRST_ENGINEER_SAY_2 "See that? Ironclad!"
#define SECOND_ENGINEER_SAY_1 "This baby is all mine! I call her, \"The Throttler.\""
#define SECOND_ENGINEER_SAY_2 "That's right. Takes a lickin' but keeps on kickin' butt!"
#define THIRD_ENGINEER_SAY_1 "Ready for inspection! ...Be gentle."
#define THIRD_ENGINEER_SAY_2 "Uh oh. Um. Oops."
#define THIRD_ENGINEER_SAY_3 "Look, look, it's okay! It's just a tiny little glitch. See?"
#define SIEGEWORKERS_SAY_1 "We'll get right on this, sir!"
#define SIEGEWORKERS_SAY_2 "Yes sir! Right away, sir!"
#define SIEGEWORKERS_SAY_3 "We're on it!"
#define DEMOLISHER_FALL "The demolisher falls apart when inspected."
#define WORKERS_REPAIR "Punish the goblin, kicking him away! Workers goes to repair it right away."
// these defines need cleaned out to be set to enums & creature_text.

class npc_hellscream_demolisher : public CreatureScript
{
public:
    npc_hellscream_demolisher() : CreatureScript("npc_hellscream_demolisher") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(26294) == QUEST_STATUS_INCOMPLETE) // Weapons of mass dysfunction
        {
            if (CAST_AI(npc_hellscream_demolisher::npc_hellscream_demolisherAI, creature->AI())->demolisher_N == 1)
            {
                if (Creature* eng_chief1 = creature->FindNearestCreature(42671, 6.0f, true)) // Find the chief engineer
                {
                    eng_chief1->MonsterSay(FIRST_ENGINEER_SAY_1, LANG_UNIVERSAL, NULL);
                    eng_chief1->MonsterSay(FIRST_ENGINEER_SAY_2, LANG_UNIVERSAL, NULL);
                    CAST_AI(npc_hellscream_demolisher::npc_hellscream_demolisherAI, creature->AI())->demolisher_N = 2;
                }
            }
            else if (CAST_AI(npc_hellscream_demolisher::npc_hellscream_demolisherAI, creature->AI())->demolisher_N == 2)
            {
                if (Creature* eng_chief2 = creature->FindNearestCreature(42671, 6.0f, true)) // Find the chief engineer
                {
                    eng_chief2->MonsterSay(SECOND_ENGINEER_SAY_1, LANG_UNIVERSAL, NULL);
                    eng_chief2->MonsterSay(SECOND_ENGINEER_SAY_2, LANG_UNIVERSAL, NULL);
                    CAST_AI(npc_hellscream_demolisher::npc_hellscream_demolisherAI, creature->AI())->demolisher_N = 3;
                }
            }
            else if (CAST_AI(npc_hellscream_demolisher::npc_hellscream_demolisherAI, creature->AI())->demolisher_N == 3)
            {
                if (Creature* eng_chief3 = creature->FindNearestCreature(42671, 6.0f, true)) // Find the chief engineer
                {
                    eng_chief3->MonsterSay(THIRD_ENGINEER_SAY_1, LANG_UNIVERSAL, NULL);
                    creature->MonsterTextEmote(DEMOLISHER_FALL, 0);
                    eng_chief3->MonsterSay(THIRD_ENGINEER_SAY_2, LANG_UNIVERSAL, NULL);
                    eng_chief3->MonsterSay(THIRD_ENGINEER_SAY_3, LANG_UNIVERSAL, NULL);
                    creature->MonsterTextEmote(WORKERS_REPAIR, 0);
                    player->CompleteQuest(26294);
                    CAST_AI(npc_hellscream_demolisher::npc_hellscream_demolisherAI, creature->AI())->demolisher_N = 1;
                }
            }
        }

        player->PlayerTalkClass->ClearMenus();
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hellscream_demolisherAI(creature);
    }

    struct npc_hellscream_demolisherAI : public ScriptedAI
    {
        npc_hellscream_demolisherAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 demolisher_N;

        void Reset()
        {
            demolisher_N = 1;
        }
    };
};

/*######
## npc_herezegor
######*/

#define HEREZEGOR_OPTION_1 "The Dragonmaw can be great again. Help our conquest of the Twilight Highlands - Can you give me a map?"
#define HEREZEGOR_OPTION_2 "Yes, a map of the coastal approaches."
#define SAY_OK "I will help, but know that you are stepping into a viper's nest. Let me draw you a map - wha - behind you!"
#define SUMMON_SAY "Cover the door! - we've got him!"
#define INK_SAY "Oh no not the bar, take it outside mon!"
#define SAY_BATTLE_1 "Only the weak hide in shadows, Twilight filth!"
#define SAY_BATTLE_2 "Feel the bite of the Dragonmaw!"
#define SAY_BATTLE_3 "Another worm driven to the ground"
#define SPAWN_COORDS    1915.459961f, -4734.319824f, 39.019798f, 1.012290f
// todo clean up these defines to enums.

class npc_herezegor : public CreatureScript
{
public:
    npc_herezegor() : CreatureScript("npc_herezegor") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            {
                creature->MonsterSay(SAY_OK, LANG_UNIVERSAL, NULL);
                CAST_AI(npc_herezegor::npc_herezegorAI, creature->AI())->Start = true;
                CAST_AI(npc_herezegor::npc_herezegorAI, creature->AI())->plrGUID = player->GetGUID();
                break;
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(26311) == QUEST_STATUS_INCOMPLETE)
        {
            if (CAST_AI(npc_herezegor::npc_herezegorAI, creature->AI())->Completed)
                player->PlayerTalkClass->SendGossipMenu(50432, creature->GetGUID());
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, HEREZEGOR_OPTION_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->PlayerTalkClass->SendGossipMenu(50431, creature->GetGUID());
            }
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_herezegorAI(creature);
    }

    struct npc_herezegorAI : public ScriptedAI
    {
        npc_herezegorAI(Creature* creature) : ScriptedAI(creature) {}

        bool Start;
        uint32 TalkTimer;
        bool summonsay;
        bool Completed;

        uint32 deadSummons;
        uint64 plrGUID;
        uint32 phase;
        uint32 say_phase;

        std::list<uint64> SummonList;

        void Reset()
        {
            Start           = false;
            Completed       = false;
            TalkTimer       = 10000;
            plrGUID         = 0;
            phase           = 1;
            say_phase       = 1;
            summonsay       = false;
            deadSummons     = 0;
        }

        void JustSummoned(Creature* summoned)
        {
            if (Player* player = Unit::GetPlayer(*me, plrGUID))
            {
                if (!summonsay)
                {
                    summoned->MonsterSay(SUMMON_SAY, LANG_UNIVERSAL, NULL);

                    if (Creature* gravy = me->FindNearestCreature(42709, 80.0f, true)) // Find Gravy
                        gravy->MonsterSay(INK_SAY, LANG_UNIVERSAL, NULL);

                    summonsay = true;
                }
                summoned->AddThreat(me, 32.0f);
                summoned->AI()->AttackStart(me);
            }
            SummonList.push_back(summoned->GetGUID());
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            if ((deadSummons++) >= 3)
                if (Player* player = Unit::GetPlayer(*me, plrGUID))
                    player->AddItem(58141, 1); // Add the quest item to the player (map)
        }

        void UpdateAI(uint32 const diff)
        {
            if (!Start)
                return;

            Player* player = Unit::GetPlayer(*me, plrGUID);

            if (!player)
                return;

            if (phase == 1)
            {
                for (uint32 i = 0; i < 3; ++i)
                    me->SummonCreature(42707, SPAWN_COORDS, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000); // Summon 3 Twilight Nightblade
                phase = 2;
            }

            if (TalkTimer <= diff && phase == 2)
            {
                switch (say_phase)
                {
                    case 1:
                    {
                        me->MonsterSay(SAY_BATTLE_1, LANG_UNIVERSAL, 0);
                        say_phase = 2;
                        TalkTimer = 3000;
                        break;
                    }
                    case 2:
                    {
                        me->MonsterSay(SAY_BATTLE_2, LANG_UNIVERSAL, 0);
                        say_phase = 0;
                        TalkTimer = 3000;
                        break;
                    }
                    case 3:
                    {
                        me->MonsterSay(SAY_BATTLE_3, LANG_UNIVERSAL, 0);
                        say_phase = 0;
                        break;
                    }
                }
            }
            else TalkTimer -= diff;
        }
    };
};

void AddSC_orgrimmar()
{
    new npc_shenthul();
    new npc_thrall_warchief();
    new npc_hellscream_demolisher();
    new npc_herezegor();
}
