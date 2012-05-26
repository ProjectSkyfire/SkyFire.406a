DROP TABLE IF EXISTS `character_currency`;
CREATE TABLE `character_currency` (
  `guid` INT(11) UNSIGNED NOT NULL,
  `currency` SMALLINT(5) UNSIGNED NOT NULL,
  `count` INT(11) UNSIGNED NOT NULL,
  `thisweek` INT(11) UNSIGNED NOT NULL,
  PRIMARY KEY (`guid`,`currency`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

SET @CURRENCY_TYPE_HONOR_POINTS = 392;
INSERT INTO character_currency SELECT guid, @CURRENCY_TYPE_HONOR_POINTS, totalHonorPoints, 0 FROM characters WHERE totalHonorPoints > 0;