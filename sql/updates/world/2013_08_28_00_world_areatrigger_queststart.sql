DROP TABLE IF EXISTS `areatrigger_queststart`;
CREATE TABLE `areatrigger_queststart` (
  `trigger_id` mediumint(8) unsigned NOT NULL DEFAULT '0' COMMENT 'Identifier',
  `quest_id` mediumint(8) unsigned NOT NULL DEFAULT '0' COMMENT 'Quest Identifier',
  PRIMARY KEY (`trigger_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

LOCK TABLES `areatrigger_queststart` WRITE;
UNLOCK TABLES;
