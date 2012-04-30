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
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "ScriptPCH.h"

enum WarriorSpells
{
    WARRIOR_SPELL_LAST_STAND_TRIGGERED           = 12976,
};

class spell_warr_last_stand : public SpellScriptLoader
{
    public:
        spell_warr_last_stand() : SpellScriptLoader("spell_warr_last_stand") { }

        class spell_warr_last_stand_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_last_stand_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_LAST_STAND_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 healthModSpellBasePoints0 = int32(GetCaster()->CountPctFromMaxHealth(30));
                GetCaster()->CastCustomSpell(GetCaster(), WARRIOR_SPELL_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
            }

            void Register()
            {
                // add dummy effect spell handler to Last Stand
                OnEffectHit += SpellEffectFn(spell_warr_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_last_stand_SpellScript();
        }
};

class spell_warr_improved_spell_reflection : public SpellScriptLoader
{
    public:
        spell_warr_improved_spell_reflection() : SpellScriptLoader("spell_warr_improved_spell_reflection") { }

        class spell_warr_improved_spell_reflection_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_improved_spell_reflection_SpellScript);

            void FilterTargets(std::list<Unit*>& unitList)
            {
                unitList.remove(GetCaster());
            }

            void Register()
            {
                OnUnitTargetSelect += SpellUnitTargetFn(spell_warr_improved_spell_reflection_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_improved_spell_reflection_SpellScript();
        }
};

enum Bloodthirst
{
    SPELL_BLOODTHIRST = 23885,
};

class spell_warr_bloodthirst : public SpellScriptLoader
{
public:
    spell_warr_bloodthirst() : SpellScriptLoader("spell_warr_bloodthirst") { }

    class spell_warr_bloodthirst_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_bloodthirst_SpellScript);

        void HandleDummy(SpellEffIndex /* effIndex */)
        {
            int32 damage = GetEffectValue();
            GetCaster()->CastCustomSpell(GetCaster(), SPELL_BLOODTHIRST, &damage, NULL, NULL, true, NULL);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_bloodthirst_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_bloodthirst_SpellScript();
    }
};

// Victory Rush
// Spell Id: 34428
class spell_warr_victory_rush : public SpellScriptLoader
{
public:
    spell_warr_victory_rush() : SpellScriptLoader("spell_warr_victory_rush") { }

    class spell_warr_victory_rush_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_victory_rush_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Formula: AttackPower * BasePoints / 100
            if (Unit* caster = GetCaster())
                SetHitDamage(int32(GetHitDamage() * caster->GetTotalAttackPowerValue(BASE_ATTACK) / 100));
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
                caster->RemoveAurasDueToSpell(32216); // Remove Victorious aura
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_warr_victory_rush::spell_warr_victory_rush_SpellScript::HandleAfterHit);
            OnEffectHitTarget += SpellEffectFn(spell_warr_victory_rush::spell_warr_victory_rush_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_victory_rush_SpellScript();
    }
};

// Cleave
// Spell Id: 845
class spell_warr_cleave : public SpellScriptLoader
{
public:
    spell_warr_cleave() : SpellScriptLoader("spell_warr_cleave") { }

    class spell_warr_cleave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_cleave_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Formula: 6 + AttackPower * 0.45
            if (Unit* caster = GetCaster())
                SetHitDamage(int32(6 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.45f));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_cleave::spell_warr_cleave_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_cleave_SpellScript();
    }
};

// Intercept
// Spell Id: 20253
// Triggered By: 20252
class spell_warr_intercept_triggered : public SpellScriptLoader
{
public:
    spell_warr_intercept_triggered() : SpellScriptLoader("spell_warr_intercept_triggered") { }

    class spell_warr_intercept_triggered_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_intercept_triggered_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Formula: 1 + AttackPower * 0.12
            if (Unit* caster = GetCaster())
                SetHitDamage(int32(1 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.12f));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_intercept_triggered::spell_warr_intercept_triggered_SpellScript::CalculateDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_intercept_triggered_SpellScript();
    }
};

enum Execute
{
    SPELL_EXECUTE               = 5308,
    SPELL_GLYPH_OF_BLOODTHRIST  = 58367,
    ICON_ID_SUDDEN_DEATH        = 1989,
};

class spell_warr_execute : public SpellScriptLoader
{
public:
    spell_warr_execute() : SpellScriptLoader("spell_warr_execute") { }

