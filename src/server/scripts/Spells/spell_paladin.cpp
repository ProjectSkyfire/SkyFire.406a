/*
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

/*
 * Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pal_".
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"

enum PaladinSpells
{
    PALADIN_SPELL_DIVINE_PLEA                    = 54428,
    PALADIN_SPELL_BLESSING_OF_SANCTUARY_BUFF     = 67480,

    PALADIN_SPELL_HOLY_SHOCK_R1                  = 20473,
    PALADIN_SPELL_HOLY_SHOCK_R1_DAMAGE           = 25912,
    PALADIN_SPELL_HOLY_SHOCK_R1_HEALING          = 25914,

    SPELL_BLESSING_OF_LOWER_CITY_DRUID           = 37878,
    SPELL_BLESSING_OF_LOWER_CITY_PALADIN         = 37879,
    SPELL_BLESSING_OF_LOWER_CITY_PRIEST          = 37880,
    SPELL_BLESSING_OF_LOWER_CITY_SHAMAN          = 37881,

    SPELL_DIVINE_PURPOSE_PROC                    = 90174,
};

// 31850 - Ardent Defender
class spell_pal_ardent_defender : public SpellScriptLoader
{
public:
    spell_pal_ardent_defender() : SpellScriptLoader("spell_pal_ardent_defender") { }

    class spell_pal_ardent_defender_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_ardent_defender_AuraScript);

        uint32 absorbPct, healPct;

        enum Spell
        {
            PAL_SPELL_ARDENT_DEFENDER_HEAL = 66235,
        };

        bool Load()
        {
            healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
            absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
            return GetUnitOwner()->ToPlayer();
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit* victim = GetTarget();
            int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();
            uint32 allowedHealth = victim->CountPctFromMaxHealth(35);
            // If damage kills us
            if (remainingHealth <= 0 && !victim->ToPlayer()->HasSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL))
            {
                // Cast healing spell, completely avoid damage
                absorbAmount = dmgInfo.GetDamage();

                uint32 defenseSkillValue = victim->GetDefenseSkillValue();
                // Max heal when defense skill denies critical hits from raid bosses
                // Formula: max defense at level + 140 (raiting from gear)
                uint32 reqDefForMaxHeal  = victim->getLevel() * 5 + 140;
                float pctFromDefense = (defenseSkillValue >= reqDefForMaxHeal)
                    ? 1.0f
                    : float(defenseSkillValue) / float(reqDefForMaxHeal);

                int32 healAmount = int32(victim->CountPctFromMaxHealth(uint32(healPct * pctFromDefense)));
                victim->CastCustomSpell(victim, PAL_SPELL_ARDENT_DEFENDER_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff);
                victim->ToPlayer()->AddSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL, 0, time(NULL) + 120);
            }
            else if (remainingHealth < int32(allowedHealth))
            {
                // Reduce damage that brings us under 35% (or full damage if we are already under 35%) by x%
                uint32 damageToReduce = (victim->GetHealth() < allowedHealth)
                    ? dmgInfo.GetDamage()
                    : allowedHealth - remainingHealth;
                absorbAmount = CalculatePctN(damageToReduce, absorbPct);
            }
        }

        void Register()
        {
             DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_ardent_defender_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
             OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_ardent_defender_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_ardent_defender_AuraScript();
    }
};

class spell_pal_blessing_of_faith : public SpellScriptLoader
{
public:
    spell_pal_blessing_of_faith() : SpellScriptLoader("spell_pal_blessing_of_faith") { }

    class spell_pal_blessing_of_faith_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_blessing_of_faith_SpellScript)
        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_BLESSING_OF_LOWER_CITY_DRUID))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_BLESSING_OF_LOWER_CITY_PALADIN))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_BLESSING_OF_LOWER_CITY_PRIEST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_BLESSING_OF_LOWER_CITY_SHAMAN))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unitTarget = GetHitUnit())
            {
                uint32 spell_id = 0;
                switch (unitTarget->getClass())
                {
                    case CLASS_DRUID:   spell_id = SPELL_BLESSING_OF_LOWER_CITY_DRUID; break;
                    case CLASS_PALADIN: spell_id = SPELL_BLESSING_OF_LOWER_CITY_PALADIN; break;
                    case CLASS_PRIEST:  spell_id = SPELL_BLESSING_OF_LOWER_CITY_PRIEST; break;
                    case CLASS_SHAMAN:  spell_id = SPELL_BLESSING_OF_LOWER_CITY_SHAMAN; break;
                    default: return;                    // ignore for non-healing classes
                }

                GetCaster()->CastSpell(GetCaster(), spell_id, true);
            }
        }

        void Register()
        {
            // add dummy effect spell handler to Blessing of Faith
            OnEffectHitTarget += SpellEffectFn(spell_pal_blessing_of_faith_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_blessing_of_faith_SpellScript();
    }
};

// 20911 Blessing of Sanctuary
// 25899 Greater Blessing of Sanctuary
class spell_pal_blessing_of_sanctuary : public SpellScriptLoader
{
public:
    spell_pal_blessing_of_sanctuary() : SpellScriptLoader("spell_pal_blessing_of_sanctuary") { }

    class spell_pal_blessing_of_sanctuary_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_blessing_of_sanctuary_AuraScript)
        bool Validate(SpellInfo const* /*entry*/)
        {
            if (!sSpellMgr->GetSpellInfo(PALADIN_SPELL_BLESSING_OF_SANCTUARY_BUFF))
                return false;
            return true;
        }

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            if (Unit* pCaster = GetCaster())
                pCaster->CastSpell(target, PALADIN_SPELL_BLESSING_OF_SANCTUARY_BUFF, true);
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            target->RemoveAura(PALADIN_SPELL_BLESSING_OF_SANCTUARY_BUFF, GetCasterGUID());
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_pal_blessing_of_sanctuary_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            AfterEffectRemove += AuraEffectRemoveFn(spell_pal_blessing_of_sanctuary_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_blessing_of_sanctuary_AuraScript();
    }
};

