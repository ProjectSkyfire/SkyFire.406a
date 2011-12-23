ALTER TABLE `game_event_model_equip` DROP COLUMN `event`;
ALTER TABLE `game_event_model_equip` ADD COLUMN `eventEntry` smallint(5) unsigned NOT NULL DEFAULT '0'AFTER `equipment_id`;