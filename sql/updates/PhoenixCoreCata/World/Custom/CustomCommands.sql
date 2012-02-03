-- -------------------------------------------------------------------------
-- ---------------------------- Custom Commands ----------------------------
-- -------------------------------------------------------------------------
-- Add item WARNING message
DELETE FROM `skyfire_string` WHERE `entry`=821;
INSERT INTO `skyfire_string` (`entry`,`content_default`,`content_loc6`,`content_loc7`) VALUES 
(821,'%s |cff04ac00Received Item %u. |cffd50303WARNING! If you try to add items without reason you will be fired! All items added by you are saved in the server log file.','%s |cff04ac00Received Item %u. |cffd50303WARNING! Si tratas de dar un ITEM sin razón valida y sin comunicarlo serás EXPULSADO DEL STAFF! Todos los ITEMS dados por ti son grabados en un historial.','%s |cff04ac00Received Item %u. |cffd50303WARNING! Si tratas de dar un ITEM sin razón valida y sin comunicarlo serás EXPULSADO DEL STAFF! Todos los ITEMS dados por ti son grabados en un historial.');
