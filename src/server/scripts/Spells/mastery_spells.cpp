#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"

class player_scripts_spec : public PlayerScript
{
public:
    player_scripts_spec() : PlayerScript("player_scripts_spec") { }

    void OnAddSpell(Player* player, uint32 spell_id, bool learning)
    {
        // learning Mastery at level 80
        switch (spell_id)
        {
            case 86470: // 87491 Druid
            case 86471: // 87492 Death Knight
            case 86472: // 87493 Hunter
            case 86473: // 86467 Mage
            case 86474: // 87494 Paladin
            case 86475: // 87495 Priest
            case 86476: // 87496 Rogue
            case 86477: // 87497 Shaman
            case 86478: // 87498 Warlock
            case 86479: // 87500 Warrior
                    player->UpdateMasteryAuras(player->GetTalentBranchSpec(player->GetActiveSpec()));
                break;
        }
    }

    void OnActivateSpec(Player* player, uint8 spec)
    {
        player->UpdateMasteryAuras(player->GetTalentBranchSpec(spec));
    }

    void OnTalentBranchSpecChanged(Player* player, uint8 spec, uint32 specID)
    {
        if (spec == player->GetActiveSpec())
            player->UpdateMasteryAuras(specID);
    }

    void OnUpdateRating(Player* player, CombatRating cr, int32& amount)
    {
        if (cr != CR_MASTERY)
            return;

        player->RecalculateMasteryAuraEffects(player->GetTalentBranchSpec(player->GetActiveSpec()));
    }
};

// 76838 Strikes of Opportunity
class spell_war_strikes_of_opportunity : public SpellScriptLoader
{
public:
    spell_war_strikes_of_opportunity() : SpellScriptLoader("spell_war_strikes_of_opportunity") { }

    class spell_war_strikes_of_opportunity_AuraScript : public MasteryScript
    {
    public:
        void OnProc(AuraEffect const* aurEff, Unit* pUnit, Unit* pVictim, uint32 damage, SpellInfo const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown)
        {
            PreventDefaultAction();
            if (attType != BASE_ATTACK && attType != OFF_ATTACK)
                return;
            uint32 procSpellId = procSpell ? procSpell->Id : 0;
            //sLog->outBasic("Strikes of Opportunity : attType %u, damage %u, procSpell %u, chance %d", attType, damage, procSpellId, aurEff->GetAmount());
            if ((procSpellId != 76858) && roll_chance_i(aurEff->GetAmount()))
            {
                pUnit->CastSpell(pVictim, 76858, true); // Opportunity Strike on melee attack
                if (cooldown && pUnit->GetTypeId() == TYPEID_PLAYER)
                    pUnit->ToPlayer()->AddSpellCooldown(76858, 0, time(NULL) + cooldown);
            }
        }
    };

    AuraScript* GetAuraScript() const
    {
        spell_war_strikes_of_opportunity_AuraScript* script = new spell_war_strikes_of_opportunity_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_DUMMY, true);
        script->SetMasteryBaseAmount(EFFECT_1, 220);
        return script;
    }
};

// 76856 Unshackled Fury
class spell_war_unshackled_fury : public SpellScriptLoader
{
public:
    spell_war_unshackled_fury() : SpellScriptLoader("spell_war_unshackled_fury") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_2, 560);
        return script;
    }
};

// 76857 Critical Block
class spell_war_critical_block : public SpellScriptLoader
{
public:
    spell_war_critical_block() : SpellScriptLoader("spell_war_critical_block") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_MOD_BLOCK_CRIT_CHANCE);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_MOD_BLOCK_PERCENT);
        script->SetMasteryBaseAmount(EFFECT_2, 150);
        return script;
    }
};

// 76547 Mana Adept
class spell_mage_mana_adept : public SpellScriptLoader
{
public:
    spell_mage_mana_adept() : SpellScriptLoader("spell_mage_mana_adept") { }

