/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"

enum DruidSpells
{
    DRUID_INCREASED_MOONFIRE_DURATION   = 38414, // Tier 6
    DRUID_GENESIS_R1                    = 57810,
    DRUID_GENESIS_R2                    = 57811,
    DRUID_GENESIS_R3                    = 57812,
};

// 54846 Glyph of Starfire
class spell_dru_glyph_of_starfire : public SpellScriptLoader
{
    public:
        spell_dru_glyph_of_starfire() : SpellScriptLoader("spell_dru_glyph_of_starfire") { }

        class spell_dru_glyph_of_starfire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_glyph_of_starfire_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(DRUID_INCREASED_MOONFIRE_DURATION) ||
                    !sSpellMgr->GetSpellInfo(DRUID_GENESIS_R1))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                    if (AuraEffect const* aurEff = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DRUID, 0x00000002, 0, 0, caster->GetGUID()))
                    {
                        Aura* aura = aurEff->GetBase();

                        uint32 countMin = aura->GetMaxDuration();
                        uint32 countMax = aura->GetSpellInfo()->GetMaxDuration() + 9000;

                        if (caster->HasAura(DRUID_INCREASED_MOONFIRE_DURATION))
                            countMax += 3000;

                        if (caster->HasAura(DRUID_GENESIS_R1))
                            countMax += 2000;

                        if (caster->HasAura(DRUID_GENESIS_R2))
                            countMax += 4000;

                        if (caster->HasAura(DRUID_GENESIS_R3))
                            countMax += 6000;

                        if (countMin < countMax)
                        {
                            aura->SetDuration(uint32(aura->GetDuration() + 3000));
                            aura->SetMaxDuration(countMin + 3000);
                        }
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dru_glyph_of_starfire_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_glyph_of_starfire_SpellScript();
        }
};

// 62606 - Savage Defense
class spell_dru_savage_defense : public SpellScriptLoader
{
    public:
        spell_dru_savage_defense() : SpellScriptLoader("spell_dru_savage_defense") { }

        class spell_dru_savage_defense_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_savage_defense_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* aurEff, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
            {
                absorbAmount = uint32(CalculatePctN(GetTarget()->GetTotalAttackPowerValue(BASE_ATTACK), absorbPct));
                aurEff->SetAmount(0);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_savage_defense_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dru_savage_defense_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_savage_defense_AuraScript();
        }
};

class spell_dru_t10_restoration_4p_bonus : public SpellScriptLoader
{
    public:
        spell_dru_t10_restoration_4p_bonus() : SpellScriptLoader("spell_dru_t10_restoration_4p_bonus") { }

        class spell_dru_t10_restoration_4p_bonus_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_t10_restoration_4p_bonus_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (!GetCaster()->ToPlayer()->GetGroup())
                {
                    targets.clear();
                    targets.push_back(GetCaster());
                }
                else
                {
                    targets.remove(GetExplTargetUnit());
                    std::list<Unit*> tempTargets;
                    for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        if ((*itr)->GetTypeId() == TYPEID_PLAYER && GetCaster()->IsInRaidWith((*itr)->ToUnit()))
                            tempTargets.push_back((*itr)->ToUnit());

                    if (tempTargets.empty())
                    {
                        targets.clear();
                        FinishCast(SPELL_FAILED_DONT_REPORT);
                        return;
                    }

                    Unit* target = SelectRandomContainerElement(tempTargets);
                    targets.clear();
                    targets.push_back(target);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_t10_restoration_4p_bonus_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_t10_restoration_4p_bonus_SpellScript();
        }
};

class spell_dru_starfall_aoe : public SpellScriptLoader
{
    public:
        spell_dru_starfall_aoe() : SpellScriptLoader("spell_dru_starfall_aoe") { }

        class spell_dru_starfall_aoe_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_starfall_aoe_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove(GetExplTargetUnit());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_starfall_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_starfall_aoe_SpellScript();
        }
};

// 40121 - Swift Flight Form (Passive)
class spell_dru_swift_flight_passive : public SpellScriptLoader
{
    public:
        spell_dru_swift_flight_passive() : SpellScriptLoader("spell_dru_swift_flight_passive") { }

        class spell_dru_swift_flight_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_swift_flight_passive_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                Unit* caster = GetCaster();
                if (!caster || !caster->ToPlayer())
                    return;

                if (caster->ToPlayer()->Has310Flyer(false))
                    amount = 310;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_swift_flight_passive_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_swift_flight_passive_AuraScript();
        }
};

// Ferocious Bite
// Spell Id: 22568
class spell_dru_ferocious_bite : public SpellScriptLoader
{
    public:
        spell_dru_ferocious_bite() : SpellScriptLoader("spell_dru_ferocious_bite") { }

        class spell_dru_ferocious_bite_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_ferocious_bite_SpellScript);

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    int32 damage = GetHitDamage();
                    float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                    float multiple = ap / 410 + GetSpellInfo()->Effects[EFFECT_1].CalcValue();
                    int32 energy = -(caster->ModifyPower(POWER_ENERGY, -30));
                    damage += int32(energy * multiple);
                    damage += int32(CalculatePctN(caster->ToPlayer()->GetComboPoints() * ap, 7));
                    SetHitDamage(damage);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dru_ferocious_bite_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_ferocious_bite_SpellScript;
        }
};

