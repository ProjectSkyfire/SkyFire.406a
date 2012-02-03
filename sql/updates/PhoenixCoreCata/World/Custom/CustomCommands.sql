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

