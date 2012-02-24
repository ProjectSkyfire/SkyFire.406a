DROP TABLE IF EXISTS `guild_news`;
CREATE TABLE `guild_news` (
  `guildid` int(12) NOT NULL,
  `type` int(10) NOT NULL,
  `date` int(12) NOT NULL,
  `value1` int(10) NOT NULL,
  `value2` int(10) NOT NULL,
  `source_guid` int(12) NOT NULL,
  `flags` int(10) NOT NULL,
  PRIMARY KEY (`guildid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;