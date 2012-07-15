DROP TABLE IF EXISTS `character_branchspec`;
ALTER TABLE `characters` ADD `talentTree` varchar(10) NOT NULL DEFAULT '0 0' AFTER `grantableLevels`;