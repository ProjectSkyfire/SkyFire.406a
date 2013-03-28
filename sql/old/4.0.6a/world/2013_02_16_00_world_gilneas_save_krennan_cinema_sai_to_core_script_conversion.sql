UPDATE creature_template SET AIName = "", scriptname = "npc_lord_godfrey_p4_8" WHERE entry = 35906;

UPDATE creature_template SET AIName = "", scriptname = "npc_commandeered_cannon" WHERE entry = 35914;

UPDATE creature_template SET AIName = "" WHERE entry =50420;

DELETE FROM smart_scripts WHERE entryorguid IN (5042000, 50420, 35096, 35914);

DELETE FROM creature WHERE guid = 69;
INSERT INTO creature VALUES (69, 35753, 638, 1, 4, 0, 0, -1674.45, 1349.29, 20.38, 6.15351, 15, 0, 0, 102, 0, 0, 0, 0, 0);

DELETE FROM creature_text WHERE entry = 35753;
INSERT INTO creature_text VALUES (35753, 0, 1, 'Help!  Up here!', 14, 0, 100, 0, 0, 20921, 'Krennan Aranas In Tree');

DELETE FROM creature_template_addon WHERE entry = 3871227;
DELETE FROM creature_addon WHERE guid = 69;
INSERT INTO creature_addon VALUES (69, 0, 0, 0, 0, 473, "");

DELETE FROM creature_template WHERE entry = 3871227;
UPDATE creature_template SET inhabittype = 7 WHERE entry = 35753;

UPDATE creature_template SET unit_flags = 512 WHERE entry = 35509;
UPDATE creature_template SET unit_flags = 134 WHERE entry = 35914;

DELETE FROM script_texts WHERE entry IN (-1999971, -1999972);

DELETE FROM creature_text WHERE entry = 35907;

INSERT INTO creature_text VALUES (35907, 0, 0, "Thank you! I owe you my life.", 12, 0, 0, 1, 0, 20922, "Saved Krennan Aranas");

DELETE FROM conditions WHERE conditionvalue2 = 3871227 LIMIT 1;
