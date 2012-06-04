DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (7744,42292,59752);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (7744,42292,72752,72757);
INSERT INTO `spell_script_names` VALUES
(7744,'spell_pvp_trinket_wotf_shared_cd'),
(42292,'spell_pvp_trinket_wotf_shared_cd');