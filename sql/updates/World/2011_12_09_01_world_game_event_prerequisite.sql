ALTER TABLE `game_event_prerequisite` DROP COLUMN `event_id`;
ALTER TABLE `game_event_prerequisite` ADD COLUMN `eventEntry` mediumint(8) unsigned NOT NULL;
