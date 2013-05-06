
-- DB Part for Ertan implementation
SET @ENTRY := 43878;
DELETE FROM `creature_text` WHERE `entry` = @ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `probability`, `sound`, `comment`) VALUES
(@ENTRY,  0, 0, 'Filthy beasts! Your presence in Skywall will not be tolerated!', 14, 100, 20876, 'Ertan - Aggro'),
(@ENTRY,  1, 0, 'Ravaged!', 14, 100, 20877, 'Ertan - Slay'),
(@ENTRY,  2, 0, 'AHHHHHHHHH!', 14, 100, 20878, 'Ertan - Death'),
(@ENTRY,  3, 0, '%s pulls her cyclone shield back!', 41, 100, 20878, 'Ertan - Cyclone Shield');

-- 70 Valor Points on heroic kill
DELETE FROM `creature_onkill_reward` WHERE `creature_id`IN (43879);
INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES
(43879, 395, 70);

UPDATE `creature_template` SET `flags_extra` = 128, `scriptname` = 'npc_cyclone_shield' WHERE `entry` = 46007;
DELETE FROM `creature` WHERE id = 46007;

-- Some Template Updates
UPDATE `creature_template` SET `difficulty_entry_1`=43879,`maxlevel`=84,`speed_walk`=1,`speed_run`=1.14286005,`mindmg`=597,`maxdmg`=820,`attackpower`=956,`dmg_multiplier`=7.5,`rangeattacktime`=2500,`minrangedmg`=597,`maxrangedmg`=820,`rangedattackpower`=956,`mingold`=18903,`maxgold`=20006,`mechanic_immune_mask`=613097436,`InhabitType`=1,`dynamicflags`=8,`Armor_mod`=10 WHERE `entry` = 43878;
UPDATE `creature_template` SET `faction_A`= 16, `faction_H`= 16 WHERE `entry`= 43879;
UPDATE `creature_template` SET `scriptname` = 'boss_grand_vizier_ertan' WHERE  `entry` = 43878;
DELETE FROM `creature_template_addon` WHERE entry = 43878;
