-- character guild updates

-- Dumping structure for table characters.guild

DROP TABLE IF EXISTS `guild`;
CREATE TABLE IF NOT EXISTS `guild` (
  `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `name` VARCHAR(24) NOT NULL DEFAULT '',
  `leaderguid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `EmblemStyle` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `EmblemColor` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `BorderStyle` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `BorderColor` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `BackgroundColor` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `info` TEXT NOT NULL,
  `motd` VARCHAR(128) NOT NULL DEFAULT '',
  `createdate` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankMoney` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guildid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='Guild System';

-- Dumping structure for table characters.guild_bank_eventlog

DROP TABLE IF EXISTS `guild_bank_eventlog`;
CREATE TABLE IF NOT EXISTS `guild_bank_eventlog` (
  `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Guild Identificator',
  `LogGuid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Log record identificator - auxiliary column',
  `TabId` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Guild bank TabId',
  `EventType` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Event type',
  `PlayerGuid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `ItemOrMoney` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `ItemStackCount` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
  `DestTabId` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Destination Tab Id',
  `TimeStamp` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Event UNIX time',
  PRIMARY KEY (`guildid`,`LogGuid`,`TabId`),
  KEY `guildid_key` (`guildid`),
  KEY `Idx_PlayerGuid` (`PlayerGuid`),
  KEY `Idx_LogGuid` (`LogGuid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

-- Dumping structure for table characters.guild_bank_item

DROP TABLE IF EXISTS `guild_bank_item`;
CREATE TABLE IF NOT EXISTS `guild_bank_item` (
  `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `TabId` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `SlotId` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `item_guid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guildid`,`TabId`,`SlotId`),
  KEY `guildid_key` (`guildid`),
  KEY `Idx_item_guid` (`item_guid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

-- Dumping structure for table characters.guild_bank_right

DROP TABLE IF EXISTS `guild_bank_right`;
CREATE TABLE IF NOT EXISTS `guild_bank_right` (
  `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `TabId` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `rid` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `gbright` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `SlotPerDay` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guildid`,`TabId`,`rid`),
  KEY `guildid_key` (`guildid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

-- Dumping structure for table characters.guild_bank_tab

DROP TABLE IF EXISTS `guild_bank_tab`;
CREATE TABLE IF NOT EXISTS `guild_bank_tab` (
  `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `TabId` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `TabName` VARCHAR(16) NOT NULL DEFAULT '',
  `TabIcon` VARCHAR(100) NOT NULL DEFAULT '',
  `TabText` VARCHAR(500) DEFAULT NULL,
  PRIMARY KEY (`guildid`,`TabId`),
  KEY `guildid_key` (`guildid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

-- Dumping structure for table characters.guild_eventlog

DROP TABLE IF EXISTS `guild_eventlog`;
CREATE TABLE IF NOT EXISTS `guild_eventlog` (
  `guildid` INT(10) UNSIGNED NOT NULL COMMENT 'Guild Identificator',
  `LogGuid` INT(10) UNSIGNED NOT NULL COMMENT 'Log record identificator - auxiliary column',
  `EventType` TINYINT(3) UNSIGNED NOT NULL COMMENT 'Event type',
  `PlayerGuid1` INT(10) UNSIGNED NOT NULL COMMENT 'Player 1',
  `PlayerGuid2` INT(10) UNSIGNED NOT NULL COMMENT 'Player 2',
  `NewRank` TINYINT(3) UNSIGNED NOT NULL COMMENT 'New rank(in case promotion/demotion)',
  `TimeStamp` INT(10) UNSIGNED NOT NULL COMMENT 'Event UNIX time',
  PRIMARY KEY (`guildid`,`LogGuid`),
  KEY `Idx_PlayerGuid1` (`PlayerGuid1`),
  KEY `Idx_PlayerGuid2` (`PlayerGuid2`),
  KEY `Idx_LogGuid` (`LogGuid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='Guild Eventlog';

-- Dumping structure for table characters.guild_member

DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE IF NOT EXISTS `guild_member` (
  `guildid` INT(10) UNSIGNED NOT NULL COMMENT 'Guild Identificator',
  `guid` INT(10) UNSIGNED NOT NULL,
  `rank` TINYINT(3) UNSIGNED NOT NULL,
  `pnote` VARCHAR(31) NOT NULL DEFAULT '',
  `offnote` VARCHAR(31) NOT NULL DEFAULT '',
  `BankResetTimeMoney` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemMoney` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankResetTimeTab0` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemSlotsTab0` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankResetTimeTab1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemSlotsTab1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankResetTimeTab2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemSlotsTab2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankResetTimeTab3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemSlotsTab3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankResetTimeTab4` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemSlotsTab4` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankResetTimeTab5` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `BankRemSlotsTab5` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  UNIQUE KEY `guid_key` (`guid`),
  KEY `guildid_key` (`guildid`),
  KEY `guildid_rank_key` (`guildid`,`rank`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='Guild System';

-- Dumping structure for table characters.guild_rank

DROP TABLE IF EXISTS `guild_rank`;
CREATE TABLE IF NOT EXISTS `guild_rank` (
  `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `rid` TINYINT(3) UNSIGNED NOT NULL,
  `rname` VARCHAR(20) NOT NULL DEFAULT '',
  `rights` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  `BankMoneyPerDay` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guildid`,`rid`),
  KEY `Idx_rid` (`rid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='Guild System';