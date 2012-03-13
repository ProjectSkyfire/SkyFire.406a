-- Un-needed table cleanup
DROP TABLE IF EXISTS `waypoint_scripts`; -- This is a world db table... not needed in characters
DROP TABLE IF EXISTS `creature_loot_template`; -- Another world db table I missed (thx Tonio)

-- Now we set character version correctly
--
-- Table structure for table `character_version`
--

DROP TABLE IF EXISTS `character_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `character_version` (
  `core_version` varchar(120) NOT NULL DEFAULT 'SkyFireEMU Rebase 4.0.6a' COMMENT 'Core revision dumped at startup.',
  `character_db_version` varchar(120) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Version Notes';
/*!40101 SET character_set_client = @saved_cs_client */;

REPLACE INTO character_version VALUES
('2012_03_11 - fad059fdde','2012_03_13_00');