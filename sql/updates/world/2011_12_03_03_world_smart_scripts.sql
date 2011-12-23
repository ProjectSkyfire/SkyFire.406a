-- Update quest_template from sniff
UPDATE `quest_template` SET `SkillOrClassMask`=-2,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28785  WHERE `entry`=28809;
UPDATE `quest_template` SET `SkillOrClassMask`=-128,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28784  WHERE `entry`=28810;
UPDATE `quest_template` SET `SkillOrClassMask`=-8,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28787  WHERE `entry`=28811;
UPDATE `quest_template` SET `SkillOrClassMask`=-256,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28788  WHERE `entry`=28812;
UPDATE `quest_template` SET `SkillOrClassMask`=-1,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28789  WHERE `entry`=28813;
UPDATE `quest_template` SET `SkillOrClassMask`=-4,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28780 WHERE `entry`=28806;
UPDATE `quest_template` SET `SkillOrClassMask`=-16,`MinLevel`=3,`QuestFlags`=524288,`PrevQuestId`=28786  WHERE `entry`=28808;
 
-- Injured Stormwind Infantry SAI
SET @ENTRY := 50047;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE `creature_template` SET `AIName`='SmartAI', scriptname = '', npcflag = 16777216 WHERE `entry`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,8,0,100,1,93072,0,100,120,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Spell Hit - Set Phase 2"),
(@ENTRY,@SOURCETYPE,2,4,61,0,100,0,0,0,0,0,19,49152,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Spell Hit - Remove Flags"),
(@ENTRY,@SOURCETYPE,3,5,25,0,100,0,0,0,0,0,18,49152,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On AI Init - Set Flags"),
(@ENTRY,@SOURCETYPE,4,9,61,0,100,0,0,0,0,0,91,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Spell Hit - Remove Field Bytes 1"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,90,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On AI Init - Set Field Bytes 1"),
(@ENTRY,@SOURCETYPE,6,7,1,1,100,1,2000,2100,2000,2100,1,0,0,0,0,0,0,12,1,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 2 - Talk"),
(@ENTRY,@SOURCETYPE,7,8,61,1,100,0,0,0,0,0,5,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 2 - Emote OneShot Wave"),
(@ENTRY,@SOURCETYPE,8,10,61,1,100,0,0,0,0,0,33,50047,0,0,0,0,0,12,1,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 2 - Give Kill Credit"),
(@ENTRY,@SOURCETYPE,9,14,61,0,100,0,0,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Spell Hit - Store Target"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 2 - Set Phase 3"),
(@ENTRY,@SOURCETYPE,11,12,60,2,100,1,5000,5100,5000,5100,69,0,0,0,0,0,0,25,50378,0,300,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 3 - Move To Dummy"),
(@ENTRY,@SOURCETYPE,12,0,61,2,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 3 - Set Phase 4"),
(@ENTRY,@SOURCETYPE,13,0,1,4,100,0,16000,17000,16000,17000,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Update Phase 4 - Despawn"),
(@ENTRY,@SOURCETYPE,14,15,61,0,100,0,0,0,0,0,11,93097,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Spell Hit - Cast Renewed Life on self"),
(@ENTRY,@SOURCETYPE,15,0,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Injured Stormwind Infantry - On Spell Hit - Remove spellclick flag");

-- Spellclick
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=@ENTRY;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`cast_flags`) VALUES
(@ENTRY,93072,28812,1,1),(@ENTRY,93072,28813,1,1),(@ENTRY,93072,29082,1,1),
(@ENTRY,93072,28811,1,1),(@ENTRY,93072,28810,1,1),(@ENTRY,93072,28808,1,1),
(@ENTRY,93072,28809,1,1),(@ENTRY,93072,28806,1,1);

-- Texts
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`TEXT`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"Bless you, hero!",12,0,100,0,0,0,"Injured Stormwind Infantry"),
(@ENTRY,0,1,"I live to fight another day!",12,0,100,0,0,0,"Injured Stormwind Infantry"),
(@ENTRY,0,2,"I... I'm ok! I'm ok!",12,0,100,0,0,0,"Injured Stormwind Infantry"),
(@ENTRY,0,3,"I will fear no evil!",12,0,100,0,0,0,"Injured Stormwind Infantry"),
(@ENTRY,0,4,"You're $N! The hero that everyone has been talking about! Thank you!",12,0,100,0,0,0,"Injured Stormwind Infantry"),
(@ENTRY,0,5,"Thank the Light!",12,0,100,0,0,0,"Injured Stormwind Infantry");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceID`=13 AND `SourceEntry`=93072 AND `SourceGroup`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (13,0,93072,18,0,1,50047,1,0,'Get our boys back - target Injured Stormwind Infantry');