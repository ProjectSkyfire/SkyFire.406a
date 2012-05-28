-- Pursuit of Justice
UPDATE `spell_proc_event` SET `Cooldown` = 0, `procFlags` = 0, `procEx` = 65536 WHERE `entry` IN (26022,26023);

-- Pursuit of Justice and Blessed Life Cooldown marker
DELETE FROM `spell_dbc` WHERE `Id` = 32733;
INSERT INTO `spell_dbc` (`Id`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `AttributesEx7`, `AttributesEx8`, `CastingTimeIndex`, `DurationIndex`, `PowerType`, `RangeIndex`, `Speed`, `SpellVisualId_1`, `SpellVisualId_2`, `SpellIconId`, `ActiveIconId`, `SchoolMask`, `RuneCostId`, `SpellDifficultyId`, `SpellScalingId`, `SpellAuraOptionsId`, `SpellAuraRestrictionsId`, `SpellCastingRequirementsId`, `SpellCategoriesId`, `SpellClassOptionsId`, `SpellCooldownsId`, `SpellEquippedItemsId`, `SpellInterruptsId`, `SpellLevelsId`, `SpellPowerId`, `SpellReagentsId`, `SpellShapeshiftId`, `SpellTargetRestrictionsId`, `SpellTotemsId`, `unk`) 
VALUES (32733, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `spelleffect_dbc` WHERE `Id` = 200000;
INSERT INTO `spelleffect_dbc` (`Id`, `effect`, `effectAmplitude`, `effectAura`, `effectAuraPeriod`, `effectBasePoints`, `effectUnk_320`, `effectChainAmplitude`, `effectChainTargets`, `effectDieSides`, `effectItemType`, `effectMechanic`, `effectMiscValue`, `effectMiscValueB`, `effectPointsPerCombo`, `effectRadiusIndex`, `effectRadiusMaxIndex`, `effectRealPointsPerLevel`, `effectSpellClassMask_1`, `effectSpellClassMask_2`, `effectSpellClassMask_3`, `effectTriggerSpell`, `implicitTargetA`, `implicitTargetB`, `effectSpellId`, `effectIndex`) 
VALUES (200000, 6, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32733, 0);



