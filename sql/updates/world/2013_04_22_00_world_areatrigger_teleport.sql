-- Fixed BRL typo, and an unknown.
DELETE FROM `areatrigger_teleport` WHERE `id`IN (1472,3728);
INSERT  INTO `areatrigger_teleport` VALUES (1472,'Blackrock Depths - Searing Gorge Instance',0,-7179.63,-923.667,166.416,1.84097);
INSERT  INTO `areatrigger_teleport` VALUES (3728,'Blackrock lair - Entrance',229,174.74,-474.77,116.84,3.2);