// 63521 Guarded by The Light
class spell_pal_guarded_by_the_light : public SpellScriptLoader
{
public:
    spell_pal_guarded_by_the_light() : SpellScriptLoader("spell_pal_guarded_by_the_light") { }

    class spell_pal_guarded_by_the_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_guarded_by_the_light_SpellScript)
        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(PALADIN_SPELL_DIVINE_PLEA))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            // Divine Plea
            if (Aura* aura = GetCaster()->GetAura(PALADIN_SPELL_DIVINE_PLEA))
                aura->RefreshDuration();
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_guarded_by_the_light_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_guarded_by_the_light_SpellScript();
    }
};

class spell_pal_holy_shock : public SpellScriptLoader
{
public:
    spell_pal_holy_shock() : SpellScriptLoader("spell_pal_holy_shock") { }

    class spell_pal_holy_shock_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_shock_SpellScript)
        bool Validate(SpellInfo const* spellEntry)
        {
            if (!sSpellMgr->GetSpellInfo(PALADIN_SPELL_HOLY_SHOCK_R1))
                return false;

            // can't use other spell than holy shock due to spell_ranks dependency
            if (sSpellMgr->GetFirstSpellInChain(PALADIN_SPELL_HOLY_SHOCK_R1) != sSpellMgr->GetFirstSpellInChain(spellEntry->Id))
                return false;

            uint8 rank = sSpellMgr->GetSpellRank(spellEntry->Id);
            if (!sSpellMgr->GetSpellWithRank(PALADIN_SPELL_HOLY_SHOCK_R1_DAMAGE, rank, true))
                return false;
            if (!sSpellMgr->GetSpellWithRank(PALADIN_SPELL_HOLY_SHOCK_R1_HEALING, rank, true))
                return false;

            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unitTarget = GetHitUnit())
            {
                Unit* caster = GetCaster();

                uint8 rank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);

                if (caster->IsFriendlyTo(unitTarget))
                    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(PALADIN_SPELL_HOLY_SHOCK_R1_HEALING, rank), true, 0);
                else
                    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(PALADIN_SPELL_HOLY_SHOCK_R1_DAMAGE, rank), true, 0);
            }
        }

        void Register()
        {
            // add dummy effect spell handler to Holy Shock
            OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_holy_shock_SpellScript();
    }
};

class spell_pal_judgement_of_command : public SpellScriptLoader
{
public:
    spell_pal_judgement_of_command() : SpellScriptLoader("spell_pal_judgement_of_command") { }

    class spell_pal_judgement_of_command_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_judgement_of_command_SpellScript)
        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unitTarget = GetHitUnit())
                if (SpellInfo const* spell_proto = sSpellMgr->GetSpellInfo(GetEffectValue()))
                    GetCaster()->CastSpell(unitTarget, spell_proto, true, NULL);
        }

        void Register()
        {
            // add dummy effect spell handler to Judgement of Command
            OnEffectHitTarget += SpellEffectFn(spell_pal_judgement_of_command_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_judgement_of_command_SpellScript();
    }
};

class spell_pal_judgements_of_the_bold : public SpellScriptLoader
{
    public:
        spell_pal_judgements_of_the_bold() : SpellScriptLoader("spell_pal_judgements_of_the_bold") { }

        class spell_pal_judgements_of_the_bold_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_judgements_of_the_bold_AuraScript);

            void CalculateMana(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* caster = GetCaster())
                {
                    canBeRecalculated = true;
                    int32 basemana = caster->ToPlayer()->GetCreateMana();
                    amount = (3 * basemana) / 100; // 3% of base mana
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_judgements_of_the_bold_AuraScript::CalculateMana, EFFECT_0, SPELL_AURA_PERIODIC_ENERGIZE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_judgements_of_the_bold_AuraScript();
        }
};

