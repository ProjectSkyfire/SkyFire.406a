UPDATE creature_template SET ainame="", scriptname="npc_blackrock_battle_worg" WHERE entry=3871226;
UPDATE creature_template SET ainame="", scriptname="npc_stormwind_infantry" WHERE entry=49869;

UPDATE creature SET curhealth = 42 WHERE id=3871226;
UPDATE creature SET curhealth = 71 WHERE id=49869;

UPDATE creature_template SET killcredit1=49871 WHERE entry=3871226;

DELETE FROM smart_scripts WHERE entryorguid IN (49869,3871226);