// Mark Of The Wild
// Spell Id: 1126
class spell_dru_mark_of_the_wild : public SpellScriptLoader
{
public:
    spell_dru_mark_of_the_wild() : SpellScriptLoader("spell_dru_mark_of_the_wild") { }

    class spell_dru_mark_of_the_wild_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_mark_of_the_wild_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    std::list<Unit*> PartyMembers;
                    caster->GetPartyMembers(PartyMembers);

                    bool Continue = false;
                    uint32 player = 0;

                    for (std::list<Unit*>::iterator itr = PartyMembers.begin(); itr != PartyMembers.end(); ++itr) // If caster is in party with a player
                    {
                        ++player;
                        if (Continue == false && player > 1)
                            Continue = true;
                    }
                    if (Continue == true)
                        caster->CastSpell(GetHitUnit(), 79061, true); // Mark of the Wild (Raid)
                    else
                        caster->CastSpell(GetHitUnit(), 79060, true); // Mark of the Wild (Caster)
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_mark_of_the_wild_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_mark_of_the_wild_SpellScript;
    }
};

enum EclipseSpells
{
    SPELL_DRUID_WRATH                    = 5176,
    SPELL_DRUID_STARFIRE                 = 2912,
    SPELL_DRUID_STARSURGE                = 78674,
    SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE = 89265,
    SPELL_DRUID_STARSURGE_ENERGIZE       = 86605,
    SPELL_DRUID_LUNAR_ECLIPSE_MARKER     = 67484, // Will make the yellow arrow on eclipse bar point to the blue side (lunar)
    SPELL_DRUID_SOLAR_ECLIPSE_MARKER     = 67483, // Will make the yellow arrow on eclipse bar point to the yellow side (solar)
    SPELL_DRUID_SOLAR_ECLIPSE            = 48517,
    SPELL_DRUID_LUNAR_ECLIPSE            = 48518,
};

// Wrath, Starfire, and Starsurge
class spell_dru_eclipse_energize : public SpellScriptLoader
{
public:
    spell_dru_eclipse_energize() : SpellScriptLoader("spell_dru_eclipse_energize") { }

    class spell_dru_eclipse_energize_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_eclipse_energize_SpellScript);

        int32 energizeAmount;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_DRUID)
                return false;

            energizeAmount = 0;

            return true;
        }

        void HandleEnergize(SpellEffIndex effIndex)
        {
            Unit* caster = GetCaster();

            // No boomy, no deal.
            if (!caster->HasSpell(SPELL_DRUID_STARSURGE))
                return;

            switch(GetSpellInfo()->Id)
            {
                case SPELL_DRUID_WRATH:
                {
                    energizeAmount = -GetSpellInfo()->Effects[effIndex].BasePoints; // -13
                    // If we are set to fill the lunar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        caster->CastCustomSpell(caster, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE,&energizeAmount, 0, 0, true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster, SPELL_DRUID_LUNAR_ECLIPSE_MARKER, true);
                    }
                    // The energizing effect brought us out of the solar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) <= 0)
                        caster->RemoveAurasDueToSpell(SPELL_DRUID_SOLAR_ECLIPSE);
                    break;
                }
                case SPELL_DRUID_STARFIRE:
                {
                    energizeAmount = GetSpellInfo()->Effects[effIndex].BasePoints; // 20
                    // If we are set to fill the solar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        caster->CastCustomSpell(caster, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE,&energizeAmount, 0, 0, true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster, SPELL_DRUID_SOLAR_ECLIPSE_MARKER, true);
                    }
                    // The energizing effect brought us out of the lunar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) >= 0)
                        caster->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);
                    break;
                }
                case SPELL_DRUID_STARSURGE:
                {
                    // If we are set to fill the solar side or we've just logged in with 0 power (confirmed with sniffs)
                    if ((!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        energizeAmount = GetSpellInfo()->Effects[effIndex].BasePoints; // 15
                        caster->CastCustomSpell(caster, SPELL_DRUID_STARSURGE_ENERGIZE,&energizeAmount, 0, 0, true);

                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster, SPELL_DRUID_SOLAR_ECLIPSE_MARKER, true);
                    }
                    else if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                    {
                        energizeAmount = -GetSpellInfo()->Effects[effIndex].BasePoints; // -15
                        caster->CastCustomSpell(caster, SPELL_DRUID_STARSURGE_ENERGIZE,&energizeAmount, 0, 0, true);
                    }
                    // The energizing effect brought us out of the lunar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) >= 0)
                        caster->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);
                    // The energizing effect brought us out of the solar eclipse, remove the aura
                    else if (caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) <= 0)
                        caster->RemoveAura(SPELL_DRUID_SOLAR_ECLIPSE);
                    break;
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_eclipse_energize_SpellScript::HandleEnergize, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_eclipse_energize_SpellScript;
    }
};
void AddSC_druid_spell_scripts()
{
    new spell_dru_glyph_of_starfire();
    new spell_dru_savage_defense();
    new spell_dru_t10_restoration_4p_bonus();
    new spell_dru_starfall_aoe();
    new spell_dru_swift_flight_passive();
    new spell_dru_ferocious_bite();
    new spell_dru_mark_of_the_wild();
    new spell_dru_eclipse_energize();
}