    class spell_mage_mana_adept_AuraScript : public MasteryScript
    {
        void CalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod, SpellInfo const* /*spellInfo*/, Unit* /*target*/)
        {
            int32 bonus = 0;
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    uint32 maxMana = player->GetMaxPower(POWER_MANA);
                    if (!maxMana)
                        return;
                    uint32 amount = aurEff->GetAmount(); // 150 * mastery / 100
                    float manaPercent = float(player->GetPower(POWER_MANA)) / float(maxMana);
                    //float mastery = player->GetMasteryPoints();
                    bonus = int32(manaPercent * (/*(mastery + 8.0f) **/ amount)/* / 100.0f*/);
                    //if (!spellMod || bonus != spellMod->value)
                    //    sLog->outBasic("Mana Adept : manaPct %.2f, amount %u, bonus %d", manaPercent, amount, bonus);
                }
            }

            if (!spellMod)
                spellMod = new SpellModifier(GetAura(), const_cast<AuraEffect*>(aurEff));

            spellMod->op = SPELLMOD_DAMAGE/*SPELLMOD_ALL_EFFECTS*/;

            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = aurEff->GetId(); // 12042 Arcane Power : 685904631, 102472, 0
            spellMod->mask = flag96(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);//GetSpellProto()->EffectSpellClassMask[aurEff->GetEffIndex()];
            spellMod->charges = GetAura()->GetCharges();

            //spellMod->spellId = aurEff->GetId(); // 12042
            spellMod->value = bonus;
        }
    };

    AuraScript* GetAuraScript() const
    {
        spell_mage_mana_adept_AuraScript *script = new spell_mage_mana_adept_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER/*SPELL_AURA_DUMMY*/); // changed in SpellMgr
        script->SetMasteryBaseAmount(EFFECT_1, 150);
        return script;
    }
};

// 76595 Flashburn
class spell_mage_flashburn : public SpellScriptLoader
{
public:
    spell_mage_flashburn() : SpellScriptLoader("spell_mage_flashburn") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_1, 280);
        return script;
    }
};

// 76613 Frostburn
class spell_mage_frostburn : public SpellScriptLoader
{
public:
    spell_mage_frostburn() : SpellScriptLoader("spell_mage_frostburn") { }

    class spell_mage_frostburn_AuraScript : public MasteryScript
    {
        void CalcSpellMod(AuraEffect const * aurEff, SpellModifier *& spellMod, SpellInfo const *spellInfo, Unit * target)
        {
            int32 bonus = 0;
            if (target && target->HasAuraState(AURA_STATE_FROZEN, spellInfo, GetCaster()))
            {
                bonus = aurEff->GetAmount(); // 250 * mastery / 100
                //if (!spellMod || bonus != spellMod->value)
                //    sLog->outBasic("Frostburn : affected spell %u bonus %d", spellInfo ? spellInfo->Id : 0, bonus);
            }

            if (!spellMod)
                spellMod = new SpellModifier(GetAura(), const_cast<AuraEffect*>(aurEff));

            spellMod->op = SPELLMOD_DAMAGE/*SPELLMOD_ALL_EFFECTS*/;
            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = aurEff->GetId(); // 12042 Arcane Power : 685904631, 102472, 0
            spellMod->mask = flag96(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);//GetSpellProto()->EffectSpellClassMask[aurEff->GetEffIndex()];
            spellMod->charges = GetAura()->GetCharges();
            //spellMod->spellId = aurEff->GetId(); // 12042
            spellMod->value = bonus;
        }
    };

    AuraScript* GetAuraScript() const
    {
        spell_mage_frostburn_AuraScript *script = new spell_mage_frostburn_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER/*SPELL_AURA_DUMMY*/); // changed in SpellMgr
        script->SetMasteryBaseAmount(EFFECT_1, 250);
        return script;
    }
};

// 77222 Elemental Overlord
class spell_sha_elemental_overlord : public SpellScriptLoader
{
public:
    spell_sha_elemental_overlord() : SpellScriptLoader("spell_sha_elemental_overlord") { }

