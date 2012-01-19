DROP TABLE IF EXISTS `spell_dbc`;
CREATE TABLE `spell_dbc` (
  `Id` INT(10) UNSIGNED NOT NULL,
  `Dispel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `Mechanic` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `Attributes` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `AttributesEx` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `AttributesEx2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `AttributesEx3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `AttributesEx4` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `AttributesEx5` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `Stances` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `StancesNot` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `Targets` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `CastingTimeIndex` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
  `AuraInterruptFlags` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `ProcFlags` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `ProcChance` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `ProcCharges` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `MaxLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `BaseLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `SpellLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `DurationIndex` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
  `RangeIndex` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
  `StackAmount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EquippedItemClass` INT(11) NOT NULL DEFAULT '-1',
  `EquippedItemSubClassMask` INT(11) NOT NULL DEFAULT '0',
  `EquippedItemInventoryTypeMask` INT(11) NOT NULL DEFAULT '0',
  `Effect1` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `Effect2` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `Effect3` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectDieSides1` INT(11) NOT NULL DEFAULT '0',
  `EffectDieSides2` INT(11) NOT NULL DEFAULT '0',
  `EffectDieSides3` INT(11) NOT NULL DEFAULT '0',
  `EffectRealPointsPerLevel1` FLOAT NOT NULL DEFAULT '0',
  `EffectRealPointsPerLevel2` FLOAT NOT NULL DEFAULT '0',
  `EffectRealPointsPerLevel3` FLOAT NOT NULL DEFAULT '0',
  `EffectBasePoints1` INT(11) NOT NULL DEFAULT '0',
  `EffectBasePoints2` INT(11) NOT NULL DEFAULT '0',
  `EffectBasePoints3` INT(11) NOT NULL DEFAULT '0',
  `EffectMechanic1` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectMechanic2` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectMechanic3` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectImplicitTargetA1` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectImplicitTargetA2` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectImplicitTargetA3` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectImplicitTargetB1` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectImplicitTargetB2` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectImplicitTargetB3` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectRadiusIndex1` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectRadiusIndex2` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectRadiusIndex3` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EffectApplyAuraName1` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
  `EffectApplyAuraName2` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
  `EffectApplyAuraName3` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
  `EffectAmplitude1` INT(11) NOT NULL DEFAULT '0',
  `EffectAmplitude2` INT(11) NOT NULL DEFAULT '0',
  `EffectAmplitude3` INT(11) NOT NULL DEFAULT '0',
  `EffectMultipleValue1` FLOAT NOT NULL DEFAULT '0',
  `EffectMultipleValue2` FLOAT NOT NULL DEFAULT '0',
  `EffectMultipleValue3` FLOAT NOT NULL DEFAULT '0',
  `EffectMiscValue1` INT(11) NOT NULL DEFAULT '0',
  `EffectMiscValue2` INT(11) NOT NULL DEFAULT '0',
  `EffectMiscValue3` INT(11) NOT NULL DEFAULT '0',
  `EffectMiscValueB1` INT(11) NOT NULL DEFAULT '0',
  `EffectMiscValueB2` INT(11) NOT NULL DEFAULT '0',
  `EffectMiscValueB3` INT(11) NOT NULL DEFAULT '0',
  `EffectTriggerSpell1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectTriggerSpell2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectTriggerSpell3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskA1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskA2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskA3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskB1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskB2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskB3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskC1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskC2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EffectSpellClassMaskC3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `MaxTargetLevel` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `SpellFamilyName` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `SpellFamilyFlags1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `SpellFamilyFlags2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `SpellFamilyFlags3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `MaxAffectedTargets` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `DmgClass` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `PreventionType` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `DmgMultiplier1` FLOAT NOT NULL DEFAULT '0',
  `DmgMultiplier2` FLOAT NOT NULL DEFAULT '0',
  `DmgMultiplier3` FLOAT NOT NULL DEFAULT '0',
  `AreaGroupId` INT(11) NOT NULL DEFAULT '0',
  `SchoolMask` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `Comment` TEXT NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Custom spell.dbc entries';
LOCK TABLES `spell_dbc` WRITE;
INSERT  INTO `spell_dbc`VALUES (62388,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,21,1,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Demonic Circle: Teleport(48020) - casterAuraSpell');
INSERT  INTO `spell_dbc` VALUES (65142,3,22,0,0,0,128,0,0,0,0,0,1,0,0,0,0,0,0,0,21,13,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,255,0,0,0,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,8,'Crypt Fever - SPELL_AURA_LINKED');
INSERT  INTO `spell_dbc` VALUES (34145,0,0,0,0,0,67108864,0,0,0,0,0,1,0,0,101,0,0,80,80,0,1,0,-1,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,29886,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,'Ritual of Souls Rank 1 - Trigger Create Soulwell (29886)');
INSERT  INTO `spell_dbc` VALUES (58888,0,0,0,0,0,67108864,0,0,0,0,0,1,0,0,101,0,0,68,68,0,1,0,-1,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,58889,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,'Ritual of Souls Rank 2 - Trigger Create Soulwell (58889)');
INSERT  INTO `spell_dbc` VALUES (61988,0,0,671089024,268436480,4,269484032,0,0,0,0,0,1,0,0,0,0,0,0,0,25,13,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Divine Shield Exclude Aura - 61988');
INSERT  INTO `spell_dbc` VALUES (200000,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,8,1,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,1,1,1,0,1,'Drain Soul increased damage - serverside spell');
INSERT  INTO `spell_dbc` VALUES (42876,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 9275 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (44987,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11521 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (48803,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 12214 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (68496,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Item_template serverside spell');
INSERT  INTO `spell_dbc` VALUES (72958,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Item_template serverside spell');
INSERT  INTO `spell_dbc` VALUES (32780,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 10040 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (45453,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11587 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (25347,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Item_template serverside spell');
INSERT  INTO `spell_dbc` VALUES (45315,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11566 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (43236,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11288 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (43459,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11332 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (43499,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11250 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (44275,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11432 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (64689,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 13854 and 13862 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (50574,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 12597 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (71356,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2108 spellid0 serverside spell');
INSERT  INTO `spell_dbc` VALUES (71803,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2108 spellid1 serverside spell');
INSERT  INTO `spell_dbc` VALUES (72111,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2136 spellid0 serverside spell');
INSERT  INTO `spell_dbc` VALUES (72125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2136 spellid1 serverside spell');
INSERT  INTO `spell_dbc` VALUES (70816,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2146 spellid0 serverside spell');
INSERT  INTO `spell_dbc` VALUES (72233,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2146 spellid1 serverside spell');
INSERT  INTO `spell_dbc` VALUES (72234,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2146 spellid2 serverside spell');
INSERT  INTO `spell_dbc` VALUES (72235,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Spelldifficulty_dbc id:2146 spellid3 serverside spell');
INSERT  INTO `spell_dbc` VALUES (58428,0,0,671089024,0,0,0,0,0,0,0,0,1,0,0,100,0,0,0,0,18,1,0,-1,0,0,6,0,0,1,0,0,0,0,0,9,0,0,0,0,0,1,0,0,0,0,0,0,0,0,226,0,0,20000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,1,1,1,0,1,'Overkill - aura remove spell');
INSERT  INTO `spell_dbc` VALUES (56817,0,0,384,0,0,0,0,0,0,0,0,1,0,16,101,1,0,67,67,1,1,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,'Rune strike proc');
INSERT  INTO `spell_dbc` VALUES (24899,0,0,400,1024,0,0,2097152,0,144,0,0,1,0,0,101,0,0,0,0,21,1,0,-1,0,0,6,0,0,1,0,0,0,0,0,-1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,137,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'Heart of the Wild Bear Effect');
INSERT  INTO `spell_dbc` VALUES (24900,0,0,400,1024,0,0,2097152,0,1,0,0,1,0,0,101,0,0,0,0,21,1,0,-1,0,0,6,0,0,1,0,0,0,0,0,-1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,166,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'Heart of the Wild Cat Effect');
INSERT  INTO `spell_dbc` VALUES (43503,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11261 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (39613,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 10967 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (34448,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,77,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Serverside spell orb of translocation (gobjid=180911)');
INSERT  INTO `spell_dbc` VALUES (34452,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,77,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Serverside spell orb of translocation (gobjid=180912)');
INSERT  INTO `spell_dbc` VALUES (39616,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 10966 reward serverside spell');
INSERT  INTO `spell_dbc` VALUES (11202,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Item 3776 spellid_1 serverside spell');
INSERT  INTO `spell_dbc` VALUES (25359,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Item 21293 spellid_2 serverside spell');
INSERT  INTO `spell_dbc` VALUES (40145,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11000 RewSpellCast serverside spell');
INSERT  INTO `spell_dbc` VALUES (45767,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 11670 RewSpellCast serverside spell');
INSERT  INTO `spell_dbc` VALUES (71098,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 24451 RewSpellCast serverside spell');
INSERT  INTO `spell_dbc` VALUES (70878,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Creature 40160 creature_addon serverside spell');
INSERT  INTO `spell_dbc` VALUES (38406,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Quest 10721 RewSpellCast serverside spell');
INSERT  INTO `spell_dbc` VALUES (44805,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Aura used in creature_addon - serverside spell');
INSERT  INTO `spell_dbc` VALUES (100000,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,-1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,0,0,0,'Bone Shield cooldown - serverside spell');
UNLOCK TABLES;