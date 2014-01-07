/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
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

#ifndef _SPELLINFO_H
#define _SPELLINFO_H

#include "SharedDefines.h"
#include "Util.h"
#include "DBCStructure.h"
#include "Object.h"

class Unit;
class Player;
class Item;
class Spell;
class SpellInfo;
struct SpellChainNode;
struct SpellTargetPosition;
struct SpellDurationEntry;
struct SpellModifier;
struct SpellRangeEntry;
struct SpellRadiusEntry;
struct SpellEntry;
struct SpellCastTimesEntry;
struct Condition;

enum SpellCastTargetFlags
{
    TARGET_FLAG_NONE            = 0x00000000,
    TARGET_FLAG_UNUSED_1        = 0x00000001,               // not used
    TARGET_FLAG_UNIT            = 0x00000002,               // guid
    TARGET_FLAG_UNIT_RAID       = 0x00000004,               // not sent, used to validate target (if raid member)
    TARGET_FLAG_UNIT_PARTY      = 0x00000008,               // not sent, used to validate target (if party member)
    TARGET_FLAG_ITEM            = 0x00000010,               // guid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // guid, 3 float
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // guid, 3 float
    TARGET_FLAG_UNIT_ENEMY      = 0x00000080,               // not sent, used to validate target (if enemy)
    TARGET_FLAG_UNIT_ALLY       = 0x00000100,               // not sent, used to validate target (if ally)
    TARGET_FLAG_CORPSE_ENEMY    = 0x00000200,               // guid
    TARGET_FLAG_UNIT_DEAD       = 0x00000400,               // not sent, used to validate target (if dead creature)
    TARGET_FLAG_GAMEOBJECT      = 0x00000800,               // guid, used with TARGET_GAMEOBJECT_TARGET
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // guid
    TARGET_FLAG_STRING          = 0x00002000,               // string
    TARGET_FLAG_GAMEOBJECT_ITEM = 0x00004000,               // not sent, used with TARGET_GAMEOBJECT_ITEM_TARGET
    TARGET_FLAG_CORPSE_ALLY     = 0x00008000,               // guid
    TARGET_FLAG_UNIT_MINIPET    = 0x00010000,               // guid, used to validate target (if non combat pet)
    TARGET_FLAG_GLYPH_SLOT      = 0x00020000,               // used in glyph spells
    TARGET_FLAG_DEST_TARGET     = 0x00040000,               // sometimes appears with DEST_TARGET spells (may appear or not for a given spell)
    TARGET_FLAG_UNUSED20        = 0x00080000,               // uint32 counter, loop { vec3 - screen position (?), guid }, not used so far
    TARGET_FLAG_UNIT_PASSENGER  = 0x00100000,               // guessed, used to validate target (if vehicle passenger)

    TARGET_FLAG_UNIT_MASK = TARGET_FLAG_UNIT | TARGET_FLAG_UNIT_RAID | TARGET_FLAG_UNIT_PARTY | TARGET_FLAG_UNIT_ENEMY | TARGET_FLAG_UNIT_ALLY | TARGET_FLAG_UNIT_DEAD | TARGET_FLAG_UNIT_MINIPET | TARGET_FLAG_UNIT_PASSENGER, TARGET_FLAG_GAMEOBJECT_MASK = TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_GAMEOBJECT_ITEM, TARGET_FLAG_CORPSE_MASK = TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY, TARGET_FLAG_ITEM_MASK = TARGET_FLAG_TRADE_ITEM | TARGET_FLAG_ITEM | TARGET_FLAG_GAMEOBJECT_ITEM,
};

enum SpellTargetSelectionCategories
{
    TARGET_SELECT_CATEGORY_NYI,
    TARGET_SELECT_CATEGORY_DEFAULT,
    TARGET_SELECT_CATEGORY_CHANNEL,
    TARGET_SELECT_CATEGORY_NEARBY,
    TARGET_SELECT_CATEGORY_CONE,
    TARGET_SELECT_CATEGORY_AREA,
};

enum SpellTargetReferenceTypes
{
    TARGET_REFERENCE_TYPE_NONE,
    TARGET_REFERENCE_TYPE_CASTER,
    TARGET_REFERENCE_TYPE_TARGET,
    TARGET_REFERENCE_TYPE_LAST,
    TARGET_REFERENCE_TYPE_SRC,
    TARGET_REFERENCE_TYPE_DEST,
};

