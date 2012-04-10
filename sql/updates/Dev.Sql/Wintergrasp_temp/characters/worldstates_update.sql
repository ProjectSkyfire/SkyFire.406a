-- update worldstates
DELETE FROM `worldstates` WHERE `entry` IN (33280,55629);
INSERT  INTO `worldstates`(`entry`,`value`,`comment`) VALUES (33280,1,NULL);
INSERT  INTO `worldstates`(`entry`,`value`,`comment`) VALUES (55629,1,NULL);