-- Scripts/UtgardePinnacle: Fixed harpoon
delete from `conditions` where `SourceEntry` = 56578 and `ConditionValue2` = 26693;
insert into `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) values (13, 56578, 18, 1, 26693);