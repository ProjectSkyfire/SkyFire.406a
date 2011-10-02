ALTER TABLE `characters` ADD `power8` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `power7`;
ALTER TABLE `characters` ADD `power9` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `power8`;
ALTER TABLE `characters` ADD `power10` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `power9`;

ALTER TABLE `character_stats` ADD `maxpower8` int(10) unsigned NOT NULL DEFAULT '0' AFTER `maxpower7`;
ALTER TABLE `character_stats` ADD `maxpower9` int(10) unsigned NOT NULL DEFAULT '0' AFTER `maxpower8`;
ALTER TABLE `character_stats` ADD `maxpower10` int(10) unsigned NOT NULL DEFAULT '0' AFTER `maxpower9`;