    class spell_warr_execute_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_execute_SpellScript);

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_EXECUTE) || !sSpellMgr->GetSpellInfo(SPELL_GLYPH_OF_BLOODTHRIST))
                return false;
            return true;
        }
        void HandleDummy(SpellEffIndex effIndex)
        {
            Unit* caster = GetCaster();
            if (Unit* target = GetHitUnit())
            {
                SpellInfo const* spellInfo = GetSpellInfo();
                int32 rageUsed = std::min<int32>(300 - spellInfo->CalcPowerCost(caster, SpellSchoolMask(spellInfo->SchoolMask)), caster->GetPower(POWER_RAGE));
                int32 newRage = std::max<int32>(0, caster->GetPower(POWER_RAGE) - rageUsed);

                // Sudden Death rage save
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_GENERIC, ICON_ID_SUDDEN_DEATH, EFFECT_0))
                {
                    int32 ragesave = aurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue() * 10;
                    newRage = std::max(newRage, ragesave);
                }

                caster->SetPower(POWER_RAGE, uint32(newRage));
                // Glyph of Execution bonus
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_GLYPH_OF_BLOODTHRIST, EFFECT_0))
                    rageUsed += aurEff->GetAmount() * 10;

                int32 bp = GetEffectValue() + int32(rageUsed * spellInfo->Effects[effIndex].DamageMultiplier + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.2f);
                caster->CastCustomSpell(target,SPELL_EXECUTE,&bp,0,0,true,0,0,GetOriginalCaster()->GetGUID());
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_execute_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_execute_SpellScript();
    }
};

// Heroic Strike
// Spell Id: 78
class spell_warr_heroic_strike : public SpellScriptLoader
{
public:
    spell_warr_heroic_strike() : SpellScriptLoader("spell_warr_heroic_strike") { }

    class spell_warr_heroic_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_heroic_strike_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Formula: 8 + AttackPower * 60 / 100
            if (Unit* caster = GetCaster())
                SetHitDamage(int32(8 + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 60 / 100));
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_heroic_strike::spell_warr_heroic_strike_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_heroic_strike_SpellScript();
    }
};

// Shockwave
// Spell Id: 46968
class spell_warr_shockwave : public SpellScriptLoader
{
public:
    spell_warr_shockwave() : SpellScriptLoader("spell_warr_shockwave") { }

    class spell_warr_shockwave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shockwave_SpellScript);

        void CalculateDamage(SpellEffIndex effect)
        {
            // Formula: [Effect2BasePoints] / 100 * AttackPower
            if (Unit* caster = GetCaster())
            {
                int32 bp2 = caster->CalculateSpellDamage(GetHitUnit(), GetSpellInfo(), EFFECT_2);
                SetHitDamage(int32(bp2 / 100 * caster->GetTotalAttackPowerValue(BASE_ATTACK)));
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_shockwave::spell_warr_shockwave_SpellScript::CalculateDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_shockwave_SpellScript();
    }
};

// Thunder Clap
// Spell Id: 6343
class spell_warr_thunderclap : public SpellScriptLoader
{
public:
    spell_warr_thunderclap() : SpellScriptLoader("spell_warr_thunderclap") { }

