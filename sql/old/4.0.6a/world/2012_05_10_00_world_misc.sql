-- since we atm have both item_scriptnames, and item_templates with the scrpitname column updating the sql.
-- item_script_names
DELETE FROM `item_script_names` WHERE `id` IN (56473);
INSERT INTO `item_script_names` (`id`,`ScriptName`) VALUES 
(56473,'item_kromgar_flame_thrower');

-- item_template | ScriptName
UPDATE `item_template` SET `ScriptName`='item_kromgar_flame_thrower' WHERE `entry`=56473;

-- forgotten part of the update.
UPDATE `gameobject_template` SET `flags`=1 WHERE `entry`=203431;