enum SpellTargetObjectTypes
{
    TARGET_OBJECT_TYPE_NONE = 0,
    TARGET_OBJECT_TYPE_SRC,
    TARGET_OBJECT_TYPE_DEST,
    TARGET_OBJECT_TYPE_UNIT,
    TARGET_OBJECT_TYPE_UNIT_AND_DEST,
    TARGET_OBJECT_TYPE_GOBJ,
    TARGET_OBJECT_TYPE_GOBJ_ITEM,
    TARGET_OBJECT_TYPE_ITEM,
    TARGET_OBJECT_TYPE_CORPSE,
    // only for effect target type
    TARGET_OBJECT_TYPE_CORPSE_ENEMY,
    TARGET_OBJECT_TYPE_CORPSE_ALLY,
};

enum SpellTargetCheckTypes
{
    TARGET_CHECK_DEFAULT,
    TARGET_CHECK_ENTRY,
    TARGET_CHECK_ENEMY,
    TARGET_CHECK_ALLY,
    TARGET_CHECK_PARTY,
    TARGET_CHECK_RAID,
    TARGET_CHECK_RAID_CLASS,
    TARGET_CHECK_PASSENGER,
};

enum SpellTargetDirectionTypes
{
    TARGET_DIR_NONE,
    TARGET_DIR_FRONT,
    TARGET_DIR_BACK,
    TARGET_DIR_RIGHT,
    TARGET_DIR_LEFT,
    TARGET_DIR_FRONT_RIGHT,
    TARGET_DIR_BACK_RIGHT,
    TARGET_DIR_BACK_LEFT,
    TARGET_DIR_FRONT_LEFT,
    TARGET_DIR_RANDOM,
    TARGET_DIR_ENTRY,
};

enum SpellEffectImplicitTargetTypes
{
    EFFECT_IMPLICIT_TARGET_NONE = 0,
    EFFECT_IMPLICIT_TARGET_EXPLICIT,
    EFFECT_IMPLICIT_TARGET_CASTER,
};

// Spell classification
enum SpellSpecificType
{
    SPELL_SPECIFIC_NORMAL                        = 0,
    SPELL_SPECIFIC_SEAL                          = 1,
    SPELL_SPECIFIC_AURA                          = 3,
    SPELL_SPECIFIC_STING                         = 4,
    SPELL_SPECIFIC_CURSE                         = 5,
    SPELL_SPECIFIC_ASPECT                        = 6,
    SPELL_SPECIFIC_TRACKER                       = 7,
    SPELL_SPECIFIC_WARLOCK_ARMOR                 = 8,
    SPELL_SPECIFIC_MAGE_ARMOR                    = 9,
    SPELL_SPECIFIC_ELEMENTAL_SHIELD              = 10,
    SPELL_SPECIFIC_MAGE_POLYMORPH                = 11,
    SPELL_SPECIFIC_JUDGEMENT                     = 13,
    SPELL_SPECIFIC_WARLOCK_CORRUPTION            = 17,
    SPELL_SPECIFIC_FOOD                          = 19,
    SPELL_SPECIFIC_DRINK                         = 20,
    SPELL_SPECIFIC_FOOD_AND_DRINK                = 21,
    SPELL_SPECIFIC_PRESENCE                      = 22,
    SPELL_SPECIFIC_CHARM                         = 23,
    SPELL_SPECIFIC_SCROLL                        = 24,
    SPELL_SPECIFIC_MAGE_ARCANE_BRILLANCE         = 25,
    SPELL_SPECIFIC_WARRIOR_ENRAGE                = 26,
    SPELL_SPECIFIC_PRIEST_DIVINE_SPIRIT          = 27,
    SPELL_SPECIFIC_HAND                          = 28,
    SPELL_SPECIFIC_PHASE                         = 29
};

