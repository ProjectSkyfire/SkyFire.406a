DROP TABLE IF EXISTS `character_version`;
CREATE TABLE `character_version` (
  `core_version` varchar(120) NOT NULL DEFAULT 'SkyFireEMU Rebase 4.0.6a' COMMENT 'Core revision dumped at startup.',
  `required_2011_12_02_02_characters_version_test` bit(1) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Version Notes';
INSERT INTO `character_version` VALUES ('SkyFireEMU Rebase 4.0.6a', '');
-- New character table version. Please follow the new standards for applying update files.