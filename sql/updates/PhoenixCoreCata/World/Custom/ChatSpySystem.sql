-- -------------------------------------------------------------------------
-- ---------------------------- Chat Spy System ----------------------------
-- -------------------------------------------------------------------------
-- chat monitor
DELETE FROM `trinity_string` WHERE `entry` IN (11009, 11010);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
(11009, '|cffffff00[|cffff0000%s|cffffff00]:|r %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11010, '|cFFFFFC00[LFG]|cffffff00[|cffff0000%s|cffffff00]:|r %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);