enum SpellCustomAttributes
{
    SPELL_ATTR0_CU_ENCHANT_PROC     = 0x00000001,
    SPELL_ATTR0_CU_CONE_BACK        = 0x00000002,
    SPELL_ATTR0_CU_CONE_LINE        = 0x00000004,
    SPELL_ATTR0_CU_SHARE_DAMAGE     = 0x00000008,
    SPELL_ATTR0_CU_NO_INITIAL_THREAT  = 0x00000010,
    SPELL_ATTR0_CU_SCALABLE         = 0x00000020,
    SPELL_ATTR0_CU_AURA_CC          = 0x00000040,
    SPELL_ATTR0_CU_DIRECT_DAMAGE    = 0x00000100,
    SPELL_ATTR0_CU_CHARGE           = 0x00000200,
    SPELL_ATTR0_CU_LINK_CAST        = 0x00000400,
    SPELL_ATTR0_CU_LINK_HIT         = 0x00000800,
    SPELL_ATTR0_CU_LINK_AURA        = 0x00001000,
    SPELL_ATTR0_CU_LINK_REMOVE      = 0x00002000,
    SPELL_ATTR0_CU_PICKPOCKET       = 0x00004000,
    SPELL_ATTR0_CU_EXCLUDE_SELF     = 0x00008000,
    SPELL_ATTR0_CU_NEGATIVE_EFF0    = 0x00010000,
    SPELL_ATTR0_CU_NEGATIVE_EFF1    = 0x00020000,
    SPELL_ATTR0_CU_NEGATIVE_EFF2    = 0x00040000,
    SPELL_ATTR0_CU_IGNORE_ARMOR     = 0x00080000,
    SPELL_ATTR0_CU_REQ_TARGET_FACING_CASTER      = 0x00100000,
    SPELL_ATTR0_CU_REQ_CASTER_BEHIND_TARGET      = 0x00200000,
    
    SPELL_ATTR0_CU_NEGATIVE = SPELL_ATTR0_CU_NEGATIVE_EFF0 | SPELL_ATTR0_CU_NEGATIVE_EFF1 | SPELL_ATTR0_CU_NEGATIVE_EFF2
};

uint32 GetTargetFlagMask(SpellTargetObjectTypes objType);

class SpellImplicitTargetInfo
{
private:
    Targets _target;
public:
    SpellImplicitTargetInfo() {}
    SpellImplicitTargetInfo(uint32 target);

    bool IsArea() const;
    SpellTargetSelectionCategories GetSelectionCategory() const;
    SpellTargetReferenceTypes GetReferenceType() const;
    SpellTargetObjectTypes GetObjectType() const;
    SpellTargetCheckTypes GetCheckType() const;
    SpellTargetDirectionTypes GetDirectionType() const;
    float CalcDirectionAngle() const;

    Targets GetTarget() const;
    uint32 GetExplicitTargetMask(bool& srcSet, bool& dstSet) const;

private:

    struct StaticData
    {
        SpellTargetObjectTypes ObjectType;               // type of object returned by target type
        SpellTargetReferenceTypes ReferenceType;         // defines which object is used as a reference when selecting target
        SpellTargetSelectionCategories SelectionCategory;
        SpellTargetCheckTypes SelectionCheckType;        // defines selection criteria
        SpellTargetDirectionTypes DirectionType;         // direction for cone and dest targets
    };
    static StaticData _data[TOTAL_SPELL_TARGETS];
};

class SpellEffectInfo
{
    SpellInfo const* _spellInfo;
    uint8     _effIndex;
public:
    uint32    Effect;
    float     ValueMultiplier;
    uint32    ApplyAuraName;
    uint32    Amplitude;
    int32     BasePoints;
    float     BonusCoefficient;
    float     DamageMultiplier;
    uint32    ChainTarget;
    int32     DieSides;
    uint32    ItemType;
    Mechanics Mechanic;
    int32     MiscValue;
    int32     MiscValueB;
    float     PointsPerComboPoint;
    SpellImplicitTargetInfo TargetA;
    SpellImplicitTargetInfo TargetB;
    SpellRadiusEntry const* RadiusEntry;
    float     RealPointsPerLevel;
    flag96    SpellClassMask;
    std::list <Condition*> * ImplicitTargetConditions;
    uint32    TriggerSpell;

    SpellEffectInfo();
    SpellEffectInfo(SpellEffectEntry const *spellEffect, SpellInfo const* spellInfo);

    bool IsEffect() const;
    bool IsEffect(SpellEffects effectName) const;
    bool IsAura() const;
    bool IsAura(AuraType aura) const;
    bool IsTargetingArea() const;
    bool IsAreaAuraEffect() const;
    bool IsFarUnitTargetEffect() const;
    bool IsFarDestTargetEffect() const;
    bool IsUnitOwnedAuraEffect() const;

    int32 CalcValue(Unit const* caster = NULL, int32 const* basePoints = NULL, Unit const* target = NULL) const;
    int32 CalcBaseValue(int32 value) const;
    float CalcValueMultiplier(Unit* caster, Spell* spell = NULL) const;
    float CalcDamageMultiplier(Unit* caster, Spell* spell = NULL) const;

