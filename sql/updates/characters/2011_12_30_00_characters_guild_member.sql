ALTER TABLE guild_member
  ADD COLUMN `BankResetTimeTab6` int(10) unsigned NOT NULL DEFAULT '0' AFTER `BankRemSlotsTab5`,
  ADD COLUMN `BankRemSlotsTab6` int(10) unsigned NOT NULL DEFAULT '0' AFTER `BankResetTimeTab6`,
  ADD COLUMN `BankResetTimeTab7` int(10) unsigned NOT NULL DEFAULT '0' AFTER `BankRemSlotsTab6`,
  ADD COLUMN `BankRemSlotsTab7` int(10) unsigned NOT NULL DEFAULT '0' AFTER `BankResetTimeTab7`;
