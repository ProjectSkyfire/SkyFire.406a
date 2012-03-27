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
