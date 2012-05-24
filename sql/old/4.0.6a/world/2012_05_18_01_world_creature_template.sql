UPDATE `instance_template` SET `script`='instance_throne_of_the_tides' WHERE `map`=643 LIMIT 1;
-- Lady Naz'jar
UPDATE `creature_template` SET `ScriptName`='boss_lady_nazjar' WHERE `entry`=40586;
-- Commander Ulthok
UPDATE `creature_template` SET `ScriptName`='boss_commander_ulthok' WHERE `entry`=40765;
-- Erunak Stonespeaker & Mindbender Ghur'sha
UPDATE `creature_template` SET `ScriptName`='boss_erunak_stonespeaker' WHERE `entry`=40825;
UPDATE `creature_template` SET `ScriptName`='boss_mindbender_ghursha' WHERE `entry`=40788;
-- Ozumat & Neptulon
DELETE FROM creature WHERE id = 42172;
UPDATE `creature_template` SET `ScriptName`='npc_neptulon' WHERE `entry`=40792;
UPDATE `creature_template` SET `ScriptName`='boss_ozumat' WHERE `entry`=42172;
