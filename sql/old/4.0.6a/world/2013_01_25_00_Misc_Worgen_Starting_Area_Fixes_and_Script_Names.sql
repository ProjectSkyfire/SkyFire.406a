

-- Small Chicken Fix Again
UPDATE creature_template SET speed_run = "0.857143", inhabittype = 1 WHERE entry = 44426;

-- Remove Double Spawn of Rogue Trainer
DELETE FROM creature WHERE guid = 338950;
-- Give her a Dagger
DELETE FROM creature_equip_template WHERE entry = 35871;
INSERT INTO creature_equip_template VALUES
(35871,50055,0,0);
-- Now we set her Bytes2 to Melee Ready (appear ready for combat) AND set her stealthy aura
DELETE FROM creature_template_addon WHERE entry = 35871;
INSERT INTO creature_template_addon VALUES
(35871, 0, 0, 0, 1, 0, '34189');
DELETE FROM creature_addon WHERE guid = 342530;
DELETE FROM creature WHERE guid IN (342530, 246);
INSERT INTO creature VALUES
(246,35871,638,1,2,0,0,-1696.627,1298.148,20.36746,2.234021,600,0,0,42,0,0,0,0,0);

DELETE FROM waypoints WHERE entry IN (3516700,3545600, 3518800, 3517000);

DELETE FROM smart_scripts WHERE entryorguid IN (35077, 35188, 3507700, 35170, 3507701, 3507702, 1415400, 1415401, 1415402, 3871204, 35167, 35456);

DELETE FROM creature_template WHERE entry IN (3871204, 35077);

INSERT INTO creature_template VALUES
(35077,0,0,0,0,0,29593,0,0,0,"Lord Darius Crowley",'','',0,88,88,0,2163,2163,3,1,1.14286,1,1,5,8,0,40,1.5,1111,0,1,0,0,0,0,0,0,0,8,11,0,7,262148,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,33,'',0,1,11,1,1,0,0,0,0,0,0,0,0,1,0,613097436,0,"npc_lord_darius_crowley_c1",13623);

UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_alpha_c1" WHERE ENTRY = 35170;
UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_alpha_c2" WHERE ENTRY = 35167;
UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_runt_c1" WHERE ENTRY = 35188;
UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_runt_c2" WHERE ENTRY = 35456;
UPDATE creature_template SET AIName = "", scriptname = "npc_sean_dempsey" WHERE ENTRY = 35081;

UPDATE quest_template SET reqcreatureorgoid1 = "0", reqcreatureorgocount1 = "0" WHERE entry = 14154;

-- Not sure why he spawns below the map but this fixes it
UPDATE creature SET position_z = 52.29 WHERE guid = 35077;
