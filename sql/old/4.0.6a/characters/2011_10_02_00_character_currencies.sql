-- char currencies
DROP TABLE IF EXISTS `character_currency`;
CREATE TABLE IF NOT EXISTS `character_currency` (
  `guid` INT(11) UNSIGNED NOT NULL,
  `currency` SMALLINT(5) UNSIGNED NOT NULL,
  `count` SMALLINT(5) UNSIGNED NOT NULL,
  `thisweek` SMALLINT(5) UNSIGNED NOT NULL,
  PRIMARY KEY (`guid`,`currency`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;
