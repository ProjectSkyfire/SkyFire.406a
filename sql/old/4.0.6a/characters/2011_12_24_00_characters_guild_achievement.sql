DROP TABLE IF EXISTS `guild_achievement`;

CREATE TABLE `guild_achievement` (
  `guildid` INT(20) UNSIGNED NOT NULL,
  `achievement` SMALLINT(10) UNSIGNED NOT NULL,
  `date` INT(20) UNSIGNED DEFAULT NULL,
  PRIMARY KEY (`guildid`,`achievement`)
) ENGINE=MYISAM DEFAULT CHARSET=latin1;
