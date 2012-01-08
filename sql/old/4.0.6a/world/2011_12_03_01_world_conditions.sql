-- Blackwhelp Net target fix
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceID`=18 AND `SourceEntry`=31129 AND `SourceGroup`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (18,0,31129,19,0,21387,0,0,0,'Blackwhelp Net should only target Wyrmcult Blackwhelps');

-- Wolpertinger Net target fix
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceID`=18 AND `SourceEntry`=32907 AND `SourceGroup`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`elseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES (18,0,32907,19,0,23487,0,0,0,'Wolpertinger Net should only target Wild Wolpertingers');
