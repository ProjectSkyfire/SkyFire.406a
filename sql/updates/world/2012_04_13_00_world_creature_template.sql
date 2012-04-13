-- Update proper modelid for Celestial Steed (31957 is wrong)
UPDATE `creature_template` SET `modelid1`=31958,`modelid2`=0 WHERE `entry`=40625;
-- Update modelid for Invincible (with not bugged animation)
UPDATE `creature_template` SET `modelid1`=31007,`modelid2`=0,`WDBVerified`=-12340 WHERE `entry`=38545;
