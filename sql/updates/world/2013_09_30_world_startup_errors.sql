-- Here some1 just forgot to set the MovementType
UPDATE `creature` SET `MovementType`=1 WHERE  `guid`=346993;
UPDATE `creature` SET `MovementType`=1 WHERE  `guid`=347005;
UPDATE `creature` SET `MovementType`=1 WHERE  `guid`=347006;


-- Those npc Entrys only exist in 5.2.0 http://de.wowhead.com/npc=66392/schleimiger-glitschigreifer
DELETE FROM `npc_spellclick_spells` WHERE  `npc_entry`=66392 AND `quest_start`=0 AND `quest_start_active`=0 AND `quest_end`=0 AND `aura_required`=0 AND `aura_forbidden`=0 AND `spell_id`=66300 AND `cast_flags`=1 AND `user_type`=0 LIMIT 1;
DELETE FROM `npc_spellclick_spells` WHERE  `npc_entry`=66392 AND `quest_start`=0 AND `quest_start_active`=0 AND `quest_end`=0 AND `aura_required`=0 AND `aura_forbidden`=0 AND `spell_id`=66298 AND `cast_flags`=1 AND `user_type`=0 LIMIT 1;
DELETE FROM `npc_spellclick_spells` WHERE  `npc_entry`=66392 AND `quest_start`=0 AND `quest_start_active`=0 AND `quest_end`=0 AND `aura_required`=0 AND `aura_forbidden`=0 AND `spell_id`=66299 AND `cast_flags`=1 AND `user_type`=0 LIMIT 1;


-- Fix Stranglethorn Vale Graveyard Zones
DELETE FROM game_graveyard_zone WHERE id=109;
INSERT INTO game_graveyard_zone (id, ghost_zone, faction) VALUES (109, 214, 0);
INSERT INTO game_graveyard_zone (id, ghost_zone, faction) VALUES (109, 5287, 0);
INSERT INTO game_graveyard_zone (id, ghost_zone, faction) VALUES (109, 5339, 0);

DELETE FROM game_graveyard_zone WHERE id=389;
INSERT INTO game_graveyard_zone (id, ghost_zone, faction) VALUES (389, 33, 0);
INSERT INTO game_graveyard_zone (id, ghost_zone, faction) VALUES (389, 214, 0);
INSERT INTO game_graveyard_zone (id, ghost_zone, faction) VALUES (389, 5339, 0);


-- Some1 forgot sourcegroup = 1 because it's an spell effect mask
UPDATE `conditions` SET `SourceGroup`=1 WHERE  `SourceTypeOrReferenceId`=13 AND `SourceGroup`=0 AND `SourceEntry`=78838 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=18 AND `ConditionTarget`=0 AND `ConditionValue1`=1 AND `ConditionValue2`=42235 AND `ConditionValue3`=0;
UPDATE `conditions` SET `SourceGroup`=1 WHERE  `SourceTypeOrReferenceId`=13 AND `SourceGroup`=0 AND `SourceEntry`=67682 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=18 AND `ConditionTarget`=0 AND `ConditionValue1`=1 AND `ConditionValue2`=35818 AND `ConditionValue3`=2;


-- Event AI Missmatch. Entry 1815 has no SmartAI, it has an EventAI
UPDATE `creature_template` SET `AIName`='EventAI' WHERE  `entry`=1815;


-- Unused gameobject and it was totally wrong anyway
DELETE FROM `smart_scripts` WHERE  `entryorguid`=-1638026 AND `source_type`=0 AND `id`=0 AND `link`=0;
