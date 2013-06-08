/* 
* sql\updates\characters\2012_02_24_00_character_guild_xp_for_level.sql 
*/ 
-- Guild xp for level
DROP TABLE IF EXISTS `guild_xp_for_level`;
CREATE TABLE `guild_xp_for_level` (
  `lvl` INT(11) NOT NULL,
  `xp_for_next_level` BIGINT(20) NOT NULL
) ENGINE=INNODB DEFAULT CHARSET=latin1;

LOCK TABLES `guild_xp_for_level` WRITE;

INSERT  INTO `guild_xp_for_level` VALUES (1,16580000);
INSERT  INTO `guild_xp_for_level` VALUES (2,18240000);
INSERT  INTO `guild_xp_for_level` VALUES (3,19900000);
INSERT  INTO `guild_xp_for_level` VALUES (4,21550000);
INSERT  INTO `guild_xp_for_level` VALUES (5,23220000);
INSERT  INTO `guild_xp_for_level` VALUES (6,24880000);
INSERT  INTO `guild_xp_for_level` VALUES (7,26530000);
INSERT  INTO `guild_xp_for_level` VALUES (8,28190000);
INSERT  INTO `guild_xp_for_level` VALUES (9,29850000);
INSERT  INTO `guild_xp_for_level` VALUES (10,31510000);
INSERT  INTO `guild_xp_for_level` VALUES (11,33170000);
INSERT  INTO `guild_xp_for_level` VALUES (12,34820000);
INSERT  INTO `guild_xp_for_level` VALUES (13,36490000);
INSERT  INTO `guild_xp_for_level` VALUES (14,38140000);
INSERT  INTO `guild_xp_for_level` VALUES (15,39800000);
INSERT  INTO `guild_xp_for_level` VALUES (16,41450000);
INSERT  INTO `guild_xp_for_level` VALUES (17,43120000);
INSERT  INTO `guild_xp_for_level` VALUES (18,44780000);
INSERT  INTO `guild_xp_for_level` VALUES (19,46430000);
INSERT  INTO `guild_xp_for_level` VALUES (20,48090000);
INSERT  INTO `guild_xp_for_level` VALUES (21,49750000);
INSERT  INTO `guild_xp_for_level` VALUES (22,51410000);
INSERT  INTO `guild_xp_for_level` VALUES (23,53060000);
INSERT  INTO `guild_xp_for_level` VALUES (24,54730000);

UNLOCK TABLES;
 
 
/* 
* sql\updates\characters\2012_04_08_00_character_lag_reports.sql 
*/ 
ALTER TABLE `lag_reports` ADD `latency` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `lag_reports` ADD `createTime` INT(10) UNSIGNED NOT NULL DEFAULT '0';
 
 
/* 
* sql\updates\characters\2012_04_09_00_character_worldstates.sql 
*/ 
-- update worldstates
DELETE FROM `worldstates` WHERE `entry` IN (31001,31002,31003,31004,33280,55629);
INSERT INTO `worldstates` VALUES ('33280', '0', NULL);
INSERT INTO `worldstates` VALUES ('55629', '0', NULL);
INSERT INTO `worldstates` VALUES ('31001', '0', 'WG war status');
INSERT INTO `worldstates` VALUES ('31002', '0', 'WG clock');
INSERT INTO `worldstates` VALUES ('31003', '0', 'WG Fortress Defender');
INSERT INTO `worldstates` VALUES ('31004', '0', 'WG TEMP Battle Control Faction');
 
 
/* 
* sql\updates\characters\2012_04_12_00_character_warden_action.sql 
*/ 
DROP TABLE IF EXISTS `warden_action`;

CREATE TABLE `warden_action` (
  `wardenId` smallint(5) unsigned NOT NULL,
  `action` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`wardenId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
 
/* 
* sql\updates\characters\2012_04_16_00_misc.sql 
*/ 
DROP TABLE IF EXISTS `character_feed_log`;
DROP TABLE IF EXISTS `cheaters`;
 
 
/* 
* sql\updates\characters\2012_04_21_00_character_pet_cleanup.sql 
*/ 
delete from character_pet where CreatedBySpell != 0;
delete from `character_pet_declinedname` WHERE `id` not in (select character_pet.id from character_pet);
delete from `pet_aura` WHERE `guid` not in (select id from character_pet);
delete from `pet_spell` WHERE `guid` not in (select id from character_pet);
delete from `pet_spell_cooldown` WHERE `guid` not in (select id from character_pet);
delete from `pet_aura` WHERE `guid` not in (select id from character_pet);
 
 