    class spell_warr_thunderclap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_thunderclap_SpellScript);

        // Lock for avoid processing the same thing multiple times when we already know the result
        bool CheckAgain;
        std::list<Unit*> targetList;

        bool Load()
        {
            CheckAgain = true;
            return true;
        }

        void FilterTargets(std::list<Unit*>& unitList)
        {
            targetList = unitList;
        }

        void OnTargetHit(SpellEffIndex effect)
        {
            if (CheckAgain) // Dont re-cast the thing on each target if its already applied
            {
                // Check for Blood and Thunder
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(84615) || (caster->HasAura(84614) && roll_chance_i(50))) // Blood and Thunder rank 1 & 2
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            if (target->HasAura(94009)) // If the target has Rend
                            {
                                CheckAgain = false;
                                for (std::list<Unit*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                                    if (Unit* curTrg = (*itr))
                                        caster->CastSpell(curTrg, 94009, true);
                            }
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_thunderclap::spell_warr_thunderclap_SpellScript::OnTargetHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnUnitTargetSelect += SpellUnitTargetFn(spell_warr_thunderclap::spell_warr_thunderclap_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_thunderclap_SpellScript();
    }
};

// Deep Wounds
// Spell Id: 12834, 12849, 12867
// Triggered Spell Id: 12162, 12850, 12868
class spell_warr_deep_wounds : public SpellScriptLoader
{
public:
    spell_warr_deep_wounds() : SpellScriptLoader("spell_warr_deep_wounds") { }

    class spell_warr_deep_wounds_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_deep_wounds_SpellScript);

        void HandleDummy(SpellEffIndex /*effect*/)
        {
            Unit* target = GetHitUnit();
            Unit* caster = GetCaster();
            int32 damage = 0;

            // apply percent damage mods
            damage = caster->SpellDamageBonus(target, GetSpellInfo(), damage, SPELL_DIRECT_DAMAGE);

            switch (GetSpellInfo()->Id)
            {
                case 12162:
                    ApplyPctN(damage, 16); break; // Rank 1
                case 12850:
                    ApplyPctN(damage, 32); break; // Rank 2
                case 12868:
                    ApplyPctN(damage, 48); break; // Rank 3
                default:
                    break;
            }

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(12721);
            uint32 ticks = spellInfo->GetDuration() / spellInfo->Effects[EFFECT_0].Amplitude;

            // Add remaining ticks to damage done
            if (AuraEffect const* aurEff = target->GetAuraEffect(12721, EFFECT_0, caster->GetGUID()))
                damage += aurEff->GetAmount() * (ticks - aurEff->GetTickNumber());

            damage /= ticks;
            caster->CastCustomSpell(target, 12721, &damage, NULL, NULL, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_deep_wounds_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_deep_wounds_SpellScript();
    }
};

enum DamageReductionAura
{
    SPELL_BLESSING_OF_SANCTUARY         = 20911,
    SPELL_GREATER_BLESSING_OF_SANCTUARY = 25899,
    SPELL_RENEWED_HOPE                  = 63944,
    SPELL_DAMAGE_REDUCTION_AURA         = 68066,
};

class spell_warr_vigilance : public SpellScriptLoader
{
public:
    spell_warr_vigilance() : SpellScriptLoader("spell_warr_vigilance") { }

    class spell_warr_vigilance_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_vigilance_AuraScript);

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DAMAGE_REDUCTION_AURA))
                return false;
            return true;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            target->CastSpell(target, SPELL_DAMAGE_REDUCTION_AURA, true);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();

            if (!target->HasAura(SPELL_DAMAGE_REDUCTION_AURA))
                return;

            if (target->HasAura(SPELL_BLESSING_OF_SANCTUARY) ||
                target->HasAura(SPELL_GREATER_BLESSING_OF_SANCTUARY) ||
                target->HasAura(SPELL_RENEWED_HOPE))
                    return;

            target->RemoveAurasDueToSpell(SPELL_DAMAGE_REDUCTION_AURA);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warr_vigilance_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectRemoveFn(spell_warr_vigilance_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_vigilance_AuraScript();
    }
};

enum Charge
{
    SPELL_JUGGERNAUT_CRIT_BONUS_TALENT      = 64976,
    SPELL_JUGGERNAUT_CRIT_BONUS_BUFF        = 65156,
    SPELL_CHARGE                            = 34846,
};

class spell_warr_charge : public SpellScriptLoader
{
public:
    spell_warr_charge() : SpellScriptLoader("spell_warr_charge") { }

    class spell_warr_charge_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_charge_SpellScript);

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_JUGGERNAUT_CRIT_BONUS_TALENT) || !sSpellMgr->GetSpellInfo(SPELL_JUGGERNAUT_CRIT_BONUS_BUFF) || !sSpellMgr->GetSpellInfo(SPELL_CHARGE))
                return false;
            return true;
        }
        void HandleDummy(SpellEffIndex /* effIndex */)
        {
            int32 chargeBasePoints0 = GetEffectValue();
            Unit* caster = GetCaster();
            caster->CastCustomSpell(caster, SPELL_CHARGE, &chargeBasePoints0, NULL, NULL, true);

            //Juggernaut crit bonus
            if (caster->HasAura(SPELL_JUGGERNAUT_CRIT_BONUS_TALENT))
                caster->CastSpell(caster, SPELL_JUGGERNAUT_CRIT_BONUS_BUFF, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_charge_SpellScript();
    }
};

enum Slam
{
    SPELL_SLAM      = 50783,
};

class spell_warr_slam : public SpellScriptLoader
{
public:
    spell_warr_slam() : SpellScriptLoader("spell_warr_slam") { }

    class spell_warr_slam_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_slam_SpellScript);

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_SLAM))
                return false;
            return true;
        }
        void HandleDummy(SpellEffIndex /* effIndex */)
        {
            int32 bp0 = GetEffectValue();
            if (GetHitUnit())
                GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_SLAM, &bp0, NULL, NULL, true, 0);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_slam_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_slam_SpellScript();
    }
};

void AddSC_warrior_spell_scripts()
{
    new spell_warr_last_stand();
    new spell_warr_improved_spell_reflection();
    new spell_warr_bloodthirst();
    new spell_warr_victory_rush();
    new spell_warr_cleave();
    new spell_warr_intercept_triggered();
    new spell_warr_execute();
    new spell_warr_heroic_strike();
    new spell_warr_shockwave();
    new spell_warr_thunderclap();
    new spell_warr_deep_wounds();
    new spell_warr_vigilance();
    new spell_warr_charge();
    new spell_warr_slam();
}
