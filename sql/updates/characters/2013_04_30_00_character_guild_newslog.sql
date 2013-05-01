-- SQL updates for GuildNews
DROP TABLE IF EXISTS `guild_news`;
CREATE TABLE `guild_newslog` (
  `guildid` int(12) NOT NULL,
  `logguid` int(10) NOT NULL,
  `eventtype` int(12) NOT NULL,
  `playerguid` int(10) NOT NULL,
  `flags` int(10) NOT NULL,
  `value` int(12) NOT NULL,
  `timestamp` int(10) NOT NULL,
  PRIMARY KEY (`guildid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES `guild_newslog` WRITE;
/*!40000 ALTER TABLE `guild_newslog` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_newslog` ENABLE KEYS */;
UNLOCK TABLES;
