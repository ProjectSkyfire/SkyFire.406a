/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

/*
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "ScriptPCH.h"

enum MageSpells
{
    SPELL_MAGE_COLD_SNAP                         = 11958,
    SPELL_MAGE_SQUIRREL_FORM                     = 32813,
    SPELL_MAGE_GIRAFFE_FORM                      = 32816,
    SPELL_MAGE_SERPENT_FORM                      = 32817,
    SPELL_MAGE_DRAGONHAWK_FORM                   = 32818,
    SPELL_MAGE_WORGEN_FORM                       = 32819,
    SPELL_MAGE_SHEEP_FORM                        = 32820,
    SPELL_MAGE_GLYPH_OF_ETERNAL_WATER            = 70937,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT  = 70908,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY  = 70907,
    SPELL_MAGE_FLAMESTRIKE                       = 2120,
    SPELL_MAGE_BLASTWAVE                         = 11113,
    SPELL_MAGE_GLYPH_OF_ICE_BARRIER              = 63095,
};

class spell_mage_blast_wave : public SpellScriptLoader
{
public:
    spell_mage_blast_wave() : SpellScriptLoader("spell_mage_blast_wave") { }

    class spell_mage_blast_wave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_blast_wave_SpellScript);

        std::list<Unit*> targetList;
        uint32 count;
        float x;
        float y;
        float z;

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FLAMESTRIKE) ||
                !sSpellMgr->GetSpellInfo(SPELL_MAGE_BLASTWAVE))
                return false;
            return true;
        }
        bool Load()
        {
            x = GetExplTargetDest()->GetPositionX();
            y = GetExplTargetDest()->GetPositionY();
            z = GetExplTargetDest()->GetPositionZ();
            count = 0;
            targetList.clear();
            return true;
        }

        void FilterTargets(std::list<Unit*>& unitList)
        {
            count = unitList.size();
        }

        void HandleExtraEffect()
        {
            Unit* caster = GetCaster();
            if (AuraEffect const* impFlamestrike = caster->GetDummyAuraEffect(SPELLFAMILY_MAGE, 37, EFFECT_0))
            {
                if (count >= 2 && roll_chance_i(impFlamestrike->GetAmount()))
                    caster->CastSpell(x, y, z, SPELL_MAGE_FLAMESTRIKE, true);
            }   
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_mage_blast_wave_SpellScript::HandleExtraEffect);
            OnUnitTargetSelect += SpellUnitTargetFn(spell_mage_blast_wave_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_blast_wave_SpellScript();
    }
};

class spell_mage_cold_snap : public SpellScriptLoader
{
public:
    spell_mage_cold_snap() : SpellScriptLoader("spell_mage_cold_snap") { }

    class spell_mage_cold_snap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_cold_snap_SpellScript)
        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // immediately finishes the cooldown on Frost spells
            const SpellCooldowns& cm = caster->ToPlayer()->GetSpellCooldownMap();
            for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first);

                if (spellInfo->SpellFamilyName == SPELLFAMILY_MAGE &&
                    (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FROST) &&
                    spellInfo->Id != SPELL_MAGE_COLD_SNAP && spellInfo->GetRecoveryTime() > 0)
                {
                    caster->ToPlayer()->RemoveSpellCooldown((itr++)->first, true);
                }
                else
                    ++itr;
            }
        }

        void Register()
        {
            // add dummy effect spell handler to Cold Snap
            OnEffectHit += SpellEffectFn(spell_mage_cold_snap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_cold_snap_SpellScript();
    }
};

class spell_mage_summon_water_elemental : public SpellScriptLoader
{
public:
    spell_mage_summon_water_elemental() : SpellScriptLoader("spell_mage_summon_water_elemental") { }

    class spell_mage_summon_water_elemental_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_summon_water_elemental_SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER) || !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY) || !sSpellMgr->GetSpellInfo(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            // Glyph of Eternal Water
            if (caster->HasAura(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER))
                caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT, true);
            else
                caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY, true);
        }

        void Register()
        {
            // add dummy effect spell handler to Summon Water Elemental
            OnEffectHit += SpellEffectFn(spell_mage_summon_water_elemental_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_summon_water_elemental_SpellScript();
    }
};

// Frost Warding
class spell_mage_frost_warding_trigger : public SpellScriptLoader
{
public:
    spell_mage_frost_warding_trigger() : SpellScriptLoader("spell_mage_frost_warding_trigger") { }

    class spell_mage_frost_warding_trigger_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_frost_warding_trigger_AuraScript);

        enum Spells
        {
            SPELL_MAGE_FROST_WARDING_TRIGGERED = 57776,
            SPELL_MAGE_FROST_WARDING_R1 = 28332,
        };

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_TRIGGERED)
                && sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_R1);
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit* target = GetTarget();
            if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_FROST_WARDING_R1, EFFECT_0))
            {
                int32 chance = talentAurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue();

                if (roll_chance_i(chance))
                {
                    absorbAmount = dmgInfo.GetDamage();
                    int32 bp = absorbAmount;
                    target->CastCustomSpell(target, SPELL_MAGE_FROST_WARDING_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
                }
            }
        }

        void Register()
        {
             OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_frost_warding_trigger_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_frost_warding_trigger_AuraScript();
    }
};

class spell_mage_incanters_absorbtion_base_AuraScript : public AuraScript
{
public:
    enum Spells
    {
        SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED = 44413,
        SPELL_MAGE_INCANTERS_ABSORBTION_R1 = 44394,
    };

    bool Validate(SpellInfo const* /*spellEntry*/)
    {
        return sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)
            && sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION_R1);
    }

    void Trigger(AuraEffect* aurEff, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
    {
        Unit* target = GetTarget();

        if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_INCANTERS_ABSORBTION_R1, EFFECT_0))
        {
            int32 bp = CalculatePctN(absorbAmount, talentAurEff->GetAmount());
            target->CastCustomSpell(target, SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
        }
    }
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_absorb : public SpellScriptLoader
{
public:
    spell_mage_incanters_absorbtion_absorb() : SpellScriptLoader("spell_mage_incanters_absorbtion_absorb") { }

    class spell_mage_incanters_absorbtion_absorb_AuraScript : public spell_mage_incanters_absorbtion_base_AuraScript
    {
        PrepareAuraScript(spell_mage_incanters_absorbtion_absorb_AuraScript);

        void Register()
        {
             AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_incanters_absorbtion_absorb_AuraScript::Trigger, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_incanters_absorbtion_absorb_AuraScript();
    }
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_manashield : public SpellScriptLoader
{
public:
    spell_mage_incanters_absorbtion_manashield() : SpellScriptLoader("spell_mage_incanters_absorbtion_manashield") { }

    class spell_mage_incanters_absorbtion_manashield_AuraScript : public spell_mage_incanters_absorbtion_base_AuraScript
    {
        PrepareAuraScript(spell_mage_incanters_absorbtion_manashield_AuraScript);

        void Register()
        {
             AfterEffectManaShield += AuraEffectManaShieldFn(spell_mage_incanters_absorbtion_manashield_AuraScript::Trigger, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_incanters_absorbtion_manashield_AuraScript();
    }
};

// Power Word Barrier
class npc_power_word_barrier : public CreatureScript
{
public:
    npc_power_word_barrier() : CreatureScript("npc_power_word_barrier") { }

    struct npc_power_word_barrierAI : public ScriptedAI
    {
        npc_power_word_barrierAI(Creature *creature) : ScriptedAI(creature) {}

        bool checker;
        uint32 cron; // Duration

        void Reset()
        {
            checker = false;
            cron = 10000;
            DoCast(me, 81781);
        }

        void InitializeAI()
        {
            ScriptedAI::InitializeAI();
            Unit* owner = me->GetOwner();
            if (!owner || owner->GetTypeId() != TYPEID_PLAYER)
                return;

            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void BarrierChecker(Unit* who)
        {
            if (who->isAlive() && !who->HasAura(81782))
            {
                me->CastSpell(who, 81782, true);
            }

            if (who->isAlive() && who->HasAura(81782))
            {
                if (AuraEffect const* aur = who->GetAuraEffect(81782, 0))
                    aur->GetBase()->SetDuration(aur->GetSpellInfo()->GetMaxDuration(), true);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (cron <= diff)
            {
                if (!checker)
                {
                    checker = true;
                    cron = 10000;   //10 seconds
                }
                else
                    me->DisappearAndDie();
            }
            else
                cron -= diff;

           //Check friendly entities
           std::list<Unit*> targets;
            SkyFire::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 7.0f);
            SkyFire::UnitListSearcher<SkyFire::AnyFriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);

            me->VisitNearbyObject(7.0f, searcher);
            for (std::list<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                BarrierChecker(*iter);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_power_word_barrierAI(creature);
    }
};

// Ice Barrier
// Spell Id: 11426
class spell_mage_ice_barrier : public SpellScriptLoader
{
public:
    spell_mage_ice_barrier() : SpellScriptLoader("spell_mage_ice_barrier") { }

    class spell_mage_ice_barrier_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_ice_barrier_AuraScript);

        void CalculateAmount(AuraEffect const* aurEff, int32 & amount, bool & canBeRecalculated)
        {
            if (AuraEffect const* glyph = GetCaster()->GetAuraEffect(SPELL_MAGE_GLYPH_OF_ICE_BARRIER, 0))
                amount += glyph->GetAmount(); // 30% increase absorb from glyph

            canBeRecalculated = false;
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_ice_barrier_AuraScript();
    }
};

void AddSC_mage_spell_scripts()
{
    new spell_mage_blast_wave;
    new spell_mage_cold_snap;
    new spell_mage_frost_warding_trigger();
    new spell_mage_incanters_absorbtion_absorb();
    new spell_mage_incanters_absorbtion_manashield();
    new spell_mage_summon_water_elemental;
    new spell_mage_ice_barrier;
}
