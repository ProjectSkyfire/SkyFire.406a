-- Wrong spell for gnomish death ray script, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 13278;

-- Wrong spell for ashbringer script, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 18112;

-- Wrong spell for hunter's scatter shot, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 19503;

-- Wrong spell for warrior's charge, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 34846;

-- Wrong spell for warrior's slam
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_warr_slam';
INSERT INTO `spell_script_names` VALUES
(1464,'spell_warr_slam');

-- Wrong spell for priest's pain and suffering, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 47580;

-- Starfall Script Correction
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_starfall_aoe'; 
INSERT INTO `spell_script_names` VALUES
(50286,'spell_dru_starfall_aoe');

-- Deprecated script
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_berserk'; 

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_warr_vigilance'; 
INSERT INTO `spell_script_names` VALUES
(50725,'spell_warr_vigilance');

-- Juggernaut proc data
DELETE FROM `spell_proc_event` WHERE `entry` IN (64976,65156);
INSERT INTO `spell_proc_event` VALUES
(64976,0,4,1,0,0,0,0,0,0,0),
(65156,0,4,35651584,0,0,0,0,0,0,0);


