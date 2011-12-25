-- Fix [Q] Protecting our own (10488)
-- P.D: Merry Xmas!
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceID`=17 AND `SourceEntry`=32578 AND `SourceGroup`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (17,0,32578,11,0,32578,0,0,0,'Gor 'drek's Ointment - should only target Thunderlord Dire Wolf without aura 32578');
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (17,0,32578,19,0,20748,0,0,0,'Gor'drek's Ointment - should only target Thunderlord Dire Wolf without aura 32578');

-- Thunderlord Dire Wolf SAI
SET @ENTRY := 20748;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,32578,0,100,120,33,21142,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Thunderlord Dire Wolf - On Spell Hit - Give Kill Credit"),
(@ENTRY,@SOURCETYPE,1,0,61,0,50,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Thunderlord Dire Wolf - Linked - Attack Player (50% chance)");

-- Remove script from the item
UPDATE item_template SET scriptname = '' WHERE entry = 30175;