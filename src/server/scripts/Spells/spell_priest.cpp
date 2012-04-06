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
 * Scripts for spells with SPELLFAMILY_PRIEST and SPELLFAMILY_GENERIC spells used by priest players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pri_".
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"

enum PriestSpells
{
    PRIEST_SPELL_GUARDIAN_SPIRIT_HEAL           = 48153,
    PRIEST_SPELL_PENANCE_R1                     = 47540,
    PRIEST_SPELL_PENANCE_R1_DAMAGE              = 47758,
    PRIEST_SPELL_PENANCE_R1_HEAL                = 47757,
    PRIEST_SPELL_REFLECTIVE_SHIELD_TRIGGERED    = 33619,
    PRIEST_SPELL_REFLECTIVE_SHIELD_R1           = 33201,
    PRIEST_SPELL_IMPROVED_POWER_WORD_SHIELD_R1  = 14748,
    PRIEST_SPELL_IMPROVED_POWER_WORD_SHIELD_R2  = 14768,
};

// Guardian Spirit
class spell_pri_guardian_spirit : public SpellScriptLoader
{
    public:
        spell_pri_guardian_spirit() : SpellScriptLoader("spell_pri_guardian_spirit") { }

        class spell_pri_guardian_spirit_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_guardian_spirit_AuraScript);

            uint32 healPct;

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                return sSpellMgr->GetSpellInfo(PRIEST_SPELL_GUARDIAN_SPIRIT_HEAL) != NULL;
            }

            bool Load()
            {
                healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                if (dmgInfo.GetDamage() < target->GetHealth())
                    return;

                int32 healAmount = int32(target->CountPctFromMaxHealth(healPct));
                // remove the aura now, we don't want 40% healing bonus
                Remove(AURA_REMOVE_BY_ENEMY_SPELL);
                target->CastCustomSpell(target, PRIEST_SPELL_GUARDIAN_SPIRIT_HEAL, &healAmount, NULL, NULL, true);
                absorbAmount = dmgInfo.GetDamage();
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_guardian_spirit_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_guardian_spirit_AuraScript::Absorb, EFFECT_1);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_guardian_spirit_AuraScript();
        }
};

class spell_pri_mana_burn : public SpellScriptLoader
{
    public:
        spell_pri_mana_burn() : SpellScriptLoader("spell_pri_mana_burn") { }

        class spell_pri_mana_burn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_mana_burn_SpellScript);

            void HandleAfterHit()
            {
                Unit* unitTarget = GetHitUnit();
                if (!unitTarget)
                    return;

                unitTarget->RemoveAurasWithMechanic((1 << MECHANIC_FEAR) | (1 << MECHANIC_POLYMORPH));
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_pri_mana_burn_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mana_burn_SpellScript;
        }
};

class spell_pri_mind_sear : public SpellScriptLoader
{
    public:
        spell_pri_mind_sear() : SpellScriptLoader("spell_pri_mind_sear") { }

        class spell_pri_mind_sear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_mind_sear_SpellScript);

            void FilterTargets(std::list<Unit*>& unitList)
            {
                unitList.remove_if (Trinity::ObjectGUIDCheck(GetCaster()->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT)));
            }

            void Register()
            {
                OnUnitTargetSelect += SpellUnitTargetFn(spell_pri_mind_sear_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mind_sear_SpellScript();
        }
};

class spell_pri_pain_and_suffering_proc : public SpellScriptLoader
{
    public:
        spell_pri_pain_and_suffering_proc() : SpellScriptLoader("spell_pri_pain_and_suffering_proc") { }

        // 47948 Pain and Suffering (proc)
        class spell_pri_pain_and_suffering_proc_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_pain_and_suffering_proc_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                // Refresh Shadow Word: Pain on target
                if (Unit* unitTarget = GetHitUnit())
                    if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, 0x8000, 0, 0, GetCaster()->GetGUID()))
                        aur->GetBase()->RefreshDuration();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_pain_and_suffering_proc_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_pain_and_suffering_proc_SpellScript;
        }
};