    bool HasRadius() const;
    float CalcRadius(Unit* caster = NULL, Spell* = NULL) const;

    uint32 GetProvidedTargetMask() const;
    uint32 GetMissingTargetMask(bool srcSet = false, bool destSet = false, uint32 mask = 0) const;

    SpellEffectImplicitTargetTypes GetImplicitTargetType() const;
    SpellTargetObjectTypes GetUsedTargetObjectType() const;

private:
    struct StaticData
    {
        SpellEffectImplicitTargetTypes ImplicitTargetType;  // defines what target can be added to effect target list if there's no valid target type provided for effect
        SpellTargetObjectTypes UsedTargetObjectType;        // defines valid target object type for spell effect
    };
    static StaticData _data [TOTAL_SPELL_EFFECTS];
};

class SpellInfo
{
public:
    uint32    Id;                                           // 0        m_ID
    uint32    Attributes;                                   // 1        m_attribute
    uint32    AttributesEx;                                 // 2        m_attributesEx
    uint32    AttributesEx2;                                // 3        m_attributesExB
    uint32    AttributesEx3;                                // 4        m_attributesExC
    uint32    AttributesEx4;                                // 5        m_attributesExD
    uint32    AttributesEx5;                                // 6        m_attributesExE
    uint32    AttributesEx6;                                // 7        m_attributesExF
    uint32    AttributesEx7;                                // 8        3.2.0 (0x20 - totems, 0x4 - paladin auras, etc...)
    uint32    AttributesEx8;                                // 9        m_attributesExH
    // uint32 unk_400_1;                                    // 10       4.0.0
    SpellCastTimesEntry const* CastTimeEntry;               // 11       m_castingTimeIndex
    SpellDurationEntry const*  DurationEntry;               // 12       m_durationIndex
    uint32 PowerType;                                       // 13       _powerType
    SpellRangeEntry const* RangeEntry;                      // 14       m_rangeIndex
    float  Speed;                                           // 15       m_speed
    uint32 SpellVisual[2];                                  // 16-17    m_spellVisualID
    uint32 SpellIconID;                                     // 18       m_spellIconID
    uint32 ActiveIconID;                                    // 19       m_activeIconID
    char*  SpellName;                                       // 20       m_name
    uint32 SpellShapeshiftId;                               // 21       SpellShapeshift.dbc
    // DBCString Description;                               // 22       m_description_lang not used
    // DBCString ToolTip;                                   // 23       m_auraDescription_lang not used
    uint32 SchoolMask;                                      // 24       m_schoolMask
    uint32 RuneCostID;                                      // 25       m_runeCostID
    // uint32  spellMissileID;                              // 26       m_spellMissileID not used
    // uint32  spellDescriptionVariableID;                  // 27       3.2.0
    uint32 SpellDifficultyId;                               // 28       m_spellDifficultyID - id from SpellDifficulty.dbc
    // float unk_f1;                                        // 29
    uint32 SpellScalingId;                                  // 30       SpellScaling.dbc
    uint32 SpellAuraOptionsId;                              // 31       SpellAuraOptions.dbc
    uint32 SpellAuraRestrictionsId;                         // 32       SpellAuraRestrictions.dbc
    uint32 SpellCastingRequirementsId;                      // 33       SpellCastingRequirements.dbc
    uint32 SpellCategoriesId;                               // 34       SpellCategories.dbc
    uint32 SpellClassOptionsId;                             // 35       SpellClassOptions.dbc
    uint32 SpellCooldownsId;                                // 36       SpellCooldowns.dbc
    // uint32 unkIndex7;                                    // 37       all zeros...
    uint32 SpellEquippedItemsId;                            // 38       SpellEquippedItems.dbc
    uint32 SpellInterruptsId;                               // 39       SpellInterrupts.dbc
    uint32 SpellLevelsId;                                   // 40       SpellLevels.dbc
    uint32 SpellPowerId;                                    // 41       SpellPower.dbc
    uint32 SpellReagentsId;                                 // 42       SpellReagents.dbc
    uint32 SpellTargetRestrictionsId;                       // 44       SpellTargetRestrictions.dbc
    uint32 SpellTotemsId;                                   // 45       SpellTotems.dbc
    // uint32 unk2;                                         // 46

    // SpellAuraOptionsEntry
    uint32 StackAmount;
    uint32 ProcFlags;
    uint32 ProcChance;
    uint32 ProcCharges;

