-- The Argent Tournament ... No Prevs ... NextQuestInLine: Mastery Of Melee
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13828 WHERE entry = 13667;
-- The Argent Tournament ... No Prevs ... NextQuestInLine: Mastery Of Melee
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13829 WHERE entry = 13668;

-- ##### Aspirant Level

-- Mastery Of Melee - A - Prev: The Argent Tournament
UPDATE quest_template SET PrevQuestId = 13667, NextQuestId = 0, ExclusiveGroup = -13828, NextQuestInChain = 0 WHERE entry = 13828;
-- Mastery Of Melee - H - Prev: The Argent Tournament
UPDATE quest_template SET PrevQuestId = 13668, NextQuestId = 0, ExclusiveGroup = -13829, NextQuestInChain = 0 WHERE entry = 13829;

-- Mastery Of The Shield-Breaker - A - Prev: The Argent Tournament
UPDATE quest_template SET PrevQuestId = 13667, NextQuestId = 0, ExclusiveGroup = -13828, NextQuestInChain = 0 WHERE entry = 13835;
-- Mastery Of The Shield-Breaker - H - Prev: The Argent Tournament
UPDATE quest_template SET PrevQuestId = 13668, NextQuestId = 0, ExclusiveGroup = -13829, NextQuestInChain = 0 WHERE entry = 13838;

-- Mastery Of The Charge - A - Prev: The Argent Tournament
UPDATE quest_template SET PrevQuestId = 13667, NextQuestId = 0, ExclusiveGroup = -13828, NextQuestInChain = 0 WHERE entry = 13837;
-- Mastery Of The Charge - H - Prev: The Argent Tournament
UPDATE quest_template SET PrevQuestId = 13668, NextQuestId = 0, ExclusiveGroup = -13829, NextQuestInChain = 0 WHERE entry = 13839;

-- Up To The Challenge - A - Prev: Mastery Of Melee AND Shield-Breaker AND Charge ... NextQuestInChain: The Aspirant's Challenge
UPDATE quest_template SET PrevQuestId = 13828, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13679 WHERE entry = 13672;
-- Up To The Challenge - H - Prev: Mastery Of Melee AND Shield-Breaker AND Charge ... NextQuestInChain: The Aspirant's Challenge
UPDATE quest_template SET PrevQuestId = 13829, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13680 WHERE entry = 13678;

-- The Aspirant's Challenge - A - Prev: Up To The Challenge
UPDATE quest_template SET PrevQuestId = 13672, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13679;
-- The Aspirant's Challenge - H - Prev: Up To The Challenge
UPDATE quest_template SET PrevQuestId = 13678, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13680;

-- Mastery Gossip by tREAK
SET @NPC_MoM    =      33973;  -- Jeran Lockwood <Master of Melee>
SET @G_MoM_0    =      10398;  -- Gossip Option
SET @G_MoM_1    = @G_MoM_0+1;  -- 10398

SET @NPC_MoSB   =      33974;  -- Valis Windchaser <Master of the Shield-Breaker>
SET @G_MoSB_0   =      10402;  -- Gossip Option
SET @G_MoSB_1   =@G_MoSB_0+1;  -- 10403

SET @NPC_MoC    =      33972;  -- Rugan Steelbelly <Master of the Charge>
SET @G_MoC_0    =      10400;  -- Gossip Option
SET @G_MoC_1    = @G_MoC_0+1;  -- 10401

UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='',`unit_flags`=`unit_flags`|1 WHERE `entry` IN (@NPC_MoM,@NPC_MoSB,@NPC_MoC);
UPDATE `creature_template` SET `gossip_menu_id`=10398 WHERE `entry`=@NPC_MoM;
UPDATE `creature_template` SET `gossip_menu_id`=10402 WHERE `entry`=@NPC_MoSB;
UPDATE `creature_template` SET `gossip_menu_id`=10400 WHERE `entry`=@NPC_MoC;

-- text_ids from sniff
DELETE FROM `gossip_menu` WHERE `entry` IN (@G_MoM_0,@G_MoM_1,@G_MoSB_0,@G_MoSB_1,@G_MoC_0,@G_MoC_1);
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES
(@G_MoM_0,14431),
(@G_MoM_1,14434),

(@G_MoSB_0,14438),
(@G_MoSB_1,14439),

(@G_MoC_0,14436),
(@G_MoC_1,14437);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (@G_MoM_0,@G_MoM_1,@G_MoSB_0,@G_MoSB_1,@G_MoC_0,@G_MoC_1);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`) VALUES
(@G_MoM_0,0,0,'Tell me more about Defend and Thrust!',1,1,@G_MoM_1,0,0,0,''),
(@G_MoM_0,1,0,'Show me how to train with a Melee Target?',1,1,0,0,0,0,''),
(@G_MoM_1,0,0,'Show me how to train with a Melee Target?',1,1,0,0,0,0,''),

(@G_MoSB_0,0,0,'Tell me more about using the Shield-Breaker.',1,1,@G_MoSB_1,0,0,0,''),
(@G_MoSB_0,1,0,'Show me how to train with a Ranged Target.',1,1,0,0,0,0,''),
(@G_MoSB_1,0,0,'Show me how to train with a Ranged Target.',1,1,0,0,0,0,''),

(@G_MoC_0,0,0,'Tell me more about the Charge!',1,1,@G_MoC_1,0,0,0,''),
(@G_MoC_0,1,0,'Show me how to train with a Charge Target?',1,1,0,0,0,0,''),
(@G_MoC_1,0,0,'Show me how to train with a Charge Target?',1,1,0,0,0,0,'');

DELETE FROM `creature_text` WHERE `entry` IN (@NPC_MoM,@NPC_MoSB,@NPC_MoC);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@NPC_MoM,1,0,'Put up Defense.$B$BThen use Thrust on a Melee Target.',41,0,100,0,0,0,'Jeran Lockwood'),
(@NPC_MoSB,1,0,'Use Shield-Breaker on a Ranged Target.$B$BThen use Shield-Breaker while the target is defenseless.',41,0,100,0,0,0,'Valis Windchaser'),
(@NPC_MoC,1,0,'Use Shield-Breaker on a Charge Target.$B$BFollow up with Charge while the target is vulnerable.',41,0,100,0,0,0,'Rugan Steelbelly');

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (@NPC_MoM,@NPC_MoSB,@NPC_MoC);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@NPC_MoM,0,0,3,62,0,100,0,@G_MoM_0,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Jeran Lockwood - on Gossip select - close Gossip'),
(@NPC_MoM,0,1,2,62,0,100,0,@G_MoM_1,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Jeran Lockwood - on Gossip select - close Gossip'),
(@NPC_MoM,0,2,3,61,0,100,0,0,0,0,0,11,64113,2,0,0,0,0,7,0,0,0,0,0,0,0,'Jeran Lockwood - on Gossip select - give Kill Credit'),
(@NPC_MoM,0,3,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Jeran Lockwood - on Gossip select - Boss Emote to Player'),

(@NPC_MoSB,0,0,3,62,0,100,0,@G_MoSB_0,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Valis Windchaser - on Gossip select - close Gossip'),
(@NPC_MoSB,0,1,2,62,0,100,0,@G_MoSB_1,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Valis Windchaser - on Gossip select - close Gossip'),
(@NPC_MoSB,0,2,3,61,0,100,0,0,0,0,0,11,64115,2,0,0,0,0,7,0,0,0,0,0,0,0,'Valis Windchaser - on Gossip select - give Kill Credit'),
(@NPC_MoSB,0,3,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Valis Windchaser - on Gossip select - Boss Emote to Player'),

(@NPC_MoC,0,0,3,62,0,100,0,@G_MoC_0,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Rugan Steelbelly - on Gossip select - close Gossip'),
(@NPC_MoC,0,1,2,62,0,100,0,@G_MoC_1,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Rugan Steelbelly - on Gossip select - close Gossip'),
(@NPC_MoC,0,2,3,61,0,100,0,0,0,0,0,11,64114,2,0,0,0,0,7,0,0,0,0,0,0,0,'Rugan Steelbelly - on Gossip select - give Kill Credit'),
(@NPC_MoC,0,3,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Rugan Steelbelly - on Gossip select - Boss Emote to Player');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup` IN (@G_MoM_0,@G_MoM_1,@G_MoSB_0,@G_MoSB_1,@G_MoC_0,@G_MoC_1);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,@G_MoM_0,0,0,9,13828,0,0,0,'','show Gossip Option if Player has taken Quest 13828'),
(15,@G_MoM_0,0,0,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
(15,@G_MoM_0,0,1,9,13829,0,0,0,'','show Gossip Option if Player has taken Quest 13829'),
(15,@G_MoM_0,0,1,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
 
(15,@G_MoSB_0,0,0,9,13835,0,0,0,'','show Gossip Option if Player has taken Quest 13835'),
(15,@G_MoSB_0,0,0,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
(15,@G_MoSB_0,0,1,9,13838,0,0,0,'','show Gossip Option if Player has taken Quest 13838'),
(15,@G_MoSB_0,0,1,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
 
(15,@G_MoC_0,0,0,9,13837,0,0,0,'','show Gossip Option if Player has taken Quest 13837'),
(15,@G_MoC_0,0,0,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
(15,@G_MoC_0,0,1,9,13839,0,0,0,'','show Gossip Option if Player has taken Quest 13839'),
(15,@G_MoC_0,0,1,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
 
(15,@G_MoM_1,0,0,9,13828,0,0,0,'','show Gossip Option if Player has rewarded Quest 13828'),
(15,@G_MoM_1,0,0,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
(15,@G_MoM_1,0,1,9,13829,0,0,0,'','show Gossip Option if Player has rewarded Quest 13829'),
(15,@G_MoM_1,0,1,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
 
(15,@G_MoSB_1,0,0,9,13835,0,0,0,'','show Gossip Option if Player has rewarded Quest 13835'),
(15,@G_MoSB_1,0,0,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
(15,@G_MoSB_1,0,1,9,13838,0,0,0,'','show Gossip Option if Player has rewarded Quest 13838'),
(15,@G_MoSB_1,0,1,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
 
(15,@G_MoC_1,0,0,9,13837,0,0,0,'','show Gossip Option if Player has rewarded Quest 13837'),
(15,@G_MoC_1,0,0,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle'),
(15,@G_MoC_1,0,1,9,13839,0,0,0,'','show Gossip Option if Player has rewarded Quest 13839'),
(15,@G_MoC_1,0,1,1,63034,0,0,0,'','show Gossip Option if Player has Aura: Ride Vehicle');


-- ## Dailys
-- Req: Up To The Challenge active and not rewarded
DELETE FROM conditions WHERE SourceTypeOrReferenceId = -13672; 
INSERT INTO conditions VALUES
(-13672,0,0,0,9,13672,0,0,0,'',''),
(-13672,0,0,0,14,13679,0,0,0,'',''),
(-13672,0,0,1,9,13678,0,0,0,'',''),
(-13672,0,0,1,14,13680,0,0,0,'','');

-- Learning the Reins - A 
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13625;
DELETE FROM conditions WHERE SourceEntry = 13625 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13625,0,-13672,0,0,0,0,'',''),
(19,0,13625,0,-13672,0,0,0,0,'','');
-- Learning the Reins - H
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13677;
DELETE FROM conditions WHERE SourceEntry = 13677 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13677,0,-13672,0,0,0,0,'',''),
(19,0,13677,0,-13672,0,0,0,0,'','');

-- Training In The Field - A
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13671;
DELETE FROM conditions WHERE SourceEntry = 13671 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13671,0,-13672,0,0,0,0,'',''),
(19,0,13671,0,-13672,0,0,0,0,'','');
-- Training In The Field - H
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13676;
DELETE FROM conditions WHERE SourceEntry = 13676 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13676,0,-13672,0,0,0,0,'',''),
(19,0,13676,0,-13672,0,0,0,0,'','');

-- A Worthy Weapon - A
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13669, NextQuestInChain = 0 WHERE entry = 13669;
DELETE FROM conditions WHERE SourceEntry = 13669 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13669,0,-13672,0,0,0,0,'',''),
(19,0,13669,0,-13672,0,0,0,0,'','');
-- A Worthy Weapon - H
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13674, NextQuestInChain = 0 WHERE entry = 13674;
DELETE FROM conditions WHERE SourceEntry = 13674 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13674,0,-13672,0,0,0,0,'',''),
(19,0,13674,0,-13672,0,0,0,0,'','');

-- A Blade Fit For A Champion - A
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13669, NextQuestInChain = 0 WHERE entry = 13666;
DELETE FROM conditions WHERE SourceEntry = 13666 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13666,0,-13672,0,0,0,0,'',''),
(19,0,13666,0,-13672,0,0,0,0,'','');
-- A Blade Fit For A Champion - H
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13674, NextQuestInChain = 0 WHERE entry = 13673;
DELETE FROM conditions WHERE SourceEntry = 13673 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13673,0,-13672,0,0,0,0,'',''),
(19,0,13673,0,-13672,0,0,0,0,'','');

-- The Edge Of Winter - A
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13669, NextQuestInChain = 0 WHERE entry = 13670;
DELETE FROM conditions WHERE SourceEntry = 13670 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13670,0,-13672,0,0,0,0,'',''),
(19,0,13670,0,-13672,0,0,0,0,'','');
-- The Edge Of Winter - H
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13674, NextQuestInChain = 0 WHERE entry = 13675;
DELETE FROM conditions WHERE SourceEntry = 13675 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13675,0,-13672,0,0,0,0,'',''),
(19,0,13675,0,-13672,0,0,0,0,'','');

-- Questpooling -- not needed
/*
DELETE FROM pool_template WHERE entry IN (13674,13669);
INSERT INTO pool_template VALUES
(13669,1,'Tournament - Aspirant - Weapon Quest'),
(13674,1,'Tournament - Aspirant - Weapon Quest');

DELETE FROM pool_quest WHERE pool_entry IN (13674,13669);
INSERT INTO pool_quest VALUES 
(13669,13669,'Tournament - Aspirant - Weapon Quest - A - A Worthy Weapon'),
(13666,13669,'Tournament - Aspirant - Weapon Quest - A - A Blade Fit For A Champion'),
(13670,13669,'Tournament - Aspirant - Weapon Quest - A - The Edge Of Winter'),
(13674,13674,'Tournament - Aspirant - Weapon Quest - H - A Worthy Weapon'),
(13673,13674,'Tournament - Aspirant - Weapon Quest - H - A Blade Fit For A Champion'),
(13675,13674,'Tournament - Aspirant - Weapon Quest - H - The Edge Of Winter');
*/

-- A Valiant of ... Prev: The Aspirant's Challenge
-- A Valiant Of Darnassus
UPDATE quest_template SET PrevQuestId = 13679, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13689;
-- A Valiant Of Gnomeregan
UPDATE quest_template SET PrevQuestId = 13679, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13688;
-- A Valiant Of Ironforge
UPDATE quest_template SET PrevQuestId = 13679, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13685;
-- A Valiant Of Stormwind
UPDATE quest_template SET PrevQuestId = 13679, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13684;
-- A Valiant Of The Exodar
UPDATE quest_template SET PrevQuestId = 13679, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13690;

-- A Valiant Of Orgrimmar
UPDATE quest_template SET PrevQuestId = 13680, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13691;
-- A Valiant Of Sen'jin
UPDATE quest_template SET PrevQuestId = 13680, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13693;
-- A Valiant Of Silvermoon
UPDATE quest_template SET PrevQuestId = 13680, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13696;
-- A Valiant Of Thunder Bluff
UPDATE quest_template SET PrevQuestId = 13680, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13694;
-- A Valiant Of Undercity
UPDATE quest_template SET PrevQuestId = 13680, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13695;

-- ##### Valiant Level

-- The Valiant's Charge ... Prev: A Valiant Of ... OR Valiant Of
-- The Valiant's Charge - Sen'jin ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13727, RequiredRaces = 690 WHERE entry = 13719;
UPDATE quest_template SET PrevQuestId = 13719, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13727;
-- The Valiant's Charge - Thunder Bluff ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13728, RequiredRaces = 690 WHERE entry = 13720;
UPDATE quest_template SET PrevQuestId = 13720, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13728;
-- The Valiant's Charge - Undercity ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13729, RequiredRaces = 690 WHERE entry = 13721;
UPDATE quest_template SET PrevQuestId = 13721, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13729;
-- The Valiant's Charge - Silvermoon City ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13731, RequiredRaces = 690 WHERE entry = 13722;
UPDATE quest_template SET PrevQuestId = 13722, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13731;
-- The Valiant's Charge - Orgrimmar ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13726, RequiredRaces = 690 WHERE entry = 13697;
UPDATE quest_template SET PrevQuestId = 13697, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13726;
-- The Valiant's Charge - Stormwind ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13699, RequiredRaces = 1101 WHERE entry = 13718;
UPDATE quest_template SET PrevQuestId = 13718, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13699;
-- The Valiant's Charge - Gnomeregan ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13723, RequiredRaces = 1101 WHERE entry = 13715;
UPDATE quest_template SET PrevQuestId = 13715, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13723;
-- The Valiant's Charge - The Exodar ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13724, RequiredRaces = 1101 WHERE entry = 13716;
UPDATE quest_template SET PrevQuestId = 13716, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13724;
-- The Valiant's Charge - Darnassus ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13725, RequiredRaces = 1101 WHERE entry = 13717;
UPDATE quest_template SET PrevQuestId = 13717, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13725;
-- The Valiant's Charge - Ironforge ... NextQuestInLine: The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13713, RequiredRaces = 1101 WHERE entry = 13714;
UPDATE quest_template SET PrevQuestId = 13714, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13713;

Delete from conditions where SourceEntry in (13719,13720,13721,13722,13697,13718,13715,13716,13717,13714)
AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
-- Sen'jin
(20,0,13719,0,8,13693,0,0,0,'',''),
(19,0,13719,0,8,13693,0,0,0,'',''),
(20,0,13719,1,8,13708,0,0,0,'',''),
(19,0,13719,1,8,13708,0,0,0,'',''),
-- Thunderbluff
(20,0,13720,0,8,13694,0,0,0,'',''),
(19,0,13720,0,8,13694,0,0,0,'',''),
(20,0,13720,1,8,13709,0,0,0,'',''),
(19,0,13720,1,8,13709,0,0,0,'',''),
-- Undercity
(20,0,13721,0,8,13695,0,0,0,'',''),
(19,0,13721,0,8,13695,0,0,0,'',''),
(20,0,13721,1,8,13710,0,0,0,'',''),
(19,0,13721,1,8,13710,0,0,0,'',''),
-- Silvermoon
(20,0,13722,0,8,13696,0,0,0,'',''),
(19,0,13722,0,8,13696,0,0,0,'',''),
(20,0,13722,1,8,13711,0,0,0,'',''),
(19,0,13722,1,8,13711,0,0,0,'',''),
-- Orgrimmar
(20,0,13697,0,8,13691,0,0,0,'',''),
(19,0,13697,0,8,13691,0,0,0,'',''),
(20,0,13697,1,8,13707,0,0,0,'',''),
(19,0,13697,1,8,13707,0,0,0,'',''),

-- Stormwind
(20,0,13718,0,8,13684,0,0,0,'',''),
(19,0,13718,0,8,13684,0,0,0,'',''),
(20,0,13718,1,8,13593,0,0,0,'',''),
(19,0,13718,1,8,13593,0,0,0,'',''),
-- Gnomeregan
(20,0,13715,0,8,13688,0,0,0,'',''),
(19,0,13715,0,8,13688,0,0,0,'',''),
(20,0,13715,1,8,13704,0,0,0,'',''),
(19,0,13715,1,8,13704,0,0,0,'',''),
-- The Exodar
(20,0,13716,0,8,13690,0,0,0,'',''),
(19,0,13716,0,8,13690,0,0,0,'',''),
(20,0,13716,1,8,13705,0,0,0,'',''),
(19,0,13716,1,8,13705,0,0,0,'',''),
-- Darnassus
(20,0,13717,0,8,13689,0,0,0,'',''),
(19,0,13717,0,8,13689,0,0,0,'',''),
(20,0,13717,1,8,13706,0,0,0,'',''),
(19,0,13717,1,8,13706,0,0,0,'',''),
-- Ironforge
(20,0,13714,0,8,13685,0,0,0,'',''),
(19,0,13714,0,8,13685,0,0,0,'',''),
(20,0,13714,1,8,13703,0,0,0,'',''),
(19,0,13714,1,8,13703,0,0,0,'','');

-- Daily:
-- Req: The Valiant's Charge and not The Valiant's Challenge
DELETE FROM conditions WHERE SourceTypeOrReferenceId in (-13719,-13720,-13721,-13722,-13697,-13718,-13715,-13716,-13717,-13714);
INSERT INTO conditions VALUES
(-13719,0,0,0,9,13719,0,0,0,'',''),
(-13719,0,0,0,14,13727,0,0,0,'',''),
(-13720,0,0,1,9,13720,0,0,0,'',''),
(-13720,0,0,1,14,13728,0,0,0,'',''),
(-13721,0,0,2,9,13721,0,0,0,'',''),
(-13721,0,0,2,14,13729,0,0,0,'',''),
(-13722,0,0,3,9,13722,0,0,0,'',''),
(-13722,0,0,3,14,13731,0,0,0,'',''),
(-13697,0,0,4,9,13697,0,0,0,'',''),
(-13697,0,0,4,14,13726,0,0,0,'',''),
(-13718,0,0,5,9,13718,0,0,0,'',''),
(-13718,0,0,5,14,13699,0,0,0,'',''),
(-13715,0,0,6,9,13715,0,0,0,'',''),
(-13715,0,0,6,14,13723,0,0,0,'',''),
(-13716,0,0,7,9,13716,0,0,0,'',''),
(-13716,0,0,7,14,13724,0,0,0,'',''),
(-13717,0,0,8,9,13717,0,0,0,'',''),
(-13717,0,0,8,14,13725,0,0,0,'',''),
(-13714,0,0,9,9,13714,0,0,0,'',''),
(-13714,0,0,9,14,13713,0,0,0,'','');

-- A Blade Fit For A Champion - Senjin
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13768;
DELETE FROM conditions WHERE SourceEntry = 13768 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13768,0,-13719,0,0,0,0,'',''),
(19,0,13768,0,-13719,0,0,0,0,'','');

