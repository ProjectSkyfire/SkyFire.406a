DROP TABLE IF EXISTS `guild_achievement_progress`;

CREATE TABLE `guild_achievement_progress` (
	`guildid` INT(10) UNSIGNED NOT NULL,
	`criteria` SMALLINT(5) UNSIGNED NOT NULL,
	`counter` INT(10) UNSIGNED NOT NULL,
	`date` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	PRIMARY KEY (`guildid`, `criteria`)
) ENGINE=MYISAM DEFAULT CHARSET=latin1;