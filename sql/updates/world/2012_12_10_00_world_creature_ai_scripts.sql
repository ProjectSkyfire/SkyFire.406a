DELETE FROM `creature_ai_scripts` WHERE `creature_id`=644 AND `id` IN (64403,55500711,55500712);
INSERT  INTO `creature_ai_scripts` VALUES (64403,47162,6,0,100,2,0,0,0,0,34,1,3,0,0,0,0,0,0,0,0,0,'Glubtok - Set Data Done when killed');
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=47162;
