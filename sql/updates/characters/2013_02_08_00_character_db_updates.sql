-- Drop unused tables from SkyFire character DB.
DROP TABLE IF EXISTS `instance_encounters`;

ALTER TABLE `characters`
	CHANGE COLUMN `map` `map` SMALLINT(5) NULL DEFAULT NULL AFTER `position_z`,
	CHANGE COLUMN `zone` `zone` SMALLINT(5) NULL DEFAULT NULL AFTER `at_login`,
	CHANGE COLUMN `drunk` `drunk` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `watchedFaction`;	
		