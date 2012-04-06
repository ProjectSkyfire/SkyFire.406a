ALTER TABLE `conditions` ADD COLUMN `NegativeCondition` tinyint(3) UNSIGNED NOT NULL default '0' AFTER `ConditionValue3`;

-- CONDITION_NO_AURA -> CONDITION_AURA + NegativeCondition
DELETE FROM `conditions` WHERE `NegativeCondition`=1 AND `ConditionTypeOrReference`=1;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) SELECT `SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`, 1 ,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`, 1 ,`ErrorTextId`,`ScriptName`,`Comment` FROM `conditions` WHERE `ConditionTypeOrReference`=11;
DELETE FROM `conditions` WHERE `ConditionTypeOrReference`=11;

-- CONDITION_NOITEM -> CONDITION_ITEM + NegativeCondition
DELETE FROM `conditions` WHERE `NegativeCondition`=1 AND `ConditionTypeOrReference`=2;                                                                                                                                                                                                                                                                          -- not a typo
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) SELECT `SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`, 2 ,`ConditionValue1`, 1 ,`ConditionValue2`, 1 ,`ErrorTextId`,`ScriptName`,`Comment` FROM `conditions` WHERE `ConditionTypeOrReference`=26;
DELETE FROM `conditions` WHERE `ConditionTypeOrReference`=26;

-- CONDITION_SPELL with ConditionValue2 = 1 -> CONDITION_SPELL + NegativeCondition
UPDATE `conditions` SET `NegativeCondition` = 1, `ConditionValue2` = 0 WHERE `ConditionTypeOrReference` = 25 AND `ConditionValue2` = 1;

ALTER TABLE `conditions` ADD COLUMN `ConditionTarget` tinyint(3) UNSIGNED NOT NULL default '0' AFTER `ConditionTypeOrReference`;

