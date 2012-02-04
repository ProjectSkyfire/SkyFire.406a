-- -------------------------------------------------------------------------
-- ---------------------------- Custom Commands ----------------------------
-- -------------------------------------------------------------------------
-- Add item WARNING message
DELETE FROM `skyfire_string` WHERE `entry`=821;
INSERT INTO `skyfire_string` (`entry`,`content_default`,`content_loc6`,`content_loc7`) VALUES 
(821,'%s |cff04ac00Received Item %u. |cffd50303WARNING! If you try to add items without reason you will be fired! All items added by you are saved in the server log file.','%s |cff04ac00Received Item %u. |cffd50303WARNING! Si tratas de dar un ITEM sin razón valida y sin comunicarlo serás EXPULSADO DEL STAFF! Todos los ITEMS dados por ti son grabados en un historial.','%s |cff04ac00Received Item %u. |cffd50303WARNING! Si tratas de dar un ITEM sin razón valida y sin comunicarlo serás EXPULSADO DEL STAFF! Todos los ITEMS dados por ti son grabados en un historial.');

-- Automatic annouce when player is banned
DELETE FROM `skyfire_string` WHERE `entry`='11002';
INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11002','|cffff0000[GM]:|r %s was banned by %s for %s. Reason: %s.',NULL,NULL,NULL,NULL,NULL,'|cffff0000[GM]:|r %s ha sido baneado por %s por %s. La Razón es: %s.','|cffff0000[GM]:|r %s ha sido baneado por %s por %s. La Razón es: %s.',NULL);
DELETE FROM `skyfire_string` WHERE `entry`='11003';
INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11003','|cffff0000[GM]:|r %s was banned by %s for eternity. Reason: %s.',NULL,NULL,NULL,NULL,NULL,'|cffff0000[GM]:|r %s ha sido baneado por %s eternamente. La Razón es: %s.','|cffff0000[GM]:|r %s ha sido baneado por %s eternamente. La Razón es: %s.',NULL);

-- Implement `.baninfo playeraccount` & `.banlist playeraccount` command
DELETE FROM `command` WHERE `name` IN ('baninfo playeraccount', 'banlist playeraccount');
INSERT INTO `command` VALUES
('baninfo playeraccount', 3, 'Syntax: .baninfo playeraccount $playerName\r\nWatch full information about a specific ban.'),
('banlist playeraccount', 3, 'Syntax: .banlist playeraccount [$Name]\r\nSearches the banlist for accounts according to a character name pattern.');

-- Moderator Add Command
DELETE FROM `skyfire_string` WHERE `entry`='11005';
INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11005','Item NOT found.',NULL,NULL,NULL,NULL,NULL,'Objeto NO autorizado.','Objeto NO autorizado.',NULL);
DELETE FROM `skyfire_string` WHERE `entry`='11006';
INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11006','Player class not allowed to have this item',NULL,NULL,NULL,NULL,NULL,'La clase del jugador no le permite obtener ese item.','La clase del jugador no le permite obtener ese item.',NULL);
DELETE FROM `skyfire_string` WHERE `entry`='11007';
INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11007','Spell NOT found.',NULL,NULL,NULL,NULL,NULL,'Spell NO autorizado.','Spell NO autorizado.',NULL);
DELETE FROM `skyfire_string` WHERE `entry`='11008';
INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11008','Player class not allowed to learn this spell',NULL,NULL,NULL,NULL,NULL,'La clase del jugador no le permite aprender ese spell.','La clase del jugador no le permite aprender ese spell.',NULL);

DROP TABLE IF EXISTS `moderator_add`;
CREATE TABLE `moderator_add` (
  `type` tinyint(1) unsigned NOT NULL DEFAULT '0', -- 0 = item, 1 = spell
  `id` int(10) unsigned NOT NULL DEFAULT '0', -- item or spell id,
  `class` int(10) unsigned NOT NULL DEFAULT '0', -- restricted character class,
  `description` varchar(30) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='';

-- CLASS_WARRIOR       = 1,
-- CLASS_PALADIN       = 2,
-- CLASS_HUNTER        = 3,
-- CLASS_ROGUE         = 4,
-- CLASS_PRIEST        = 5,
-- CLASS_DEATH_KNIGHT  = 6,
-- CLASS_SHAMAN        = 7,
-- CLASS_MAGE          = 8,
-- CLASS_WARLOCK       = 9,
-- CLASS_DRUID         = 11
