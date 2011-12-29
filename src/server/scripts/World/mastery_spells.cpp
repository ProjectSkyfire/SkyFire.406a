// mastery bonus for each branch
struct MasteryData
{
    uint32 talentBranch;
    uint32 masterySpell1;
    uint32 masterySpell2;
};

// mastery branch data for each player class (3 branches for each class)
struct MasterySet
{
    uint32 dummySpell;
    MasteryData data[3];
    void UpdateMastery(Player* player, uint32 branch)
    {
        //sLog->outBasic("[%u][%s] talent branch %u, dummySpell %u", player->GetGUIDLow(), player->GetName(), branch, dummySpell);
        bool canHaveMastery = player->HasSpell(dummySpell);
        for (int i = 0; i < 3; i ++)
        {
            if (canHaveMastery && data[i].talentBranch == branch)
            {
                if (data[i].masterySpell1 && !player->HasSpell(data[i].masterySpell1))
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "learn mastery %u", data[i].masterySpell1);
                    player->learnSpell(data[i].masterySpell1, true);
                }
                if (data[i].masterySpell2 && !player->HasSpell(data[i].masterySpell2))
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "learn mastery %u", data[i].masterySpell2);
                    player->learnSpell(data[i].masterySpell2, true);
                }
            }
            else
            {
                if (data[i].masterySpell1 && player->HasSpell(data[i].masterySpell1))
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "remove mastery %u", data[i].masterySpell1);
                    player->removeSpell(data[i].masterySpell1);
                }
                if (data[i].masterySpell2 && player->HasSpell(data[i].masterySpell2))
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "remove mastery %u", data[i].masterySpell2);
                    player->removeSpell(data[i].masterySpell2);
                }
            }
        }
    }

    void RecalculateMasteryAuraEffects(Player* player)
    {
        for (int i = 0; i < 3; i ++)
        {
            if (data[i].masterySpell1)
            {
                if (Aura* aura = player->GetAura(data[i].masterySpell1))
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "recalculate mastery amount %u", data[i].masterySpell1);
                    aura->RecalculateAmountOfEffects();
                }
            }
            if (data[i].masterySpell2)
            {
                if (Aura* aura = player->GetAura(data[i].masterySpell2))
                {
                    sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "recalculate mastery amount %u", data[i].masterySpell2);
                    aura->RecalculateAmountOfEffects();
                }
            }
        }
    }
};

class player_scripts_spec : public PlayerScript
{
public:
    player_scripts_spec() : PlayerScript("player_scripts_spec")
    {
        // definitions of the mastery branch data
        // it's hacky and should be replaced with accessing sTalentTabStore

        AddMastery(CLASS_WARRIOR, 87500,
            BS_WARRIOR_ARMS, 76838, 0,         // Strikes of Opportunity
            BS_WARRIOR_FURY, 76856, 0,         // Unshackled Fury
            BS_WARRIOR_PROTECTION, 76857, 0);  // Critical Block

        AddMastery(CLASS_PALADIN, 87494,
            BS_PALADIN_HOLY, 76669, 0,         // Illuminated Healing
            BS_PALADIN_PROTECTION, 76671, 0,   // Divine Bulwark
            BS_PALADIN_RETRIBUTION, 76672, 0); // Hand of Light

        AddMastery(CLASS_HUNTER, 87493,
            BS_HUNTER_BEAST_MASTERY, 76657, 0, // Master of Beasts
            BS_HUNTER_SURVIVAL, 76658, 0,      // Essence of the Viper
            BS_HUNTER_MARKMANSHIP, 76659, 0);  // Wild Quiver

        AddMastery(CLASS_ROGUE, 87496,
            BG_ROGUE_ASSASINATION, 76803, 0,   // Potent Poisons
            BS_ROGUE_COMBAT, 76806, 0,         // Main Gauche
            BS_ROGUE_SUBTLETY, 76808, 0);      // Executioner

        AddMastery(CLASS_PRIEST, 87495,
            BS_PRIEST_DISCIPLINE, 77484, 0,    // Shield Discipline
            BS_PRIEST_HOLY, 77485, 0,          // Echo of Light
            BS_PRIEST_SHADOW, 77486, 0);       // Shadow Orb Power

        AddMastery(CLASS_DEATH_KNIGHT, 87492,
            BS_DEATH_KNIGHT_BLOOD, 77513, 0,    // Blood Shield
            BS_DEATH_KNIGHT_FROST, 77514, 0,    // Frozen Heart
            BS_DEATH_KNIGHT_UNHOLY, 77515, 0);  // Dreadblade

        AddMastery(CLASS_SHAMAN, 87497,
            BS_SHAMAN_ELEMENTAL, 77222, 0,      // Elemental Overload
            BS_SHAMAN_ENCHANCEMENT, 77223, 0,   // Enhanced Elements
            BS_SHAMAN_RESTORATION, 77226, 0);   // Deep Healing

        AddMastery(CLASS_MAGE, 86467,
            BS_MAGE_ARCANE, 76547, 0,           // Mana Adept
            BS_MAGE_FIRE, 76595, 0,             // Flashburn
            BS_MAGE_FROST, 76613, 0);           // Frostburn

        AddMastery(CLASS_WARLOCK, 87498,
            BS_WARLOCK_AFFLICTION, 77215, 0,    // Potent Afflictions
            BS_WARLOCK_DEMONOLOGY, 77219, 0,    // Master Demonologist
            BS_WARLOCK_DESTRUCTION, 77220, 0);  // Fiery Apocalypse

        AddMastery(CLASS_DRUID, 87491,
            BS_DRUID_BALANCE, 77492, 0,         // Total Eclipse
            BS_DRUID_FERAL_COMBAT, 77493,       // Razor Claws
            77494,       // Savage Defender
            BS_DRUID_RESTORATION, 77495, 0);    // Harmony
    }