class spell_pri_penance : public SpellScriptLoader
{
    public:
        spell_pri_penance() : SpellScriptLoader("spell_pri_penance") { }

        class spell_pri_penance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_penance_SpellScript);

            bool Validate(SpellInfo const* spellEntry)
            {
                if (!sSpellMgr->GetSpellInfo(PRIEST_SPELL_PENANCE_R1))
                    return false;
                // can't use other spell than this penance due to spell_ranks dependency
                if (sSpellMgr->GetFirstSpellInChain(PRIEST_SPELL_PENANCE_R1) != sSpellMgr->GetFirstSpellInChain(spellEntry->Id))
                    return false;

                uint8 rank = sSpellMgr->GetSpellRank(spellEntry->Id);
                if (!sSpellMgr->GetSpellWithRank(PRIEST_SPELL_PENANCE_R1_DAMAGE, rank, true))
                    return false;
                if (!sSpellMgr->GetSpellWithRank(PRIEST_SPELL_PENANCE_R1_HEAL, rank, true))
                    return false;

                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* unitTarget = GetHitUnit();
                if (!unitTarget || !unitTarget->isAlive())
                    return;

                Unit* caster = GetCaster();

                uint8 rank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);

                if (caster->IsFriendlyTo(unitTarget))
                    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(PRIEST_SPELL_PENANCE_R1_HEAL, rank), false, 0);
                else
                    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(PRIEST_SPELL_PENANCE_R1_DAMAGE, rank), false, 0);
            }

            void Register()
            {
                // add dummy effect spell handler to Penance
                OnEffectHitTarget += SpellEffectFn(spell_pri_penance_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_penance_SpellScript;
        }
};

// Reflective Shield
class spell_pri_reflective_shield_trigger : public SpellScriptLoader
{
    public:
        spell_pri_reflective_shield_trigger() : SpellScriptLoader("spell_pri_reflective_shield_trigger") { }

        class spell_pri_reflective_shield_trigger_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_reflective_shield_trigger_AuraScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                return sSpellMgr->GetSpellInfo(PRIEST_SPELL_REFLECTIVE_SHIELD_TRIGGERED) && sSpellMgr->GetSpellInfo(PRIEST_SPELL_REFLECTIVE_SHIELD_R1);
            }

            void Trigger(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                if (dmgInfo.GetAttacker() == target)
                    return;
                Unit* caster = GetCaster();
                if (!caster)
                    return;
                if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(PRIEST_SPELL_REFLECTIVE_SHIELD_R1, EFFECT_0))
                {
                    int32 bp = CalculatePctN(absorbAmount, talentAurEff->GetAmount());
                    target->CastCustomSpell(dmgInfo.GetAttacker(), PRIEST_SPELL_REFLECTIVE_SHIELD_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
                }
            }

            void Register()
            {
                 AfterEffectAbsorb += AuraEffectAbsorbFn(spell_pri_reflective_shield_trigger_AuraScript::Trigger, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_reflective_shield_trigger_AuraScript();
        }
};

// Shadow Word: Death
// Spell Id: 32379
class spell_pri_shadow_word_death : public SpellScriptLoader
{
    public:
        spell_pri_shadow_word_death() : SpellScriptLoader("spell_pri_shadow_word_death") { }

