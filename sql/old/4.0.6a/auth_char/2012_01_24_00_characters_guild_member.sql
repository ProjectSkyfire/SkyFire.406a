ALTER TABLE `guild_member` ADD COLUMN `FirstProffLevel` int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `BankRemSlotsTab7`;
ALTER TABLE `guild_member` ADD COLUMN `FirstProffSkill` int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `FirstProffLevel`;
ALTER TABLE `guild_member` ADD COLUMN `FirstProffRank` int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `FirstProffSkill`;
ALTER TABLE `guild_member` ADD COLUMN `SecondProffLevel` int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `FirstProffRank`;
ALTER TABLE `guild_member` ADD COLUMN `SecondProffSkill` int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `SecondProffLevel`;
ALTER TABLE `guild_member` ADD COLUMN `SecondProffRank` int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `SecondProffSkill`;