    void AddMastery(uint8 classType, uint32 dummySpell,
        uint32 talentBranch1, uint32 mastery1Spell1, uint32 mastery1Spell2,
        uint32 talentBranch2, uint32 mastery2Spell1, uint32 mastery2Spell2,
        uint32 talentBranch3, uint32 mastery3Spell1, uint32 mastery3Spell2)
    {
        MasterySet set;
        set.dummySpell = dummySpell;
        set.data[0].talentBranch = talentBranch1;
        set.data[0].masterySpell1 = mastery1Spell1;
        set.data[0].masterySpell2 = mastery1Spell2;
        set.data[1].talentBranch = talentBranch2;
        set.data[1].masterySpell1 = mastery2Spell1;
        set.data[1].masterySpell2 = mastery2Spell2;
        set.data[2].talentBranch = talentBranch3;
        set.data[2].masterySpell1 = mastery3Spell1;
        set.data[2].masterySpell2 = mastery3Spell2;
        MasteryMap[classType] = set;
    }

    void OnAddSpell(Player* player, uint32 spell_id, bool learning)
    {
        // learning Mastery at level 80
        switch(spell_id)
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
            std::map<uint8, MasterySet>::iterator iter = MasteryMap.find(player->getClass());
            if (iter != MasteryMap.end())
            {
                //sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "UpdateMastery(AddSpell) %u", spell_id);
                iter->second.UpdateMastery(player, player->GetTalentBranchSpec(player->GetActiveSpec()));
            }
            break;
        }
    }

    void OnActivateSpec(Player* player, uint8 spec)
    {
        uint8 classType = player->getClass();
        std::map<uint8, MasterySet>::iterator iter = MasteryMap.find(classType);
        if (iter != MasteryMap.end())
        {
            //sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "UpdateMastery(ActivateSpec) %u", spec);
            iter->second.UpdateMastery(player, player->GetTalentBranchSpec(spec));
        }
    }

    void OnTalentBranchSpecChanged(Player* player, uint8 spec, uint32 specID)
    {
        if (spec == player->GetActiveSpec())
        {
            std::map<uint8, MasterySet>::iterator iter = MasteryMap.find(player->getClass());
            if (iter == MasteryMap.end())
                return;
            //sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "UpdateMastery(TalentBranchChanged) %u", specID);
            iter->second.UpdateMastery(player, specID);
        }
    }

    void OnUpdateRating(Player* player, CombatRating cr, int32& amount)
    {
        if (cr != CR_MASTERY)
            return;
        std::map<uint8, MasterySet>::iterator iter = MasteryMap.find(player->getClass());
        if (iter == MasteryMap.end())
            return;
        //sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "RecalculateMasteryAuraEffects(UpdateRating)");
        iter->second.RecalculateMasteryAuraEffects(player);
    }
};

// Mastery helper class
class MasteryScript : public AuraScript
{
    PrepareAuraScript(MasteryScript);

protected:
    struct MasteryAuraData
    {
        AuraType auraType;
        bool handleProc;
    };

    MasteryAuraData masteryAuras[MAX_SPELL_EFFECTS];
    int32 dummyEffectIndex;
    uint32 defaultBaseAmount;

public:
    MasteryScript(AuraType auraType = SPELL_AURA_NONE, SpellEffIndex _dummyEffIndex = EFFECT_1, uint32 baseAmount = 0)
        : dummyEffectIndex(_dummyEffIndex), defaultBaseAmount(baseAmount)
    {
        SetMasteryAura(EFFECT_0, auraType);
        SetMasteryAura(EFFECT_1, SPELL_AURA_NONE);
        SetMasteryAura(EFFECT_2, SPELL_AURA_NONE);
    }

