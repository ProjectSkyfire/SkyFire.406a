-- Updated the title data fields for "Sergeant Major <name>" Was removed in cata but remains in the DBC.
DELETE FROM conditions WHERE SourceEntry= 60535;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
 (13, 1, 60535, 0, 15, 31, 0, 5, 192117, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 5, 31, 0, 5, 192069, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 0, 31, 0, 5, 191440, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 2, 31, 0, 5, 191445, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 6, 31, 0, 5, 192070, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 18, 31, 0, 5, 192852, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 17, 31, 0, 5, 192850, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 9, 31, 0, 5, 192085, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 19, 31, 0, 5, 192853, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 20, 31, 0, 5, 192854, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 12, 31, 0, 5, 192088, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 16, 31, 0, 5, 192119, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 14, 31, 0, 5, 192116, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 7, 31, 0, 5, 192083, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 1, 31, 0, 5, 191444, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 11, 31, 0, 5, 192087, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 8, 31, 0, 5, 192084, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 13, 31, 0, 5, 192089, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 3, 31, 0, 5, 191665, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 4, 31, 0, 5, 192067, 0, 0, 0, '', NULL),
 (13, 1, 60535, 0, 10, 31, 0, 5, 192086, 0, 0, 0, '', NULL);
 