-- A Blade Fit For A Champion - Thunder Bluff
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13773;
DELETE FROM conditions WHERE SourceEntry = 13773 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13773,0,-13720,0,0,0,0,'',''),
(19,0,13773,0,-13720,0,0,0,0,'','');

-- A Blade Fit For A Champion - Undercity
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13778;
DELETE FROM conditions WHERE SourceEntry = 13778 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13778,0,-13721,0,0,0,0,'',''),
(19,0,13778,0,-13721,0,0,0,0,'','');

-- A Blade Fit For A Champion - Silvermoon City
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13783;
DELETE FROM conditions WHERE SourceEntry = 13783 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13783,0,-13722,0,0,0,0,'',''),
(19,0,13783,0,-13722,0,0,0,0,'','');

-- A Blade Fit For A Champion - Orgrimmar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13762;
DELETE FROM conditions WHERE SourceEntry = 13762 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13762,0,-13697,0,0,0,0,'',''),
(19,0,13762,0,-13697,0,0,0,0,'','');

-- A Blade Fit For A Champion - Stormwind
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13603;
DELETE FROM conditions WHERE SourceEntry = 13603 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13603,0,-13718,0,0,0,0,'',''),
(19,0,13603,0,-13718,0,0,0,0,'','');

-- A Blade Fit For A Champion - Gnomeregan
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13746;
DELETE FROM conditions WHERE SourceEntry = 13746 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13746,0,-13715,0,0,0,0,'',''),
(19,0,13746,0,-13715,0,0,0,0,'','');

-- A Blade Fit For A Champion - The Exodar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13752;
DELETE FROM conditions WHERE SourceEntry = 13752 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13752,0,-13716,0,0,0,0,'',''),
(19,0,13752,0,-13716,0,0,0,0,'','');

-- A Blade Fit For A Champion - Darnassus
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13757;
DELETE FROM conditions WHERE SourceEntry = 13757 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13757,0,-13717,0,0,0,0,'',''),
(19,0,13757,0,-13717,0,0,0,0,'','');

-- A Blade Fit For A Champion - Ironforge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13741;
DELETE FROM conditions WHERE SourceEntry = 13741 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13741,0,-13714,0,0,0,0,'',''),
(19,0,13741,0,-13714,0,0,0,0,'','');

-- A Worthy Weapon - Senjin
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13769;
DELETE FROM conditions WHERE SourceEntry = 13769 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13769,0,-13719,0,0,0,0,'',''),
(19,0,13769,0,-13719,0,0,0,0,'','');

-- A Worthy Weapon - Thunder Bluff
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13774;
DELETE FROM conditions WHERE SourceEntry = 13774 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13774,0,-13720,0,0,0,0,'',''),
(19,0,13774,0,-13720,0,0,0,0,'','');

-- A Worthy Weapon - Undercity
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13779;
DELETE FROM conditions WHERE SourceEntry = 13779 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13779,0,-13721,0,0,0,0,'',''),
(19,0,13779,0,-13721,0,0,0,0,'','');

-- A Worthy Weapon - Silvermoon City
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13784;
DELETE FROM conditions WHERE SourceEntry = 13784 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13784,0,-13722,0,0,0,0,'',''),
(19,0,13784,0,-13722,0,0,0,0,'','');

-- A Worthy Weapon - Orgrimmar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13763;
DELETE FROM conditions WHERE SourceEntry = 13763 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13763,0,-13697,0,0,0,0,'',''),
(19,0,13763,0,-13697,0,0,0,0,'','');

-- A Worthy Weapon - Stormwind
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13600;
DELETE FROM conditions WHERE SourceEntry = 13600 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13600,0,-13718,0,0,0,0,'',''),
(19,0,13600,0,-13718,0,0,0,0,'','');

-- A Worthy Weapon - Gnomeregan
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13747;
DELETE FROM conditions WHERE SourceEntry = 13747 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13747,0,-13715,0,0,0,0,'',''),
(19,0,13747,0,-13715,0,0,0,0,'','');

-- A Worthy Weapon - The Exodar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13753;
DELETE FROM conditions WHERE SourceEntry = 13753 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13753,0,-13716,0,0,0,0,'',''),
(19,0,13753,0,-13716,0,0,0,0,'','');

-- A Worthy Weapon - Darnassus
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13758;
DELETE FROM conditions WHERE SourceEntry = 13758 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13758,0,-13717,0,0,0,0,'',''),
(19,0,13758,0,-13717,0,0,0,0,'','');

-- A Worthy Weapon - Ironforge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13742;
DELETE FROM conditions WHERE SourceEntry = 13742 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13742,0,-13714,0,0,0,0,'',''),
(19,0,13742,0,-13714,0,0,0,0,'','');

-- The Edge Of Winter - Senjin
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13770;
DELETE FROM conditions WHERE SourceEntry = 13770 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13770,0,-13719,0,0,0,0,'',''),
(19,0,13770,0,-13719,0,0,0,0,'','');

-- The Edge Of Winter - Thunder Bluff
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13775;
DELETE FROM conditions WHERE SourceEntry = 13775 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13775,0,-13720,0,0,0,0,'',''),
(19,0,13775,0,-13720,0,0,0,0,'','');

-- The Edge Of Winter - Undercity
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13780;
DELETE FROM conditions WHERE SourceEntry = 13780 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13780,0,-13721,0,0,0,0,'',''),
(19,0,13780,0,-13721,0,0,0,0,'','');

-- The Edge Of Winter - Silvermoon City
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13785;
DELETE FROM conditions WHERE SourceEntry = 13785 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13785,0,-13722,0,0,0,0,'',''),
(19,0,13785,0,-13722,0,0,0,0,'','');

-- The Edge Of Winter - Orgrimmar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13764;
DELETE FROM conditions WHERE SourceEntry = 13764 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13764,0,-13697,0,0,0,0,'',''),
(19,0,13764,0,-13697,0,0,0,0,'','');

-- The Edge Of Winter - Stormwind
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13616;
DELETE FROM conditions WHERE SourceEntry = 13616 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13616,0,-13718,0,0,0,0,'',''),
(19,0,13616,0,-13718,0,0,0,0,'','');

-- The Edge Of Winter - Gnomeregan
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13748;
DELETE FROM conditions WHERE SourceEntry = 13748 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13748,0,-13715,0,0,0,0,'',''),
(19,0,13748,0,-13715,0,0,0,0,'','');

-- The Edge Of Winter - The Exodar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13754;
DELETE FROM conditions WHERE SourceEntry = 13754 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13754,0,-13716,0,0,0,0,'',''),
(19,0,13754,0,-13716,0,0,0,0,'','');

-- The Edge Of Winter - Darnassus
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13759;
DELETE FROM conditions WHERE SourceEntry = 13759 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13759,0,-13717,0,0,0,0,'',''),
(19,0,13759,0,-13717,0,0,0,0,'','');

-- The Edge Of Winter - Ironforge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13768, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13743;
DELETE FROM conditions WHERE SourceEntry = 13743 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13743,0,-13714,0,0,0,0,'',''),
(19,0,13743,0,-13714,0,0,0,0,'','');

-- A Valiant's Field Training - Senjin
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13771;
DELETE FROM conditions WHERE SourceEntry = 13771 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13771,0,-13719,0,0,0,0,'',''),
(19,0,13771,0,-13719,0,0,0,0,'','');
-- A Valiant's Field Training - Thunder Bluff
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13776;
DELETE FROM conditions WHERE SourceEntry = 13776 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13776,0,-13720,0,0,0,0,'',''),
(19,0,13776,0,-13720,0,0,0,0,'','');
-- A Valiant's Field Training - Undercity
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13781;
DELETE FROM conditions WHERE SourceEntry = 13781 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13781,0,-13721,0,0,0,0,'',''),
(19,0,13781,0,-13721,0,0,0,0,'','');
-- A Valiant's Field Training - Silvermoon City
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13786;
DELETE FROM conditions WHERE SourceEntry = 13786 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13786,0,-13722,0,0,0,0,'',''),
(19,0,13786,0,-13722,0,0,0,0,'','');
-- A Valiant's Field Training - Orgrimmar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13765;
DELETE FROM conditions WHERE SourceEntry = 13765 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13765,0,-13697,0,0,0,0,'',''),
(19,0,13765,0,-13697,0,0,0,0,'','');
-- A Valiant's Field Training - Stormwind
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13592;
DELETE FROM conditions WHERE SourceEntry = 13592 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13592,0,-13718,0,0,0,0,'',''),
(19,0,13592,0,-13718,0,0,0,0,'','');
-- A Valiant's Field Training - Gnomeregan
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13749;
DELETE FROM conditions WHERE SourceEntry = 13749 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13749,0,-13715,0,0,0,0,'',''),
(19,0,13749,0,-13715,0,0,0,0,'','');
-- A Valiant's Field Training - The Exodar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13755;
DELETE FROM conditions WHERE SourceEntry = 13755 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13755,0,-13716,0,0,0,0,'',''),
(19,0,13755,0,-13716,0,0,0,0,'','');
-- A Valiant's Field Training - Darnassus
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13760;
DELETE FROM conditions WHERE SourceEntry = 13760 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13760,0,-13717,0,0,0,0,'',''),
(19,0,13760,0,-13717,0,0,0,0,'','');
-- A Valiant's Field Training - Ironforge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13771, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13744;
DELETE FROM conditions WHERE SourceEntry = 13744 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13744,0,-13714,0,0,0,0,'',''),
(19,0,13744,0,-13714,0,0,0,0,'','');

-- At Enemy's Gates - Senjin
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13857;
DELETE FROM conditions WHERE SourceEntry = 13857 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13857,0,-13719,0,0,0,0,'',''),
(19,0,13857,0,-13719,0,0,0,0,'','');
-- At Enemy's Gates - Thunder Bluff
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13858;
DELETE FROM conditions WHERE SourceEntry = 13858 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13858,0,-13720,0,0,0,0,'',''),
(19,0,13858,0,-13720,0,0,0,0,'','');
-- At Enemy's Gates - Silvermoon City
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13859;
DELETE FROM conditions WHERE SourceEntry = 13859 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13859,0,-13722,0,0,0,0,'',''),
(19,0,13859,0,-13722,0,0,0,0,'','');
-- At Enemy's Gates - Undercity 
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13860;
DELETE FROM conditions WHERE SourceEntry = 13860 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13860,0,-13721,0,0,0,0,'',''),
(19,0,13860,0,-13721,0,0,0,0,'','');
-- At Enemy's Gates - Orgrimmar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13856;
DELETE FROM conditions WHERE SourceEntry = 13856 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13856,0,-13697,0,0,0,0,'',''),
(19,0,13856,0,-13697,0,0,0,0,'','');
-- At Enemy's Gates - Stormwind
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13847;
DELETE FROM conditions WHERE SourceEntry = 13847 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13847,0,-13718,0,0,0,0,'',''),
(19,0,13847,0,-13718,0,0,0,0,'','');
-- At Enemy's Gates - Gnomeregan
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13852;
DELETE FROM conditions WHERE SourceEntry = 13852 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13852,0,-13715,0,0,0,0,'',''),
(19,0,13852,0,-13715,0,0,0,0,'','');
-- At Enemy's Gates - The Exodar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13854;
DELETE FROM conditions WHERE SourceEntry = 13854 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13854,0,-13716,0,0,0,0,'',''),
(19,0,13854,0,-13716,0,0,0,0,'','');
-- At Enemy's Gates - Darnassus
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13855;
DELETE FROM conditions WHERE SourceEntry = 13855 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13855,0,-13717,0,0,0,0,'',''),
(19,0,13855,0,-13717,0,0,0,0,'','');
-- At Enemy's Gates - Ironforge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13857, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13851;
DELETE FROM conditions WHERE SourceEntry = 13851 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13851,0,-13714,0,0,0,0,'',''),
(19,0,13851,0,-13714,0,0,0,0,'','');

-- The Grand Melee
-- The Grand Melee - Senjin
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13772;
DELETE FROM conditions WHERE SourceEntry = 13772 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13772,0,-13719,0,0,0,0,'',''),
(19,0,13772,0,-13719,0,0,0,0,'','');
-- The Grand Melee - Thunder Bluff
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13777;
DELETE FROM conditions WHERE SourceEntry = 13777 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13777,0,-13720,0,0,0,0,'',''),
(19,0,13777,0,-13720,0,0,0,0,'','');
-- The Grand Melee - Undercity
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13782;
DELETE FROM conditions WHERE SourceEntry = 13782 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13782,0,-13721,0,0,0,0,'',''),
(19,0,13782,0,-13721,0,0,0,0,'','');
-- The Grand Melee - Silvermoon City
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13787;
DELETE FROM conditions WHERE SourceEntry = 13787 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13787,0,-13722,0,0,0,0,'',''),
(19,0,13787,0,-13722,0,0,0,0,'','');
-- The Grand Melee - Orgrimmar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 690 WHERE entry = 13767;
DELETE FROM conditions WHERE SourceEntry = 13767 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13767,0,-13697,0,0,0,0,'',''),
(19,0,13767,0,-13697,0,0,0,0,'','');
-- The Grand Melee - Stormwind
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13665;
DELETE FROM conditions WHERE SourceEntry = 13665 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13665,0,-13718,0,0,0,0,'',''),
(19,0,13665,0,-13718,0,0,0,0,'','');
-- The Grand Melee - Gnomeregan
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13750;
DELETE FROM conditions WHERE SourceEntry = 13750 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13750,0,-13715,0,0,0,0,'',''),
(19,0,13750,0,-13715,0,0,0,0,'','');
-- The Grand Melee - The Exodar
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13756;
DELETE FROM conditions WHERE SourceEntry = 13756 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13756,0,-13716,0,0,0,0,'',''),
(19,0,13756,0,-13716,0,0,0,0,'','');
-- The Grand Melee - Darnassus
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13761;
DELETE FROM conditions WHERE SourceEntry = 13761 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13761,0,-13717,0,0,0,0,'',''),
(19,0,13761,0,-13717,0,0,0,0,'','');
-- The Grand Melee - Ironforge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 13772, NextQuestInChain = 0, RequiredRaces = 1101 WHERE entry = 13745;
DELETE FROM conditions WHERE SourceEntry = 13745 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13745,0,-13714,0,0,0,0,'',''),
(19,0,13745,0,-13714,0,0,0,0,'','');

-- Questpooling
/*
DELETE FROM pool_template WHERE entry IN (13768,13773,13778,13783,13762,13603,13746,13752,13757,13741);
INSERT INTO pool_template VALUES
(13768,1,'Tournament - Aspirant - Weapon Quest - Senjin'),
(13773,1,'Tournament - Aspirant - Weapon Quest - Thunder Bluff'),
(13778,1,'Tournament - Aspirant - Weapon Quest - Undercity'),
(13783,1,'Tournament - Aspirant - Weapon Quest - Silvermoon City'),
(13762,1,'Tournament - Aspirant - Weapon Quest - Orgrimmar'),
(13603,1,'Tournament - Aspirant - Weapon Quest - Stormwind'),
(13746,1,'Tournament - Aspirant - Weapon Quest - Gnomeregan'),
(13752,1,'Tournament - Aspirant - Weapon Quest - The Exodar'),
(13757,1,'Tournament - Aspirant - Weapon Quest - Darnassus'),
(13741,1,'Tournament - Aspirant - Weapon Quest - Ironforge');

DELETE FROM pool_quest WHERE pool_entry IN (13768,13773,13778,13783,13762,13603,13746,13752,13757,13741);
INSERT INTO pool_quest VALUES 
(13769,13768,'Tournament - Aspirant - Weapon Quest - Senjin - A Worthy Weapon'),
(13768,13768,'Tournament - Aspirant - Weapon Quest - Senjin - A Blade Fit For A Champion'),
(13770,13768,'Tournament - Aspirant - Weapon Quest - Senjin - The Edge Of Winter'),
(13774,13773,'Tournament - Aspirant - Weapon Quest - Thunder Bluff - A Worthy Weapon'),
(13773,13773,'Tournament - Aspirant - Weapon Quest - Thunder Bluff - A Blade Fit For A Champion'),
(13775,13773,'Tournament - Aspirant - Weapon Quest - Thunder Bluff - The Edge Of Winter'),
(13779,13778,'Tournament - Aspirant - Weapon Quest - Undercity - A Worthy Weapon'),
(13778,13778,'Tournament - Aspirant - Weapon Quest - Undercity - A Blade Fit For A Champion'),
(13780,13778,'Tournament - Aspirant - Weapon Quest - Undercity - The Edge Of Winter'),
(13784,13783,'Tournament - Aspirant - Weapon Quest - Silvermoon City - A Worthy Weapon'),
(13783,13783,'Tournament - Aspirant - Weapon Quest - Silvermoon City - A Blade Fit For A Champion'),
(13785,13783,'Tournament - Aspirant - Weapon Quest - Silvermoon City - The Edge Of Winter'),
(13763,13762,'Tournament - Aspirant - Weapon Quest - Orgrimmar - A Worthy Weapon'),
(13762,13762,'Tournament - Aspirant - Weapon Quest - Orgrimmar - A Blade Fit For A Champion'),
(13764,13762,'Tournament - Aspirant - Weapon Quest - Orgrimmar - The Edge Of Winter'),
(13600,13603,'Tournament - Aspirant - Weapon Quest - Stormwind - A Worthy Weapon'),
(13603,13603,'Tournament - Aspirant - Weapon Quest - Stormwind - A Blade Fit For A Champion'),
(13616,13603,'Tournament - Aspirant - Weapon Quest - Stormwind - The Edge Of Winter'),
(13747,13746,'Tournament - Aspirant - Weapon Quest - Gnomeregan - A Worthy Weapon'),
(13746,13746,'Tournament - Aspirant - Weapon Quest - Gnomeregan - A Blade Fit For A Champion'),
(13748,13746,'Tournament - Aspirant - Weapon Quest - Gnomeregan - The Edge Of Winter'),
(13753,13752,'Tournament - Aspirant - Weapon Quest - The Exodar - A Worthy Weapon'),
(13752,13752,'Tournament - Aspirant - Weapon Quest - The Exodar - A Blade Fit For A Champion'),
(13754,13752,'Tournament - Aspirant - Weapon Quest - The Exodar - The Edge Of Winter'),
(13758,13757,'Tournament - Aspirant - Weapon Quest - Darnassus - A Worthy Weapon'),
(13757,13757,'Tournament - Aspirant - Weapon Quest - Darnassus - A Blade Fit For A Champion'),
(13759,13757,'Tournament - Aspirant - Weapon Quest - Darnassus - The Edge Of Winter'),
(13742,13741,'Tournament - Aspirant - Weapon Quest - Ironforge - A Worthy Weapon'),
(13741,13741,'Tournament - Aspirant - Weapon Quest - Ironforge - A Blade Fit For A Champion'),
(13743,13741,'Tournament - Aspirant - Weapon Quest - Ironforge - The Edge Of Winter');
*/

-- ##### Champion