    void SetMasteryAura(SpellEffIndex effIndex, AuraType auraType, bool handleProc = false)
    {
        masteryAuras[effIndex].auraType = auraType;
        masteryAuras[effIndex].handleProc = handleProc;
    }

    void SetMasteryBaseAmount(int32 effIndex = EFFECT_1, uint32 baseAmount = 0)
    {
        dummyEffectIndex = effIndex;
        defaultBaseAmount = baseAmount;
    }

    virtual uint32 GetMasteryBaseAmount();
    virtual void OnProc(AuraEffect const * aurEff, Unit* pUnit, Unit *pVictim, uint32 damage, SpellEntry const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown) {}
    virtual void CalcAmount(AuraEffect const* /*aurEffect*/, int32& /*amount*/, bool& /*canBeRecalculated*/);
    virtual void CalcSpellMod(AuraEffect const * /*aurEff*/, SpellModifier *& /*spellMod*/, SpellEntry const * /*spellInfo*/, Unit * /*target*/) {}
    virtual void Register();
};

uint32 MasteryScript::GetMasteryBaseAmount()
{
    if (dummyEffectIndex >= 0 && dummyEffectIndex < MAX_SPELL_EFFECTS)
    {
        if (SpellEntry const* spellInfo = GetAura()->GetSpellProto())
            return spellInfo->EffectBasePoints[dummyEffectIndex] ? spellInfo->EffectBasePoints[dummyEffectIndex] : defaultBaseAmount;
        //if (AuraEffect* effect = GetAura()->GetEffect(dummyEffectIndex))
        //    return effect->GetBaseAmount()/*GetAmount()*/;
    }
    return defaultBaseAmount;
}

void MasteryScript::CalcAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
{
    if (Unit* caster = GetCaster())
    {
        if (Player* player = caster->ToPlayer())
        {
            uint32 baseAmount = GetMasteryBaseAmount();
            float mastery = player->GetMasteryPoints();
            int32 newAmount = int32((mastery + 8.0f) * baseAmount / 100.0f); // mastery points based on 8.00
            if (amount != newAmount)
            {
                amount = newAmount;
                sLog->outDetail("Mastery spell %u eff %u: mastery %.2f, amount %u, bonus %d", aurEff->GetId(), aurEff->GetEffIndex(), mastery, baseAmount, newAmount);
            }
        }
    }
    canBeRecalculated = true;
}

void MasteryScript::Register()
{
    for (uint8 i = EFFECT_0; i < MAX_SPELL_EFFECTS; i++)
    {
        if (masteryAuras[i].auraType != SPELL_AURA_NONE)
        {
            sLog->outDetail("MasteryScript::Register mastery aura %u : %u", i, masteryAuras[i].auraType);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(MasteryScript::CalcAmount, i, masteryAuras[i].auraType);
            DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(MasteryScript::CalcSpellMod, i, masteryAuras[i].auraType);
            if (masteryAuras[i].handleProc)
            {
                OnEffectProc += AuraEffectProcFn(MasteryScript::OnProc, i, masteryAuras[i].auraType);
            }
        }
    }
}


// 76838 Strikes of Opportunity
class spell_war_strikes_of_opportunity : public SpellScriptLoader
{
public:
    spell_war_strikes_of_opportunity() : SpellScriptLoader("spell_war_strikes_of_opportunity") { }

    class spell_hunter_wild_quiver_AuraScript : public MasteryScript
    {
    public:
        void OnProc(AuraEffect const * aurEff, Unit* pUnit, Unit *pVictim, uint32 damage, SpellEntry const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown)
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

    AuraScript *GetAuraScript() const
    {
        spell_hunter_wild_quiver_AuraScript* script = new spell_hunter_wild_quiver_AuraScript();
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

    AuraScript *GetAuraScript() const
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

    AuraScript *GetAuraScript() const
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
        void CalcSpellMod(AuraEffect const * aurEff, SpellModifier *& spellMod, SpellEntry const * /*spellInfo*/, Unit * /*target*/)
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
            {
                spellMod = new SpellModifier(GetAura(), const_cast<AuraEffect*>(aurEff));
                spellMod->op = SPELLMOD_DAMAGE/*SPELLMOD_ALL_EFFECTS*/;

                spellMod->type = SPELLMOD_PCT;
                spellMod->spellId = aurEff->GetId(); // 12042 Arcance Power : 685904631, 102472, 0
                spellMod->mask = flag96(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);//GetSpellProto()->EffectSpellClassMask[aurEff->GetEffIndex()];
                spellMod->charges = GetAura()->GetCharges();

                //sLog->outDetail("Mana Adept : creating spell mod");
            }
            //spellMod->spellId = aurEff->GetId(); // 12042
            spellMod->value = bonus;
        }
    };

