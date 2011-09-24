
DROP TABLE IF EXISTS `character_tutorial`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `character_tutorial` (
  `account` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Account Identifier',
  `tut0` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut1` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut2` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut3` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut4` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut5` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut6` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tut7` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`account`)
) ENGINE=INNODB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8 COMMENT='Player System';
/*!40101 SET character_set_client = @saved_cs_client */;

LOCK TABLES `character_tutorial` WRITE;
/*!40000 ALTER TABLE `character_tutorial` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_tutorial` ENABLE KEYS */;
UNLOCK TABLES;




