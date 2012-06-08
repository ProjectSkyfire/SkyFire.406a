DROP TABLE IF EXISTS `player_xp_for_level`;
CREATE TABLE `player_xp_for_level` (
  `lvl` INT(3) UNSIGNED NOT NULL,
  `xp_for_next_level` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`lvl`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8 COMMENT='CTDB Player xp for level';

/*Data for the table `player_xp_for_level` */

LOCK TABLES `player_xp_for_level` WRITE;

INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (1,400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (2,900);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (3,1400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (4,2100);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (5,2800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (6,3600);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (7,4500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (8,5400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (9,6500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (10,7600);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (11,8700);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (12,9800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (13,11000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (14,12300);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (15,13600);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (16,15000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (17,16400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (18,17800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (19,19300);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (20,20800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (21,22400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (22,24000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (23,25500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (24,27200);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (25,28900);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (26,30500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (27,32200);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (28,33900);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (29,36300);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (30,38800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (31,41600);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (32,44600);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (33,48000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (34,51400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (35,55000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (36,58700);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (37,62400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (38,66200);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (39,70200);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (40,74300);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (41,78500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (42,82800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (43,87100);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (44,91600);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (45,96300);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (46,101000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (47,105800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (48,110700);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (49,115700);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (50,120900);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (51,126100);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (52,131500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (53,137000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (54,142500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (55,148200);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (56,154000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (57,159900);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (58,165800);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (59,172000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (60,290000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (61,317000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (62,349000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (63,386000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (64,428000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (65,475000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (66,527000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (67,585000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (68,648000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (69,717000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (70,1219040);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (71,1231680);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (72,1244560);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (73,1257440);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (74,1270320);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (75,1283360);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (76,1296560);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (77,1309920);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (78,1323120);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (79,1336640);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (80,1686300);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (81,2121500);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (82,4004000);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (83,5203400);
INSERT  INTO `player_xp_for_level`(`lvl`,`xp_for_next_level`) VALUES (84,9165100);

UNLOCK TABLES;
