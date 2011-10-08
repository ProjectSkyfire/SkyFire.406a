/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2011 MigCore <http://wow-mig.ru/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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
#include "bastion_of_twilight.h"

enum Spells
{
    SPELL_DRAGON_VENGEANCE      = 87683,
    SPELL_BERSERK               = 26662,
    SPELL_MALEVOLENT_STRAKES    = 39171,
    SPELL_SHADOW_WRAPPED        = 83952,
    SPELL_BIND_WILL             = 83432,
    SPELL_FRENZIED_ASSAULT      = 83693,
    SPELL_FURIOUS_ROAR          = 83710,
    SPELL_SHADOW_NOVA           = 83703,

    // minion's spells
    SPELL_CYCLONE_WINDS         = 83612,
    SPELL_STONE_TOUCH           = 83603,

    SPELL_FREE_DRAGON           = 83447,

    // proto-behemoth spells
    SPELL_SUPERHEATED_BREATH    = 83956,
    SPELL_DANCING_FLAMES        = 84106,
    SPELL_FIREBALL_BARRAGE      = 83706,
    SPELL_SCORCHING_BREATH      = 83707,
    SPELL_FIREBALL              = 86058
};

enum Events
{
    EVENT_NONE,
    EVENT_BERSERK,
    EVENT_SHADOW_NOVA,
    EVENT_FURIOUS_ROAR
};

enum ePhases
{
    PHASE_1   = 1,
    PHASE_2   = 2,
};

class boss_halfus_wyrmbreaker : public CreatureScript
{
public:
    boss_halfus_wyrmbreaker() : CreatureScript("boss_halfus_wyrmbreaker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_halfus_wyrmbreakerAI (creature);
    }

    struct boss_halfus_wyrmbreakerAI : public ScriptedAI
    {
        boss_halfus_wyrmbreakerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 ShadowNovaTimer;
        uint32 BerserkTimer;
        uint32 FuriousRoarTimer;
        uint32 FuriousRoarCount;
        uint32 Phase;
        bool StormRider;
        bool Berserk;

        void Reset()
        {
            ShadowNovaTimer = urand(12000, 17000);
            BerserkTimer = 360000;
            FuriousRoarTimer = 0;
            FuriousRoarCount = 0;
            Phase = PHASE_1;
            StormRider = false;
            Berserk = false;
            if (instance)
            {
                instance->SetData(DATA_HALFUS, NOT_STARTED);
                if (instance->GetData(DATA_STORM_RIDER) == 1)
                {
                    DoCast(me, SPELL_SHADOW_WRAPPED);
                    StormRider = true;
                }
                if (instance->GetData(DATA_THE_SLATE_DRAGON) == 1)
                    DoCast(me, SPELL_MALEVOLENT_STRAKES);
                if (instance->GetData(DATA_NETHER_SCION) == 1)
                    DoCast(me, SPELL_FRENZIED_ASSAULT);
            }
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (instance)
                instance->SetData(DATA_HALFUS, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SetData(DATA_HALFUS, DONE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (StormRider)
                if (ShadowNovaTimer <= diff)
                {
                    DoCast(SPELL_SHADOW_NOVA);
                    ShadowNovaTimer = urand(12000, 17000);
                }
                else
                    ShadowNovaTimer -= diff;

            if (Phase == PHASE_2)
                if (FuriousRoarTimer <= diff)
                    if (FuriousRoarCount < 3)
                    {
                        DoCast(SPELL_FURIOUS_ROAR);
                        ++FuriousRoarCount;
                        FuriousRoarTimer = 1500;
                    }
                    else
                    {
                        DoCast(SPELL_SHADOW_NOVA);
                        FuriousRoarCount = 0;
                        FuriousRoarTimer = urand(12000, 17000);
                    }
                else
                    FuriousRoarTimer -= diff;

            if (!Berserk)
                if (BerserkTimer <= diff)
                {
                    DoCast(SPELL_BERSERK);
                    Berserk = true;
                }
                else
                    BerserkTimer -= diff;

            if (Phase == PHASE_1 && me->HealthBelowPct(50))
                Phase = PHASE_2;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_halfus_dragon_prisoner : public CreatureScript
{
public:
    npc_halfus_dragon_prisoner() : CreatureScript("npc_halfus_dragon_prisoner") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->CastSpell(creature, SPELL_FREE_DRAGON, false);
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_halfus_dragon_prisonerAI (creature);
    }

    struct npc_halfus_dragon_prisonerAI : public ScriptedAI
    {
        npc_halfus_dragon_prisonerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 StoneTouchTimer;

        void Reset()
        {
            StoneTouchTimer = 35000;
        }

        void JustDied(Unit* /*Killer*/)
        {
            if (instance)
                if (Creature* halfus = Unit::GetCreature(*me, instance->GetData64(DATA_HALFUS)))
                    if (Aura* aura = halfus->GetAura(87683))
                        aura->SetStackAmount(aura->GetStackAmount() + 1);
                    else
                        me->AddAura(87683, halfus);
        }

        void SpellHit(Unit* unit, const SpellEntry* spell)
        {
            switch (spell->Id)
            {
                case SPELL_FREE_DRAGON:
                    {
                        if (!instance)
                            return;
                        Creature* halfus = Unit::GetCreature(*me, instance->GetData64(DATA_HALFUS));
                        if (!halfus)
                            return;
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        switch (me->GetEntry())
                        {
                            case NPC_STORM_RIDER:
                                me->AddAura(84092, halfus);
                                break;
                            case NPC_NETHER_SCION:
                                me->AddAura(83611, halfus);
                                break;
                        }
                        halfus->CastSpell(me, SPELL_BIND_WILL, false);
                    }
                    break;
                case SPELL_BIND_WILL:
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (instance)
                if (me->GetEntry() == NPC_THE_SLATE_DRAGON)
                    if (StoneTouchTimer <= diff)
                    {
                        StoneTouchTimer = 35000;
                        if (Creature* halfus = Unit::GetCreature(*me, instance->GetData64(DATA_HALFUS)))
                        {
                            me->AddAura(SPELL_STONE_TOUCH, halfus);
                            if (Aura* stone = halfus->GetAura(SPELL_STONE_TOUCH))
                                stone->SetDuration(12000);
                        }
                    }
                    else
                        StoneTouchTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class boss_proto_behemoth : public CreatureScript
{
public:
    boss_proto_behemoth() : CreatureScript("boss_proto_behemoth") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_proto_behemothAI (creature);
    }

    struct boss_proto_behemothAI : public ScriptedAI
    {
        boss_proto_behemothAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset() {}

        void EnterCombat(Unit* /*who*/) {}

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_halfus_stone_touch : public SpellScriptLoader
{
    public:
        spell_halfus_stone_touch() : SpellScriptLoader("spell_halfus_stone_touch") { }

        class spell_halfus_stone_touch_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halfus_stone_touch_AuraScript);

            void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit * target = GetTarget())
                {
                    target->AddUnitState(UNIT_STAT_STUNNED);
                    target->ClearUnitState(UNIT_STAT_CASTING);
                }
            }

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
               if (Unit* target = GetTarget())
               {
                   target->ClearUnitState(UNIT_STAT_STUNNED);
                   target->AddUnitState(UNIT_STAT_CASTING);
               }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_halfus_stone_touch_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_halfus_stone_touch_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halfus_stone_touch_AuraScript();
        }
};

void AddSC_boss_halfus_wyrmbreaker()
{
    new boss_halfus_wyrmbreaker();
    new boss_proto_behemoth();
    new npc_halfus_dragon_prisoner();
    new spell_halfus_stone_touch();
}