DROP TABLE IF EXISTS `locales_creature_text`;
CREATE TABLE `locales_creature_text` (
  `entry` INT(10) UNSIGNED NOT NULL,
  `textGroup` TINYINT(3) UNSIGNED NOT NULL,
  `id` INT(10) UNSIGNED NOT NULL,
  `text_loc1` TEXT,
  `text_loc2` TEXT,
  `text_loc3` TEXT,
  `text_loc4` TEXT,
  `text_loc5` TEXT,
  `text_loc6` TEXT,
  `text_loc7` TEXT,
  `text_loc8` TEXT,
  PRIMARY KEY (`entry`,`textGroup`,`id`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8;