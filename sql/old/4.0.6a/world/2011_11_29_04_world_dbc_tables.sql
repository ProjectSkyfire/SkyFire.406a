/*
SQLyog Ultimate v9.30 
MySQL - 5.1.41 : Database - skyfire_world
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `spell_dbc` */

DROP TABLE IF EXISTS `spell_dbc`;

CREATE TABLE `spell_dbc` (
  `Id` int(10) NOT NULL DEFAULT '0',
  `Attributes` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx2` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx3` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx4` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx5` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx6` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx7` int(10) unsigned NOT NULL DEFAULT '0',
  `AttributesEx8` int(10) unsigned NOT NULL DEFAULT '0',
  `CastingTimeIndex` int(11) NOT NULL DEFAULT '0',
  `DurationIndex` int(11) NOT NULL DEFAULT '0',
  `PowerType` int(11) NOT NULL DEFAULT '0',
  `RangeIndex` int(11) NOT NULL DEFAULT '0',
  `Speed` float NOT NULL DEFAULT '0',
  `SpellVisualId_1` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellVisualId_2` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellIconId` int(11) NOT NULL DEFAULT '0',
  `ActiveIconId` int(11) NOT NULL DEFAULT '0',
  `SchoolMask` int(11) NOT NULL DEFAULT '0',
  `RuneCostId` int(11) NOT NULL DEFAULT '0',
  `SpellDifficultyId` int(11) NOT NULL DEFAULT '0',
  `SpellScalingId` int(11) NOT NULL DEFAULT '0',
  `SpellAuraOptionsId` int(11) NOT NULL DEFAULT '0',
  `SpellAuraRestrictionsId` int(11) NOT NULL DEFAULT '0',
  `SpellCastingRequirementsId` int(11) NOT NULL DEFAULT '0',
  `SpellCategoriesId` int(11) NOT NULL DEFAULT '0',
  `SpellClassOptionsId` int(11) NOT NULL DEFAULT '0',
  `SpellCooldownsId` int(11) NOT NULL DEFAULT '0',
  `SpellEquippedItemsId` int(11) NOT NULL DEFAULT '0',
  `SpellInterruptsId` int(11) NOT NULL DEFAULT '0',
  `SpellLevelsId` int(11) NOT NULL DEFAULT '0',
  `SpellPowerId` int(11) NOT NULL DEFAULT '0',
  `SpellReagentsId` int(11) NOT NULL DEFAULT '0',
  `SpellShapeshiftId` int(11) NOT NULL DEFAULT '0',
  `SpellTargetRestrictionsId` int(11) NOT NULL DEFAULT '0',
  `SpellTotemsId` int(11) NOT NULL DEFAULT '0',
  `unk` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `spell_dbc` */

insert  into `spell_dbc`(`Id`,`Attributes`,`AttributesEx`,`AttributesEx2`,`AttributesEx3`,`AttributesEx4`,`AttributesEx5`,`AttributesEx6`,`AttributesEx7`,`AttributesEx8`,`CastingTimeIndex`,`DurationIndex`,`PowerType`,`RangeIndex`,`Speed`,`SpellVisualId_1`,`SpellVisualId_2`,`SpellIconId`,`ActiveIconId`,`SchoolMask`,`RuneCostId`,`SpellDifficultyId`,`SpellScalingId`,`SpellAuraOptionsId`,`SpellAuraRestrictionsId`,`SpellCastingRequirementsId`,`SpellCategoriesId`,`SpellClassOptionsId`,`SpellCooldownsId`,`SpellEquippedItemsId`,`SpellInterruptsId`,`SpellLevelsId`,`SpellPowerId`,`SpellReagentsId`,`SpellShapeshiftId`,`SpellTargetRestrictionsId`,`SpellTotemsId`,`unk`) values (62388,0,0,0,0,0,0,0,0,0,1,21,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

/*Table structure for table `spellaurarestrictions_dbc` */

DROP TABLE IF EXISTS `spellaurarestrictions_dbc`;

CREATE TABLE `spellaurarestrictions_dbc` (
  `Id` int(11) NOT NULL DEFAULT '0',
  `CasterAuraState` int(11) NOT NULL DEFAULT '0',
  `TargetAuraState` int(11) NOT NULL DEFAULT '0',
  `CasterAuraStateNot` int(11) NOT NULL DEFAULT '0',
  `TargetAuraStateNot` int(11) NOT NULL DEFAULT '0',
  `casterAuraSpell` int(11) NOT NULL DEFAULT '0',
  `targetAuraSpell` int(11) NOT NULL DEFAULT '0',
  `excludeCasterAuraSpell` int(11) NOT NULL DEFAULT '0',
  `excludeTargetAuraSpell` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `spellaurarestrictions_dbc` */

/*Table structure for table `spellclassoptions_dbc` */

DROP TABLE IF EXISTS `spellclassoptions_dbc`;

CREATE TABLE `spellclassoptions_dbc` (
  `Id` int(10) unsigned NOT NULL DEFAULT '0',
  `modalNextSpell` int(10) unsigned NOT NULL DEFAULT '0',
  `spellClassMask_1` int(10) unsigned NOT NULL DEFAULT '0',
  `spellClassMask_2` int(10) unsigned NOT NULL DEFAULT '0',
  `spellClassMask_3` int(10) unsigned NOT NULL DEFAULT '0',
  `spellClassSet` int(10) unsigned NOT NULL DEFAULT '0',
  `description` text NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `spellclassoptions_dbc` */

/*Table structure for table `spelleffect_dbc` */

DROP TABLE IF EXISTS `spelleffect_dbc`;

CREATE TABLE `spelleffect_dbc` (
  `Id` int(10) unsigned NOT NULL DEFAULT '0',
  `effect` int(10) unsigned NOT NULL DEFAULT '0',
  `effectAmplitude` float NOT NULL DEFAULT '0',
  `effectAura` int(10) unsigned NOT NULL DEFAULT '0',
  `effectAuraPeriod` int(10) unsigned NOT NULL DEFAULT '0',
  `effectBasePoints` int(11) NOT NULL DEFAULT '0',
  `effectUnk_320` float NOT NULL DEFAULT '0',
  `effectChainAmplitude` float NOT NULL DEFAULT '0',
  `effectChainTargets` int(10) unsigned NOT NULL DEFAULT '0',
  `effectDieSides` int(10) unsigned NOT NULL DEFAULT '0',
  `effectItemType` int(10) unsigned NOT NULL DEFAULT '0',
  `effectMechanic` int(10) unsigned NOT NULL DEFAULT '0',
  `effectMiscValue` int(11) NOT NULL DEFAULT '0',
  `effectMiscValueB` int(11) NOT NULL DEFAULT '0',
  `effectPointsPerCombo` float NOT NULL DEFAULT '0',
  `effectRadiusIndex` int(10) unsigned NOT NULL DEFAULT '0',
  `effectRadiusMaxIndex` int(10) unsigned NOT NULL DEFAULT '0',
  `effectRealPointsPerLevel` float NOT NULL DEFAULT '0',
  `effectSpellClassMask_1` int(10) unsigned NOT NULL DEFAULT '0',
  `effectSpellClassMask_2` int(10) unsigned NOT NULL DEFAULT '0',
  `effectSpellClassMask_3` int(10) unsigned NOT NULL DEFAULT '0',
  `effectTriggerSpell` int(11) NOT NULL DEFAULT '0',
  `implicitTargetA` int(10) unsigned NOT NULL DEFAULT '0',
  `implicitTargetB` int(10) unsigned NOT NULL DEFAULT '0',
  `effectSpellId` int(10) unsigned NOT NULL DEFAULT '0',
  `effectIndex` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `spelleffect_dbc` */

insert  into `spelleffect_dbc`(`Id`,`effect`,`effectAmplitude`,`effectAura`,`effectAuraPeriod`,`effectBasePoints`,`effectUnk_320`,`effectChainAmplitude`,`effectChainTargets`,`effectDieSides`,`effectItemType`,`effectMechanic`,`effectMiscValue`,`effectMiscValueB`,`effectPointsPerCombo`,`effectRadiusIndex`,`effectRadiusMaxIndex`,`effectRealPointsPerLevel`,`effectSpellClassMask_1`,`effectSpellClassMask_2`,`effectSpellClassMask_3`,`effectTriggerSpell`,`implicitTargetA`,`implicitTargetB`,`effectSpellId`,`effectIndex`) values (102649,6,0,4,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,62388,0);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
