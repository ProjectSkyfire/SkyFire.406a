ALTER TABLE `spell_proc` DROP COLUMN `ttributesMask`;
ALTER TABLE `spell_proc` ADD COLUMN `attributesMask` int(10) unsigned NOT NULL DEFAULT '0' AFTER `hitMask`;
