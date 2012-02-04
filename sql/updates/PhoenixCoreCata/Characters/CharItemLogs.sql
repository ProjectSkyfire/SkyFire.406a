-- -------------------------------------------------------------------------
-- -------------------------- Character Item Log ---------------------------
-- -------------------------------------------------------------------------

--
-- Table structure for table `character_itemlog`
--

DROP TABLE IF EXISTS `character_itemlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `character_itemlog` (
  `id` int(9) NOT NULL auto_increment,
  `date` timestamp NOT NULL,
  `guid` int(9) NOT NULL default '0',
  `name` varchar(12) NOT NULL,
  `item` int(6) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `character_itemlog`
--

LOCK TABLES `character_inventory` WRITE;
/*!40000 ALTER TABLE `character_itemlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_itemlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `character_itemlog_delete`
--

DROP TABLE IF EXISTS `character_itemlog_delete`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `character_itemlog_delete` (
  `id` int(9) NOT NULL AUTO_INCREMENT,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `guid` int(9) NOT NULL DEFAULT '0',
  `name` varchar(12) NOT NULL,
  `item` int(6) NOT NULL DEFAULT '0',
  `comment` varchar(12) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `character_itemlog_delete`
--

LOCK TABLES `character_inventory` WRITE;
/*!40000 ALTER TABLE `character_itemlog_delete` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_itemlog_delete` ENABLE KEYS */;
UNLOCK TABLES;