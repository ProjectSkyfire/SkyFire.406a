-- Fix [Q] Protecting our own (10488)
-- P.D: Merry Xmas!
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceID`=17 AND `SourceEntry`=32578 AND `SourceGroup`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (17,0,32578,11,0,32578,0,0,0,"Gor 'drek's Ointment - should only target Thunderlord Dire Wolf without aura 32578");
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (17,0,32578,19,0,20748,0,0,0,"Gor'drek's Ointment - should only target Thunderlord Dire Wolf without aura 32578");

-- Thunderlord Dire Wolf SAI
SET @ENTRY := 20748;
SET @SPELL_GROWL := 5781;
SET @SPELL_OINTMENT := 32578;
SET @SPELL_DETECTION := 37691;
UPDATE `quest_template` SET `ReqSpellCast1`=0 WHERE `entry`=10488;
UPDATE `creature_template` SET `AIName`='SmartAI',`flags_extra`=2 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY,@ENTRY*100+0,@ENTRY*100+1,@ENTRY*100+2);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,0,0,0,0,11,@SPELL_DETECTION,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - Out of Combat - Cast Stealth Detecetion"),
(@ENTRY,0,1,0,1,0,100,1,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - Out of Combat - Set React Passive"),
(@ENTRY,0,2,0,0,0,100,0,11000,11000,15000,20000,11,@SPELL_GROWL,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - In Combat - Cast Threatening Growl"),
(@ENTRY,0,3,0,8,0,100,0,@SPELL_OINTMENT,0,0,0,87,@ENTRY*100+0,@ENTRY*100+1,@ENTRY*100+2,0,0,0,1,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - On Spellhit - Run Random Script"),
(@ENTRY*100+0,0,0,0,0,0,100,0,0,0,0,0,33,21142,0,0,0,0,0,7,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - On Script - Quest Credit"),
(@ENTRY*100+1,0,0,0,0,0,100,0,0,0,0,0,33,21142,0,0,0,0,0,7,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - On Script - Quest Credit"),
(@ENTRY*100+2,0,0,0,0,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Thunderlord Dire Wolf - On Script - Attack Player");


-- Remove script from the item
UPDATE item_template SET scriptname = '' WHERE entry = 30175;