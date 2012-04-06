DROP TABLE IF EXISTS `currency_loot`;
CREATE TABLE `currency_loot` (
  `entry` mediumint(8) NOT NULL,
  `type` smallint(5) NOT NULL,
  `currencyId` int(11) NOT NULL,
  `currencyAmount` int(11) NOT NULL,
  PRIMARY KEY (`entry`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;