    class spell_sha_elemental_overlord_AuraScript : public MasteryScript
    {
    public:
        void OnProc(AuraEffect const* aurEff, Unit* unit, Unit* victim, uint32 damage, SpellInfo const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown)
        {
            PreventDefaultAction();
            if (!(procFlag & PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_NEG))
                return;

            Player* player = unit->ToPlayer();
            if (!player)
                return;

            // custom cooldown processing case
            uint32 auraSpellId = GetAura()->GetId();
            if (cooldown && player->HasSpellCooldown(auraSpellId))
                return;

            uint32 procSpellId = procSpell ? procSpell->Id : 0;
            uint32 spellId = 0;
            switch (procSpellId)
            {
                // Lightning Bolt
                case 403:
                    spellId = 45284;
                    break;
                // Chain Lightning
                case 421:
                    spellId = 45297;
                    break;
                // Lava Burst
                case 51505:
                    spellId = 77451;
                    break;
                default:
                    return;
            }

            //sLog->outDetail("Elemental Overlord : attType %u, damage %u, procSpell %u, chance %d", attType, damage, procSpellId, aurEff->GetAmount());

            // Chain Lightning
            if (procSpell->SpellFamilyFlags[0] & 0x2)
            {
                // Chain lightning has [LightOverload_Proc_Chance] / [Max_Number_of_Targets] chance to proc of each individual target hit.
                // A maxed LO would have a 33% / 3 = 11% chance to proc of each target.
                // LO chance was already "accounted" at the proc chance roll, now need to divide the chance by [Max_Number_of_Targets]
                float chance = 100.0f / procSpell->Effects[EFFECT_0].ChainTarget;
                if (!roll_chance_f(chance))
                    return;

                // Remove cooldown (Chain Lightning - have Category Recovery time)
                player->RemoveSpellCooldown(spellId);
            }

            if (roll_chance_i(aurEff->GetAmount()))
            {
                unit->CastSpell(victim, spellId, true, NULL, aurEff);
                if (cooldown)
                    player->AddSpellCooldown(auraSpellId, 0, time(NULL) + cooldown);
            }
        }
    };

    AuraScript* GetAuraScript() const
    {
        spell_sha_elemental_overlord_AuraScript* script = new spell_sha_elemental_overlord_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_DUMMY, true);
        script->SetMasteryBaseAmount(EFFECT_1, 250);
        return script;
    }
};

// 77223 Enhanced Elements
class spell_sha_enhanced_elements : public SpellScriptLoader
{
public:
    spell_sha_enhanced_elements() : SpellScriptLoader("spell_sha_enhanced_elements") { }

    AuraScript *GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
        script->SetMasteryBaseAmount(EFFECT_1, 250);
        return script;
    }
};

// 77226 Deep Healing
class spell_sha_deep_healing : public SpellScriptLoader
{
public:
    spell_sha_deep_healing() : SpellScriptLoader("spell_sha_deep_healing") { }

    class spell_sha_deep_healing_AuraScript : public MasteryScript
    {
    public:
        void CalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod, SpellInfo const* /*spellInfo*/, Unit* target)
        {
            int32 bonus = 0;
            float pct = 0.0f;
            if (target)
            {
                pct = target->GetHealthPct();
                uint32 amount = aurEff->GetAmount(); // 300
                //float mastery = player->GetMasteryPoints();
                bonus = int32((100.0f - pct) * amount/*((mastery + 8.0f) * amount)*/ / 100.0f);
            }

            if (!spellMod)
                spellMod = new SpellModifier(GetAura(), const_cast<AuraEffect*>(aurEff));

            spellMod->op = SPELLMOD_DAMAGE/*SPELLMOD_ALL_EFFECTS*/;

            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = aurEff->GetId(); // 16188 Nature's Swiftness
            spellMod->mask = GetSpellInfo()->Effects[aurEff->GetEffIndex()].SpellClassMask;
            spellMod->charges = GetAura()->GetCharges();

            spellMod->value = bonus;
        }
    };

    AuraScript *GetAuraScript() const
    {
        spell_sha_deep_healing_AuraScript* script = new spell_sha_deep_healing_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER/*SPELL_AURA_DUMMY*/); // changed in SpellMgr
        script->SetMasteryBaseAmount(EFFECT_1, 300);
        return script;
    }
};

