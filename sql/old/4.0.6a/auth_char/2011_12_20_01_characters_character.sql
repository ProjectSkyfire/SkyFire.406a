ALTER TABLE `characters`
  CHANGE COLUMN `petSlotUsed` `petSlotUsed` BIGINT(10) NULL DEFAULT NULL AFTER `currentPetSlot`,
  CHANGE COLUMN `grantableLevels` `grantableLevels` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `petSlotUsed`,
  DROP COLUMN `ammoId`;
