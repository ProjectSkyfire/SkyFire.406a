UPDATE `instance_template` SET `script` = 'instance_halls_of_origination' WHERE `map` = 644;
UPDATE `creature_template` SET `ScriptName`= 'boss_setesh' WHERE `entry`=39732;
UPDATE `creature_template` SET `ScriptName`= 'boss_anraphet' WHERE `entry`=39788;
UPDATE `creature_template` SET `ScriptName`= 'boss_ammunae' WHERE `entry`=39731;
UPDATE `creature_template` SET `ScriptName`= 'boss_ptah' WHERE `entry`=39428;
UPDATE `creature_template` SET `ScriptName`= 'boss_isiset' WHERE `entry`=39587;
UPDATE `creature_template` SET `ScriptName`= 'boss_rajh' WHERE `entry`=39378;
UPDATE `creature_template` SET `ScriptName`= 'boss_flame_warden' WHERE `entry`=39800;
UPDATE `creature_template` SET `ScriptName`= 'boss_air_warden' WHERE `entry`=39803;
UPDATE `creature_template` SET `ScriptName`= 'boss_earth_warden' WHERE `entry`=39801;
UPDATE `creature_template` SET `ScriptName`= 'boss_water_warden' WHERE `entry`=39802;

UPDATE `creature_template` SET `ScriptName`= 'mob_bloodpetal_blossom' WHERE `entry`=40620;
UPDATE `creature_template` SET `ScriptName`= 'mob_seed_pod' WHERE `entry`=51329;
UPDATE `creature_template` SET `ScriptName`= 'mob_spore' WHERE `entry`=40585;
UPDATE `creature_template` SET `ScriptName`= 'mob_solar_wind' WHERE `entry` IN (39634,39635,47922);
UPDATE `creature_template` SET `ScriptName`= 'mob_choas_portal' WHERE `entry`=41055;
UPDATE `creature_template` SET `ScriptName`= 'mob_seed_of_chaos' WHERE `entry`=41126;
UPDATE `creature_template` SET `ScriptName`= 'mob_void_sentinel' WHERE `entry`=41208;
UPDATE `creature_template` SET `ScriptName`= 'mob_void_seeker' WHERE `entry`=41371;

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_isiset_supernova';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(74136,'spell_isiset_supernova');