-- Taking Battle To The Enemy ... Prev: Eadric the Pure / The Scourgebane
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13810;
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13789;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13791;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13813;
-- Battle Before The Citadel ... Prev: Eadric the Pure / The Scourgebane
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13862;
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13861;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13863;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13864;
-- Among the Champions ... Prev: Eadric the Pure
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13811;
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13790;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13814;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13793;

-- Threat From Above ... Prev: Eadric the Pure
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13809;
UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13682;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13812;
UPDATE quest_template SET PrevQuestId = 13795, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13788;

DELETE FROM conditions WHERE SourceTypeOrReferenceId IN (-2782,-2788,-2817,-2816,-3676,-3677);
INSERT INTO conditions
VALUES
-- Allianz 
(-2782,0,0,0,8,13725,0,0,0,"","needs Champion"),
(-2782,0,0,1,8,13713,0,0,0,"","needs Champion"),
(-2782,0,0,2,8,13723,0,0,0,"","needs Champion"),
(-2782,0,0,3,8,13724,0,0,0,"","needs Champion"),
(-2782,0,0,4,8,13699,0,0,0,"","needs Champion"),
-- Horde
(-2788,0,0,0,8,13727,0,0,0,"","needs Champion"),
(-2788,0,0,1,8,13728,0,0,0,"","needs Champion"),
(-2788,0,0,2,8,13729,0,0,0,"","needs Champion"),
(-2788,0,0,3,8,13731,0,0,0,"","needs Champion"),
(-2788,0,0,4,8,13726,0,0,0,"","needs Champion"),

(-2817,0,0,0,17,2817,0,0,0,"","needs Exalted Champion"), -- Allianz
(-2816,0,0,0,17,2816,0,0,0,"","needs Exalted Champion"), -- Horde

(-3676,0,0,0,17,3676,0,0,0,"","needs Silver Confidant"),
(-3677,0,0,0,17,3677,0,0,0,"","needs The Sunreaver");

DELETE FROM conditions WHERE 
SourceTypeOrReferenceId IN (19,20) AND SourceEntry IN
(13846,14101,14102,14104,14105,13810,13862,13811,13794,14140,14143,14144,14096,14136,14092,14107,14108,14141,14145,13795,14080,14074,14077,14142,14152,14076,14090,14112,13684,13688,13685,13690,13689);
INSERT INTO conditions
VALUES 
(19,0,13846,0,-2782,0,0,0,0,"","Contributin To The Cause - Daily needs Champion"),
(20,0,13846,0,-2782,0,0,0,0,"","Contributin To The Cause - Daily needs Champion"),
(19,0,13846,1,-2788,0,0,0,0,"","Contributin To The Cause - Daily needs Champion"),
(20,0,13846,1,-2788,0,0,0,0,"","Contributin To The Cause - Daily needs Champion"),

(19,0,14101,0,-2817,0,0,0,0,"","Drottinn Hrothgar - Daily needs Exalted Champion"),
(20,0,14101,0,-2817,0,0,0,0,"","Drottinn Hrothgar - Daily needs Exalted Champion"),
(19,0,14101,1,-2816,0,0,0,0,"","Drottinn Hrothgar - Daily needs Exalted Champion"),
(20,0,14101,1,-2816,0,0,0,0,"","Drottinn Hrothgar - Daily needs Exalted Champion"),
(19,0,14102,0,-2817,0,0,0,0,"","Mistcaller Yngvar - Daily needs Exalted Champion"),
(20,0,14102,0,-2817,0,0,0,0,"","Mistcaller Yngvar - Daily needs Exalted Champion"),
(19,0,14102,1,-2816,0,0,0,0,"","Mistcaller Yngvar - Daily needs Exalted Champion"),
(20,0,14102,1,-2816,0,0,0,0,"","Mistcaller Yngvar - Daily needs Exalted Champion"),
(19,0,14104,0,-2817,0,0,0,0,"","Ornolf The Scarred - Daily needs Exalted Champion"),
(20,0,14104,0,-2817,0,0,0,0,"","Ornolf The Scarred - Daily needs Exalted Champion"),
(19,0,14104,1,-2816,0,0,0,0,"","Ornolf The Scarred - Daily needs Exalted Champion"),
(20,0,14104,1,-2816,0,0,0,0,"","Ornolf The Scarred - Daily needs Exalted Champion"),
(19,0,14105,0,-2817,0,0,0,0,"","Deathspeaker Kharos - Daily needs Exalted Champion"),
(20,0,14105,0,-2817,0,0,0,0,"","Deathspeaker Kharos - Daily needs Exalted Champion"),
(19,0,14105,1,-2816,0,0,0,0,"","Deathspeaker Kharos - Daily needs Exalted Champion"),
(20,0,14105,1,-2816,0,0,0,0,"","Deathspeaker Kharos - Daily needs Exalted Champion"),

(19,0,14107,0,-2817,0,0,0,0,"","The Fate Of The Fallen - Daily needs Champion"),
(20,0,14107,0,-2817,0,0,0,0,"","The Fate Of The Fallen - Daily needs Champion"),
(19,0,14107,1,-2816,0,0,0,0,"","The Fate Of The Fallen - Daily needs Champion"),
(20,0,14107,1,-2816,0,0,0,0,"","The Fate Of The Fallen - Daily needs Champion"),
(19,0,14108,0,-2817,0,0,0,0,"","Get Kraken! - Daily needs Champion"),
(20,0,14108,0,-2817,0,0,0,0,"","Get Kraken! - Daily needs Champion"),
(19,0,14108,1,-2816,0,0,0,0,"","Get Kraken! - Daily needs Champion"),
(20,0,14108,1,-2816,0,0,0,0,"","Get Kraken! - Daily needs Champion"),

-- (19,0,13810,0,-2782,0,0,0,0,"","Taking Battle To The Enemy - Daily needs Champion"),
-- (20,0,13810,0,-2782,0,0,0,0,"","Taking Battle To The Enemy - Daily needs Champion"),
-- (19,0,13810,1,-2788,0,0,0,0,"","Taking Battle To The Enemy - Daily needs Champion"),
-- (20,0,13810,1,-2788,0,0,0,0,"","Taking Battle To The Enemy - Daily needs Champion"),

-- (19,0,13862,0,-2782,0,0,0,0,"","Battle Before The Citadel - Daily needs Champion"),
-- (20,0,13862,0,-2782,0,0,0,0,"","Battle Before The Citadel - Daily needs Champion"),
-- (19,0,13862,1,-2788,0,0,0,0,"","Battle Before The Citadel - Daily needs Champion"),
-- (20,0,13862,1,-2788,0,0,0,0,"","Battle Before The Citadel - Daily needs Champion"),

-- (19,0,13811,0,-2782,0,0,0,0,"","Among the Champions - Daily needs Champion"),
-- (20,0,13811,0,-2782,0,0,0,0,"","Among the Champions - Daily needs Champion"),
-- (19,0,13811,1,-2788,0,0,0,0,"","Among the Champions - Daily needs Champion"),
-- (20,0,13811,1,-2788,0,0,0,0,"","Among the Champions - Daily needs Champion"),

(19,0,13794,0,-2782,0,0,0,0,"","Eadric the Pure - Daily needs Champion"),
(20,0,13794,0,-2782,0,0,0,0,"","Eadric the Pure - Daily needs Champion"),
(19,0,13794,1,-2788,0,0,0,0,"","Eadric the Pure - Daily needs Champion"),
(20,0,13794,1,-2788,0,0,0,0,"","Eadric the Pure - Daily needs Champion"),

(19,0,13795,0,-2782,0,0,0,0,"","The Scourgebane - Daily needs Champion"),
(20,0,13795,0,-2782,0,0,0,0,"","The Scourgebane - Daily needs Champion"),
(19,0,13795,1,-2788,0,0,0,0,"","The Scourgebane - Daily needs Champion"),
(20,0,13795,1,-2788,0,0,0,0,"","The Scourgebane - Daily needs Champion"),

-- Horde Only
(19,0,14140,0,-3677,0,0,0,0,"","Stop The Aggressors - Daily needs The Sunreaver"),
(20,0,14140,0,-3677,0,0,0,0,"","Stop The Aggressors - Daily needs The Sunreaver"),
(19,0,14143,0,-3677,0,0,0,0,"","A Leg Up - Daily needs The Sunreaver"),
(20,0,14143,0,-3677,0,0,0,0,"","A Leg Up - Daily needs The Sunreaver"),
(19,0,14144,0,-3677,0,0,0,0,"","The Light's Mercy - Daily needs The Sunreaver"),
(20,0,14144,0,-3677,0,0,0,0,"","The Light's Mercy - Daily needs The Sunreaver"),
(19,0,14136,0,-3677,0,0,0,0,"","Rescue at Sea - Daily needs The Sunreaver"),
(20,0,14136,0,-3677,0,0,0,0,"","Rescue at Sea - Daily needs The Sunreaver"),
(19,0,14142,0,-3677,0,0,0,0,"","Youve Really Done It This Time, Kul - Daily needs The Sunreaver"),
(20,0,14142,0,-3677,0,0,0,0,"","Youve Really Done It This Time, Kul - Daily needs The Sunreaver"),

(19,0,14092,0,-3677,0,0,0,0,"","Breakfast Of Champions - Daily needs The Sunreaver"),
(20,0,14092,0,-3677,0,0,0,0,"","Breakfast Of Champions - Daily needs The Sunreaver"),
(19,0,14141,0,-3677,0,0,0,0,"","Gormok Wants His Snobolds - Daily needs The Sunreaver"),
(20,0,14141,0,-3677,0,0,0,0,"","Gormok Wants His Snobolds - Daily needs The Sunreaver"),
(19,0,14145,0,-3677,0,0,0,0,"","What Do You Feed a Yeti, Anyway? - Daily needs The Sunreaver"),
(20,0,14145,0,-3677,0,0,0,0,"","What Do You Feed a Yeti, Anyway? - Daily needs The Sunreaver"),

-- Alliance Only
(19,0,14080,0,-3676,0,0,0,0,"","Stop The Aggressors - Daily needs Silver Confidant"),
(20,0,14080,0,-3676,0,0,0,0,"","Stop The Aggressors - Daily needs Silver Confidant"),
(19,0,14074,0,-3676,0,0,0,0,"","A Leg Up - Daily needs Silver Confidant"),
(20,0,14074,0,-3676,0,0,0,0,"","A Leg Up - Daily needs Silver Confidant"),
(19,0,14077,0,-3676,0,0,0,0,"","The Light's Mercy - Daily needs Silver Confidant"),
(20,0,14077,0,-3676,0,0,0,0,"","The Light's Mercy - Daily needs Silver Confidant"),
(19,0,14152,0,-3676,0,0,0,0,"","Rescue at Sea - Daily needs Silver Confidant"),
(20,0,14152,0,-3676,0,0,0,0,"","Rescue at Sea - Daily needs Silver Confidant"),
(19,0,14096,0,-3676,0,0,0,0,"","Youve Really Done It This Time, Kul - Daily needs Silver Confidant"),
(20,0,14096,0,-3676,0,0,0,0,"","Youve Really Done It This Time, Kul - Daily needs Silver Confidant"),

(19,0,14076,0,-3676,0,0,0,0,"","Breakfast Of Champions - Daily needs Silver Confidant"),
(20,0,14076,0,-3676,0,0,0,0,"","Breakfast Of Champions - Daily needs Silver Confidant"),
(19,0,14090,0,-3676,0,0,0,0,"","Gormok Wants His Snobolds - Daily needs Silver Confidant"),
(20,0,14090,0,-3676,0,0,0,0,"","Gormok Wants His Snobolds - Daily needs Silver Confidant"),
(19,0,14112,0,-3676,0,0,0,0,"","What Do You Feed a Yeti, Anyway? - Daily needs Silver Confidant"),
(20,0,14112,0,-3676,0,0,0,0,"","What Do You Feed a Yeti, Anyway? - Daily needs Silver Confidant");


DELETE FROM conditions WHERE SourceTypeOrReferenceId IN (-13707,-13708,-13711,-13709,-13710 ,-13593,-13704,-13703,-13705,-13706);
INSERT INTO conditions
VALUES
-- Horde 
(-13707,0,0,0,14,13707,0,0,0,"","Valiant Orgrimmar not running - Valiant none"),
(-13707,0,0,1,8,13707,0,0,0,"","Valiant Orgrimmar not running - Valiant Complete"),
(-13707,0,0,1,8,13697,0,0,0,"","Valiant Orgrimmar not running - and Marks Complete"),
(-13707,0,0,1,8,13726,0,0,0,"","Valiant Orgrimmar not running - and Challenge Complete"),

(-13708,0,0,0,14,13708,0,0,0,"","Valiant Sen'jin not running - Valiant none"),
(-13708,0,0,1,8,13708,0,0,0,"","Valiant Sen'jin not running - Valiant Complete"),
(-13708,0,0,1,8,13719,0,0,0,"","Valiant Sen'jin not running - and Marks Complete"),
(-13708,0,0,1,8,13727,0,0,0,"","Valiant Sen'jin not running - and Challenge Complete"),

(-13711,0,0,0,14,13711,0,0,0,"","Valiant Silvermoon not running - Valiant none"),
(-13711,0,0,1,8,13711,0,0,0,"","Valiant Silvermoon not running - Valiant Complete"),
(-13711,0,0,1,8,13722,0,0,0,"","Valiant Silvermoon not running - and Marks Complete"),
(-13711,0,0,1,8,13731,0,0,0,"","Valiant Silvermoon not running - and Challenge Complete"),

(-13709,0,0,0,14,13709,0,0,0,"","Valiant Thunder Bluff not running - Valiant none"),
(-13709,0,0,1,8,13709,0,0,0,"","Valiant Thunder Bluff not running - Valiant Complete"),
(-13709,0,0,1,8,13720,0,0,0,"","Valiant Thunder Bluff not running - and Marks Complete"),
(-13709,0,0,1,8,13728,0,0,0,"","Valiant Thunder Bluff not running - and Challenge Complete"),

(-13710,0,0,0,14,13710,0,0,0,"","Valiant Undercity not running - Valiant none"),
(-13710,0,0,1,8,13710,0,0,0,"","Valiant Undercity not running - Valiant Complete"),
(-13710,0,0,1,8,13721,0,0,0,"","Valiant Undercity not running - and Marks Complete"),
(-13710,0,0,1,8,13729,0,0,0,"","Valiant Undercity not running - and Challenge Complete"),

-- Allianz
(-13593,0,0,0,14,13593,0,0,0,"","Valiant Stormwind not running - Valiant none"),
(-13593,0,0,1,8,13593,0,0,0,"","Valiant Stormwind not running - Valiant Complete"),
(-13593,0,0,1,8,13718,0,0,0,"","Valiant Stormwind not running - and Marks Complete"),
(-13593,0,0,1,8,13699,0,0,0,"","Valiant Stormwind not running - and Challenge Complete"),

(-13704,0,0,0,14,13704,0,0,0,"","Valiant Gnomeregan not running - Valiant none"),
(-13704,0,0,1,8,13704,0,0,0,"","Valiant Gnomeregan not running - Valiant Complete"),
(-13704,0,0,1,8,13715,0,0,0,"","Valiant Gnomeregan not running - and Marks Complete"),
(-13704,0,0,1,8,13723,0,0,0,"","Valiant Gnomeregan not running - and Challenge Complete"),

(-13703,0,0,0,14,13703,0,0,0,"","Valiant Ironforge not running - Valiant none"),
(-13703,0,0,1,8,13703,0,0,0,"","Valiant Ironforge not running - Valiant Complete"),
(-13703,0,0,1,8,13714,0,0,0,"","Valiant Ironforge not running - and Marks Complete"),
(-13703,0,0,1,8,13713,0,0,0,"","Valiant Ironforge not running - and Challenge Complete"),

(-13705,0,0,0,14,13705,0,0,0,"","Valiant Exodar not running - Valiant none"),
(-13705,0,0,1,8,13705,0,0,0,"","Valiant Exodar not running - Valiant Complete"),
(-13705,0,0,1,8,13716,0,0,0,"","Valiant Exodar not running - and Marks Complete"),
(-13705,0,0,1,8,13724,0,0,0,"","Valiant Exodar not running - and Challenge Complete"),

(-13706,0,0,0,14,13706,0,0,0,"","Valiant Darnassus not running - Valiant none"),
(-13706,0,0,1,8,13706,0,0,0,"","Valiant Darnassus not running - Valiant Complete"),
(-13706,0,0,1,8,13717,0,0,0,"","Valiant Darnassus not running - and Marks Complete"),
(-13706,0,0,1,8,13725,0,0,0,"","Valiant Darnassus not running - and Challenge Complete");

