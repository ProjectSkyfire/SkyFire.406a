DROP TABLE IF EXISTS `character_branchspec`;
CREATE TABLE `character_branchspec` (
  `guid` INT(11) UNSIGNED NOT NULL DEFAULT '0',
  `spec` INT(11) UNSIGNED NOT NULL DEFAULT '0',
  `branchSpec` INT(11) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`spec`)
) ENGINE=MYISAM DEFAULT CHARSET=latin1;
