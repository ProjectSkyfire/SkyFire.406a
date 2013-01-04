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

/*
 * Scripts for spells with SPELLFAMILY_SHAMAN and SPELLFAMILY_GENERIC spells used by shaman players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_sha_".
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"

enum ShamanSpells
{
    SHAMAN_SPELL_GLYPH_OF_MANA_TIDE     = 55441,
    SHAMAN_SPELL_MANA_TIDE_TOTEM        = 16191,
    SHAMAN_SPELL_FIRE_NOVA_R1           = 1535,
    SHAMAN_SPELL_FIRE_NOVA_TRIGGERED_R1 = 8349,
    SHAMAN_SPELL_EARTHQUAKE_KNOCKDOWN   = 77505,

    //For Earthen Power
    SHAMAN_TOTEM_SPELL_EARTHBIND_TOTEM  = 6474, //Spell casted by totem
    SHAMAN_TOTEM_SPELL_EARTHEN_POWER    = 59566, //Spell witch remove snare effect
};

// 16191 - Mana Tide
class spell_sha_mana_tide : public SpellScriptLoader
{
public:
    spell_sha_mana_tide() : SpellScriptLoader("spell_sha_mana_tide") { }

    class spell_sha_mana_tide_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_mana_tide_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_MANA_TIDE_TOTEM))
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 &amount, bool & /*canBeRecalculated*/)
        {
            // 400% of caster's spirit
            // Caster is totem, we need owner
            if (Unit* owner = GetCaster()->GetOwner())
                amount = int32(owner->GetStat(STAT_SPIRIT) * 4.0f);
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_mana_tide_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_STAT);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_mana_tide_AuraScript();
    }
};

// 51474 - Astral shift
class spell_sha_astral_shift : public SpellScriptLoader
{
public:
    spell_sha_astral_shift() : SpellScriptLoader("spell_sha_astral_shift") { }

    class spell_sha_astral_shift_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_astral_shift_AuraScript);

        uint32 absorbPct;

        bool Load()
        {
            absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
            return true;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            // reduces all damage taken while stun, fear or silence
            if (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_FLEEING | UNIT_FLAG_SILENCED) || (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_STUNNED) && GetTarget()->HasAuraWithMechanic(1<<MECHANIC_STUN)))
                absorbAmount = CalculatePctN(dmgInfo.GetDamage(), absorbPct);
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_astral_shift_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_sha_astral_shift_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_astral_shift_AuraScript();
    }
};

// 1535 Fire Nova
class spell_sha_fire_nova : public SpellScriptLoader
{
public:
    spell_sha_fire_nova() : SpellScriptLoader("spell_sha_fire_nova") { }

    class spell_sha_fire_nova_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_fire_nova_SpellScript);

        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_FIRE_NOVA_R1))
                return false;
            if (sSpellMgr->GetFirstSpellInChain(SHAMAN_SPELL_FIRE_NOVA_R1) != sSpellMgr->GetFirstSpellInChain(spellEntry->Id))
                return false;

            uint8 rank = sSpellMgr->GetSpellRank(spellEntry->Id);
            if (!sSpellMgr->GetSpellWithRank(SHAMAN_SPELL_FIRE_NOVA_TRIGGERED_R1, rank, true))
                return false;
            return true;
        }

        SpellCastResult CheckFireTotem()
        {
            // fire totem
            if (!GetCaster()->m_SummonSlot[1])
            {
                SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM);
                return SPELL_FAILED_CUSTOM_ERROR;
            }

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            uint8 rank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);
            if (uint32 spellId = sSpellMgr->GetSpellWithRank(SHAMAN_SPELL_FIRE_NOVA_TRIGGERED_R1, rank))
            {
                Creature* totem = caster->GetMap()->GetCreature(caster->m_SummonSlot[1]);
                if (totem && totem->isTotem())
                    totem->CastSpell(totem, spellId, true);
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_sha_fire_nova_SpellScript::CheckFireTotem);
            OnEffectHitTarget += SpellEffectFn(spell_sha_fire_nova_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_fire_nova_SpellScript();
    }
};

// 6474 - Earthbind Totem - Fix Talent:Earthen Power
class spell_sha_earthbind_totem : public SpellScriptLoader
{
public:
    spell_sha_earthbind_totem() : SpellScriptLoader("spell_sha_earthbind_totem") { }