DELETE FROM conditions WHERE 
SourceTypeOrReferenceId IN (19,20) AND SourceEntry IN (13593,13703,13704,13705,13706,13707,13708,13709,13710,13711);
INSERT INTO conditions VALUES
-- Horde
(19,0,13707,0,-2788,0,0,0,0,"","Valiant Of Orgrimmar - Quest needs Champion"),
(20,0,13707,0,-2788,0,0,0,0,"","Valiant Of Orgrimmar - Quest needs Champion"),
(19,0,13707,0,14,13691,0,0,0,"","Valiant Of Orgrimmar - and Only for other Factions"),
(20,0,13707,0,14,13691,0,0,0,"","Valiant Of Orgrimmar - and Only for other Factions"),
(19,0,13707,0,-13708,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(20,0,13707,0,-13708,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(19,0,13707,0,-13711,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(20,0,13707,0,-13711,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(19,0,13707,0,-13709,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(20,0,13707,0,-13709,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(19,0,13707,0,-13710,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),
(20,0,13707,0,-13710,0,0,0,0,"","Valiant Of Orgrimmar - and Not other Quest running"),

(19,0,13708,0,-2788,0,0,0,0,"","Valiant Of Sen'jin - Quest needs Champion"),
(20,0,13708,0,-2788,0,0,0,0,"","Valiant Of Sen'jin - Quest needs Champion"),
(19,0,13708,0,14,13693,0,0,0,"","Valiant Of Sen'jin - and Only for other Factions"),
(20,0,13708,0,14,13693,0,0,0,"","Valiant Of Sen'jin - and Only for other Factions"),
(19,0,13708,0,-13707,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(20,0,13708,0,-13707,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(19,0,13708,0,-13711,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(20,0,13708,0,-13711,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(19,0,13708,0,-13709,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(20,0,13708,0,-13709,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(19,0,13708,0,-13710,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),
(20,0,13708,0,-13710,0,0,0,0,"","Valiant Of Sen'jin - and Not other Quest running"),

(19,0,13711,0,-2788,0,0,0,0,"","Valiant Of Silvermoon - Quest needs Champion"),
(20,0,13711,0,-2788,0,0,0,0,"","Valiant Of Silvermoon - Quest needs Champion"),
(19,0,13711,0,14,13696,0,0,0,"","Valiant Of Silvermoon - and Only for other Factions"),
(20,0,13711,0,14,13696,0,0,0,"","Valiant Of Silvermoon - and Only for other Factions"),
(19,0,13711,0,-13707,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(20,0,13711,0,-13707,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(19,0,13711,0,-13708,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(20,0,13711,0,-13708,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(19,0,13711,0,-13709,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(20,0,13711,0,-13709,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(19,0,13711,0,-13710,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),
(20,0,13711,0,-13710,0,0,0,0,"","Valiant Of Silvermoon - and Not other Quest running"),

(19,0,13709,0,-2788,0,0,0,0,"","Valiant Of Thunder Bluff - Quest needs Champion"),
(20,0,13709,0,-2788,0,0,0,0,"","Valiant Of Thunder Bluff - Quest needs Champion"),
(19,0,13709,0,14,13694,0,0,0,"","Valiant Of Thunder Bluff - and Only for other Factions"),
(20,0,13709,0,14,13694,0,0,0,"","Valiant Of Thunder Bluff - and Only for other Factions"),
(19,0,13709,0,-13707,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(20,0,13709,0,-13707,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(19,0,13709,0,-13708,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(20,0,13709,0,-13708,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(19,0,13709,0,-13711,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(20,0,13709,0,-13711,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(19,0,13709,0,-13710,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),
(20,0,13709,0,-13710,0,0,0,0,"","Valiant Of Thunder Bluff - and Not other Quest running"),

(19,0,13710,0,-2788,0,0,0,0,"","Valiant Of Undercity - Quest needs Champion"),
(20,0,13710,0,-2788,0,0,0,0,"","Valiant Of Undercity - Quest needs Champion"),
(19,0,13710,0,14,13695,0,0,0,"","Valiant Of Undercity - and Only for other Factions"),
(20,0,13710,0,14,13695,0,0,0,"","Valiant Of Undercity - and Only for other Factions"),
(19,0,13710,0,-13707,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(20,0,13710,0,-13707,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(19,0,13710,0,-13708,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(20,0,13710,0,-13708,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(19,0,13710,0,-13711,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(20,0,13710,0,-13711,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(19,0,13710,0,-13709,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),
(20,0,13710,0,-13709,0,0,0,0,"","Valiant Of Undercity - and Not other Quest running"),


-- Allianz
(19,0,13593,0,-2782,0,0,0,0,"","Valiant Of Stormwind - Quest needs Champion"),
(20,0,13593,0,-2782,0,0,0,0,"","Valiant Of Stormwind - Quest needs Champion"),
(19,0,13593,0,14,13684,0,0,0,"","Valiant Of Stormwind - and Only for other Factions"),
(20,0,13593,0,14,13684,0,0,0,"","Valiant Of Stormwind - and Only for other Factions"),
(19,0,13593,0,-13704,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(20,0,13593,0,-13704,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(19,0,13593,0,-13703,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(20,0,13593,0,-13703,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(19,0,13593,0,-13705,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(20,0,13593,0,-13705,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(19,0,13593,0,-13706,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),
(20,0,13593,0,-13706,0,0,0,0,"","Valiant Of Stormwind - and Not other Quest running"),

(19,0,13704,0,-2782,0,0,0,0,"","Valiant Of Gnomeregan - Quest needs Champion"),
(20,0,13704,0,-2782,0,0,0,0,"","Valiant Of Gnomeregan - Quest needs Champion"),
(19,0,13704,0,14,13688,0,0,0,"","Valiant Of Gnomeregan - and Only for other Factions"),
(20,0,13704,0,14,13688,0,0,0,"","Valiant Of Gnomeregan - and Only for other Factions"),
(19,0,13704,0,-13593,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(20,0,13704,0,-13593,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(19,0,13704,0,-13703,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(20,0,13704,0,-13703,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(19,0,13704,0,-13705,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(20,0,13704,0,-13705,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(19,0,13704,0,-13706,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),
(20,0,13704,0,-13706,0,0,0,0,"","Valiant Of Gnomeregan - and Not other Quest running"),

(19,0,13703,0,-2782,0,0,0,0,"","Valiant Of Ironforge - Quest needs Champion"),
(20,0,13703,0,-2782,0,0,0,0,"","Valiant Of Ironforge - Quest needs Champion"),
(19,0,13703,0,14,13685,0,0,0,"","Valiant Of Ironforge - and Only for other Factions"),
(20,0,13703,0,14,13685,0,0,0,"","Valiant Of Ironforge - and Only for other Factions"),
(19,0,13703,0,-13593,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(20,0,13703,0,-13593,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(19,0,13703,0,-13704,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(20,0,13703,0,-13704,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(19,0,13703,0,-13705,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(20,0,13703,0,-13705,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(19,0,13703,0,-13706,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),
(20,0,13703,0,-13706,0,0,0,0,"","Valiant Of Ironforge - and Not other Quest running"),

(19,0,13705,0,-2782,0,0,0,0,"","Valiant Of Exodar - Quest needs Champion"),
(20,0,13705,0,-2782,0,0,0,0,"","Valiant Of Exodar - Quest needs Champion"),
(19,0,13705,0,14,13690,0,0,0,"","Valiant Of Exodar - and Only for other Factions"),
(20,0,13705,0,14,13690,0,0,0,"","Valiant Of Exodar - and Only for other Factions"),
(19,0,13705,0,-13593,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(20,0,13705,0,-13593,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(19,0,13705,0,-13704,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(20,0,13705,0,-13704,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(19,0,13705,0,-13703,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(20,0,13705,0,-13703,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(19,0,13705,0,-13706,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),
(20,0,13705,0,-13706,0,0,0,0,"","Valiant Of Exodar - and Not other Quest running"),


(19,0,13706,0,-2782,0,0,0,0,"","Valiant Of Darnassus - Quest needs Champion"),
(20,0,13706,0,-2782,0,0,0,0,"","Valiant Of Darnassus - Quest needs Champion"),
(19,0,13706,0,14,13689,0,0,0,"","Valiant Of Darnassus - and Only for other Factions"),
(20,0,13706,0,14,13689,0,0,0,"","Valiant Of Darnassus - and Only for other Factions"),
(19,0,13706,0,-13593,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(20,0,13706,0,-13593,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(19,0,13706,0,-13704,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(20,0,13706,0,-13704,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(19,0,13706,0,-13703,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(20,0,13706,0,-13703,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(19,0,13706,0,-13705,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running"),
(20,0,13706,0,-13705,0,0,0,0,"","Valiant Of Darnassus - and Not other Quest running");

-- The Sunreavers * The Silver Covenant Quests
DELETE FROM pool_template WHERE entry IN (34880,34771);
INSERT INTO pool_template VALUES
(34880,1,'Tournament - Champion - The Silver Covenant - Sea'),
(34771,1,'Tournament - Champion - The Sunreavers - Sea');

UPDATE quest_template SET ExclusiveGroup = 14074 WHERE entry in (14074,14152,14077,14080);
UPDATE quest_template SET ExclusiveGroup = 14143 WHERE entry in (14143,14136,14144,14140);
UPDATE quest_template SET ExclusiveGroup = 0 WHERE entry in (14142,14096); -- Kul Quest enable everyday
-- Fix for Kul Quest - Not Closing Cages
UPDATE `gameobject_template` SET `data2`=30000 WHERE `entry` = 195310;
UPDATE gameobject SET state = 1 WHERE id = 195310;


DELETE FROM pool_quest WHERE pool_entry IN (34880,34771);
INSERT INTO pool_quest VALUES 
(14074,34880,'Tournament - Champion - The Silver Covenant - Sea - A Leg Up'),
(14152,34880,'Tournament - Champion - The Silver Covenant - Sea - Rescue At Sea'),
(14077,34880,'Tournament - Champion - The Silver Covenant - Sea - The Lights Mercy'),
(14080,34880,'Tournament - Champion - The Silver Covenant - Sea - Stop the Aggression'),
(14143,34771,'Tournament - Champion - The Sunreavers - Sea - A Leg Up'),
(14136,34771,'Tournament - Champion - The Sunreavers - Sea - Rescue At Sea'),
(14144,34771,'Tournament - Champion - The Sunreavers - Sea - The Lights Mercy'),
(14140,34771,'Tournament - Champion - The Sunreavers - Sea - Stop the Aggression');

DELETE FROM pool_template WHERE entry IN (34912,34914);
INSERT INTO pool_template VALUES
(34912,1,'Tournament - Champion - The Silver Covenant - Tournament'),
(34914,1,'Tournament - Champion - The Sunreavers - Tournament');

UPDATE quest_template SET ExclusiveGroup = 14092 WHERE entry in (14092,14141,14145);
UPDATE quest_template SET ExclusiveGroup = 14076 WHERE entry in (14076,14090,14112);
DELETE FROM pool_quest WHERE pool_entry IN (34912,34914);
INSERT INTO pool_quest VALUES 
(14092,34912,'Tournament - Champion - The Silver Covenant - Tournament - Breakfast Of Champions'),
(14141,34912,'Tournament - Champion - The Silver Covenant - Tournament - Gormok Wants His Snobolds'),
(14145,34912,'Tournament - Champion - The Silver Covenant - Tournament - What Do You Feed a Yeti, Anyway?'),
(14076,34914,'Tournament - Champion - The Sunreavers - Tournament - Breakfast Of Champions'),
(14090,34914,'Tournament - Champion - The Sunreavers - Tournament - Gormok Wants His Snobolds'),
(14112,34914,'Tournament - Champion - The Sunreavers - Tournament - What Do You Feed a Yeti, Anyway?');

DELETE FROM pool_template WHERE entry IN (34882);
INSERT INTO pool_template VALUES
(34882,1,'Tournament - Champion - The Argent Crusade - Defeat');

UPDATE quest_template SET ExclusiveGroup = 14101 WHERE entry in (14101,14102,14104,14105);
DELETE FROM pool_quest WHERE pool_entry IN (34882);
INSERT INTO pool_quest VALUES 
(14101,34882,'Tournament - Champion - The Argent Crusade - Defeat - Drottinn Hrothgar'),
(14102,34882,'Tournament - Champion - The Argent Crusade - Defeat - Mistcaller Yngvar'),
(14104,34882,'Tournament - Champion - The Argent Crusade - Defeat - Ornolf The Scarred'),
(14105,34882,'Tournament - Champion - The Argent Crusade - Defeat - Deathspeaker Kharos');

DELETE FROM pool_template WHERE entry IN (35094);
INSERT INTO pool_template VALUES
(35094,1,'Tournament - Champion - The Argent Crusade - Kraken');

UPDATE quest_template SET ExclusiveGroup = 14107 WHERE entry in (14107,14108);
DELETE FROM pool_quest WHERE pool_entry IN (35094);
INSERT INTO pool_quest VALUES 
(14107,35094,'Tournament - Champion - The Argent Crusade - Kraken - The Fate Of The Fallen'),
(14108,35094,'Tournament - Champion - The Argent Crusade - Kraken - Get Kraken!');

-- Valiant Spellaura on Vehicle Quest: The Grand Melee
DELETE FROM spell_linked_spell WHERE spell_trigger IN (63151,-63151);
INSERT INTO spell_linked_spell VALUES
(63151,63405,0,'Darnassus Valiant'),
(63151,63422,0,'Exodar Valiant'),
(63151,63395,0,'Gnomeregan Valiant'),
(63151,63426,0,'Ironforge Valiant'),
(63151,63432,0,'Orgrimmar Valiant'),
(63151,63398,0,'SenJin Valiant'),
(63151,63402,0,'Silvermoon Valiant'),
(63151,62596,0,'Stormwind Valiant'),
(63151,63435,0,'Thunder Bluff Valiant'),
(63151,63429,0,'Undercity Valiant'),
(-63151,-63405,0,'Darnassus Valiant remove'),
(-63151,-63422,0,'Exodar Valiant remove'),
(-63151,-63395,0,'Gnomeregan Valiant remove'),
(-63151,-63426,0,'Ironforge Valiant remove'),
(-63151,-63432,0,'Orgrimmar Valiant remove'),
(-63151,-63398,0,'SenJin Valiant remove'),
(-63151,-63402,0,'Silvermoon Valiant remove'),
(-63151,-62596,0,'Stormwind Valiant remove'),
(-63151,-63435,0,'Thunder Bluff Valiant remove'),
(-63151,-63429,0,'Undercity Valiant remove');

DELETE FROM conditions WHERE SourceEntry IN (63405,63422,63395,63426,63432,63398,63402,62596,63435,63429);
INSERT INTO conditions VALUES
(17,0,63405,0,9,13761,0,0,0,'','Darnassus Valiant'),
(17,0,63422,0,9,13756,0,0,0,'','Exodar Valiant'),
(17,0,63395,0,9,13750,0,0,0,'','Gnomeregan Valiant'),
(17,0,63426,0,9,13745,0,0,0,'','Ironforge Valiant'),
(17,0,63432,0,9,13767,0,0,0,'','Orgrimmar Valiant'),
(17,0,63398,0,9,13772,0,0,0,'','SenJin Valiant'),
(17,0,63402,0,9,13787,0,0,0,'','Silvermoon Valiant'),
(17,0,62596,0,9,13665,0,0,0,'','Stormwind Valiant'),
(17,0,63435,0,9,13777,0,0,0,'','Thunder Bluff Valiant'),
(17,0,63429,0,9,13782,0,0,0,'','Undercity Valiant');

-- Champion Spellaura on Vehicle Quest: Among the Champions
/*
DELETE FROM spell_linked_spell WHERE spell_trigger IN (63151,-63151);
INSERT INTO spell_linked_spell VALUES
(63151,63406,0,'Darnassus Champion'),
(63151,63423,0,'Exodar Champion'),
(63151,63396,0,'Gnomeregan Champion'),
(63151,63427,0,'Ironforge Champion'),
(63151,63433,0,'Orgrimmar Champion'),
(63151,63399,0,'SenJin Champion'),
(63151,63403,0,'Silvermoon Champion'),
(63151,62594,0,'Stormwind Champion'),
(63151,63436,0,'Thunder Bluff Champion'),
(63151,63430,0,'Undercity Champion'),
(-63151,-63406,0,'Darnassus Champion remove'),
(-63151,-63423,0,'Exodar Champion remove'),
(-63151,-63396,0,'Gnomeregan Champion remove'),
(-63151,-63427,0,'Ironforge Champion remove'),
(-63151,-63433,0,'Orgrimmar Champion remove'),
(-63151,-63399,0,'SenJin Champion remove'),
(-63151,-63403,0,'Silvermoon Champion remove'),
(-63151,-62594,0,'Stormwind Champion remove'),
(-63151,-63436,0,'Thunder Bluff Champion remove'),
(-63151,-63430,0,'Undercity Champion remove');

DELETE FROM conditions WHERE SourceEntry IN (63406,63423,63396,63427,63433,63399,63403,62594,63436,63430);
INSERT INTO conditions VALUES
(17,0,63406,0,9,13790,0,0,0,'','Darnassus Champion'),
(17,0,63423,0,9,13790,0,0,0,'','Exodar Champion'),
(17,0,63396,0,9,13790,0,0,0,'','Gnomeregan Champion'),
(17,0,63427,0,9,13790,0,0,0,'','Ironforge Champion'),
(17,0,63433,0,9,13811,0,0,0,'','Orgrimmar Champion'),
(17,0,63399,0,9,13811,0,0,0,'','SenJin Champion'),
(17,0,63403,0,9,13811,0,0,0,'','Silvermoon Champion'),
(17,0,62594,0,9,13790,0,0,0,'','Stormwind Champion'),
(17,0,63436,0,9,13811,0,0,0,'','Thunder Bluff Champion'),
(17,0,63430,0,9,13811,0,0,0,'','Undercity Champion'),

(17,0,63406,1,9,13793,0,0,0,'','Darnassus Champion'),
(17,0,63423,1,9,13793,0,0,0,'','Exodar Champion'),
(17,0,63396,1,9,13793,0,0,0,'','Gnomeregan Champion'),
(17,0,63427,1,9,13793,0,0,0,'','Ironforge Champion'),
(17,0,63433,1,9,13814,0,0,0,'','Orgrimmar Champion'),
(17,0,63399,1,9,13814,0,0,0,'','SenJin Champion'),
(17,0,63403,1,9,13814,0,0,0,'','Silvermoon Champion'),
(17,0,62594,1,9,13793,0,0,0,'','Stormwind Champion'),
(17,0,63436,1,9,13814,0,0,0,'','Thunder Bluff Champion'),
(17,0,63430,1,9,13814,0,0,0,'','Undercity Champion');
*/

-- The Black Knight Questline
-- The Black Knight of Silverpine? ... Prev: The Argent Tournament ... NextQuestInLine: The Seer's Crystal
UPDATE quest_template SET PrevQuestId = 13668, NextQuestId = 13641, ExclusiveGroup = 0, NextQuestInChain = 13641 WHERE entry = 13634;
-- The Black Knight of Westfall? ... Prev: The Argent Tournament ... NextQuestInLine: The Seer's Crystal
UPDATE quest_template SET PrevQuestId = 13667, NextQuestId = 13641, ExclusiveGroup = 0, NextQuestInChain = 13641 WHERE entry = 13633;

-- The Seer's Crystal ... Prev: The Black Knight of Westfall? ... NextQuestInLine: The Stories Dead Men Tell
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13643 WHERE entry = 13641;

-- The Stories Dead Men Tell ... Prev: The Seer's Crystal ... NextQuestInLine: There's Something About the Squire
UPDATE quest_template SET PrevQuestId = 13641, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13654 WHERE entry = 13643;

-- There's Something About the Squire ... Prev: The Stories Dead Men Tell ... NextQuestInLine: The Black Knight's Orders
UPDATE quest_template SET PrevQuestId = 13643, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13663  WHERE entry = 13654;

-- Questfix
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=33498;
DELETE FROM  creature_ai_scripts WHERE `creature_id`=33498;
 
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=33498;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(33498,0,0,0,23,0,100,0,63124,1,0,0,81,16777216,0,0,0,0,0,1,0,0,0,0,0,0,0,'Maloric - on Aura: Incapacitate Maloric - set npcflag: Spellklick'),
(33498,0,1,0,23,0,100,0,63124,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Maloric - on NoAura: Incapacitate Maloric - set npcflag: none');
 
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=33498;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(33498,63126,13654,1,13654,2,0,0,0);
 
UPDATE `creature_template` SET `lootid`=`entry` WHERE `entry`=33499;
 
DELETE FROM `creature_loot_template` WHERE `entry`=33499;
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
(33499,45080,-100,0,0,1,1);

-- The Black Knight's Orders ... Prev: There's Something About the Squire
UPDATE quest_template SET PrevQuestId = 13654, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13663;

-- The Black Knight's Fall ... Prev: The Black Knight's Orders ... NextQuestInLine: The Black Knight's Curse
UPDATE quest_template SET PrevQuestId = 13663, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 14016  WHERE entry = 13664;

-- The Black Knight's Curse ... Prev: The Black Knight's Fall ... NextQuestInLine: The Black Knight's Fate
UPDATE quest_template SET PrevQuestId = 13664, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 14017  WHERE entry = 14016;

-- The Black Knight's Fate... Prev: The Black Knight's Curse 
UPDATE quest_template SET PrevQuestId = 14016, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 14017;

-- The Black Knight's Fall only avalable as Champion
DELETE FROM conditions WHERE SourceTypeOrReferenceId IN (19,20) AND SourceEntry = 13664;
INSERT INTO conditions
VALUES 
(19,0,13664,0,-2782,0,0,0,0,"","The Black Knight's Fall - Daily needs Champion"),
(20,0,13664,0,-2782,0,0,0,0,"","The Black Knight's Fall - Daily needs Champion"),
(19,0,13664,1,-2788,0,0,0,0,"","The Black Knight's Fall - Daily needs Champion"),
(20,0,13664,1,-2788,0,0,0,0,"","The Black Knight's Fall - Daily needs Champion");

-- Mount for Argent Champion
DELETE FROM `creature_template_addon` WHERE `entry` IN (33707);
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(33707,0,28919,0,0,0,''); -- Argent Champion - Mount

-- The Scourgebane - DK only
UPDATE quest_template SET SkillOrClassMask = -32 WHERE entry = 13795;
-- Eradic the Pure - DK forbitten
UPDATE quest_template SET SkillOrClassMask = -1503 WHERE entry = 13794;

-- Spell: Trample Scourge
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 63001;
INSERT INTO conditions VALUES 
(13,0,63001,0,18,1,33438,0,0,'','');
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 268435520 WHERE `entry` = 33438; -- NO-XP and respawntime ignore

-- Visibility of Black Knight
DELETE FROM spell_area WHERE spell = 67471;
INSERT INTO spell_area VALUES
(67471,4658,0,0,13664,0,0,2,1);

-- What Do You Feed a Yeti, Anyway? ... Factions
UPDATE `creature_template` SET `faction_A`=14  , `faction_H`=14, `InhabitType`=3 WHERE `entry` IN (35060,35061,35071,35072);

-- Get Kraken!
DELETE FROM spell_script_names WHERE spell_id IN (66588);
INSERT INTO spell_script_names (spell_id,Scriptname)
VALUES
(66588,'spell_flaming_spear_targeting');

-- ########################## Citadel Footsteps #########################

-- Blackwatch ... Prev: The Shadow Vault Allianz OR The Shadow Vault Horde
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13106;
DELETE FROM conditions WHERE SourceEntry = 13106 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13106,0,8,12898,0,0,0,'',''),
(19,0,13106,0,8,12898,0,0,0,'',''),
(20,0,13106,1,8,12899,0,0,0,'',''),
(19,0,13106,1,8,12899,0,0,0,'','');

-- Where Are They Coming From? ... Prev: Blackwatch
UPDATE quest_template SET PrevQuestId = 13106, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13117;

-- Death's Gaze ... Prev: Where Are They Coming From?
UPDATE quest_template SET PrevQuestId = 13117, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13120;
-- Destroying the Altars ... Prev: Where Are They Coming From?
UPDATE quest_template SET PrevQuestId = 13117, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13119;

-- I'm Not Dead Yet! H ... Prev: Death's Gaze AND Destroying the Altars
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13229;
DELETE FROM conditions WHERE SourceEntry = 13229 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13229,0,8,13120,0,0,0,'',''),
(19,0,13229,0,8,13120,0,0,0,'',''),
(20,0,13229,0,8,13119,0,0,0,'',''),
(19,0,13229,0,8,13119,0,0,0,'','');
-- I'm Not Dead Yet! A ... Prev: Death's Gaze AND Destroying the Altars
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13221;
DELETE FROM conditions WHERE SourceEntry = 13221 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13221,0,8,13120,0,0,0,'',''),
(19,0,13221,0,8,13120,0,0,0,'',''),
(20,0,13221,0,8,13119,0,0,0,'',''),
(19,0,13221,0,8,13119,0,0,0,'','');

-- Spill Their Blood ... Prev: Death's Gaze AND Destroying the Altars
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13134;
DELETE FROM conditions WHERE SourceEntry = 13134 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13134,0,8,13120,0,0,0,'',''),
(19,0,13134,0,8,13120,0,0,0,'',''),
(20,0,13134,0,8,13119,0,0,0,'',''),
(19,0,13134,0,8,13119,0,0,0,'','');
-- Jagged Shards ... Prev: Death's Gaze AND Destroying the Altars
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13136;
DELETE FROM conditions WHERE SourceEntry = 13136 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13136,0,8,13120,0,0,0,'',''),
(19,0,13136,0,8,13120,0,0,0,'',''),
(20,0,13136,0,8,13119,0,0,0,'',''),
(19,0,13136,0,8,13119,0,0,0,'','');

-- The Runesmiths of Malykriss ... Prev: Jagged Shards     
UPDATE quest_template SET PrevQuestId = 13136, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13140;
-- I'm Smelting... Smelting! ... Prev: Jagged Shards
UPDATE quest_template SET PrevQuestId = 13136, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13138;
-- By Fire Be Purged ... Prev: I'm Smelting... Smelting! AND The Runesmiths of Malykriss AND Spill Their Blood 
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13211;
DELETE FROM conditions WHERE SourceEntry = 13211 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13211,0,8,13140,0,0,0,'',''),
(19,0,13211,0,8,13140,0,0,0,'',''),
(20,0,13211,0,8,13134,0,0,0,'',''),
(19,0,13211,0,8,13134,0,0,0,'',''),
(20,0,13211,0,8,13138,0,0,0,'',''),
(19,0,13211,0,8,13138,0,0,0,'','');
-- A Visit to the Doctor ... Prev: I'm Smelting... Smelting! AND The Runesmiths of Malykriss AND Spill Their Blood 
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13152;
DELETE FROM conditions WHERE SourceEntry = 13152 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13152,0,8,13140,0,0,0,'',''),
(19,0,13152,0,8,13140,0,0,0,'',''),
(20,0,13152,0,8,13134,0,0,0,'',''),
(19,0,13152,0,8,13134,0,0,0,'',''),
(20,0,13152,0,8,13138,0,0,0,'',''),
(19,0,13152,0,8,13138,0,0,0,'','');

-- Killing Two Scourge With One Skeleton ... Prev: A Visit to the Doctor AND By Fire Be Purged
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13144;
DELETE FROM conditions WHERE SourceEntry = 13144 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13144,0,8,13152,0,0,0,'',''),
(19,0,13144,0,8,13152,0,0,0,'',''),
(20,0,13144,0,8,13211,0,0,0,'',''),
(19,0,13144,0,8,13211,0,0,0,'','');

-- Let's Get Out of Here A ... Prev: Killing Two Scourge With One Skeleton 
UPDATE quest_template SET PrevQuestId = 13144, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13482;
-- Let's Get Out of Here H ... Prev: Killing Two Scourge With One Skeleton
UPDATE quest_template SET PrevQuestId = 13144, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13481;
-- He's Gone to Pieces ... Prev: Killing Two Scourge With One Skeleton ... NextQuestInChain: Putting Olakin Back Together Again
UPDATE quest_template SET PrevQuestId = 13144, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13220 WHERE entry = 13212;
-- Putting Olakin Back Together Again ... Prev: He's Gone to Pieces ... NextQuestInChain: The Flesh Giant Champion
UPDATE quest_template SET PrevQuestId = 13212, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13235 WHERE entry = 13220;
-- The Flesh Giant Champion ... Prev: Putting Olakin Back Together Again
UPDATE quest_template SET PrevQuestId = 13220, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13235;

-- ####################################################

-- Exploiting an Opening(A) ... Prev: The SkyBreaker AND The ShadowVault ... NextQuestInChain: Securing the Perimeter
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13387 WHERE entry = 13386;
DELETE FROM conditions WHERE SourceEntry = 13386 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13386,0,8,12898,0,0,0,'',''),
(19,0,13386,0,8,12898,0,0,0,'',''),
(20,0,13386,0,8,13225,0,0,0,'',''),
(19,0,13386,0,8,13225,0,0,0,'','');
-- Securing the Perimeter ... Prev: Exploiting an Opening ... NextQuestInChain: Set it Off!
UPDATE quest_template SET PrevQuestId = 13386, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13388 WHERE entry = 13387;
-- Set it Off! ... Prev: Securing the Perimeter ... NextQuestInChain: A Short Fuse
UPDATE quest_template SET PrevQuestId = 13387, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13389 WHERE entry = 13388;
-- A Short Fuse ... Prev: Set it Off! ... NextQuestInChain: A Voice in the Dark
UPDATE quest_template SET PrevQuestId = 13388, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13390 WHERE entry = 13389;
-- A Voice in the Dark ... Prev: A Short Fuse ... NextQuestInChain: Time to Hide
UPDATE quest_template SET PrevQuestId = 13389, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13391 WHERE entry = 13390;
--  Time to Hide ... Prev:  A Voice in the Dark ... NextQuestInChain: Return to the Surface
UPDATE quest_template SET PrevQuestId = 13390, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13392 WHERE entry = 13391;
-- Return to the Surface ... Prev: Time to Hide ... NextQuestInChain: Field Repairs
UPDATE quest_template SET PrevQuestId = 13391, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13393 WHERE entry = 13392;
-- Field Repairs ... Prev: Return to the Surface 
UPDATE quest_template SET PrevQuestId = 13392, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13393;

-- Do Your Worst ... Prev: Field Repairs ... NextQuestInChain: Army of the Damned
UPDATE quest_template SET PrevQuestId = 13393, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13395 WHERE entry = 13394;
-- Army of the Damned ... Prev: Do Your Worst ... NextQuestInChain: Futility
UPDATE quest_template SET PrevQuestId = 13394, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13396 WHERE entry = 13395;
-- Futility ... Prev: Army of the Damned ... NextQuestInChain: Sindragosa's Fall
UPDATE quest_template SET PrevQuestId = 13395, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13397 WHERE entry = 13396;
-- Sindragosa's Fall ... Prev: Futility 
UPDATE quest_template SET PrevQuestId = 13396, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13397;

-- Where Dragons Fell ... Prev: Futility ... NextQuestInChain:	Time for Answers	
UPDATE quest_template SET PrevQuestId = 13396, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13399 WHERE entry = 13398;
-- Time for Answers ... Prev: Where Dragons Fell ... NextQuestInChain: The Hunter and the Prince
UPDATE quest_template SET PrevQuestId = 13398, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13400 WHERE entry = 13399;
-- The Hunter and the Prince ... Prev: Time for Answers ... NextQuestInChain: Knowledge is a Terrible Burden
UPDATE quest_template SET PrevQuestId = 13399, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13401 WHERE entry = 13400;
-- Knowledge is a Terrible Burden ... Prev: The Hunter and the Prince ... NextQuestInChain: Tirion's Help
UPDATE quest_template SET PrevQuestId = 13400, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13402 WHERE entry = 13401;
-- Tirion's Help ... Prev: Knowledge is a Terrible Burden ... NextQuestInChain: Tirion's Gambit
UPDATE quest_template SET PrevQuestId = 13401, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13403 WHERE entry = 13402;
-- Tirion's Gambit ... Prev: Tirion's Help
UPDATE quest_template SET PrevQuestId = 13402, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13403;

-- ####################################################

-- Opportunity ... Prev: Orgrim's Hammer AND The ShadowVault ... NextQuestInChain: Establishing Superiority
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13259 WHERE entry = 13258;
DELETE FROM conditions WHERE SourceEntry = 13258 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13258,0,8,13224,0,0,0,'',''),
(19,0,13258,0,8,13224,0,0,0,'',''),
(20,0,13258,0,8,12899,0,0,0,'',''),
(19,0,13258,0,8,12899,0,0,0,'','');

-- Establishing Superiority ... Prev: Opportunity ... NextQuestInChain: Blow it Up!
UPDATE quest_template SET PrevQuestId = 13258, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13262 WHERE entry = 13259;
-- Blow it Up! ... Prev:  Establishing Superiority ... NextQuestInChain: A Short Fuse
UPDATE quest_template SET PrevQuestId = 13259, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13263 WHERE entry = 13262;
-- A Short Fuse ... Prev: Blow it Up! ... NextQuestInChain: A Voice in the Dark
UPDATE quest_template SET PrevQuestId = 13262, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13271 WHERE entry = 13263;
-- A Voice in the Dark ... Prev: A Short Fuse ... NextQuestInChain: Time to Hide
UPDATE quest_template SET PrevQuestId = 13263, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13275 WHERE entry = 13271;
-- Time to Hide ... Prev: A Voice in the Dark ... NextQuestInChain: Return to the Surface
UPDATE quest_template SET PrevQuestId = 13271, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13282 WHERE entry = 13275;
-- Return to the Surface ... Prev: Time to Hide ... NextQuestInChain: Field Repairs
UPDATE quest_template SET PrevQuestId = 13275, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13304 WHERE entry = 13282;
-- Field Repairs ... Prev: Return to the Surface
UPDATE quest_template SET PrevQuestId = 13282, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13304;

-- Do Your Worst ... Prev: Field Repairs ... NextQuestInChain: Army of the Damned
UPDATE quest_template SET PrevQuestId = 13304, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13236 WHERE entry = 13305;
-- Army of the Damned ... Prev: Do Your Worst ... NextQuestInChain: Futility
UPDATE quest_template SET PrevQuestId = 13305, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13348 WHERE entry = 13236;
-- Futility ... Prev: Army of the Damned ... NextQuestInChain: Cradle of the Frostbrood
UPDATE quest_template SET PrevQuestId = 13236, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13349 WHERE entry = 13348;
-- Cradle of the Frostbrood ... Prev: Futility
UPDATE quest_template SET PrevQuestId = 13348, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13349;

-- Where Dragons Fell ... Prev: Futility
UPDATE quest_template SET PrevQuestId = 13349, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13359;
-- Time for Answers ... Prev: Where Dragons Fell ... NextQuestInChain: The Hunter and the Prince
UPDATE quest_template SET PrevQuestId = 13359, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13361 WHERE entry = 13360;
-- The Hunter and the Prince ... Prev: Time for Answers ... NextQuestInChain: Knowledge is a Terrible Burden
UPDATE quest_template SET PrevQuestId = 13360, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13362 WHERE entry = 13361;
-- Knowledge is a Terrible Burden ... Prev: The Hunter and the Prince
UPDATE quest_template SET PrevQuestId = 13361, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13362;

-- Argent Aid ... Prev: Knowledge is a Terrible Burden ... NextQuestInChain: Tirion's Gambit
UPDATE quest_template SET PrevQuestId = 13362, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13364 WHERE entry = 13363;
-- Tirion's Gambit ... Prev: Argent Aid
UPDATE quest_template SET PrevQuestId = 13363, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13364;

-- ###############################

-- Parting Gifts ... Prev: A Short Fuse A OR A Short Fuse H
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13168;
DELETE FROM conditions WHERE SourceEntry = 13168 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13168,0,8,13263,0,0,0,'',''),
(19,0,13168,0,8,13263,0,0,0,'',''),
(20,0,13168,1,8,13389,0,0,0,'',''),
(19,0,13168,1,8,13389,0,0,0,'','');

-- An Undead's Best Friend ... Prev: Parting Gifts
UPDATE quest_template SET PrevQuestId = 13168, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13169;
-- Honor is for the Weak ... Prev: Parting Gifts
UPDATE quest_template SET PrevQuestId = 13168, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13170;
-- From Whence They Came ... Prev: Parting Gifts
UPDATE quest_template SET PrevQuestId = 13168, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13171;

-- Seeds of Chaos ... Prev: An Undead's Best Friend AND Honor is for the Weak AND From Whence They Came
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13172;
DELETE FROM conditions WHERE SourceEntry = 13172 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13172,0,8,13169,0,0,0,'',''),
(19,0,13172,0,8,13169,0,0,0,'',''),
(20,0,13172,0,8,13170,0,0,0,'',''),
(19,0,13172,0,8,13170,0,0,0,'',''),
(20,0,13172,0,8,13171,0,0,0,'',''),
(19,0,13172,0,8,13171,0,0,0,'','');
-- Amidst the Confusion ... Prev: An Undead's Best Friend AND Honor is for the Weak AND From Whence They Came
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13174;
DELETE FROM conditions WHERE SourceEntry = 13174 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13174,0,8,13169,0,0,0,'',''),
(19,0,13174,0,8,13169,0,0,0,'',''),
(20,0,13174,0,8,13170,0,0,0,'',''),
(19,0,13174,0,8,13170,0,0,0,'',''),
(20,0,13174,0,8,13171,0,0,0,'',''),
(19,0,13174,0,8,13171,0,0,0,'','');

-- Vereth the Cunning ... Prev: Amidst the Confusion AND Seeds of Chaos ... NextQuestInChain: New Recruit
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13143 WHERE entry = 13155;
DELETE FROM conditions WHERE SourceEntry = 13155 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13155,0,8,13174,0,0,0,'',''),
(19,0,13155,0,8,13174,0,0,0,'',''),
(20,0,13155,0,8,13172,0,0,0,'',''),
(19,0,13155,0,8,13172,0,0,0,'','');

-- New Recruit ... Prev: Vereth the Cunning ... NextQuestInChain: The Vile Hold
UPDATE quest_template SET PrevQuestId = 13155, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13145 WHERE entry = 13143;
-- The Vile Hold ... Prev: New Recruit
UPDATE quest_template SET PrevQuestId = 13143, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13145;

-- Generosity Abounds ... Prev: The Vile Hold
UPDATE quest_template SET PrevQuestId = 13145, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13146;
-- Stunning View ... Prev: The Vile Hold
UPDATE quest_template SET PrevQuestId = 13145, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13160;
-- Matchmaker ... Prev: The Vile Hold
UPDATE quest_template SET PrevQuestId = 13145, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13147;

-- The Rider of the Unholy ... Prev: Generosity Abounds AND Stunning View AND Matchmaker
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13161;
DELETE FROM conditions WHERE SourceEntry = 13161 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13161,0,8,13146,0,0,0,'',''),
(19,0,13161,0,8,13146,0,0,0,'',''),
(20,0,13161,0,8,13160,0,0,0,'',''),
(19,0,13161,0,8,13160,0,0,0,'',''),
(20,0,13161,0,8,13147,0,0,0,'',''),
(19,0,13161,0,8,13147,0,0,0,'','');
-- The Rider of the Frost ... Prev: Generosity Abounds AND Stunning View AND Matchmaker
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13162;
DELETE FROM conditions WHERE SourceEntry = 13162 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13162,0,8,13146,0,0,0,'',''),
(19,0,13162,0,8,13146,0,0,0,'',''),
(20,0,13162,0,8,13160,0,0,0,'',''),
(19,0,13162,0,8,13160,0,0,0,'',''),
(20,0,13162,0,8,13147,0,0,0,'',''),
(19,0,13162,0,8,13147,0,0,0,'','');
-- The Rider of the Blood ... Prev: Generosity Abounds AND Stunning View AND Matchmaker
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13163;
DELETE FROM conditions WHERE SourceEntry = 13163 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13163,0,8,13146,0,0,0,'',''),
(19,0,13163,0,8,13146,0,0,0,'',''),
(20,0,13163,0,8,13160,0,0,0,'',''),
(19,0,13163,0,8,13160,0,0,0,'',''),
(20,0,13163,0,8,13147,0,0,0,'',''),
(19,0,13163,0,8,13147,0,0,0,'','');

-- The Fate of Bloodbane ... Prev: The Rider of the Blood AND Frost AND Unholy
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13164;
DELETE FROM conditions WHERE SourceEntry = 13164 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13164,0,8,13161,0,0,0,'',''),
(19,0,13164,0,8,13161,0,0,0,'',''),
(20,0,13164,0,8,13162,0,0,0,'',''),
(19,0,13164,0,8,13162,0,0,0,'',''),
(20,0,13164,0,8,13163,0,0,0,'',''),
(19,0,13164,0,8,13163,0,0,0,'','');

-- ##########################  Crusaders' Pinnacle ##########################

-- Judgment Day Comes! Allianz ... Next Quest: Honor Above All Else
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 13036, ExclusiveGroup = 13226, NextQuestInChain = 0 WHERE entry = 13226;

-- Judgment Day Comes! Horde ... Next Quest: Honor Above All Else
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 13036, ExclusiveGroup = 13226, NextQuestInChain = 0 WHERE entry = 13227;

-- Wenn das nicht funktioniert:
-- Honor Above All Else ... Prev: Judgment Day Comes! Allianz ODER Judgment Day Comes! Horde ... NextInChain: Scourge Tactics
-- DELETE FROM conditions WHERE SourceEntry = 13036 AND SourceTypeOrReferenceId IN (20,19);
-- INSERT INTO conditions VALUES
-- (20,0,13036,0,8,13226,0,0,0,'',''),
-- (19,0,13036,0,8,13226,0,0,0,'',''),
-- (20,0,13036,1,8,13227,0,0,0,'',''),
-- (19,0,13036,1,8,13227,0,0,0,'','');
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13008 WHERE entry = 13036;

-- Scourge Tactics ... Prev: Honor Above All Else
UPDATE quest_template SET PrevQuestId = 13036, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13008;
-- Defending The Vanguard ... Prev: Honor Above All Else
UPDATE quest_template SET PrevQuestId = 13036, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13039;
-- Curing The Incurable ... Prev: Honor Above All Else
UPDATE quest_template SET PrevQuestId = 13036, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13040;

-- If There Are Survivors... Prev: Scourge Tactics AND Defending The Vanguard AND Curing The Incurable
-- NextInChain: Into The Wild Green Yonder
UPDATE quest_template SET ExclusiveGroup = -13008 WHERE entry = 13008;
UPDATE quest_template SET ExclusiveGroup = -13008 WHERE entry = 13039;
UPDATE quest_template SET ExclusiveGroup = -13008 WHERE entry = 13040;
UPDATE quest_template SET PrevQuestId = 13008, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13045 WHERE entry = 13044;
-- Into The Wild Green Yonder ... Prev:  If There Are Survivors ... NextInChain: A Cold Front Approaches
UPDATE quest_template SET PrevQuestId = 13044, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13070 WHERE entry = 13045;
-- A Cold Front Approaches ... Prev: Into The Wild Green Yonder ... NextInChain: The Last Line Of Defense
UPDATE quest_template SET PrevQuestId = 13045, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13086 WHERE entry = 13070;
-- The Last Line Of Defense ... Prev: A Cold Front Approaches
UPDATE quest_template SET PrevQuestId = 13070, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13086;

-- Tirions Mount
DELETE FROM `creature_template_addon` WHERE `entry` IN (30677);
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(30677,0,2325,0,0,0,'');  -- Tirion Fordring - Mount

-- Once More Unto The Breach, Hero
-- Once More Unto The Breach, Hero  DK only
UPDATE quest_template SET PrevQuestId = 13086, NextQuestId = 0, ExclusiveGroup = 13104, NextQuestInChain = 0 WHERE entry = 13104;
UPDATE quest_template SET PrevQuestId = 13086, NextQuestId = 0, ExclusiveGroup = 13104, NextQuestInChain = 0 WHERE entry = 13105;

-- The Scourgestone ... Prev: Once More Unto The Breach, Hero ODER Once More Unto The Breach, Hero DK only
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13122;
DELETE FROM conditions WHERE SourceEntry = 13122 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13122,0,8,13104,0,0,0,'',''),
(19,0,13122,0,8,13104,0,0,0,'',''),
(20,0,13122,1,8,13105,0,0,0,'',''),
(19,0,13122,1,8,13105,0,0,0,'','');

-- The Purging Of Scourgeholme ... Prev: Once More Unto The Breach, Hero ODER Once More Unto The Breach, Hero DK only
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13118;
DELETE FROM conditions WHERE SourceEntry = 13118 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13118,0,8,13104,0,0,0,'',''),
(19,0,13118,0,8,13104,0,0,0,'',''),
(20,0,13118,1,8,13105,0,0,0,'',''),
(19,0,13118,1,8,13105,0,0,0,'','');

-- The Restless Dead ... Prev: Once More Unto The Breach, Hero ODER Once More Unto The Breach, Hero DK only
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13110;
DELETE FROM conditions WHERE SourceEntry = 13110 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13110,0,8,13104,0,0,0,'',''),
(19,0,13110,0,8,13104,0,0,0,'',''),
(20,0,13110,1,8,13105,0,0,0,'',''),
(19,0,13110,1,8,13105,0,0,0,'','');


-- It Could Kill Us All ... Prev: Once More Unto The Breach, Hero ODER Once More Unto The Breach, Hero DK only
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13135;
DELETE FROM conditions WHERE SourceEntry = 13135 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13135,0,8,13104,0,0,0,'',''),
(19,0,13135,0,8,13104,0,0,0,'',''),
(20,0,13135,1,8,13105,0,0,0,'',''),
(19,0,13135,1,8,13105,0,0,0,'','');

-- The Stone That Started A Revolution ... Prev: Once More Unto The Breach, Hero ODER Once More Unto The Breach, Hero DK only
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13130;
DELETE FROM conditions WHERE SourceEntry = 13130 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13130,0,8,13104,0,0,0,'',''),
(19,0,13130,0,8,13104,0,0,0,'',''),
(20,0,13130,1,8,13105,0,0,0,'',''),
(19,0,13130,1,8,13105,0,0,0,'','');

-- The Air Stands Still ... Prev: The Scourgestone UND The Purging Of Scourgeholme
UPDATE quest_template SET NextQuestId = 13125, ExclusiveGroup = -13122 WHERE entry = 13122;
UPDATE quest_template SET NextQuestId = 13125, ExclusiveGroup = -13122 WHERE entry = 13118;
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13125;

-- Into The Frozen Heart Of Northrend ... Prev: The Air Stands Still AND The Restless Dead AND The Stone That Started A Revolution AND It Could Kill Us All
-- NextQuestInChain: The Battle For Crusaders' Pinnacle
UPDATE quest_template SET NextQuestId = 13139, ExclusiveGroup = -13135 WHERE entry = 13135;
UPDATE quest_template SET NextQuestId = 13139, ExclusiveGroup = -13135 WHERE entry = 13110;
UPDATE quest_template SET NextQuestId = 13139, ExclusiveGroup = -13135 WHERE entry = 13130;
UPDATE quest_template SET NextQuestId = 13139, ExclusiveGroup = -13135 WHERE entry = 13125;
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13141 WHERE entry = 13139;

-- The Battle For Crusaders' Pinnacle ... Prev: Into The Frozen Heart Of Northrend ... NextQuestInChain: The Crusaders' Pinnacle
UPDATE quest_template SET PrevQuestId = 13139, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13157 WHERE entry = 13141;
-- The Crusaders' Pinnacle ... PRev: The Battle For Crusaders' Pinnacle
UPDATE quest_template SET PrevQuestId = 13141, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13157;

-- ##########################  Orgrim's Hammer ##########################

--
-- DELETE FROM `creature_transport` WHERE `guid`=77 AND `transport_entry`=192241 AND `npc_entry`=31261;
-- INSERT INTO `creature_transport` (`guid`,`transport_entry`,`npc_entry`,`TransOffsetX`,`TransOffsetY`,`TransOffsetZ`,`TransOffsetO`,`emote`) VALUES
-- (77,192241,31261,52.5,5.3,30.5268,3.94314,0);


-- Orgrim's Hammer ... Prequest Crusader Pinacle
UPDATE quest_template SET PrevQuestId = 13157, NextQuestId = 0, ExclusiveGroup = 13225, NextQuestInChain = 0 WHERE entry = 13224;
-- Expoiting a Openinig ... Prev: Orgrim's Hammer AND The Shadow Vault - Next in Chain: Securing the Perimeter
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13224;
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13259 WHERE entry = 13258;
DELETE FROM conditions WHERE SourceEntry = 13258 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13258,0,8,12899,0,0,0,'',''),
(19,0,13258,0,8,12899,0,0,0,'',''),
(20,0,13258,0,8,13224,0,0,0,'',''),
(19,0,13258,0,8,13224,0,0,0,'','');


-- Blood of the Choosen ... Prev: Orgrim's Hammer
UPDATE quest_template SET PrevQuestId = 13224, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13330;
-- Joining the Assault ... Prev: Orgrim's Hammer
UPDATE quest_template SET PrevQuestId = 13224, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13340;
-- -- Assault by ... Prev: Joining the Assault
UPDATE quest_template SET PrevQuestId = 13340, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13310;
UPDATE quest_template SET PrevQuestId = 13340, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13301;

-- Mind Tricks ... Prev: Orgrim's Hammer
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13308;
DELETE FROM conditions WHERE SourceEntry = 13308 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13308,0,8,13225,0,0,0,'',''),
(19,0,13308,0,8,13225,0,0,0,'',''),
(20,0,13308,1,8,13224,0,0,0,'',''),
(19,0,13308,1,8,13224,0,0,0,'','');
-- Slaves to Saronite ... Prev: Orgrim's Hammer
UPDATE quest_template SET PrevQuestId = 13224, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13302;
-- Get to Ymirheim! ... Prev: Orgrim's Hammer ... NextChain: King of the Mountain
UPDATE quest_template SET PrevQuestId = 13224, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13283 WHERE entry = 13293;
-- -- King of the Mountain ... Prev Get to Ymirheim
UPDATE quest_template SET PrevQuestId = 13293, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13283;

-- The Broken Front ... Prev: Orgrim's Hammer
UPDATE quest_template SET PrevQuestId = 13224, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13228;
-- -- Avenge me... Prev: Orgrim's Hammer
UPDATE quest_template SET PrevQuestId = 13224, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13230;
-- Make Them Pay! ... Prev: The Broken Front
UPDATE quest_template SET PrevQuestId = 13228, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13234;

-- Good For Something? ... Prev: The Broken Front ... Next in Chain: Volatility
UPDATE quest_template SET PrevQuestId = 13228, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13239 WHERE entry = 13238;
-- -- Volatility
UPDATE quest_template SET PrevQuestId = 13238, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13239;
-- -- -- Volatility Daily ... Prev: Volatility
UPDATE quest_template SET PrevQuestId = 13239, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13261;
-- -- Green Technology ... Prev: Volatility ... NextinChain: Fringe Science Benefits
UPDATE quest_template SET PrevQuestId = 13239, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13373 WHERE entry = 13379;
-- -- -- Fringe Science Benefits
UPDATE quest_template SET PrevQuestId = 13379, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13373;
-- -- -- -- Riding the Wavelength: The Bombardment ... Prev: Fringe Science Benefits
UPDATE quest_template SET PrevQuestId = 13373, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13406;
-- -- -- -- Total Ohmage: The Valley of Lost Hope! ... Prev: Fringe Science Benefits
UPDATE quest_template SET PrevQuestId = 13373, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13376;

-- Takes One to Know One ... Prev: The Broken Front ... NextInChain: Poke and Prod
UPDATE quest_template SET PrevQuestId = 13228, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13237 WHERE entry = 13260;
-- Poke and Prod ... Prev: Takes One to Know One
UPDATE quest_template SET PrevQuestId =  13260, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13237;

-- Against the Giants ... Prev: Poke and Prod ... Next in Chain: Basic Chemistry
UPDATE quest_template SET PrevQuestId = 13237, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13279 WHERE entry = 13277;
-- Coprous the Defiled ... Prev: Against the Giants
UPDATE quest_template SET PrevQuestId = 13277, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13278;
-- Basic Chemistry ... Prev: Against the Giants
UPDATE quest_template SET PrevQuestId = 13277, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13279;
-- -- Neutralizing the Plague ... Prev: Basic Chemistry
UPDATE quest_template SET PrevQuestId = 13279, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13281;

-- That's Abominable! ... Prev: Poke and Prod 
UPDATE quest_template SET PrevQuestId = 13237, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13264;
-- -- That's Abominable! Daily ... Prev: That's Abominable!
UPDATE quest_template SET PrevQuestId = 13264, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13276;

-- Sneak Preview ... Prev: That's Abominable!
UPDATE quest_template SET PrevQuestId = 13264, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13351;
-- Chain of Command ... Prev: Sneak Preview
UPDATE quest_template SET PrevQuestId = 13351, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13354;
-- Cannot Reproduce ... Prev: Sneak Preview ... Next In Chain: Retest Now
UPDATE quest_template SET PrevQuestId = 13351, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13356 WHERE entry = 13355;
-- -- Retest Now ... Prev: Cannot Reproduce
UPDATE quest_template SET PrevQuestId = 13355, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13356;
-- -- Retest Now Daily ... Prev: Retest Now
UPDATE quest_template SET PrevQuestId = 13356, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13357;

-- Drag and Drop ... Prev: Sneak Preview  
UPDATE quest_template SET PrevQuestId = 13351, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13352;
-- -- Drag and Drop Daily ... Prev: Drag and Drop
UPDATE quest_template SET PrevQuestId = 13352, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13353;
-- -- Not a Bug ... Prev: Drag and Drop
UPDATE quest_template SET PrevQuestId = 13352, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13358;
-- -- -- Not a Bug Daily ... Prev: Not a Bug
UPDATE quest_template SET PrevQuestId = 13358, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13365;

-- Need more Info ... Prev: Drag and Drop ... Next in Chain: No Rest For The Wicked
UPDATE quest_template SET PrevQuestId = 13352, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13367 WHERE entry = 13366;
-- No Rest For the Wicked ... Prev: Need more Info 
UPDATE quest_template SET PrevQuestId = 13366, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13367;
-- -- No Rest For the Wicked Daily ... Prev: No Rest For the Wicked
UPDATE quest_template SET PrevQuestId = 13367, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13368;
-- Raise the Barricades ... Prev: Need more Info 
UPDATE quest_template SET PrevQuestId = 13366, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13306;

-- The Ironwall Rampart ... Prev: Raise the Barricades AND No Rest For the Wicked
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13312;
-- * NextQuestId not used yet so:
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13306;
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13367;
DELETE FROM conditions WHERE SourceEntry = 13312 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13312,0,8,13306,0,0,0,'',''),
(19,0,13312,0,8,13306,0,0,0,'',''),
(20,0,13312,0,8,13367,0,0,0,'',''),
(19,0,13312,0,8,13367,0,0,0,'','');

-- Blinding the Eyes in the Sky ... Prev: Raise the Barricades
UPDATE quest_template SET PrevQuestId = 13306, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13313;
-- -- Keeping the Alliance Blind ... Prev: Blinding the Eyes in the Sky
UPDATE quest_template SET PrevQuestId = 13313, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13331;
-- Bloodspattered Banners ... Prev: Raise the Barricades
UPDATE quest_template SET PrevQuestId = 13306, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13307;
-- Before the Gate of Horror ... Prev:  Bloodspattered Banners AND The Ironwall Rampart
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13329;
-- * NextQuestId not used yet so:
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13307;
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13312;
DELETE FROM conditions WHERE SourceEntry = 13329 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13329,0,8,13307,0,0,0,'',''),
(19,0,13329,0,8,13307,0,0,0,'',''),
(20,0,13329,0,8,13312,0,0,0,'',''),
(19,0,13329,0,8,13312,0,0,0,'','');

-- Shatter the Shards ... Prev: Before the Gate of Horror
UPDATE quest_template SET PrevQuestId = 13329, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13328;
-- The Guardians of Corp'rethar ... Prev: Before the Gate of Horror
UPDATE quest_template SET PrevQuestId = 13329, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13316;

-- ##########################  The Shadow Vault #########################

-- If He Cannot Be Turned Alliance ... Prev: Non ... NextInChain: The Shadow Vault
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12898 WHERE entry = 12896;
-- If He Cannot Be Turned Horde ... Prev: Non ... NextInChain: The Shadow Vault
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12899 WHERE entry = 12897;
-- The Shadow Vault Alliance... Prev: If He Cannot Be Turned Alliance ... NextInChain: The Duke
UPDATE quest_template SET PrevQuestId = 12896, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12938 WHERE entry = 12898;
-- The Shadow Vault Horde... Prev: If He Cannot Be Turned Alliance ... NextInChain: The Duke
UPDATE quest_template SET PrevQuestId = 12897, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12938 WHERE entry = 12899;
-- The Duke... Prev: The Shadow Vault Alliance OR Horde ... NextInChain: Honor Challenge
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12939 WHERE entry = 12938;
DELETE FROM conditions WHERE SourceEntry = 12938 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,12938,0,8,12898,0,0,0,'',''),
(19,0,12938,0,8,12898,0,0,0,'',''),
(20,0,12938,1,8,12899,0,0,0,'',''),
(19,0,12938,1,8,12899,0,0,0,'','');

-- Honor Challenge ... Prev: The Duke ... NextInChain: Shadow Vault Decree
UPDATE quest_template SET PrevQuestId = 12938, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12943 WHERE entry = 12939;
-- Shadow Vault Decree ... Prev: Honor Challenge
UPDATE quest_template SET PrevQuestId = 12939, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12943;

-- Get the Key ... Prev: Honor Challenge ... NextInChain: Let the Baron Know
UPDATE quest_template SET PrevQuestId = 12938, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12951 WHERE entry = 12949;
-- Let the Baron Know ... Prev: Get the Key 
UPDATE quest_template SET PrevQuestId = 12949, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12951;

-- Vandalizing Jotunheim ... Prev: Let the Baron Know AND Shadow Vault Decree 
UPDATE quest_template SET PrevQuestId = 12943, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13084;
DELETE FROM conditions WHERE SourceEntry = 13084 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13084,0,8,12951,0,0,0,'',''),
(19,0,13084,0,8,12951,0,0,0,'',''),
(20,0,13084,0,8,12943,0,0,0,'',''),
(19,0,13084,0,8,12943,0,0,0,'','');
-- Leave Our Mark ... Prev: Let the Baron Know AND Shadow Vault Decree 
UPDATE quest_template SET PrevQuestId = 12943, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12995;
DELETE FROM conditions WHERE SourceEntry = 12995 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,12995,0,8,12951,0,0,0,'',''),
(19,0,12995,0,8,12951,0,0,0,'',''),
(20,0,12995,0,8,12943,0,0,0,'',''),
(19,0,12995,0,8,12943,0,0,0,'','');

/*
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 23301;
INSERT INTO conditions VALUES
(13,0,23301,0,18,2,29880,0,0,'',''),
(13,0,23301,0,18,2,30243,0,0,'',''),
(13,0,23301,0,18,2,30632,0,0,'',''),
(13,0,23301,0,18,2,30725,0,0,'','');
*/

-- Crush Dem Vrykuls! ... Prev: Let the Baron Know AND Shadow Vault Decree ... NextInChain: Vile Like Fire!
UPDATE quest_template SET PrevQuestId = 12943, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13071 WHERE entry = 12992;
DELETE FROM conditions WHERE SourceEntry = 12992 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,12992,0,8,12951,0,0,0,'',''),
(19,0,12992,0,8,12951,0,0,0,'',''),
(20,0,12992,0,8,12943,0,0,0,'',''),
(19,0,12992,0,8,12943,0,0,0,'','');
-- -- Vile Like Fire! ... Prev: Crush Dem Vrykuls!
UPDATE quest_template SET PrevQuestId = 12992, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13071;

-- Vaelen Has Returned ... Prev: Let the Baron Know AND Shadow Vault Decree ... NextInChain: Ebon Blade Prisoners
UPDATE quest_template SET PrevQuestId = 12943, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12982 WHERE entry = 13085;
-- Ebon Blade Prisoners ... Prev: Vaelen Has Returned
UPDATE quest_template SET PrevQuestId = 13085, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12982;
-- -- Shoot 'Em Up ... Prev: Ebon Blade Prisoners
UPDATE quest_template SET PrevQuestId = 12982, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13069;

-- To the Rise with all Due Haste! ... Prev: Ebon Blade Prisoners ... NextInChain: The Story Thus Far...
UPDATE quest_template SET PrevQuestId = 12982, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12807 WHERE entry = 12806;
-- The Story Thus Far... ... Prev: To the Rise with all Due Haste! ... NextInChain: Blood in the Water 
UPDATE quest_template SET PrevQuestId = 12806, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12810 WHERE entry = 12807;
-- Blood in the Water ... Prev: The Story Thus Far... ... NextInChain: You'll Need a Gryphon
UPDATE quest_template SET PrevQuestId = 12807, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12814 WHERE entry = 12810;
-- You'll Need a Gryphon
UPDATE quest_template SET PrevQuestId = 12810, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12814;
-- Fix for "You'll Need a Gryphon"
UPDATE `creature_template` SET `spell1`=54420  , `VehicleId`=165  , `InhabitType`=7 WHERE `entry` = 29403;
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 17 AND SourceEntry = 54420;
INSERT INTO conditions VALUES
(17,0,54420,0,29,29405,10,0,0,'','Deliver Gryphon only near Uzo Deathcaller');

-- -- From Their Corpses, Rise! ... Prev: The Story Thus Far...
UPDATE quest_template SET PrevQuestId = 12807, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12813;
-- -- No Fly Zone ... Prev: You'll Need a Gryphon
UPDATE quest_template SET PrevQuestId = 12814, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12815;
-- -- Intelligence Gathering ... Prev: The Story Thus Far...
UPDATE quest_template SET PrevQuestId = 12807, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12838;
-- -- -- The Grand (Admiral's) Plan ... Prev:  The Story Thus Far... ... NextInChain: In Strict Confidence
UPDATE quest_template SET PrevQuestId = 12807, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12840 WHERE entry = 12839;
-- -- -- In Strict Confidence ... Prev: The Grand (Admiral's) Plan ... NextInChain: Second Chances
UPDATE quest_template SET PrevQuestId = 12839, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12847 WHERE entry = 12840;
-- -- -- Second Chances ... Prev: In Strict Confidence ... NextInChain: The Admiral Revealed
UPDATE quest_template SET PrevQuestId = 12840, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12852 WHERE entry = 12847;
-- -- -- The Admiral Revealed ... Prev: Second Chances
UPDATE quest_template SET PrevQuestId = 12847, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12852;

-- Eliminate the Competition ... Prev: The Duke ... NextInChain: The Bone Witch
UPDATE quest_template SET PrevQuestId = 12938, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 12999 WHERE entry = 12955;
-- The Bone Witch ... Prev: Eliminate the Competition
UPDATE quest_template SET PrevQuestId = 12955, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 12999;
-- -- Reading the Bones ... Prev: The Bone Witch
UPDATE quest_template SET PrevQuestId = 12999, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13092;
-- -- Reading the Bones Repeatable ... Prev: Reading the Bones
UPDATE quest_template SET PrevQuestId = 13092, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13093;

-- Deep in the Bowels of The Underhalls ... Prev: The Bone Witch
UPDATE quest_template SET PrevQuestId = 12999, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13042;
-- Revenge for the Vargul ... Prev: The Bone Witch
UPDATE quest_template SET PrevQuestId = 12999, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13059;

-- The Sum is Greater than the Parts ... Prev: The Bone Witch ... NextInChain: The Art of Being a Water Terror
UPDATE quest_template SET PrevQuestId = 12999, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13091 WHERE entry = 13043;
-- The Art of Being a Water Terror ... Prev: The Sum is Greater than the Parts ... NextInChain: Through the Eye
UPDATE quest_template SET PrevQuestId = 13043, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13121 WHERE entry = 13091;
--  Through the Eye ... Prev: The Art of Being a Water Terror ... NextInChain: Find the Ancient Hero
UPDATE quest_template SET PrevQuestId = 13091, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13133 WHERE entry = 13121;
-- Find the Ancient Hero ... Prev: Through the Eye  ... NextInChain: Not-So-Honorable Combat
UPDATE quest_template SET PrevQuestId = 13121, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13137 WHERE entry = 13133;
-- Not-So-Honorable Combat ... Prev: Find the Ancient Hero  ... NextInChain: Banshee's Revenge
UPDATE quest_template SET PrevQuestId = 13133, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13142 WHERE entry =13137;
-- Banshee's Revenge ... Prev: Not-So-Honorable Combat ... NextInChain: Battle at Valhalas
UPDATE quest_template SET PrevQuestId = 13137, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13213 WHERE entry = 13142;
-- Battle at Valhalas ... Prev: Banshee's Revenge
UPDATE quest_template SET PrevQuestId = 13142, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13213;

-- Battle at Valhalas: Fallen Heroes ... Prev: Battle at Valhalas
UPDATE quest_template SET PrevQuestId = 13213, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13214;
-- Battle at Valhalas: Khit'rix the Dark Master ... Prev: Battle at Valhalas: Fallen Heroes
UPDATE quest_template SET PrevQuestId = 13214, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13215;
-- Battle at Valhalas: The Return of Sigrid Iceborn ... Prev: Battle at Valhalas: Khit'rix the Dark Master
UPDATE quest_template SET PrevQuestId = 13215, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13216;
-- Battle at Valhalas: Carnage! ... Prev: Battle at Valhalas: The Return of Sigrid Iceborn
UPDATE quest_template SET PrevQuestId = 13216, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13217;
-- Battle at Valhalas: Thane Deathblow ... Prev: Battle at Valhalas: Carnage!
UPDATE quest_template SET PrevQuestId = 13217, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13218;
-- Battle at Valhalas: Final Challenge ... Prev: Battle at Valhalas: Thane Deathblow
UPDATE quest_template SET PrevQuestId = 13217, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13219;

-- ##########################  The Skybreaker ###########################

-- The Skybreaker ... Prequest Crusader Pinacle
UPDATE quest_template SET PrevQuestId = 13157, NextQuestId = 0, ExclusiveGroup = 13225, NextQuestInChain = 0 WHERE entry = 13225;
-- Expoiting a Openinig ... Prev: The Skybreaker AND The Shadow Vault - Next in Chain: Securing the Perimeter
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13225;
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13387 WHERE entry = 13386;
DELETE FROM conditions WHERE SourceEntry = 13386 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13386,0,8,12898,0,0,0,'',''),
(19,0,13386,0,8,12898,0,0,0,'',''),
(20,0,13386,0,8,13225,0,0,0,'',''),
(19,0,13386,0,8,13225,0,0,0,'','');

-- Blood of the Choosen ... Prev: The Skybreaker
UPDATE quest_template SET PrevQuestId = 13225, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13336;
-- Joining the Assault ... Prev: The Skybreaker
UPDATE quest_template SET PrevQuestId = 13225, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13341;
-- -- Assault by ... Prev: Joining the Assault
UPDATE quest_template SET PrevQuestId = 13341, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13309;
UPDATE quest_template SET PrevQuestId = 13341, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13284;

-- Mind Tricks ... Prev: Skybreaker OR Orgrims Hammer
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13308;
DELETE FROM conditions WHERE SourceEntry = 13308 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13308,0,8,13225,0,0,0,'',''),
(19,0,13308,0,8,13225,0,0,0,'',''),
(20,0,13308,1,8,13224,0,0,0,'',''),
(19,0,13308,1,8,13224,0,0,0,'','');
-- Slaves to Saronite ... Prev: Skybreaker
UPDATE quest_template SET PrevQuestId = 13225, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13300;
-- Get to Ymirheim! ... Prev: Skybreaker ... NextChain: King of the Mountain
UPDATE quest_template SET PrevQuestId = 13225, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13280 WHERE entry = 13296;
-- -- King of the Mountain ... Prev Get to Ymirheim
UPDATE quest_template SET PrevQuestId = 13296, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13280;

-- The Broken Front ... Prev: Skybreaker
UPDATE quest_template SET PrevQuestId = 13225, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13231;
-- -- Finish Me ... Prev: Skybreaker
UPDATE quest_template SET PrevQuestId = 13225, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13232;
-- No Mercy ... Prev: The Broken Front
UPDATE quest_template SET PrevQuestId = 13231, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13233;

-- Your Attention, Please ... Prev: The Broken Front ... Next in Chain: Borrowed Technology
UPDATE quest_template SET PrevQuestId = 13231, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13291 WHERE entry = 13290;
-- -- Borrowed Technology
UPDATE quest_template SET PrevQuestId = 13290, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13291;
-- -- -- The Solution Solution Prev: Borrowed Technology
UPDATE quest_template SET PrevQuestId = 13291, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13292;
-- -- Killohertz ... Prev: Borrowed Technology ... NextinChain: Leading the Charge
UPDATE quest_template SET PrevQuestId = 13291, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13380 WHERE entry = 13383;
-- -- -- Leading the Charge
UPDATE quest_template SET PrevQuestId = 13383, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13380;
-- -- -- -- Static Shock Troops: the Bombardment Prev: Leading the Charge
UPDATE quest_template SET PrevQuestId = 13380, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13404;
-- -- -- -- Putting the Hertz: The Valley of Lost Hope Prev: Leading the Charge
UPDATE quest_template SET PrevQuestId = 13380, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13382;

-- ...All the Help We Can Get. ... Prev: The Broken Front ... NextInChain: Poke and Prod
UPDATE quest_template SET PrevQuestId = 13231, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13287 WHERE entry = 13286;
-- Poke and Prod ... Prev: ...All the Help We Can Get.
UPDATE quest_template SET PrevQuestId = 13286, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13287;

-- Against the Giants ... Prev: Poke and Prod ... Next in Chain: Basic Chemistry
UPDATE quest_template SET PrevQuestId = 13287, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13295 WHERE entry = 13294;
-- Coprous the Defiled ... Prev: Against the Giants
UPDATE quest_template SET PrevQuestId = 13294, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13298;
-- Basic Chemistry ... Prev: Against the Giants
UPDATE quest_template SET PrevQuestId = 13294, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13295;
-- -- Neutralizing the Plague ... Prev: Basic Chemistry
UPDATE quest_template SET PrevQuestId = 13295, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13297;

-- That's Abominable! ... Prev: Poke and Prod 
UPDATE quest_template SET PrevQuestId = 13287, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13288;
-- -- That's Abominable! Daily ... Prev: That's Abominable!
UPDATE quest_template SET PrevQuestId = 13288, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13289;

-- Sneak Preview ... Prev: That's Abominable!
UPDATE quest_template SET PrevQuestId = 13288, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13315;
-- Chain of Command ... Prev: Sneak Preview
UPDATE quest_template SET PrevQuestId = 13315, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13319;
-- Cannot Reproduce ... Prev: Sneak Preview ... Next In Chain: Retest Now
UPDATE quest_template SET PrevQuestId = 13315, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13321 WHERE entry = 13320;
-- -- Retest Now ... Prev: Cannot Reproduce
UPDATE quest_template SET PrevQuestId = 13320, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13321;
-- -- Retest Now Daily ... Prev: Retest Now
UPDATE quest_template SET PrevQuestId = 13321, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13322;

-- Drag and Drop ... Prev: Sneak Preview  
UPDATE quest_template SET PrevQuestId = 13315, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13318;
-- -- Drag and Drop Daily ... Prev: Drag and Drop
UPDATE quest_template SET PrevQuestId = 13318, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13323;
-- -- Not a Bug ... Prev: Drag and Drop
UPDATE quest_template SET PrevQuestId = 13318, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13342;
-- -- -- Not a Bug Daily ... Prev: Not a Bug
UPDATE quest_template SET PrevQuestId = 13342, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13344;

-- Need more Info ... Prev: Drag and Drop ... Next in Chain: No Rest For The Wicked
UPDATE quest_template SET PrevQuestId = 13318, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 13346 WHERE entry = 13345;
-- No Rest For the Wicked ... Prev: Need more Info 
UPDATE quest_template SET PrevQuestId = 13345, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13346;
-- -- No Rest For the Wicked Daily ... Prev: No Rest For the Wicked
UPDATE quest_template SET PrevQuestId = 13346, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13350;
-- Raise the Barricades ... Prev: Need more Info 
UPDATE quest_template SET PrevQuestId = 13345, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13332;

-- The Ironwall Rampart ... Prev: Raise the Barricades AND No Rest For the Wicked
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13337;
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13346;
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13332;
DELETE FROM conditions WHERE SourceEntry = 13337 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13337,0,8,13346,0,0,0,'',''),
(19,0,13337,0,8,13346,0,0,0,'',''),
(20,0,13337,0,8,13332,0,0,0,'',''),
(19,0,13337,0,8,13332,0,0,0,'','');

-- Get the Message ... Prev: Raise the Barricades
UPDATE quest_template SET PrevQuestId = 13332, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13314;
-- -- Capture More Dispatches ... Prev: Get the Message
UPDATE quest_template SET PrevQuestId = 13314, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13333;
-- Bloodspattered Banners ... Prev: Raise the Barricades
UPDATE quest_template SET PrevQuestId = 13332, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13334;
-- Before the Gate of Horror ... Prev:  Bloodspattered Banners AND The Ironwall Rampart
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13335;
-- * NextQuestId not used yet so:
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13334;
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 13337;
DELETE FROM conditions WHERE SourceEntry = 13335 AND SourceTypeOrReferenceId IN (20,19);
INSERT INTO conditions VALUES
(20,0,13335,0,8,13334,0,0,0,'',''),
(19,0,13335,0,8,13334,0,0,0,'',''),
(20,0,13335,0,8,13337,0,0,0,'',''),
(19,0,13335,0,8,13337,0,0,0,'','');

-- Shatter the Shards ... Prev: Before the Gate of Horror
UPDATE quest_template SET PrevQuestId = 13335, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13339;
-- The Guardians of Corp'rethar ... Prev: Before the Gate of Horror
UPDATE quest_template SET PrevQuestId = 13335, NextQuestId = 0, ExclusiveGroup = 0, NextQuestInChain = 0 WHERE entry = 13338;

-- -------------------------------------------------------------------------
-- ------------------------------- QUESTS ----------------------------------
-- -------------------------------------------------------------------------
-- -------------------------------------------------------------------------
-- ---------------------------- Northrend ----------------------------------
-- -------------------------------------------------------------------------
-- Borean Tundra
-- Quest "Emergency Protocol: Section 8.2, Paragraph C"  http://www.wowhead.com/quest=11795 and Quest "Emergency Supplies" http://www.wowhead.com/quest=11887
UPDATE `creature_template` SET `npcflag` = `npcflag`|1, `AIName` = '', `ScriptName` = 'npc_recon_pilot' WHERE `entry` = 25841;
-- Despawn Wyrmrest Skytalons for Quest "Aces High!" http://www.wowhead.com/quest=13413 and http://www.wowhead.com/quest=13414 after 1 minute not in use
UPDATE `creature_template` SET scriptname = 'vehicle_wyrmrest_skytalon' WHERE entry = 32535;
-- Quest "The Power of the Elements" http://www.wowhead.com/quest=11893 increase Totem Range, script for npc "Steam Rager" http://www.wowhead.com/npc=24601, this npc has SmartAI too but need testing
UPDATE `creature_template` SET `ScriptName`='mob_steam_rager' WHERE `entry`=24601;
-- Quest "Emergency Protocol: Section 8.2, Paragraph D" http://www.wowhead.com/quest=11796 trigger
DELETE FROM `creature_template` WHERE `entry`=97000;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (97000, 0, 0, 0, 0, 0, 17519, 11686, 0, 0, 'q11796 trigger', '', '', 0, 80, 80, 0, 114, 114, 0, 1, 1.14286, 1, 0, 104, 138, 0, 252, 1, 2000, 0, 1, 33587968, 8, 0, 0, 0, 0, 0, 72, 106, 26, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1.35, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 130, 'npc_q11796_trigger', 12340);
-- trigger spawns
SET @GUID := 4000020;
DELETE FROM `creature` WHERE `id`=33089;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`) VALUES
(@GUID+00,97000,571,1,1,3604.6,5065,13.2919,5.39233,100),
(@GUID+02,97000,571,1,1,3476.66,4918.67,13.8639,4.62499,100),
(@GUID+03,97000,571,1,1,3355.87,5049.47,14.2951,6.05756,100);
-- spell conditions
DELETE FROM `conditions` WHERE `sourcetypeorreferenceid` = 13 AND `sourceentry` = 46171;
INSERT INTO `conditions` (`sourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `conditionvalue1`, `conditionvalue2`, `conditionvalue3`, `errortextid`, `comment`) VALUES
(13,46171,18,1,97000,0,1335,'q11796 - antorcha limitada al trigger 97000');
-- Quest "The Honored Dead" http://www.wowhead.com/quest=11593 & "Plan B"  http://www.wowhead.com/quest=11658
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_fallen_caravan_guard' WHERE `entry` IN (25342,25343);
-- cleanup
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (25342,25343);
-- Quest "The Collapse" http://www.wowhead.com/quest=11706 & "Deploy the Shake-n-Quake!" http://www.wowhead.com/quest=11723
UPDATE `creature_template` SET `KillCredit1` = 25742, `KillCredit2` = 25794 WHERE `entry` = 25629;
UPDATE `item_template` SET `ScriptName` = 'item_snq_control_unit' WHERE `entry` = 34981;
-- SAI for Steam Rager
SET @ENTRY := 24601;
UPDATE `creature_template` SET `ScriptName`='',`AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY; -- Remove EAI
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,11,36151,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Steam Rager - On spawn - Cast Cosmetic: Steam Aura on self'),
(@ENTRY,0,1,0,0,0,100,0,4000,8000,11000,14000,11,50375,1,0,0,0,0,2,0,0,0,0,0,0,0, 'Steam Rager - Combat - Cast Steam Blast on victom');
-- Quest "Postponing the Inevitable" http://www.wowhead.com/quest=11905
UPDATE `item_template` SET `ScriptName` = 'item_interdimensional_refabricator' WHERE `entry` = 35479;

-- Dalaran
INSERT INTO npc_text (ID,text0_0) VALUES 
(40006,'Amazing! There are passages in here that I have never seen before. This must have taken quite a while for you to track down. If you ever find anymore books like this, I would like to be notified immediately. $B$BPlease take one of my Kirin Tor Familiars with you just in case you stumble across anything.');
UPDATE creature_template SET scriptname = 'npc_archmage_vargoth' WHERE entry = 19481;

UPDATE `creature_template` SET `ScriptName`='npc_rhonin' WHERE `entry`=16128;
  
-- Dragonblight
-- Quests "Mystery of the Infinite" http://www.wowhead.com/quest=12470 & "Mystery of the Infinite, Redux" http://www.wowhead.com/quest=13343
UPDATE `creature_template` SET `ScriptName` = 'npc_hourglass' WHERE `entry` IN (27840,32327);
UPDATE `creature_template` SET `AIName` = '' WHERE `entry` = 27840;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (27840, 27900);
-- Quest completion
SET @ENTRY := 27900;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY);
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = @ENTRY;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 

(@ENTRY,0,0,0,0,0,100,0,5000,8000,11000,15000,11,51020,0,0,0,0,0,2,0,0,0,0,0,0,0,'Infinite Timerender - Cast Time Lapse'),
(@ENTRY,0,1,0,6,0,100,0,0,0,0,0,26,12470,0,0,0,0,0,0,0,0,0,0,0,0,0,'Infinite Timerender - Complete Q12470 on die'),
(@ENTRY,0,2,0,6,0,100,0,0,0,0,0,26,13343,0,0,0,0,0,0,0,0,0,0,0,0,0,'Infinite Timerender - Complete Q13343 on die');

UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` in (27896,27897,27898,27900);

UPDATE `creature_template` SET `ScriptName` = 'npc_denouncement_target' WHERE `entry` IN (27237,27235,27234,27236); -- Blacksmith Goodman, Lead Cannoneer Zierhut, Stable Master Mercer & Commander Jordan.
UPDATE `creature_template` SET `ScriptName` = 'vehicle_forsaken_blight_spreader' WHERE `entry` = 26523; -- Forsaken Blight Spreader http://www.wowhead.com/npc=26523
UPDATE `creature_template` SET `ScriptName` = 'npc_warsong_battle_standard' WHERE `entry` = 26678; -- Warsong Battle Standard http://www.wowhead.com/npc=26678
UPDATE `creature_template` SET `ScriptName` = 'npc_emissary_brighthoof' WHERE `entry` = 26181; -- Emissary Brighthoof <Tauren Emissary> http://www.wowhead.com/npc=26181
UPDATE `creature_template` SET `ScriptName` = 'npc_wintergarde_mine_bomb' WHERE `entry` = 27435; -- Wintergarde Mine Bomb http://www.wowhead.com/npc=27435
UPDATE `creature_template` SET `ScriptName` = 'npc_devout_bodyguard' WHERE `entry` = 27247; -- Devout Bodyguard http://www.wowhead.com/npc=27247
UPDATE `creature_template` SET `ScriptName` = 'npc_high_abbot_landgren' WHERE `entry` IN (27245,27439); -- High Abbot Landgren
UPDATE `creature_template` SET `ScriptName` = 'npc_agent_skully' WHERE `entry` = 27350; -- Agent Skully <Onslaught Caretaker> http://www.wowhead.com/npc=27350
-- Quest 12326
UPDATE `creature_template` SET `ScriptName` = 'npc_7th_legion_siege_engineer' WHERE `entry` = 27163; -- 7th Legion Siege Engineer http://www.wowhead.com/npc=27163
UPDATE `creature_template` SET `ScriptName` = 'vehicle_alliance_steamtank' WHERE `entry` = 27587; -- Alliance Steam Tank http://www.wowhead.com/npc=27587
UPDATE `creature_template` SET `flags_extra` = flags_extra | 2 WHERE `entry` = 27607;
INSERT INTO spell_area (`spell`,`area`,`autocast`) VALUES (49081,4246,0);
UPDATE `creature_template` SET `scriptname` = 'mob_woodlands_walker', `npcflag` = npcflag|1 WHERE `entry` = 26421; -- Woodlands Walker http://www.wowhead.com/npc=26421

-- IcecrownZoneQuests
-- -------------------------------------------------------------------------
-- ---------------- Quests: Icecrown & Argent Tournament -------------------
-- -------------------------------------------------------------------------

-- ARGENT TOURNAMENT BLIZLIKE SUPORT.

-- Vehicle Spells
DELETE FROM spell_script_names WHERE spell_id IN (62552,66482,62719);
INSERT INTO spell_script_names VALUES
(62552,'spell_tournament_defend'),
(66482,'spell_tournament_defend'),
(62719,'spell_tournament_defend');
-- Dummy Script: "Melee Target" http://www.wowhead.com/npc=33229,  "Charge Target" http://www.wowhead.com/npc=33272 & "Ranged Target" http://www.wowhead.com/npc=33243
UPDATE creature_template SET scriptname = 'npc_tournament_dummy' WHERE entry IN (33229,33272,33243);

-- Vendor Champions
UPDATE creature_template SET scriptname = 'npc_vendor_tournament_fraction_champion' WHERE entry IN (33657,33650,33653,33307,33310,33553,33554,33557,33556,33555);
-- Valiant Champions
-- Quest "The Grand Melee" http://old.wowhead.com/search?q=The+Grand+Melee
UPDATE creature_template SET scriptname = 'npc_faction_valiant_champion' WHERE entry IN (33559,33562,33558,33564,33306,33285,33382,33561,33383,33384);
UPDATE creature_template SET scriptname = 'npc_faction_valiant_champion' WHERE entry IN (33738,33739,33740,33743,33744,33745,33746,33747,33748,33749);

-- Quest "A Blade Fit For A Champion" http://old.wowhead.com/search?q=A+Blade+Fit+For+A+Champion
-- "Lake Frog" http://www.wowhead.com/npc=33211 & http://www.wowhead.com/npc=33224
UPDATE creature_template SET scriptname = 'npc_lake_frog' WHERE entry IN (33211,33224);

-- "Maiden of Drak'Mar" http://www.wowhead.com/npc=33273 [Dragonblight]
DELETE FROM `event_scripts` WHERE `id`=20990;
INSERT INTO `event_scripts` (`id`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(20990,1,10,33273,60000,0,4602.782715,-1600.874146,158,1.387292);
UPDATE creature_template SET scriptname = 'npc_maiden_of_drakmar' WHERE entry = 33273;

-- "Squire Danny" http://www.wowhead.com/npc=33518 [Icecrown]
UPDATE creature_template SET scriptname = 'npc_squire_danny' WHERE entry = 33518;

-- Argent Champion http://www.wowhead.com/npc=33707
UPDATE creature_template SET scriptname = 'npc_argent_champion' WHERE entry = 33707;

-- "Argent Squire" http://old.wowhead.com/npc=33238 and 	"Argent Gruntling" http://old.wowhead.com/npc=33239
UPDATE creature_template SET scriptname = 'npc_argent_squire_gruntling', npcflag=1 WHERE entry in (33238,33239);

--  Quest "Gormok Wants His Snobolds" [A] http://www.wowhead.com/quest=14090 & [H] http://www.wowhead.com/quest=14141
UPDATE creature_template SET scriptname = 'npc_snowblind_follower' WHERE entry = 29618;

-- Quest "The Black Knight's Fall" http://www.wowhead.com/quest=13664
-- "Squire Cavin" http://www.wowhead.com/npc=33522
UPDATE creature_template SET scriptname = 'npc_squire_cavin' WHERE entry = 33522;
-- "The Black Knight" http://www.wowhead.com/npc=33785
UPDATE creature_template SET scriptname = 'npc_the_black_knight' WHERE entry = 33785;

-- Quest "The Black Knight's Orders" http://www.wowhead.com/quest=13663
-- Script for "Black Knight's Gryphon" http://www.wowhead.com/npc=33519
UPDATE `creature_template` SET `AIName`='', scriptname = 'vehicle_black_knights_gryphon' WHERE `entry` = 33519;
-- cleaning
DELETE FROM `smart_scripts` WHERE `entryorguid`=33519;

-- Quest "The Black Knight's Curse" http://www.wowhead.com/quest=14016
-- Script for "Black Knight's Grave" http://www.wowhead.com/npc=34735
UPDATE creature_template SET scriptname = 'npc_black_knights_grave' WHERE entry = 34735;

-- Quest "The Light's Mercy" http://www.wowhead.com/quest=14144 in Icecrown and Hrothgar's Landing.
-- Script for "Slain Tualiq Villager" http://www.wowhead.com/npc=34852
UPDATE creature_template SET scriptname = 'npc_slain_tualiq_villager' WHERE entry = 34852;

-- Spell "Flaming Spear" http://old.wowhead.com/spell=66588 for Quest "Get Kraken!" http://old.wowhead.com/quest=14108
DELETE FROM spell_script_names WHERE spell_id IN (66588);
INSERT INTO spell_script_names (spell_id,Scriptname) VALUES 
(66588,'spell_flaming_spear_targeting');


-- ICECROWN

-- Webbed Crusader http://old.wowhead.com/npc=30273 & http://old.wowhead.com/npc=30268
UPDATE `creature_template` SET AIName = '', `ScriptName` = 'npc_webbed_crusader' WHERE `entry` IN (30273,30268);
-- cleaning
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (30273,30268);

-- Fix Spell "Drop Off Captured Crusader" http://old.wowhead.com/spell=56684 for Quest "Into The Wild Green Yonder" http://www.wowhead.com/quest=13045
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 17 AND SourceEntry = 56684;
INSERT INTO conditions VALUES
(17,0,56684,0,30,192522,10,0,0,'',''),
(17,0,56684,0,29,30407,10,0,0,'','');

-- Quest "The Last Line Of Defense" http://www.wowhead.com/quest=13086
-- Vehicle for Argent Cannon http://www.wowhead.com/npc=30236
UPDATE creature_template SET VehicleId = 160 WHERE entry = 30236;
-- Spell ScriptName fo Argent Cannon
DELETE FROM spell_script_names WHERE spell_id IN (57385,57412);
INSERT INTO spell_script_names VALUES
(57385,'spell_argent_cannon'),
(57412,'spell_argent_cannon');
-- Spell npc_spellclick_spells Argent Cannon Gunner http://old.wowhead.com/spell=57573
DELETE FROM npc_spellclick_spells WHERE npc_entry = 30236;
INSERT INTO  npc_spellclick_spells VALUES
(30236,57573,13086,1,13086,1,0,0,0);
-- "Forgotten Depths Slayer" http://www.wowhead.com/npc=30593 & "Frostbrood Destroyer" http://www.wowhead.com/npc=30575 spawn quick and movement
UPDATE creature_template SET  flags_extra = flags_extra | 64 | 262144 | 268435456 WHERE entry IN (30593,30575);
UPDATE `creature` SET `spawndist` = 30, `MovementType` = 1 WHERE `id` IN (30593,30575);
UPDATE `creature_template` SET `MovementType` = 1 WHERE `entry` IN (30593,30575);
UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 30575;

-- Quest "The Battle For Crusaders' Pinnacle" http://old.wowhead.com/quest=13141
-- Script for NPC "Blessed Banner of the Crusade" http://www.wowhead.com/npc=30891
UPDATE creature_template SET scriptname = 'npc_blessed_banner' WHERE entry = 30891;
UPDATE creature_template SET faction_A = 2068, faction_H = 2068 WHERE entry IN (30986,30984,30987,30989);
UPDATE creature_template SET faction_A = 2131, faction_H = 2131 WHERE entry IN (31003,30919,30900);
DELETE FROM event_scripts WHERE id = 20082;
INSERT INTO event_scripts VALUES
(20082,0,10,30891,600000,0,6418.31,423.00,511.2,5.945);

-- "Captured Crusader" http://www.wowhead.com/npc=30407	- let him use cpp script, fixes mysterious SmartAI problem
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_captured_crusader' WHERE `entry`=30407;
-- cleaning
DELETE FROM `smart_scripts` WHERE `entryorguid`=30407; 

-- Quest "If He Cannot Be Turned" [A] http://www.wowhead.com/quest=12896 & [H] http://www.wowhead.com/quest=12897
-- Quest "It's All Fun and Games" [A] http://www.wowhead.com/quest=12887 & [B] http://www.wowhead.com/quest=12892
-- "The Ocular" http://www.wowhead.com/npc=29747
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|268435456,`AIName`='',`InhabitType`=`InhabitType`|4,`ScriptName`='npc_the_ocular' WHERE `entry`=29747;
UPDATE `creature_model_info` SET `combat_reach`=100 WHERE `modelid`=26533;
-- cleaning
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=29747;
DELETE FROM `smart_scripts` WHERE `entryorguid`=29747;
/*
DELETE FROM `creature_template_addon` WHERE `entry`=29747;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(29747,0,0,0,0,0,'55162'); -- The Ocular: Transform
*/
-- "The Ocular - Eye of Acherus Exterior Shell" http://www.wowhead.com/npc=29790
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|2|33554432 WHERE `entry`=29790;
-- condition
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=30740;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,0,30740,0,18,1,29747,0,63,'','Eyesore Blaster only target The Oculus');
-- "General Lightsbane" http://www.wowhead.com/npc=29851
UPDATE `creature_template` SET AIName='', `ScriptName`='npc_general_lightsbane' WHERE `entry` = 29851;

-- Quest "Free Your Mind" http://www.wowhead.com/quest=12893
-- "Vile" http://www.wowhead.com/npc=29769, "Lady Nightswood" http://www.wowhead.com/npc=29770 & "The Leaper" http://www.wowhead.com/npc=29840 
UPDATE `creature_template` SET ScriptName = 'npc_free_your_mind' WHERE `entry` IN (29769,29770,29840);
 
-- Quest "Slaves to Saronite" [A] http://www.wowhead.com/quest=13300 & [H] http://www.wowhead.com/quest=13302
-- "Saronite Mine Slave" http://www.wowhead.com/npc=31397
UPDATE `creature_template` SET ScriptName = 'npc_saronite_mine_slave' WHERE `entry` = 31397;


-- Fix Missions Quel'Delar Chain: Thalorien Buscalba
-- Gossip Text
SET @ENTRY := 37552;
SET @TEXTID := 537552;
DELETE FROM gossip_menu WHERE entry=@ENTRY;
INSERT INTO gossip_menu VALUES (@ENTRY, @TEXTID);

-- need more TEXT Not complete
DELETE FROM npc_text WHERE id = @TEXTID;
INSERT INTO npc_text (ID, text0_0) VALUES (@TEXTID, 'It seems that these are remnants Buscalba Thalorien you, the last bearer of Quel\Delar');

-- NPCs
DELETE FROM `creature_template` WHERE `entry` IN (37552, 37205, 37542, 37541, 37539, 37538);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(37552, 0, 0, 0, 0, 0, 30659, 0, 0, 0, 'Thalorien Dawnseeker\'s Remains', '', '', 0, 80, 80, 0, 35, 35, 1, 1, 1.14286, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 32772, 44, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_thalorien', 12340),
(37205, 0, 0, 0, 0, 0, 30570, 0, 0, 0, 'Thalorien Dawnseeker', '', '', 0, 80, 80, 0, 35, 35, 0, 1, 1.14286, 1, 1, 400, 600, 0, 472, 2, 1500, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 10.3181, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 12340),
(37542, 0, 0, 0, 0, 0, 30657, 0, 0, 0, 'Morlen Coldgrip', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 1, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 7.076, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340),
(37541, 0, 0, 0, 0, 0, 30651, 30653, 30654, 0, 'Crypt Raider', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 0, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 3.538, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340),
(37539, 0, 0, 0, 0, 0, 30647, 30648, 30649, 30650, 'Ghoul Invader', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 0, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 2.9483, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340),
(37538, 0, 0, 0, 0, 0, 30645, 30644, 30643, 30646, 'Scourge Zombie', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 0, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1.887, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340);

DELETE FROM `creature_template_addon` WHERE (`entry`=@ENTRY);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (@ENTRY, 0, 0, 0, 0, 0, '25824 31261 31261');

DELETE FROM `smart_scripts` WHERE (`entryorguid` IN (37552, 37205, 37542, 37541, 37539, 37538) AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(37205, 0, 0, 0, 0, 0, 100, 30, 5000, 7000, 15000, 15000, 11, 67541, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Filotormenta'),
(37205, 0, 1, 0, 0, 0, 100, 0, 2000, 2000, 13000, 13000, 11, 67542, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Golpe mortal'),
(37205, 0, 2, 0, 0, 0, 100, 0, 19000, 19000, 19000, 19000, 11, 67716, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Torbellino'),
(37205, 0, 3, 0, 0, 0, 100, 0, 1000, 1000, 8000, 8000, 11, 57846, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Golpe heroico'),
(37542, 0, 0, 0, 0, 0, 100, 30, 2000, 3000, 9000, 10000, 11, 50688, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Morlen Manosfrias - Golpe de peste'),
(37541, 0, 0, 0, 0, 0, 100, 30, 1000, 2000, 4000, 5000, 11, 31600, 2, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 'Asaltante de la cripta - Escarabajos de la cripta'),
(37539, 0, 0, 0, 0, 0, 100, 30, 1000, 2000, 9000, 10000, 11, 38056, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Invasor necrofago - Desgarrar carne'),
(37538, 0, 0, 0, 0, 0, 100, 30, 1000, 2000, 9000, 10000, 11, 49861, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Zombi de la plaga - Mordedura infectada');

-- -------------------------------------------------------------------------
-- --------------- End of Quests: Icecrown & Argent Tournament -------------
-- -------------------------------------------------------------------------
 
-- Howling Fjord
-- Spell "Plague Spray" http://www.wowhead.com/spell=43381 for Item "Plague Spray" http://www.wowhead.com/item=33621 for Quest: "Field Test" http://www.wowhead.com/quest=11307
DELETE FROM `spell_script_names` WHERE `spell_id` = 43385;
INSERT INTO `spell_script_names` VALUES
(43385, 'spell_q11307_plagued_vrykul_dummy');

-- Sholazar Basin
-- Quest "Still At It" http://www.wowhead.com/quest=12644
UPDATE creature_template SET scriptname = 'npc_tipsy_mcmanus' where entry = 28566;
UPDATE gameobject_template SET scriptname = 'go_brew_event' where entry in (190635,190636,190637,190638,190639);

-- Quest "A Cleansing Song" http://old.wowhead.com/quest=12735 - Fix item "Chime of Cleansing" http://www.wowhead.com/item=39572
UPDATE `item_template` SET `ScriptName`='item_chime_of_cleansing' WHERE `entry`=39572;

-- Quest "Reclamation" http://www.wowhead.com/quest=12546
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 28222 AND `spell_id` = 46598;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(28222,46598,0,0,0,1,0,0,0);
UPDATE `creature_template` SET `vehicleid` = 22 WHERE `entry` = 28222;
UPDATE `creature_template` SET `flags_extra` = `flags_extra`|64 WHERE `entry` IN (28218,28220);
DELETE FROM `conditions` WHERE `sourcetypeorreferenceid` = 17 AND `sourceentry` IN (50978,50980,50983,50985);
INSERT INTO `conditions` (`sourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `conditionvalue1`, `errortextid`, `comment`) VALUES
(17,50978,23,4282,1335,'Spell1 Etimidiano limited to Avalanche (Sholazar)'),
(17,50980,23,4282,1335,'Spell2 Etimidiano limited to Avalanche (Sholazar)'),
(17,50983,23,4282,1335,'Spell3 Etimidiano limited to Avalanche (Sholazar)'),
(17,50985,23,4282,1335,'Spell4 Etimidiano limited to Avalanche (Sholazar)');

-- Script for "High-Oracle Soo-say" http://www.wowhead.com/npc=28027
UPDATE `creature_template` SET `ScriptName`='npc_high_oracle_soo_say' WHERE `entry`=28027;

-- Invisible Location Trigger
UPDATE `creature_template` SET `minlevel`=60, `maxlevel`=60, `unit_flags`=33587968, `InhabitType`=7, `flags_extra`=130, `ScriptName`='npc_generic_oracle_treasure_trigger' WHERE `entry`=28088;

-- Quest "The Angry Gorloc" http://www.wowhead.com/quest=12578 - "Appeasing the Great Rain Stone" http://www.wowhead.com/quest=12704 - "Gods like Shiny Things" Quest Suport: http://www.wowhead.com/quest=12572
-- Scripted NPCs Lafoo http://www.wowhead.com/npc=28120, Jaloot http://www.wowhead.com/npc=28121 and  Moodle http://www.wowhead.com/npc=28122 
UPDATE `creature_template` SET `ScriptName`='npc_generic_oracle_treasure_seeker' WHERE `entry` IN (28120, 28121, 28122);

-- Script Npc Change Faction Oracles<->Frenzyheart
-- Script for "Jaloot" http://www.wowhead.com/npc=28667 and "Zepik the Gorloc Hunter" http://www.wowhead.com/npc=28668
UPDATE `creature_template` SET `ScriptName`='oracle_frenzyheart_switch' WHERE `entry` IN (28667, 28668);

-- Quest "A Rough Ride" http://www.wowhead.com/quest=12536
-- Script for "Zepik the Gorloc Hunter" http://www.wowhead.com/npc=28216
UPDATE `creature_template` SET `ScriptName` = 'npc_frenzyheart_zepik' WHERE `entry` = 28216;

-- Quest "The Mosswalker Savior" http://www.wowhead.com/quest=12580
-- Script for "Mosswalker Victim" http://www.wowhead.com/npc=28113
UPDATE `creature_template` SET `ScriptName`= 'npc_mosswalker_victim' WHERE `entry` = 28113;

-- Script for "Artruis the Heartless" http://www.wowhead.com/npc=28659;
UPDATE `creature_template` SET `ScriptName` = 'npc_artruis_the_heartless' WHERE `entry` = 28659;

-- Quest: Fix Quest "A Heros's Headgear" http://old.wowhead.com/quest=12758
-- Script for "Stormwatcher" http://www.wowhead.com/npc=28877
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_stormwatcher' WHERE `entry`=28877;
-- cleaning
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=28877;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-10 WHERE `item`=39651; -- increase Droppchance of Venture Co. Explosives (1% is to less)
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=18 AND `SourceEntry`=39651;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(18,0,39651,0,24,2,28877,0,0,'','Venture Co. Explosives only target dead Stormwatcher');

-- Quest: Fix Quest "Rejek: First Blood" http://old.wowhead.com/quest=12734
-- Script for "Sapphire Hive Wasp" http://www.wowhead.com/npc=28086, "Hardknuckle Charger" http://www.wowhead.com/npc=28096, "Mistwhisper Oracle" http://www.wowhead.com/npc=28110 and "Mistwhisper Warrior" http://www.wowhead.com/npc=28109.
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_rejek_first_blood' WHERE `entry` IN (28086,28096,28110,28109);
-- cleaning
DELETE FROM `creature_ai_scripts` WHERE `creature_id`IN (28086,28096,28110,28109);

-- Quest "Song of Wind and Water" http://old.wowhead.com/quest=12726
-- update creature_template data of "Haiphoon, the Great Tempest" http://www.wowhead.com/npc=28999 & http://www.wowhead.com/npc=28985
-- set some Vehicle & Spell Conditions
-- move EAI to SAI for "Storm Revenant" http://www.wowhead.com/npc=28858
SET @HAIPHOON_W     :=28999; -- WATER
SET @HAIPHOON_A     :=28985; -- AIR
SET @STORM          :=28858; -- Storm Revenant
SET @AQUEOUS        :=28862; -- Aqueous Spirit
-- WATER SPELLS
SET @SPELL_W_1      :=61375; -- Water Bolt
SET @SPELL_W_2      :=61376; -- Frost Nova
SET @SPELL_W_3      :=52862; -- Devour Wind
SET @SPELL_W_4      :=52869; -- Evocation
-- AIR SPELLS
SET @SPELL_A_1      :=71934; -- Lightning Bolt (61374 original ID but needs mana - use another relative equal SpellID)
SET @SPELL_A_2      :=52870; -- Windshear
SET @SPELL_A_3      :=52864; -- Devour Water

UPDATE `creature_template` SET
`spell1`=@SPELL_W_1,
`spell2`=@SPELL_W_2,
`spell3`=@SPELL_W_3,
`spell4`=@SPELL_W_4,
`npcflag`=`npcflag`|16777216,
`unit_flags`=`unit_flags`|16777216,
`type_flags`=`type_flags`|2048,
`VehicleId`=257,
`AIName`='',
`exp`=2,
`minlevel`=80,
`maxlevel`=80,
`mindmg`=417,
`maxdmg`=582,
`attackpower`=608,
`minrangedmg`=341,
`maxrangedmg`=506,
-- `rangeatackpower`=80,
`ScriptName`='vehicle_haiphoon'
WHERE `entry`=@HAIPHOON_W;

UPDATE `creature_template` SET
`spell1`=@SPELL_A_1,
`spell2`=@SPELL_A_2,
`spell3`=@SPELL_A_3,
`npcflag`=`npcflag`|16777216,
`unit_flags`=`unit_flags`|16777216,
`type_flags`=`type_flags`|2048,
`VehicleId`=257,
`AIName`='',
`exp`=2,
`minlevel`=80,
`maxlevel`=80,
`mindmg`=417,
`maxdmg`=582,
`attackpower`=608,
`minrangedmg`=341,
`maxrangedmg`=506,
-- `rangeatackpower`=80,
`ScriptName`='vehicle_haiphoon'
WHERE `entry`=@HAIPHOON_A;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (@HAIPHOON_W,@HAIPHOON_A);
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(@HAIPHOON_W,46598,12726,1,12726,1,0,0,0),
(@HAIPHOON_A,46598,12726,1,12726,1,0,0,0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry` IN (@SPELL_W_3,@SPELL_A_3);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=16 AND `SourceEntry` IN (@HAIPHOON_W,@HAIPHOON_A);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,@SPELL_W_3,0,19,@STORM,0,0,63,'','Spell only target Storm Revenant'),
(17,0,@SPELL_A_3,0,19,@AQUEOUS,0,0,63,'','Spell only target Aqueous Spirit'),
(16,0,@HAIPHOON_W,0,23,4392,0,0,0,'','Ride Vehicle only in Area'),
(16,0,@HAIPHOON_A,0,23,4392,0,0,0,'','Ride Vehicle only in Area');

UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry` IN (@STORM,@AQUEOUS);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (@STORM,@AQUEOUS);
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (@STORM,@AQUEOUS);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@STORM,0,0,0,0,0,100,0,2000,4000,5000,7000,11,32018,1,0,0,0,0,2,0,0,0,0,0,0,0,'Storm Revenant - IC - Cast Call Lightning'),
(@AQUEOUS,0,0,0,0,0,100,0,6000,9000,7000,10000,11,55087,1,0,0,0,0,2,0,0,0,0,0,0,0,'Aqueous Spirit - IC - Cast Typhoon');

-- Quest "A Rough Ride" http://www.wowhead.com/quest=12536 Vezax
-- Script for "Captive Crocolisk" http://www.wowhead.com/npc=28298
-- Captive Crocolisk ScriptName (Gossip)
UPDATE `creature_template` SET `ScriptName` = 'npc_captive_croco_gossip' WHERE `entry` = 28298;
-- Captive Crocolisk Stats (Vehicle) http://www.wowhead.com/npc=28308
DELETE FROM `creature_template` WHERE (`entry`=28308);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(28308, 0, 0, 0, 0, 0, 25107, 0, 0, 0, 'Captive Crocolisk', '', '', 0, 80, 80, 2, 2, 2, 0, 1, 2, 1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 16777472, 8, 6, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 115, 0, 0, '', 0, 3, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 0, 'npc_captive_croco_vehicle', 12340);
-- Quest "A Rough Ride" http://www.wowhead.com/quest=12536 QuestTaker Summoner (item)
UPDATE `quest_template` SET `SrcItemId` = 38512, `SrcItemCount` = 1 WHERE `entry` = 12536;
-- Script for "Elder Harkek" http://www.wowhead.com/npc=28138
UPDATE `creature_template` SET `ScriptName` = 'npc_harkek_gossip' WHERE `entry` = 28138;
