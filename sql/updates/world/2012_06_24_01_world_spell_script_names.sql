-- Wrong spell id for spell_marrowgar_bone_spike_graveyard, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 73143;

-- Wrong spell id for spell_deathbringer_rune_of_blood, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 72410;

-- Wrong spell id for spell_deathbringer_blood_link_aura, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 72202;

-- Wrong spell id for spell_deathbringer_blood_link
DELETE FROM `spell_script_names` WHERE `spell_id` = 70897;
INSERT INTO `spell_script_names` VALUES 
(72202,'spell_deathbringer_blood_link');

-- Wrong spell id for spell_cultist_dark_martyrdom, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 72176;

-- Wrong spell id for spell_marrowgar_coldflame.
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_marrowgar_coldflame';
INSERT INTO `spell_script_names` VALUES
(69140,'spell_marrowgar_coldflame');

-- Wrong spell id for spell_xt002_gravity_bomb_damage.
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_xt002_gravity_bomb_damage';
INSERT INTO `spell_script_names` VALUES
(63025,'spell_xt002_gravity_bomb_damage'),
(64233,'spell_xt002_gravity_bomb_damage');

-- Wrong spell id for spell_tournament_trust.
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_tournament_trust';
INSERT INTO `spell_script_names` VALUES
(62544,'spell_tournament_trust');