DROP TABLE IF EXISTS `character_cp_weekcap`;
CREATE TABLE `character_cp_weekcap` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `source` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `maxWeekRating` smallint(5) unsigned NOT NULL DEFAULT '0',
  `weekCap` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`source`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES `character_cp_weekcap` WRITE;
UNLOCK TABLES;