// Shield of Righteous
// Spell Id: 53600
class spell_pal_shield_of_righteous : public SpellScriptLoader
{
public:
    spell_pal_shield_of_righteous() : SpellScriptLoader("spell_pal_shield_of_righteous") { }

    class spell_pal_shield_of_righteous_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_shield_of_righteous_SpellScript)

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if(Unit* caster = GetCaster())
            {
                int32 damage = GetHitDamage();
                switch(caster->GetPower(POWER_HOLY_POWER))
                {
                    case 0:
                        damage = int32(damage * 1.16f);
                        break;
                    case 1:
                        damage = int32((damage * 1.16f) * 3);
                        break;
                    case 2:
                        damage = int32((damage * 1.16f) * 6);
                        break;
                }
                SetHitDamage(damage);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_shield_of_righteous_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_shield_of_righteous_SpellScript();
    }
};

class spell_pal_word_of_glory : public SpellScriptLoader
{
public:
    spell_pal_word_of_glory() : SpellScriptLoader("spell_pal_word_of_glory") { }

    class spell_pal_word_of_glory_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_word_of_glory_heal_SpellScript)

        int32 totalheal;

        bool Load()
        {
            totalheal = GetSpellInfo()->Effects[EFFECT_0].CalcValue();

            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void ChangeHeal(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (GetCaster()->HasAura(SPELL_DIVINE_PURPOSE_PROC))
            {
                totalheal *= 3;

                // Selfless Healer
                if (AuraEffect const* auraEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PALADIN, 3924, EFFECT_0))
                    if (target != caster)
                        totalheal += totalheal + (totalheal * auraEff->GetAmount()) / 100;

                SetHitHeal(totalheal);
                return;
            }

            switch (caster->GetPower(POWER_HOLY_POWER))
            {
                case 1: // 1 Holy Power
                {
                    totalheal = totalheal;
                    break;
                }
                case 2: // 2 Holy Power
                {
                    totalheal *= 2;
                    break;
                }
                case 3: // 3 Holy Power
                {
                    totalheal *= 3;
                    break;
                }

            }
            // Selfless Healer
            if (AuraEffect const* auraEff = caster->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 3924, EFFECT_0))
                if (target != caster)
                    totalheal += totalheal + (totalheal * auraEff->GetAmount()) / 100;

            SetHitHeal(totalheal);
        }

        void HandlePeriodic()
        {
            // Glyph of Long Word
            if (!GetCaster()->HasAura(93466))
                PreventHitAura();
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_word_of_glory_heal_SpellScript::ChangeHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            AfterHit += SpellHitFn(spell_pal_word_of_glory_heal_SpellScript::HandlePeriodic);
        }
    };

    class spell_pal_word_of_glory_heal_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_word_of_glory_heal_AuraScript)

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }
        
        void CalculateOvertime(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
        {
            if (AuraEffect const* longWord = GetCaster()->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 4127, 1))
            {
                canBeRecalculated = true;
                amount = ((GetSpellInfo()->Effects[EFFECT_0].CalcValue() * longWord->GetAmount()) / 100)  / 3;
            }
        }
        
        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_word_of_glory_heal_AuraScript::CalculateOvertime, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_word_of_glory_heal_AuraScript();
    }

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_word_of_glory_heal_SpellScript();
    }
};

class spell_pal_selfless_healer : public SpellScriptLoader
{
    public:
        spell_pal_selfless_healer() : SpellScriptLoader("spell_pal_selfless_healer") { }

        class spell_pal_selfless_healer_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_selfless_healer_AuraScript);

            void CalculateBonus(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* caster = GetCaster())
                {
                    canBeRecalculated = true;

                    if (caster->HasAura(SPELL_DIVINE_PURPOSE_PROC))
                    {
                        amount = 12;
                        return;
                    }

                    switch (caster->GetPower(POWER_HOLY_POWER))
                    {
                        case 0: // 1 Holy Power
                        {
                            amount = 4;
                            break;
                        }
                        case 1: // 2 Holy Power
                        {
                            amount = 8;
                            break;
                        }
                        case 2: // 3 Holy Power
                        {
                            amount = 12;
                            break;
                        }
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_selfless_healer_AuraScript::CalculateBonus, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pal_selfless_healer_AuraScript();
        }
};

void AddSC_paladin_spell_scripts()
{
    new spell_pal_ardent_defender();
    new spell_pal_blessing_of_faith();
    new spell_pal_blessing_of_sanctuary();
    new spell_pal_guarded_by_the_light();
    new spell_pal_holy_shock();
    new spell_pal_judgement_of_command();
    new spell_pal_shield_of_righteous();
    new spell_pal_judgements_of_the_bold();
    new spell_pal_word_of_glory();
    new spell_pal_selfless_healer();
}