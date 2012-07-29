-- WHO THE FUCK set a sacred cleasing quest spell into the sacred cleasing paladin talent? for gods sake.
-- the right id is already on DB
DELETE FROM `spell_script_names` WHERE `spell_id` = 53551;

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_mark_of_nature';
INSERT INTO `spell_script_names` VALUES
(25042,'spell_mark_of_nature');

-- Missing mark of nature and xt002 heart overload
DELETE FROM `spelleffect_dbc` WHERE `Id` IN (200001,200002);
INSERT INTO `spelleffect_dbc` (`Id`, `effect`, `effectAmplitude`, `effectAura`, `effectAuraPeriod`, `effectBasePoints`, `effectUnk_320`, `effectChainAmplitude`, `effectChainTargets`, `effectDieSides`, `effectItemType`, `effectMechanic`, `effectMiscValue`, `effectMiscValueB`, `effectPointsPerCombo`, `effectRadiusIndex`, `effectRadiusMaxIndex`, `effectRealPointsPerLevel`, `effectSpellClassMask_1`, `effectSpellClassMask_2`, `effectSpellClassMask_3`, `effectTriggerSpell`, `implicitTargetA`, `implicitTargetB`, `effectSpellId`, `effectIndex`) VALUES 
(200001, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 62791, 0),
(200002, 6, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 22, 15, 25042, 0);

-- Telluric poultice completion spell wrong spellscript id the right one is already on DB
DELETE FROM `spell_script_names` WHERE `spell_id` = 55797;

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_freya_attuned_to_nature_dose_reduction';
INSERT INTO `spell_script_names` VALUES
(62524,'spell_freya_attuned_to_nature_dose_reduction'), -- 2 stack reduction
(62525,'spell_freya_attuned_to_nature_dose_reduction'), -- 10 stack reduction
(62521,'spell_freya_attuned_to_nature_dose_reduction'); -- 25 stack reduction