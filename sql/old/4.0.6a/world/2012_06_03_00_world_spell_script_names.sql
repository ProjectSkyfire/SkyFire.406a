DELETE FROM `spell_script_names` WHERE `spell_id`=-5308; -- Execute "Ranks", clear one more stupid warning on startup

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_item_gnomish_death_ray';
INSERT INTO `spell_script_names` VALUES
(13280,'spell_item_gnomish_death_ray');


DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (13278,-13278);
INSERT INTO `spell_linked_spell` VALUES
(13278,13493,0,'Gnomish Death Ray caster overtime damage apply'),
(-13278,-13493,0,'Gnomish Death Ray caster overtime damage removal');