    class spell_sha_earthbind_totem_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earthbind_totem_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SHAMAN_TOTEM_SPELL_EARTHBIND_TOTEM))
                return false;
            if (!sSpellMgr->GetSpellInfo(SHAMAN_TOTEM_SPELL_EARTHEN_POWER))
                return false;
            return true;
        }

        void HandleEffectPeriodic(AuraEffect const* aurEff)
        {
            Unit* target = GetTarget();
            if (Unit* caster = aurEff->GetBase()->GetCaster())
                if (AuraEffect* aur = caster->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, 2289, 0))
                    if (roll_chance_i(aur->GetBaseAmount()))
                        target->CastSpell(target, SHAMAN_TOTEM_SPELL_EARTHEN_POWER, true, NULL, aurEff);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthbind_totem_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_earthbind_totem_AuraScript();
    }
};

enum RaidHasteSpellsBuffsAndDebuffs
{
    HASTE_BUFF_BLOODLUST                = 2825,
    HASTE_DEBUFF_SATED                  = 57724,

    HASTE_BUFF_HEROISM                  = 32182,
    HASTE_DEBUFF_EXHAUSTION             = 57723,

    HASTE_BUFF_TIME_WARP                = 80353,
    HASTE_DEBUFF_TEMPORAL_DISPLACEMENT  = 80354,

    HASTE_BUFF_ANCIENT_HYSTERIA         = 90355,
    HASTE_DEBUFF_INSANITY               = 95809,
};
// Filter targets for Ancient Hysteria, Bloodlust, Heroism, and Time Warp.
class spell_raid_haste : public SpellScriptLoader
{
public:
    spell_raid_haste() : SpellScriptLoader("spell_raid_haste") { }

    class spell_raid_haste_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_raid_haste_SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(HASTE_DEBUFF_SATED) ||
                !sSpellMgr->GetSpellInfo(HASTE_DEBUFF_EXHAUSTION) ||
                !sSpellMgr->GetSpellInfo(HASTE_DEBUFF_TEMPORAL_DISPLACEMENT) ||
                !sSpellMgr->GetSpellInfo(HASTE_DEBUFF_INSANITY))
                return false;
            return true;
        }

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(SkyFire::UnitAuraCheck(true, HASTE_DEBUFF_SATED));
            targets.remove_if(SkyFire::UnitAuraCheck(true, HASTE_DEBUFF_EXHAUSTION));
            targets.remove_if(SkyFire::UnitAuraCheck(true, HASTE_DEBUFF_TEMPORAL_DISPLACEMENT));
            targets.remove_if(SkyFire::UnitAuraCheck(true, HASTE_DEBUFF_INSANITY));
        }

        void ApplyDebuff()
        {
            switch (GetSpellInfo()->Id)
            {
                case HASTE_BUFF_BLOODLUST:
                    GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_SATED, true);
                    break;
                case HASTE_BUFF_HEROISM:
                    GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_EXHAUSTION, true);
                    break;
                case HASTE_BUFF_TIME_WARP:
                    GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_TEMPORAL_DISPLACEMENT, true);
                    break;
                case HASTE_BUFF_ANCIENT_HYSTERIA:
                    GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_INSANITY, true);
                    break;
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raid_haste_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raid_haste_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raid_haste_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
            AfterHit += SpellHitFn(spell_raid_haste_SpellScript::ApplyDebuff);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_raid_haste_SpellScript();
    }
};

// 73920 - Healing Rain
class spell_sha_healing_rain : public SpellScriptLoader
{
public:
    spell_sha_healing_rain() : SpellScriptLoader("spell_sha_healing_rain") { }

    class spell_sha_healing_rain_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_healing_rain_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/)
        {
            if (DynamicObject* dynObj = GetCaster()->GetDynObject(73920))
                GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), 73921, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_healing_rain_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_healing_rain_AuraScript();
    }
};

// 77478 - Earthquake
class spell_sha_earthquake : public SpellScriptLoader
{
public:
    spell_sha_earthquake() : SpellScriptLoader("spell_sha_earthquake") { }

    class spell_sha_earthquake_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_earthquake_SpellScript);

        int32 chance;

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellStore.LookupEntry(SHAMAN_SPELL_EARTHQUAKE_KNOCKDOWN))
                return false;
            return true;
        }

        bool Load()
        {
            chance = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (roll_chance_i(chance))
                GetCaster()->CastSpell(GetHitUnit(), SHAMAN_SPELL_EARTHQUAKE_KNOCKDOWN, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_sha_earthquake_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_earthquake_SpellScript();
    }
};

void AddSC_shaman_spell_scripts()
{
    new spell_sha_mana_tide();
    new spell_sha_astral_shift();
    new spell_sha_fire_nova();
    new spell_sha_earthbind_totem();
    new spell_sha_healing_rain();
    new spell_sha_earthquake();
    new spell_raid_haste();
}
