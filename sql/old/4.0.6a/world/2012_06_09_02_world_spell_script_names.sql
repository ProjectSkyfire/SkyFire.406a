-- spell_items
DELETE FROM `spell_script_names` WHERE `spell_id` IN (29200,47170,51582,55004,50243,35745);
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (29200,'spell_item_purify_helboar_meat');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (47170,'spell_item_impale_leviroth');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (51582,'spell_item_rocket_boots');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (55004,'spell_item_nitro_boots');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (50243,'spell_item_teach_language');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (35745,'spell_item_socrethars_stone');