// 76659 Wild Quiver
class spell_hun_wild_quiver : public SpellScriptLoader
{
public:
    spell_hun_wild_quiver() : SpellScriptLoader("spell_hun_wild_quiver") { }

    class spell_hun_wild_quiver_AuraScript : public MasteryScript
    {
    public:
        void OnProc(AuraEffect const* aurEff, Unit* unit, Unit* victim, uint32 damage, SpellInfo const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown)
        {
            PreventDefaultAction();
            if (attType != RANGED_ATTACK && attType != OFF_ATTACK)
                return;
            uint32 procSpellId = procSpell ? procSpell->Id : 0;
            if ((procSpellId != 76663) && roll_chance_i(aurEff->GetAmount()))
            {
                unit->CastSpell(victim, 76663, true); // Wild Quiver on auto-shot
                if (cooldown && unit->GetTypeId() == TYPEID_PLAYER)
                    unit->ToPlayer()->AddSpellCooldown(76663, 0, time(NULL) + cooldown);
            }
        }
    };

    AuraScript* GetAuraScript() const
    {
        spell_hun_wild_quiver_AuraScript* script = new spell_hun_wild_quiver_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_DUMMY, true);
        script->SetMasteryBaseAmount(EFFECT_1, 180);
        return script;
    }
};

// 76657 Master of Beasts
class spell_hun_master_of_beasts : public SpellScriptLoader
{
public:
    spell_hun_master_of_beasts() : SpellScriptLoader("spell_hun_master_of_beasts") { }

    AuraScript *GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_1, 170);
        return script;
    }
};

// 76803 Potent Poisons
class spell_rog_potent_poisons : public SpellScriptLoader
{
public:
    spell_rog_potent_poisons() : SpellScriptLoader("spell_rog_potent_poisons") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_2, 350);
        return script;
    }
};

// 76806 Main Gauche
class spell_rog_main_gauche : public SpellScriptLoader
{
public:
    spell_rog_main_gauche() : SpellScriptLoader("spell_rog_main_gauche") { }

    class spell_rog_main_gauche_AuraScript : public MasteryScript
    {
    public:
        void OnProc(AuraEffect const* aurEff, Unit* unit, Unit* victim, uint32 damage, SpellInfo const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown)
        {
            PreventDefaultAction();
            if (attType != BASE_ATTACK)
                return;
            uint32 procSpellId = procSpell ? procSpell->Id : 0;
            if ((procSpellId != 86392) && roll_chance_i(aurEff->GetAmount()))
            {
                unit->CastSpell(victim, 86392, true); // Main Gauche on melee
                if (cooldown && unit->GetTypeId() == TYPEID_PLAYER)
                    unit->ToPlayer()->AddSpellCooldown(86392, 0, time(NULL) + cooldown);
            }
        }
    };

    AuraScript* GetAuraScript() const
    {
        spell_rog_main_gauche_AuraScript* script = new spell_rog_main_gauche_AuraScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_DUMMY, true);
        script->SetMasteryBaseAmount(EFFECT_1, 200);
        return script;
    }
};

// 76808 Executioner
class spell_rog_executioner : public SpellScriptLoader
{
public:
    spell_rog_executioner() : SpellScriptLoader("spell_rog_executioner") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_2, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_0, 250);
        return script;
    }
};

void AddSC_mastery_spells()
{
    new player_scripts_spec;

    // Warrior masteries
    new spell_war_strikes_of_opportunity;
    new spell_war_unshackled_fury;
    new spell_war_critical_block;

    // Mage masteries
    new spell_mage_mana_adept;
    new spell_mage_flashburn;
    new spell_mage_frostburn;

    // Shaman masteries
    new spell_sha_elemental_overlord;
    new spell_sha_enhanced_elements;
    new spell_sha_deep_healing;

    // Hunter masteries
    new spell_hun_wild_quiver;
    new spell_hun_master_of_beasts;

    // Rogue masteries
    new spell_rog_potent_poisons;
    new spell_rog_main_gauche;
    new spell_rog_executioner;
}
