-- Rom'ogg Bonecrusher (Blackrock Caverns) Updates

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_romogg_bonecrusher' WHERE `entry`=39665 LIMIT 1;
-- DELETE FROM `smart_scripts` WHERE `entryorguid` = 39665;

-- Angared Earth fixes:
UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14 WHERE `entry`=50376 LIMIT 1;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=50376 LIMIT 1;
UPDATE `creature_template` SET `Health_mod`=0.7, `exp`=3 WHERE `entry`=50376 LIMIT 1;

-- Chains of Woe fixes:
UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14 WHERE `entry`=40447 LIMIT 1;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=40447 LIMIT 1;
UPDATE `creature_template` SET `Health_mod`=0.8, `exp`=3 WHERE `entry`=40447 LIMIT 1;