    // SpellAuraRestrictionsEntry
    uint32 CasterAuraState;
    uint32 TargetAuraState;
    uint32 CasterAuraStateNot;
    uint32 TargetAuraStateNot;
    uint32 CasterAuraSpell;
    uint32 TargetAuraSpell;
    uint32 ExcludeCasterAuraSpell;
    uint32 ExcludeTargetAuraSpell;

    // SpellCastingRequirementsEntry
    uint32 FacingCasterFlags;
    int32  AreaGroupId;
    uint32 RequiresSpellFocus;

    // SpellCategoriesEntry
    uint32 Category;
    uint32 DmgClass;
    uint32 Dispel;
    uint32 Mechanic;
    uint32 PreventionType;
    uint32 StartRecoveryCategory;

    // SpellClassOptionsEntry
    uint32 SpellFamilyName;
    flag96 SpellFamilyFlags;

    // SpellCooldownsEntry
    uint32 RecoveryTime;
    uint32 CategoryRecoveryTime;
    uint32 StartRecoveryTime;

    // SpellEffectEntry
    SpellEffectInfo Effects[MAX_SPELL_EFFECTS];

    // SpellEquippedItemsEntry
    int32  EquippedItemClass;
    int32  EquippedItemSubClassMask;
    int32  EquippedItemInventoryTypeMask;

    // SpellInterruptsEntry
    uint32 InterruptFlags;
    uint32 AuraInterruptFlags;
    uint32 ChannelInterruptFlags;

    // SpellLevelsEntry
    uint32 MaxLevel;
    uint32 BaseLevel;
    uint32 SpellLevel;

    // SpellPowerEntry
    uint32 ManaCost;
    uint32 ManaCostPerlevel;
    uint32 ManaPerSecond;
    uint32 ManaCostPercentage;
    //uint32 ManaPerSecondPerLevel;  // 4.0.1  MP5.REMOVED

    // SpellReagentsEntry
    int32  Reagent [MAX_SPELL_REAGENTS];
    uint32 ReagentCount [MAX_SPELL_REAGENTS];

    // SpellScalingEntry
    int32  castTimeMin;
    int32  castTimeMax;
    uint32 castScalingMaxLevel;
    int32  playerClass;
    float  Multiplier[3];
    float  RandomMultiplier[3];
    float  OtherMultiplier[3];
    float  CoefBase;
    uint32 CoefLevelBase;

    // SpellShapeshiftEntry
    uint32 Stances;
    uint32 StancesNot;

    // SpellTargetRestrictionsEntry
    uint32 Targets;
    uint32 TargetCreatureType;
    uint32 MaxTargetLevel;
    uint32 MaxAffectedTargets;

    // SpellTotemsEntry
    uint32 Totem[2];
    uint32 TotemCategory[2];

    // Custom
    uint32 AttributesCu;
    uint32 ExplicitTargetMask;
    SpellChainNode const* ChainEntry;

    SpellInfo(SpellEntry const* spellEntry);
    ~SpellInfo();

    void LoadSpellAddons();
    void LoadSpellEffect(SpellEffectEntry const *spellEffect);

    // struct access functions
    SpellAuraOptionsEntry const*            GetSpellAuraOptions() const;
    SpellAuraRestrictionsEntry const*       GetSpellAuraRestrictions() const;
    SpellCastingRequirementsEntry const*    GetSpellCastingRequirements() const;
    SpellCategoriesEntry const*             GetSpellCategories() const;
    SpellClassOptionsEntry const*           GetSpellClassOptions() const;
    SpellCooldownsEntry const*              GetSpellCooldowns() const;
    SpellEquippedItemsEntry const*          GetSpellEquippedItems() const;
    SpellInterruptsEntry const*             GetSpellInterrupts() const;
    SpellLevelsEntry const*                 GetSpellLevels() const;
    SpellPowerEntry const*                  GetSpellPower() const;
    SpellReagentsEntry const*               GetSpellReagents() const;
    SpellScalingEntry const*                GetSpellScaling() const;
    SpellShapeshiftEntry const*             GetSpellShapeshift() const;
    SpellTargetRestrictionsEntry const*     GetSpellTargetRestrictions() const;
    SpellTotemsEntry const*                 GetSpellTotems() const;

    bool HasEffect(SpellEffects effect) const;
    bool HasAura(AuraType aura) const;
    bool HasAreaAuraEffect() const;