    AuraScript *GetAuraScript() const
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

    AuraScript *GetAuraScript() const
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
        void CalcSpellMod(AuraEffect const * aurEff, SpellModifier *& spellMod, SpellEntry const *spellInfo, Unit * target)
        {
            int32 bonus = 0;
            if (target && target->HasAuraState(AURA_STATE_FROZEN, spellInfo, GetCaster()))
            {
                bonus = aurEff->GetAmount(); // 250 * mastery / 100
                //if (!spellMod || bonus != spellMod->value)
                //    sLog->outBasic("Frostburn : affected spell %u bonus %d", spellInfo ? spellInfo->Id : 0, bonus);
            }

            if (!spellMod)
            {
                spellMod = new SpellModifier(GetAura(), const_cast<AuraEffect*>(aurEff));
                spellMod->op = SPELLMOD_DAMAGE/*SPELLMOD_ALL_EFFECTS*/;

                spellMod->type = SPELLMOD_PCT;
                spellMod->spellId = aurEff->GetId(); // 12042 Arcance Power : 685904631, 102472, 0
                spellMod->mask = flag96(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);//GetSpellProto()->EffectSpellClassMask[aurEff->GetEffIndex()];
                spellMod->charges = GetAura()->GetCharges();

                //sLog->outDetail("Frostburn : creating spell mod");
            }
            //spellMod->spellId = aurEff->GetId(); // 12042
            spellMod->value = bonus;
        }
    };

    AuraScript *GetAuraScript() const
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
        void OnProc(AuraEffect const * aurEff, Unit* pUnit, Unit *pVictim, uint32 damage, SpellEntry const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, int32 cooldown)
        {
            PreventDefaultAction();
            if (!(procFlag & PROC_FLAG_DONE_SPELL_MAGIC_DMG_CLASS_NEG))
                return;

            Player* player = pUnit->ToPlayer();
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
            case   403: spellId = 45284; break;
                // Chain Lightning
            case   421: spellId = 45297; break;
                // Lava Burst
            case 51505: spellId = 77451; break;
            default:    return;
            }

            //sLog->outDetail("Elemental Overlord : attType %u, damage %u, procSpell %u, chance %d", attType, damage, procSpellId, aurEff->GetAmount());

            // Chain Lightning
            if (procSpell->SpellFamilyFlags[0] & 0x2)
            {
                // Chain lightning has [LightOverload_Proc_Chance] / [Max_Number_of_Targets] chance to proc of each individual target hit.
                // A maxed LO would have a 33% / 3 = 11% chance to proc of each target.
                // LO chance was already "accounted" at the proc chance roll, now need to divide the chance by [Max_Number_of_Targets]
                float chance = 100.0f / procSpell->EffectChainTarget[0];
                if (!roll_chance_f(chance))
                    return;

                // Remove cooldown (Chain Lightning - have Category Recovery time)
                player->RemoveSpellCooldown(spellId);
            }

            if (roll_chance_i(aurEff->GetAmount()))
            {
                pUnit->CastSpell(pVictim, spellId, true, NULL, aurEff);
                if (cooldown)
                    player->AddSpellCooldown(auraSpellId, 0, time(NULL) + cooldown);
            }
        }
    };

    AuraScript *GetAuraScript() const
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

// 77226 Deed Healing
class spell_sha_deep_healing : public SpellScriptLoader
{
public:
    spell_sha_deep_healing() : SpellScriptLoader("spell_sha_deep_healing") { }

    class spell_sha_deep_healing_AuraScript : public MasteryScript
    {
    public:
        void CalcSpellMod(AuraEffect const * aurEff, SpellModifier *& spellMod, SpellEntry const * /*spellInfo*/, Unit * target)
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
            {
                spellMod = new SpellModifier(GetAura(), const_cast<AuraEffect*>(aurEff));
                spellMod->op = SPELLMOD_DAMAGE/*SPELLMOD_ALL_EFFECTS*/;

                spellMod->type = SPELLMOD_PCT;
                spellMod->spellId = aurEff->GetId(); // 16188 Nature's Swiftness
                spellMod->mask = GetSpellProto()->EffectSpellClassMask[aurEff->GetEffIndex()];
                spellMod->charges = GetAura()->GetCharges();

                //sLog->outDetail("Deep Healing : creating spell mod");
            }
            //spellMod->spellId = 16188;//aurEff->GetId(); // 16188 Nature's Swiftness
            //if (spellMod->value != bonus)
            //    sLog->outDetail("Deep Healing : %s hpPct %.2f, bonus %d", target ? target->GetName() : "<None>", pct, bonus);
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
