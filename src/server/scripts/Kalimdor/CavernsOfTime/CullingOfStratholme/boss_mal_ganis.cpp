/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
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

/* Script Data Start
SFName: Boss mal_ganis
SFAuthor: Tartalo
SF%Complete: 80
SFComment: TODO: Intro & outro
SFCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_CARRION_SWARM                         = 52720, //A cresting wave of chaotic magic splashes over enemies in front of the caster, dealing 3230 to 3570 Shadow damage and 380 to 420 Shadow damage every 3 sec. for 15 sec.
    H_SPELL_CARRION_SWARM                       = 58852,
    SPELL_MIND_BLAST                            = 52722, //Inflicts 4163 to 4837 Shadow damage to an enemy.
    H_SPELL_MIND_BLAST                          = 58850,
    SPELL_SLEEP                                 = 52721, //Puts an enemy to sleep for up to 10 sec. Any damage caused will awaken the target.
    H_SPELL_SLEEP                               = 58849,
    SPELL_VAMPIRIC_TOUCH                        = 52723, //Heals the caster for half the damage dealt by a melee attack.
    SPELL_KILL_CREDIT                           = 58630  // Non-existing spell as encounter credit, created in spell_dbc
};

enum Yells
{
    SAY_INTRO_1                                 = -1595009,
    SAY_INTRO_2                                 = -1595010,
    SAY_AGGRO                                   = -1595011,
    SAY_KILL_1                                  = -1595012,
    SAY_KILL_2                                  = -1595013,
    SAY_KILL_3                                  = -1595014,
    SAY_SLAY_1                                  = -1595015,
    SAY_SLAY_2                                  = -1595016,
    SAY_SLAY_3                                  = -1595017,
    SAY_SLAY_4                                  = -1595018,
    SAY_SLEEP_1                                 = -1595019,
    SAY_SLEEP_2                                 = -1595020,
    SAY_30HEALTH                                = -1595021,
    SAY_15HEALTH                                = -1595022,
    SAY_ESCAPE_SPEECH_1                         = -1595023,
    SAY_ESCAPE_SPEECH_2                         = -1595024,
    SAY_OUTRO                                   = -1595025,
};

enum CombatPhases
{
    COMBAT,
    OUTRO
};

#define MalGanis_Kill_Credit 31006

class boss_mal_ganis : public CreatureScript
{
public:
    boss_mal_ganis() : CreatureScript("boss_mal_ganis") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_mal_ganisAI (creature);
    }

    struct boss_mal_ganisAI : public ScriptedAI
    {
        boss_mal_ganisAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        uint32 CarrionSwarmTimer;
        uint32 MindBlastTimer;
        uint32 VampiricTouchTimer;
        uint32 SleepTimer;

        uint8 OutroStep;
        uint32 OutroTimer;

        bool bYelled;
        bool bYelled2;

        CombatPhases Phase;

        InstanceScript* instance;

        void Reset()
        {
             bYelled = false;
             bYelled2 = false;
             Phase = COMBAT;
             CarrionSwarmTimer = 6000;
             MindBlastTimer = 11000;
             VampiricTouchTimer = urand(10000, 15000);
             SleepTimer = urand(15000, 20000);
             OutroTimer = 1000;

             if (instance)
                 instance->SetData(DATA_MAL_GANIS_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            if (instance)
                instance->SetData(DATA_MAL_GANIS_EVENT, IN_PROGRESS);
        }

        void DamageTaken(Unit* done_by, uint32 &damage)
        {
            if (damage >= me->GetHealth() && done_by != me)
                damage = me->GetHealth()-1;
        }

        void UpdateAI(const uint32 diff)
        {
            switch (Phase)
            {
                case COMBAT:
                    //Return since we have no target
                    if (!UpdateVictim())
                        return;

                    if (!bYelled && HealthBelowPct(30))
                    {
                        DoScriptText(SAY_30HEALTH, me);
                        bYelled = true;
                    }

                    if (!bYelled2 && HealthBelowPct(15))
                    {
                        DoScriptText(SAY_15HEALTH, me);
                        bYelled2 = true;
                    }

                    if (HealthBelowPct(1))
                    {
                        //Handle Escape Event: Don't forget to add Player::RewardPlayerAndGroupAtEvent
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        OutroStep = 1;
                        Phase = OUTRO;
                        return;
                    }

                    if (Creature* pArthas = me->GetCreature(*me, instance ? instance->GetData64(DATA_ARTHAS) : 0))
                        if (pArthas->isDead())
                        {
                            EnterEvadeMode();
                            me->DisappearAndDie();
                            if (instance)
                                instance->SetData(DATA_MAL_GANIS_EVENT, FAIL);
                        }

                    if (CarrionSwarmTimer < diff)
                    {
                        DoCastVictim(SPELL_CARRION_SWARM);
                        CarrionSwarmTimer = 7000;
                    }
                    else CarrionSwarmTimer -= diff;

                    if (MindBlastTimer < diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_MIND_BLAST);
                        MindBlastTimer = 6000;
                    }
                    else MindBlastTimer -= diff;

                    if (VampiricTouchTimer < diff)
                    {
                        DoCast(me, SPELL_VAMPIRIC_TOUCH);
                        VampiricTouchTimer = 32000;
                    }
                    else VampiricTouchTimer -= diff;

                    if (SleepTimer < diff)
                    {
                        DoScriptText(RAND(SAY_SLEEP_1, SAY_SLEEP_2), me);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_SLEEP);
                        SleepTimer = urand(15000, 20000);
                    }
                    else SleepTimer -= diff;

                    DoMeleeAttackIfReady();
                    break;
                case OUTRO:
                    if (OutroTimer < diff)
                    {
                        switch (OutroStep)
                        {
                            case 1:
                                DoScriptText(SAY_ESCAPE_SPEECH_1, me);
                                me->GetMotionMaster()->MoveTargetedHome();
                                ++OutroStep;
                                OutroTimer = 8000;
                                break;
                            case 2:
                                me->SetTarget(instance ? instance->GetData64(DATA_ARTHAS) : 0);
                                me->HandleEmoteCommand(29);
                                DoScriptText(SAY_ESCAPE_SPEECH_2, me);
                                ++OutroStep;
                                OutroTimer = 9000;
                                break;
                            case 3:
                                DoScriptText(SAY_OUTRO, me);
                                ++OutroStep;
                                OutroTimer = 16000;
                                break;
                            case 4:
                                me->HandleEmoteCommand(33);
                                ++OutroStep;
                                OutroTimer = 500;
                                break;
                            case 5:
                                if (instance)
                                {
                                    Map::PlayerList const & PlList = instance->instance->GetPlayers();
                                    if (!PlList.isEmpty())
                                        for (Map::PlayerList::const_iterator itr = PlList.begin(); itr != PlList.end(); ++itr)
                                            if (Player * player = itr->getSource())
                                                player->KilledMonsterCredit(MalGanis_Kill_Credit, 0);
                                }
                                me->SetVisible(false);
                                me->Kill(me);
                                break;
                        }
                    }
                    else
                        OutroTimer -= diff;
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (instance)
            {
                instance->SetData(DATA_MAL_GANIS_EVENT, DONE);

                // give achievement credit and LFG rewards to players. criteria use spell 58630 which doesn't exist, but it was created in spell_dbc
                DoCast(me, SPELL_KILL_CREDIT);
            }
        }

        void KilledUnit(Unit* victim)
        {
            if (victim == me)
                return;

            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3, SAY_SLAY_4), me);
        }
    };
};

void AddSC_boss_mal_ganis()
{
    new boss_mal_ganis();
}