        class spell_pri_shadow_word_death_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_shadow_word_death_SpellScript);

            void DamageCaster(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 back_damage = caster->SpellDamageBonus(GetHitUnit(), GetSpellInfo(), uint32(GetHitDamage()), SPELL_DIRECT_DAMAGE);
                    if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 2874, 1))
                        back_damage -= back_damage * (-aurEff->GetAmount() / 100);

                    if (back_damage < int32(GetHitUnit()->GetHealth()))
                    {
                        caster->CastCustomSpell(caster, 32409, &back_damage, NULL, NULL, true);
                        if (GetHitUnit()->HealthBelowPct(25))
                        {
                            SetHitDamage(int32(GetHitDamage() * 3)); // Deals 3 times more damage to targets below 25% health

                            if (caster->HasAura(55682) && !GetHitUnit()->HasAura(95652)) // Glyph of Shadow Word: Death
                            {
                                caster->AddAura(95652, GetHitUnit()); // Glyph of Shadow Word: Death - Marker
                                if (caster->GetTypeId() == TYPEID_PLAYER)
                                    caster->ToPlayer()->RemoveSpellCooldown(32379, true); // Shadow Word: Death
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_shadow_word_death_SpellScript::DamageCaster, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_shadow_word_death_SpellScript;
        }
};

// Mind Blast
// Spell Id: 8092
class spell_pri_mind_blast : public SpellScriptLoader
{
    public:
        spell_pri_mind_blast() : SpellScriptLoader("spell_pri_mind_blast") { }

        class spell_pri_mind_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_mind_blast_SpellScript);

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect * aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 95, 1)) // If we have Improved Mind Blast
                        if (caster->GetShapeshiftForm() == FORM_SHADOW)
                            if (roll_chance_i(aurEff->GetAmount()))
                                caster->CastSpell(GetHitUnit(), 48301, true); // Cast Mind Trauma

                    // Remove Mind Melt
                    caster->RemoveAurasDueToSpell(87160);
                    caster->RemoveAurasDueToSpell(81292);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_mind_blast_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_mind_blast_SpellScript;
        }
};

// Power Word: Fortitude
// Spell Id: 21562
class spell_pri_power_word_fortitude : public SpellScriptLoader
{
    public:
        spell_pri_power_word_fortitude() : SpellScriptLoader("spell_pri_power_word_fortitude") { }

        class spell_pri_power_word_fortitude_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pri_power_word_fortitude_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> PartyMembers;
                    caster->GetPartyMembers(PartyMembers);
                    if (PartyMembers.size() > 1)
                        caster->CastSpell(GetHitUnit(), 79105, true); // Power Word : Fortitude (Raid)
                    else
                        caster->CastSpell(GetHitUnit(), 79104, true); // Power Word : Fortitude (Caster)
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_pri_power_word_fortitude_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pri_power_word_fortitude_SpellScript;
        }
};

// Power Word: Shield
// Spell Id: 17
class spell_pri_power_word_shield : public SpellScriptLoader
{
    public:
        spell_pri_power_word_shield() : SpellScriptLoader("spell_pri_power_word_shield") { }

        class spell_pri_power_word_shield_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pri_power_word_shield_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Improved Power Word: Shield rank 1
                if (AuraEffect const* improved = GetCaster()->GetAuraEffect(PRIEST_SPELL_IMPROVED_POWER_WORD_SHIELD_R1, EFFECT_0))
                    amount += improved->GetAmount();

                // Improved Power Word: Shield rank 2
                if (AuraEffect const* improved = GetCaster()->GetAuraEffect(PRIEST_SPELL_IMPROVED_POWER_WORD_SHIELD_R2, EFFECT_0))
                    amount += improved->GetAmount();

                amount *= GetCaster()->GetTotalAuraMultiplier(SPELL_AURA_MOD_HEALING_DONE_PERCENT);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_power_word_shield_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pri_power_word_shield_AuraScript();
        }
};

void AddSC_priest_spell_scripts()
{
    new spell_pri_guardian_spirit();
    new spell_pri_mana_burn;
    new spell_pri_pain_and_suffering_proc;
    new spell_pri_penance;
    new spell_pri_reflective_shield_trigger();
    new spell_pri_mind_sear();
    new spell_pri_shadow_word_death();
    new spell_pri_mind_blast();
    new spell_pri_power_word_fortitude();
    new spell_pri_power_word_shield();
}