    bool IsExplicitDiscovery() const;
    bool IsLootCrafting() const;
    bool IsQuestTame() const;
    bool IsProfessionOrRiding() const;
    bool IsProfession() const;
    bool IsPrimaryProfession() const;
    bool IsPrimaryProfessionFirstRank() const;
    bool IsAbilityLearnedWithProfession() const;
    bool IsAbilityOfSkillType(uint32 skillType) const;

    bool IsAffectingArea() const;
    bool IsTargetingArea() const;
    bool NeedsExplicitUnitTarget() const;
    bool NeedsToBeTriggeredByCaster() const;

    bool IsPassive() const;
    bool IsAutocastable() const;
    bool IsStackableWithRanks() const;
    bool IsPassiveStackableWithRanks() const;
    bool IsMultiSlotAura() const;
    bool IsFlightAura() const;
    bool IsDeathPersistent() const;
    bool IsRequiringDeadTarget() const;
    bool IsAllowingDeadTarget() const;
    bool CanBeUsedInCombat() const;
    bool IsPositive() const;
    bool IsPositiveEffect(uint8 effIndex) const;
    bool IsChanneled() const;
    bool NeedsComboPoints() const;
    bool IsBreakingStealth() const;
    bool IsRangedWeaponSpell() const;
    bool IsAutoRepeatRangedSpell() const;

    bool IsAffectedBySpellMods() const;
    bool IsAffectedBySpellMod(SpellModifier* mod) const;

    bool CanPierceImmuneAura(SpellInfo const* aura) const;
    bool CanDispelAura(SpellInfo const* aura) const;

    bool IsSingleTarget() const;
    bool IsSingleTargetWith(SpellInfo const* spellInfo) const;
    bool IsAuraExclusiveBySpecificWith(SpellInfo const* spellInfo) const;
    bool IsAuraExclusiveBySpecificPerCasterWith(SpellInfo const* spellInfo) const;

    SpellCastResult CheckShapeshift(uint32 form) const;
    SpellCastResult CheckLocation(uint32 map_id, uint32 zone_id, uint32 area_id, Player const* player = NULL, uint8 effMask = MAX_EFFECT_MASK) const;
    SpellCastResult CheckTarget(Unit const* caster, WorldObject const* target, bool implicit = true) const;
    SpellCastResult CheckExplicitTarget(Unit const* caster, WorldObject const* target, Item const* itemTarget = NULL) const;
    bool CheckTargetCreatureType(Unit const* target) const;

    SpellSchoolMask GetSchoolMask() const;
    uint32 GetAllEffectsMechanicMask() const;
    uint32 GetEffectMechanicMask(uint8 effIndex) const;
    uint32 GetSpellMechanicMaskByEffectMask(uint32 effectMask) const;
    Mechanics GetEffectMechanic(uint8 effIndex) const;
    bool HasAnyEffectMechanic() const;
    uint32 GetDispelMask() const;
    static uint32 GetDispelMask(DispelType type);
    uint32 GetExplicitTargetMask() const;

    AuraStateType GetAuraState() const;
    SpellSpecificType GetSpellSpecific() const;

    float GetMinRange(bool positive = false) const;
    float GetMaxRange(bool positive = false, Unit* caster = NULL, Spell* spell = NULL) const;

    int32 GetDuration() const;
    int32 GetMaxDuration() const;

    uint32 CalcCastTime(Unit* caster = NULL, Spell* spell = NULL) const;
    uint32 GetRecoveryTime() const;

    uint32 CalcPowerCost(Unit const* caster, SpellSchoolMask schoolMask) const;

    bool IsRanked() const;
    uint8 GetRank() const;
    SpellInfo const* GetFirstRankSpell() const;
    SpellInfo const* GetLastRankSpell() const;
    SpellInfo const* GetNextRankSpell() const;
    SpellInfo const* GetPrevRankSpell() const;
    SpellInfo const* GetAuraRankForLevel(uint8 level) const;
    bool IsRankOf(SpellInfo const* spellInfo) const;
    bool IsDifferentRankOf(SpellInfo const* spellInfo) const;
    bool IsHighRankOf(SpellInfo const* spellInfo) const;

    // loading helpers
    uint32 _GetExplicitTargetMask() const;
    bool _IsPositiveEffect(uint8 effIndex, bool deep) const;
    bool _IsPositiveSpell() const;
    static bool _IsPositiveTarget(uint32 targetA, uint32 targetB);

    // unloading helpers
    void _UnloadImplicitTargetConditionLists();
};

#endif // _SPELLINFO_H
