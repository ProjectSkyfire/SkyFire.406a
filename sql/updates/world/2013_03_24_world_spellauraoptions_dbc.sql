DROP TABLE IF EXISTS `spellauraoptions_dbc`;

CREATE TABLE `spellauraoptions_dbc` (
  `Id` int(10) unsigned NOT NULL DEFAULT '0',
  `StackAmount` int(10) unsigned NOT NULL DEFAULT '0',
  `procChance` int(10) unsigned NOT NULL DEFAULT '0',
  `procCharges` int(10) unsigned NOT NULL DEFAULT '0',
  `procFlags` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
