UPDATE `creature_template` SET `dynamicflags` = 8 WHERE `entry` IN (49355,49356);

DELETE FROM `creature` WHERE `id` IN (49355,49356);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(346863, 49355, 609, 1, 4, 0, 0, 1331.62, -5760.19, 137.652, 3.11027, 300, 0, 0, 3090, 0, 0, 0, 0, 0),
(346864, 49356, 609, 1, 4, 0, 0, 1321, -5757.45, 137.562, 6.26701, 300, 0, 0, 3090, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (346863,346864);
INSERT INTO `creature_addon` VALUES
(346863, 0, 0, 65544, 1, 0, NULL),
(346864, 0, 0, 65544, 1, 0, NULL);
