DROP TABLE IF EXISTS `lfg_dungeon_event`;
CREATE TABLE `lfg_dungeon_event` (
  `dungeonId` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Dungeon entry from dbc',
  `eventEntry` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Event Associated to Dungeon Finder',
  PRIMARY KEY  (`dungeonId`,`eventEntry`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8;


INSERT INTO `lfg_dungeon_event` VALUES ('285', '12');
INSERT INTO `lfg_dungeon_event` VALUES ('286', '1');
INSERT INTO `lfg_dungeon_event` VALUES ('287', '24');
INSERT INTO `lfg_dungeon_event` VALUES ('288', '8');
INSERT INTO `lfg_dungeon_event` VALUES ('296', '0');
INSERT INTO `lfg_dungeon_event` VALUES ('297', '0');
INSERT INTO `lfg_dungeon_event` VALUES ('298', '0');
INSERT INTO `lfg_dungeon_event` VALUES ('299', '0');
