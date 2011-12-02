ALTER TABLE `characters` DROP COLUMN `stable_slots`;
ALTER TABLE `characters` ADD COLUMN `currentPetSlot` int(10) AFTER `actionBars`;
ALTER TABLE `characters` ADD COLUMN `petSlotUsed` int(10) AFTER `currentPetSlot`;