-- 52598 Ebon Hold: Chapter II, Skybox aura removal on quest 12779 completion (an end to all things...)
-- Chapter IV applies a new screen effect.
UPDATE `spell_area` SET `quest_end`=12779 WHERE  `spell`=52598 AND `area`=4298 AND `quest_start`=12706;

-- Player's death gate teleport correction, was using orbaz's deathgate one.
UPDATE `gameobject_template` SET `data0` = 53822 WHERE `entry` = 190942;

-- Deathgate teleport floor correction (should teleport to the second one).
UPDATE `spell_target_position` SET `target_position_z` = 426.02 WHERE `id` = 53822;

-- Acherus portals floor correction.
DELETE FROM `gameobject` WHERE `id` IN (193052,193053);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES 
(NULL, 193053, 0, 1, 256, 2321.82, -5662.22, 426.03, 0.686441, 0, 0, 0.336521, 0.941676, 300, 0, 1),
(NULL, 193052, 0, 1, 256, 2345.86, -5695.94, 426.029, 0.501083, 0, 0, 0.247929, 0.968778, 300, 0, 1);
