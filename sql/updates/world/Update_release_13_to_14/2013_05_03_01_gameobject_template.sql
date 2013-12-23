-- Correct Anvil and Forge in Gilneas.
DELETE FROM `gameobject_template` WHERE `entry`IN (196879,196880);
INSERT INTO `gameobject_template` VALUES 
(196879, 8, 9141, 'Forge', '', '', '', 0, 0, 0.85, 0, 0, 0, 0, 0, 0, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 15595), -- Forge
(196880, 8, 9142, 'Anvil', '', '', '', 0, 0, 1.56, 0, 0, 0, 0, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 15595); -- Anvil

