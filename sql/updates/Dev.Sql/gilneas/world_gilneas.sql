/* 
* sql\updates\world\creature.sql 
*/ 
-- NPC Prince Liam Greymane 34850(Phase 1)
DELETE FROM `creature` WHERE `id`=34850;
INSERT INTO `creature` VALUES (@, 34850, 638, 1, 1, 0, 34913, -1447.71, 1409.86, 35.5561, 0.0125672, 300, 0, 0, 98, 115, 0, 0, 0, 0, 0);

-- NPC Prince Liam Greymane 34913 (Phase 2+4)
DELETE FROM `creature` WHERE `id`=34913;
INSERT INTO `creature` VALUES (@, 34913, 638, 1, 6, 0, 34913, -1437.23, 1401.34, 35.556, 3.22987, 300, 0, 0, 98, 115, 0, 0, 0, 0, 0);

-- 1x 34863 Lietenant Walden (Phase 1)
DELETE FROM `creature` WHERE `id` = 34863;
INSERT INTO `creature` VALUES (@, 34863, 638, 7, 1, 0, 34916, -1405.486, 1447.415, 35.63926, 0, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);

-- 8x 39095 Slain Guard (Phase 1)
DELETE FROM `creature` WHERE `id` = 39095;
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1669.826, 1435.016, 52.37046, 0.4537856, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1686.365, 1381.307, 52.37962, 0, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1735.67, 1437.476, 52.37084, 1.937315, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1715.153, 1435.698, 21.75196, 0, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1738.149, 1408.92, 21.75196, 0.1745329, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1701.415, 1378.955, 23.04241, 0, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1404.509, 1435.073, 35.63926, 3.804818, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);
INSERT INTO `creature` VALUES (@, 39095, 638, 7, 1, 0, 34916, -1396.684, 1445.738, 36.04398, 0, 300, 0, 0, 69, 79, 0, 0, 0, 4, 32);

-- 13x 34864 Gilneas City Guard (Phase 1)
DELETE FROM `creature` WHERE `id` = 34864;
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1444.95, 1414.047, 35.63924, 3.228859, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1444.941, 1418, 35.63924, 3.263766, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1441.144, 1418.014, 35.63924, 3.263766, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1441.104, 1413.96, 35.63924, 3.228859, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1444.915, 1410.274, 35.63924, 3.193953, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1441.116, 1410.38, 35.63924, 3.193953, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1441.002, 1397.965, 35.63926, 3.124139, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1441.313, 1402.193, 35.63924, 3.141593, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1441.21, 1405.986, 35.63924, 3.159046, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1444.939, 1398.372, 35.63924, 3.124139, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1444.622, 1402.186, 35.63924, 3.141593, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34864, 638, 7, 1, 0, 34916, -1444.934, 1405.981, 35.63924, 3.159046, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (3486400, 34864, 638, 1, 1, 0, 34916, -1430.47, 1345.55, 35.57663, 1.780236, 300, 0, 0, 69, 79, 0, 0, 0, 0, 0); -- guid must be static, because of creature_addon

-- 34916 Gilneas City Guard in phase 2+4(=6)
DELETE FROM `creature` WHERE `id` = 34916 AND `map` = 638;
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1440.47, 1420.69, 35.5564, 3.14412, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1436.13, 1394.69, 35.5564, 4.33383, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1461.53, 1430.1, 35.5563, 3.13584, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1535.63, 1436.08, 35.7435, 6.24994, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1557.11, 1386.33, 35.6834, 1.57735, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1548.53, 1421.76, 35.5562, 4.63955, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1499.42, 1380.68, 35.5561, 1.62365, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1506.98, 1401.15, 35.5561, 2.34198, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1526.96, 1388.05, 35.5562, 0.231602, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1511.85, 1398.82, 35.5561, 0.049396, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1541.35, 1404.07, 35.5562, 2.3148, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1555.94, 1407.04, 35.5562, 0.0721774, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1417.16, 1366.91, 35.5568, 1.9821, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1456.52, 1391.31, 35.5564, 3.13433, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1447.38, 1361.1, 35.5568, 1.75433, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1403.71, 1379.57, 35.5568, 2.26117, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1487.81, 1404.46, 35.5561, 4.29589, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1528.73, 1329.09, 35.5562, 1.96026, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1552.29, 1338.98, 35.5562, 1.34058, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1495.28, 1349.98, 35.5572, 3.23889, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34916, 638, 1, 6, 0, 34916, -1512.39, 1342.46, 35.5562, 0.664352, 300, 5, 0, 84000, 0, 0, 1, 0, 0, 0);

-- 34884 Rampaging Worgen in phases 2+4(=6)
DELETE FROM `creature` WHERE `id` = 34884;
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1437.58, 1397.96, 35.5564, 1.59687, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1437.86, 1404.88, 35.5566, 4.77052, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1443.63, 1421.04, 35.5561, 5.33929, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1460.43, 1433.96, 35.716, 3.27291, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1470.61, 1422.06, 35.5562, 2.47966, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1499.15, 1428.62, 35.5562, 2.49851, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1518.02, 1435.13, 35.7051, 2.98388, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1533.9, 1429.27, 35.5566, 2.86372, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1553.53, 1422.92, 35.5566, 4.72275, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1551.08, 1407.41, 35.5566, 4.49185, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1560.64, 1391.84, 35.7602, 4.85941, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1551.7, 1382.98, 35.5618, 6.03751, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1527.82, 1389.53, 35.5561, 0.166659, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1519.17, 1392.23, 35.5561, 0.722722, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1510.81, 1391.19, 35.5561, 5.82545, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1502.11, 1381.81, 35.5561, 0.209071, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1492.05, 1397.76, 35.5561, 1.35183, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1474.72, 1390.96, 35.5561, 5.62989, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1459.62, 1388.09, 35.5561, 0.0771246, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1444.19, 1364.19, 35.5563, 5.0055, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1417.06, 1371.12, 35.5563, 0.814614, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1487.37, 1345.63, 35.5572, 3.07395, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1505.54, 1340.62, 35.5563, 2.95378, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1523.54, 1337.85, 35.5563, 3.84914, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1546.78, 1334.13, 35.5563, 2.41107, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1489.1, 1354.05, 35.5801, 3.34962, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1519.87, 1354.65, 35.9377, 3.65122, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1536.66, 1353.73, 35.9706, 3.41324, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34884, 638, 1, 6, 0, 0, -1406.45, 1370.29, 35.556, 1.9956, 300, 5, 0, 42, 0, 0, 1, 0, 0, 0);

-- 35660 Rampaging Worgen spawned by script in phases 2+4
DELETE FROM `creature` WHERE `id` = 35660; -- 35660 spawned only by script!

-- 34936 Gwen Armstead
DELETE FROM `creature` WHERE `id` = 34936;
INSERT INTO `creature` VALUES (@, 34936, 638, 1, 2, 0, 34936, -1465.22, 1403.52, 35.6392, 4.59022, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);

-- 8x 34851 Panicked Citizen (Phase 1) running, movement type 2
DELETE FROM `creature` WHERE `id` = 34851;
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1432.875, 1431.646, 35.63927, 3.560472, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1517.184, 1358.682, 35.67543, 5.585053, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1476.811, 1439.623, 35.63926, 5.585053, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1475.917, 1355.622, 35.63927, 5.585053, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1398.113, 1431.059, 35.63926, 3.176499, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1545.533, 1436.92, 35.8738, 5.585053, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1566.021, 1390.835, 36.08628, 0.08726646, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1557.66, 1333.977, 35.63924, 1.43117, 0, 0, 0, 42, 0, 0, 2, 0, 0, 0);
-- 8x standing at square
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1559.502, 1384.313, 36.2494, 0.5759587, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1511.776, 1382.741, 35.95466, 1.099557, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1470.285, 1384.361, 36.08721, 1.099557, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1510.833, 1437.731, 35.94954, 5.532694, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1521.514, 1403.049, 35.63925, 4.520403, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1559, 1419.451, 35.79858, 5.532694, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1458.681, 1418.543, 35.63924, 1.029744, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 34851, 638, 1, 1, 0, 0, -1453.01, 1437.085, 35.94489, 5.096361, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);

-- 10x 44086 Panicked Citizen (Phase 1) infront of gates, not moving, emoting, speaking
DELETE FROM `creature` WHERE `id` = 44086;
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1431.38, 1356.77, 35.63923, 4.834562, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1432.83, 1354.98, 35.63923, 4.956735, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1432.97, 1352.17, 35.63923, 5.061455, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1435.73, 1355.46, 35.63923, 5.148721, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1435.15, 1352.44, 35.63923, 5.218534, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1428.64, 1356.64, 35.63923, 4.625123, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1430.37, 1353.85, 35.63923, 4.764749, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1427.55, 1354.11, 35.63923, 4.520403, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1437.52, 1350.65, 35.63923, 5.410521, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1438.47, 1353.14, 35.63923, 5.427974, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
-- 11x infront of gate in military district gate + 1 standing near slain citizen
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1673.36, 1348.91, 15.32633, 5.096361, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1769.48, 1339.98, 20.03683, 3.769911, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1770.6, 1337.48, 20.03943, 1.43117, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1773.59, 1332.55, 19.96173, 2.146755, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1771.85, 1339.88, 20.04223, 6.143559, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1774.83, 1333.91, 19.96123, 5.497787, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1774.7, 1337.94, 20.04733, 3.996804, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1777.4, 1344.69, 19.93393, 5.061455, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1776.7, 1343.02, 19.86513, 2.146755, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1778.8, 1339.37, 19.88103, 3.839724, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1776.27, 1339.79, 19.92853, 3.944444, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (@, 44086, 638, 1, 1, 0, 0, -1777.36, 1337.95, 19.95563, 3.839724, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);
-- 1x running along water channel, movement type 2, static_guid
INSERT INTO `creature` VALUES (4408600, 44086, 638, 1, 1, 0, 0, -1633.72, 1315.79, 19.7603, 1.55008, 300, 0, 0, 42, 0, 0, 2, 0, 0, 0);

-- 1x 44105 Slain Citizen
DELETE FROM `creature` WHERE `id` = 44105;
INSERT INTO `creature` VALUES (@, 44105, 638, 1, 1, 0, 0, -1674.79, 1346.61, 15.33933, 5.096361, 300, 0, 0, 42, 0, 0, 0, 0, 4, 32);

-- 3x 4075 Rat (Phase 1), static guid needed because od waypoint_data
DELETE FROM `creature` WHERE `id` = 4075 and `map` = 638;
INSERT INTO `creature` VALUES (407500, 4075, 638, 1, 1, 0, 4075, -1402.63, 1419.77, 35.5561, 3.22454, 300, 0, 0, 21, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (407501, 4075, 638, 1, 1, 0, 4075, -1527.87, 1362.03, 36.005, 4.17488, 300, 0, 0, 21, 0, 0, 2, 0, 0, 0);
INSERT INTO `creature` VALUES (407502, 4075, 638, 1, 1, 0, 4075, -1430.29, 1439.38, 35.9533, 3.48294, 300, 0, 0, 21, 0, 0, 2, 0, 0, 0);

-- Clean up --
-- 34511 Forsaken Invader
DELETE FROM `creature` WHERE `id` = 34511 AND `map`= 638 AND `phaseMask` = 1; -- Delete incorrect spawn in CTDB
-- 34981, 35836 Frightened Citizen
DELETE FROM `creature` WHERE `id` IN (34981, 35836); -- spawned by script 
 
/* 
* sql\updates\world\creature_addon.sql 
*/ 
-- 44086 Panicked Citizen, running along water channel
REPLACE INTO `creature_addon` VALUES (4408600, 44086000, 0, 0, 0, 0, '');

-- 4075 Rat
REPLACE INTO `creature_addon` VALUES (407500, 4075000, 0, 0, 0, 0, '');
REPLACE INTO `creature_addon` VALUES (407501, 4075010, 0, 0, 0, 0, '');
REPLACE INTO `creature_addon` VALUES (407502, 4075020, 0, 0, 0, 0, '');
 
 
/* 
* sql\updates\world\creature_equip_template.sql 
*/ 
-- NPC Prince Liam Greymane 34913 (Phase 2+4)
REPLACE INTO `creature_equip_template` VALUES (34913, 23505, 66439, 0); -- rapier + gun

-- 34916 Gilneas City Guard
REPLACE INTO `creature_equip_template` VALUES (34916, 25143, 54990, 0); -- sword + shield

-- 34936 Gwen Armstead
REPLACE INTO `creature_equip_template` VALUES (34936, 23505, 0, 0); -- rapier
 
 
/* 
* sql\updates\world\creature_involvedrelation.sql 
*/ 
-- NPC Prince Liam Greymane 34850(Phase 1)
DELETE FROM `creature_involvedrelation` WHERE `id` = 34850;
 
 
/* 
* sql\updates\world\creature_template.sql 
*/ 
-- Bloodfang Worgen 35118
REPLACE INTO `creature_template` VALUES (35118, 0, 0, 0, 0, 0, 36772, 36771, 36770, 0, 'Bloodfang Worgen', '', '', 0, 2, 3, 0, 16, 16, 3, 1, 1.14286, 1, 0, 13, 17, 0, 42, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 9, 13, 0, 7, 0, 35118, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 1);

-- NPC Prince Liam Greymane 34850(Phase 1)
REPLACE INTO `creature_template` VALUES (34850, 0, 0, 0, 0, 0, 29463, 0, 0, 0, 'Prince Liam Greymane', '', '', 0, 5, 5, 0, 1, 1, 3, 1, 1.14286, 1, 0, 4, 5, 0, 0, 1, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 3, 4, 0, 7, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 34913, 0, 0, 'npc_prince_liam_greymane_phase1', 1);

-- NPC Prince Liam Greymane 34913 (Phase 2+4)
REPLACE INTO `creature_template` VALUES (34913, 0, 0, 0, 0, 0, 29463, 0, 0, 0, 'Prince Liam Greymane', '', '', 0, 5, 5, 0, 1, 1, 3, 1, 1.14286, 1, 0, 4, 5, 0, 0, 1, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 3, 4, 0, 7, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 34913, 0, 0, 'npc_prince_liam_greymane_phase2', 1);

-- 34863 Lietenant Walden
REPLACE INTO `creature_template` VALUES (34863, 0, 0, 0, 0, 0, 29476, 0, 0, 0, 'Lieutenant Walden', '', '', 0, 3, 3, 0, 1, 1, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 4, 32, 0, 0, 0, 0, 0, 0, 0, 0, 7, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_lieutenant_walden', 1);

-- 39095 Slain Guard
REPLACE INTO `creature_template` VALUES (39095, 0, 0, 0, 0, 0, 29466, 29467, 0, 0, 'Slain Guard', '', '', 0, 3, 3, 0, 1, 1, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 4, 32, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 1);

-- 34864 Gilneas City Guard in phase 1
REPLACE INTO `creature_template` VALUES (34864, 0, 0, 0, 0, 0, 29466, 29467, 0, 0, 'Gilneas City Guard', '', '', 0, 3, 3, 0, 1, 1, 0, 1, 1.14286, 1, 0, 6, 8, 0, 0, 1, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 34916, 0, 0, 'npc_gilneas_city_guard_phase1', 1);

-- 34916 Gilneas City Guard in phase (1+)2+4
REPLACE INTO `creature_template` VALUES (34916, 0, 0, 0, 0, 0, 29466, 29467, 0, 0, 'Gilneas City Guard', '', '', 0, 1, 1, 0, 1, 1, 0, 1, 1.14286, 1, 0, 4, 5, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 34916, 0, 0, 'npc_gilneas_city_guard_phase2', 1);

-- 34884 Rampaging Worgen in phases 2+4
REPLACE INTO `creature_template` VALUES (34884, 0, 0, 0, 35660, 0, 36770, 36771, 0, 0, 'Rampaging Worgen', '', '', 0, 1, 2, 0, 32, 32, 0, 1, 1.14286, 1, 0, 4, 5, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 34884, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, '', 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_rampaging_worgen', 1);

-- 35660 Rampaging Worgen spawned by script in phases 2+4
REPLACE INTO `creature_template` VALUES (35660, 0, 0, 0, 34884, 0, 36770, 36771, 0, 0, 'Rampaging Worgen', '', '', 0, 2, 2, 0, 16, 16, 0, 1, 1.14286, 1, 0, 4, 5, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 35660, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, '', 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_rampaging_worgen2', 1);

-- 34936 Gwen Armstead
REPLACE INTO `creature_template` VALUES (34936, 0, 0, 0, 0, 0, 29290, 0, 0, 0, 'Gwen Armstead', '', '', 0, 1, 1, 0, 1, 1, 3, 1, 1.14286, 1, 0, 4, 5, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 34936, 0, 0, '', 1);

-- 34981, 35836 Frightened Citizen
REPLACE INTO `creature_template` VALUES (34981, 0, 0, 0, 0, 0, 30214, 30215, 30217, 30218, 'Frightened Citizen', '', '', 0, 1, 1, 0, 1, 1, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 512, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_frightened_citizen', 1);
REPLACE INTO `creature_template` VALUES (35836, 0, 0, 0, 0, 0, 30217, 30218, 30215, 30216, 'Frightened Citizen', '', '', 0, 1, 1, 0, 1, 1, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 512, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_frightened_citizen', 1);

-- 34851, 44086 Panicked Citizen
REPLACE INTO `creature_template` VALUES (34851, 0, 0, 0, 0, 0, 30217, 30218, 30214, 30216, 'Panicked Citizen', '', '', 0, 1, 1, 0, 1, 1, 0, 1, 1.14286, 1, 0, 2, 2, 0, 24, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_panicked_citizen_2', 1);
REPLACE INTO `creature_template` VALUES (44086, 0, 0, 0, 0, 0, 30217, 30218, 30214, 30216, 'Panicked Citizen', '', '', 0, 1, 1, 0, 35, 35, 0, 1, 1.14286, 1, 0, 13, 17, 0, 42, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 9, 13, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_panicked_citizen', 1);

-- 44105 Slain Citizen
REPLACE INTO `creature_template` VALUES (44105, 0, 0, 0, 0, 0, 30217, 30218, 30214, 30216, 'Slain Citizen', '', '', 0, 1, 1, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 4, 32, 0, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 1);

-- 4075 Rat
REPLACE INTO `creature_template` VALUES (4075, 0, 0, 0, 0, 0, 1141, 1418, 2176, 0, 'Rat', '', NULL, 0, 1, 1, 0, 31, 31, 0, 1, 0.8, 1, 0, 2, 2, 0, 24, 3.5, 2000, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 1, 1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 1, 3, 0.5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 100, 1, 4075, 0, 2, '', 12340);
 
 
/* 
* sql\updates\world\creature_template_addon.sql 
*/ 
-- Panicked Citizen emote state 34851, 44086
REPLACE INTO `creature_template_addon` VALUES (34851, 0, 0, 0, 0, 431, NULL); -- cowering in fear
REPLACE INTO `creature_template_addon` VALUES (44086, 0, 0, 0, 0, 431, NULL); -- cowering in fear

-- Prince Liam Greymane 34913 Phase 2+4(=6)
REPLACE INTO `creature_template_addon` VALUES (34913, 0, 2410, 0, 0, 0, NULL); -- mounted

-- Prince Liam Greymane 34850 Phase 1
REPLACE INTO `creature_template_addon` VALUES (34850, 0, 2410, 0, 0, 0, NULL); -- mounted

-- Lieutenant Walden 34863
REPLACE INTO `creature_template_addon` VALUES (34863, 0, 0, 7, 0, 65, NULL); -- appear dead

-- Slain Guards
REPLACE INTO `creature_template_addon` VALUES (39095, 0, 0, 7, 0, 65, NULL); -- appear dead

-- 44105 Slain Citizen
REPLACE INTO `creature_template_addon` VALUES (44105, 0, 0, 7, 0, 65, ''); -- dead flag

-- Gwen Armstead 34936 Phase 1
REPLACE INTO `creature_template_addon` VALUES (34936, 0, 0, 0, 0, 375, NULL); -- Ready 2H
 
 
/* 
* sql\updates\world\creature_text_fixes.sql 
*/ 
-- CTDB Bug fix... Wrong sound ids in wrong entries
UPDATE `creature_text` SET `sound` = 0 WHERE entry IN(42722, 31111, 240);

-- Already added in script_texts
DELETE FROM `creature_text` WHERE `entry` = 34850; 
 
/* 
* sql\updates\world\dev_script_waypoint.sql 
*/ 
-- Panicked Citizens Waypoints, only for development
DELETE FROM `script_waypoint` WHERE `entry` = 34851;
INSERT INTO `script_waypoint` VALUES (34851, 0, -1566.02, 1390.83, 36.0032, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 1, -1558.73, 1402.79, 36.0235, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 2, -1547.98, 1424.54, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 3, -1532.51, 1421.62, 35.5542, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 4, -1528.98, 1417.29, 35.5486, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 5, -1512.02, 1416.73, 35.5546, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 6, -1507.48, 1395.54, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 7, -1481.48, 1397.29, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 8, -1442.48, 1402.54, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 9, -1431.01, 1414.15, 36.0051, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 10, -1411.48, 1416.89, 35.556, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 11, -1403.48, 1403.79, 36.368, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 12, -1392.73, 1404.54, 36.0235, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 20, -1554.83, 1435.67, 35.862, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 21, -1555.83, 1370.97, 35.7729, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 22, -1567.9, 1319.63, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 23, -1575.96, 1316.9, 35.6613, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 24, -1602.9, 1312.18, 18.6024, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 25, -1653.84, 1298.35, 20.2844, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 26, -1653.83, 1297.69, 20.6563, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 30, -1430.33, 1380.1, 35.9986, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 31, -1443.77, 1393.83, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 32, -1493.24, 1395.46, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 33, -1498.95, 1401.16, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 34, -1505.27, 1424.45, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 35, -1523.75, 1431.33, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 36, -1537.52, 1442.04, 35.9924, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 37, -1537.58, 1443.49, 36.2197, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 40, -1508.09, 1418.65, 35.556, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 41, -1481.79, 1425.94, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 42, -1446.81, 1425.7, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 43, -1430.25, 1435.19, 35.8471, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 44, -1428.56, 1436.68, 35.8276, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 45, -1427.39, 1436.74, 36.0647, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 50, -1527.87, 1385.33, 36.0039, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 51, -1527.9, 1385.91, 36.0039, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 52, -1527.9, 1385.91, 36.0039, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 53, -1548.23, 1409.73, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 54, -1541.5, 1419.58, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 55, -1527.95, 1423.09, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 56, -1510.47, 1423.91, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 57, -1476.95, 1427.05, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 58, -1463.98, 1440.68, 35.9795, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 59, -1464.05, 1443.43, 36.1846, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 60, -1461.12, 1385.44, 36.0038, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 61, -1462.58, 1394.63, 35.5559, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 62, -1481.02, 1396.93, 35.5559, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 63, -1490.98, 1404.75, 35.5559, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 64, -1503.92, 1427.83, 35.5559, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 65, -1535.22, 1438.28, 35.8835, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 66, -1537.48, 1441.27, 35.9838, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 67, -1537.49, 1442.52, 35.9968, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 70, -1526.45, 1417.26, 35.5539, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 71, -1499.59, 1421.65, 35.5556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 72, -1494.79, 1395.92, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 73, -1472.77, 1393.62, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 74, -1439.77, 1372.62, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 75, -1404.88, 1372.45, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 76, -1404.25, 1387.27, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 77, -1396.93, 1403.14, 35.9617, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 78, -1394.81, 1403.23, 36.3069, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 80, -1476.64, 1440.43, 35.9767, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 81, -1483.37, 1431.67, 35.5561, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 82, -1501.7, 1403.94, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 83, -1505.28, 1343.45, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 84, -1570.7, 1318.5, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 85, -1576.12, 1317.7, 35.6618, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 86, -1602.52, 1313.39, 18.8297, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 87, -1684.82, 1305.89, 19.7826, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 88, -1693.14, 1296.73, 20.2849, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 89, -1693.46, 1294.45, 20.2843, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 90, -1545.79, 1401.09, 35.5565, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 91, -1546.99, 1368.88, 36.004, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 92, -1512.94, 1360.46, 36.0008, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 93, -1487.13, 1337.06, 35.854, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 94, -1486.43, 1334.71, 36.3382, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 100, -1479.38, 1385.88, 36.0043, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 101, -1482.24, 1390.25, 35.5561, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 102, -1518.33, 1391.43, 35.5563, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 103, -1548.55, 1398.05, 35.556, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 104, -1559.93, 1408.89, 36.0108, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 105, -1561.57, 1409.17, 36.1485, 0, 'End');
INSERT INTO `script_waypoint` VALUES (34851, 110, -1431.14, 1380.33, 35.9987, 0, 'Start');
INSERT INTO `script_waypoint` VALUES (34851, 111, -1441.25, 1366.81, 35.5565, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 112, -1451.09, 1358.72, 35.5565, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 113, -1572.47, 1319.31, 35.5565, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 114, -1576.16, 1318.63, 35.6612, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 115, -1602.91, 1313.71, 18.6614, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 116, -1635.55, 1329.6, 19.8798, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 117, -1642.01, 1332.57, 19.8541, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 118, -1673.66, 1332.39, 15.1353, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 119, -1675.09, 1331.32, 15.4996, 0, NULL);
INSERT INTO `script_waypoint` VALUES (34851, 120, -1675.09, 1330.63, 15.9361, 0, 'End'); 
 
/* 
* sql\updates\world\gameobject.sql 
*/ 
-- Spawned Mailbox in Gilneas City... Please correct if phaseMask is not correct
DELETE FROM `gameobject` WHERE `map` = 638 AND `id` = 202591;
INSERT INTO `gameobject` VALUES (@, 202591, 638, 1, 7, -1496.19, 1409.73, 35.5562, 4.69959, 0, 0, 0.711617, -0.702568, 300, 0, 1);

-- Phase 1 gameobjects
DELETE FROM `gameobject` WHERE `id` IN (401862,401863,402361,402362) AND `map` = 638 AND `phaseMask` = 1;
INSERT INTO `gameobject` VALUES (@, 402362, 638, 1, 1, -1486.87, 1357.83, 35.8334, 0.0785386, 0, 0, 0.0392592, 0.999229, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1493.51, 1357.36, 35.7989, 0.0117798, 0, 0, 0.00588986, 0.999983, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1488.11, 1418.26, 35.5564, 5.04618, 0, 0, 0.579817, -0.814746, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1429.18, 1375.58, 35.687, 2.13628, 0, 0, 0.876305, 0.481757, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1539.91, 1346.38, 35.7626, 2.05381, 0, 0, 0.855701, 0.51747, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401863, 638, 1, 1, -1530.18, 1352.76, 36.0583, 5.66664, 0, 0, 0.303413, -0.952859, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 402361, 638, 1, 1, -1535.72, 1356.68, 35.817, 0.00391817, 0, 0, 0.00195908, 0.999998, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 402362, 638, 1, 1, -1543.96, 1356.11, 35.729, 2.45436, 0, 0, 0.941543, 0.336893, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1536.2, 1350.01, 35.9364, 2.52898, 0, 0, 0.953453, 0.301541, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 402362, 638, 1, 1, -1511.35, 1358.83, 35.5576, 0.0903118, 0, 0, 0.0451406, 0.998981, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 402361, 638, 1, 1, -1517.9, 1358.24, 35.63, 0.592967, 0, 0, 0.292159, 0.95637, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1519.77, 1353.63, 35.9139, 2.50934, 0, 0, 0.950447, 0.310888, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1568.27, 1338.49, 35.7816, 3.53429, 0, 0, 0.980786, -0.195089, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 402361, 638, 1, 1, -1453.15, 1370.15, 35.8176, 4.76344, 0, 0, 0.688829, -0.724924, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 402361, 638, 1, 1, -1449.85, 1370, 35.6124, 0.212054, 0, 0, 0.105828, 0.994384, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401863, 638, 1, 1, -1450.76, 1375.34, 35.7253, 5.14436, 0, 0, 0.539137, -0.842218, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1447.33, 1377.7, 35.5561, 4.08801, 0, 0, 0.890111, -0.455743, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401863, 638, 1, 1, -1428.45, 1443.51, 36.0091, 1.20166, 0, 0, 0.565327, 0.824867, 300, 0, 1);
INSERT INTO `gameobject` VALUES (@, 401862, 638, 1, 1, -1429.85, 1440.95, 35.9821, 1.19381, 0, 0, 0.562084, 0.82708, 300, 0, 1);

-- Supply Crate
DELETE FROM `gameobject` WHERE `id` = 195306;
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1470.16, 1382.9, 36.0044, 4.68124, 0, 0, 0.718032, -0.69601, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1493.2, 1380.59, 35.8557, 4.77078, 0, 0, 0.686166, -0.727445, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1549.53, 1305.57, 35.879, 0.288341, 0, 0, 0.143672, 0.989625, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1580.39, 1360.24, 35.9998, 4.65908, 0, 0, 0.7257, -0.688012, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1536.47, 1379.34, 36.0049, 0.00559856, 0, 0, 0.00279928, 0.999996, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1573.34, 1386.53, 36.5311, 4.58054, 0, 0, 0.752153, -0.658988, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1561.3, 1406.11, 36.1642, 3.21787, 0, 0, 0.999273, -0.0381279, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1555.25, 1437.56, 35.9326, 1.55282, 0, 0, 0.700723, 0.713433, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1533.82, 1443.16, 36.0041, 1.55282, 0, 0, 0.700723, 0.713433, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1529.38, 1415.91, 35.5483, 4.22318, 0, 0, 0.857301, -0.514815, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1500.18, 1441.23, 35.9867, 1.6078, 0, 0, 0.720067, 0.693904, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1468.17, 1443.02, 36.0026, 1.5646, 0, 0, 0.704914, 0.709292, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1441.36, 1441.24, 35.9884, 1.59209, 0, 0, 0.714595, 0.699539, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1462.29, 1412.72, 35.5559, 4.62765, 0, 0, 0.736423, -0.676521, 300, 0, 1);
INSERT INTO `gameobject` values (@, 195306, 638, 1, 6, -1521.32, 1407.05, 35.5562, 1.86462, 0, 0, 0.802999, 0.595981, 300, 0, 1);

-- Merchant Square Door
DELETE FROM `gameobject` WHERE  `id` = 195327;
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1394.08, 1403.29, 36.4232, 3.14, 0, 0, 1, 0.000795917, 0, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1549.02, 1309.71, 36.4268, 3.40029, 0, 0, 0.991646, -0.128989, 0, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1486.16, 1334.04, 36.4894, 1.85808, 0, 0, 0.801046, 0.598602, 0, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1562.9, 1409.65, 36.6444, 6.28119, 0, 0, 0.000997694, -1, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1513.93, 1371.12, 36.535, 0.002388, 0, 0, 0.001194, 0.999999, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1537.49, 1444.15, 36.572, 4.68448, 0, 0, 0.716906, -0.69717, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1463.98, 1444.47, 36.6447, 4.67034, 0, 0, 0.721816, -0.692085, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1576.71, 1335.87, 36.5351, 6.24978, 0, 0, 0.0167039, -0.99986, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1569.81, 1385.02, 36.9232, 1.54289, 0, 0, 0.69717, 0.716906, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1421.11, 1412.92, 36.7947, 1.55076, 0, 0, 0.699988, 0.714155, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1426.63, 1436.45, 36.4232, 3.15599, 0, 0, 0.999974, -0.00719772, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1529.32, 1322.13, 36.5852, 1.84564, 0, 0, 0.797308, 0.603573, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1583.43, 1358.93, 36.5342, 1.5574, 0, 0, 0.702356, 0.711826, 3600, 0, 1);
INSERT INTO `gameobject` values (@, 195327, 638, 1, 1039, -1493.61, 1371.21, 36.5382, 3.14155, 0, 0, 1, 0.0000227253, 3600, 0, 1);
 
 
/* 
* sql\updates\world\gameobject_loot_template.sql 
*/ 
-- Supply Crate
REPLACE INTO `gameobject_loot_template` VALUES (195306, 46896, -100, 1, 0, 1, 1); -- quest item
 
 
/* 
* sql\updates\world\gameobject_template.sql 
*/ 
-- Merchant Square Door
REPLACE INTO `gameobject_template` VALUES (195327, 10, 9023, 'Merchant Square Door', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 14098, 0, 25000, 0, 0, 0, 0, 0, 0, 66639, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', 'go_merchant_square_door', 13329);

-- Supply Crate
REPLACE INTO `gameobject_template` VALUES (195306, 3, 336, 'Supply Crate', '', '', '', 0, 0, 1, 46896, 0, 0, 0, 0, 0, 1691, 195306, 0, 1, 0, 0, 0, 0, 14094, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13329);

-- Mailbox (Gilneas City)
REPLACE INTO `gameobject_template` VALUES (202591, 19, 9139, 'Mailbox', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13329);

-- Doodads? (un-interactable objects)
REPLACE INTO `gameobject_template` VALUES (401862, 14, 8956, 'gilneas_bush_02', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623);
REPLACE INTO `gameobject_template` VALUES (401863, 14, 8957, 'gilneas_bush_05', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623);
REPLACE INTO `gameobject_template` VALUES (402361, 14, 10436, 'gilneas_bush_04', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623);
REPLACE INTO `gameobject_template` VALUES (402362, 14, 10437, 'gilneas_bush_03', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623);
 
 
/* 
* sql\updates\world\quest_template.sql 
*/ 
-- Phase 1 Start --
-- 14078 Lockdown!
REPLACE INTO `quest_template` VALUES (14078, 2, 4755, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 786432, 4, 0, 0, 0, 0, 0, 14091, 0, 14091, 5, 0, 0, 0, 'Lockdown!', 'What are you still doing here, citizen?  Haven\'t you heard?  The city\'s under complete lockdown.$B$BGo see Lieutenant Walden -- he\'ll give you further directions for evacuation.', 'Find Lieutenant Walden in the northwestern end of the Merchant Square.', 'Deep claw marks run through the man\'s corpse.', NULL, '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);

-- Phase 2 Start --
-- 14091 Something's Amiss
REPLACE INTO `quest_template` VALUES (14091, 2, 4755, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 786432, 4, 0, 0, 0, 0, 14078, 0, 0, 0, 5, 0, 0, 0, 'Something\'s Amiss', 'The lieutenant appears to have died from severe wounds.  The prince might want to hear this news.$B$BYou hear the sound of fighting coming from the market.', 'Return to Prince Liam Greymane in the Merchant Square.', 'It`s you again.  Looks like you`re not one to hide in the face of danger.  Very well, then.', NULL, '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);

-- 14093 All Hell Breaks Loose
REPLACE INTO `quest_template` VALUES (14093, 2, 4755, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14091, 14099, -14093, 0, 6, 0, 0, 0, 'All Hell Breaks Loose', 'Worgen!  My father had warned me that Archmage Arugal\'s creations had run amok.$B$BBut where are they coming from?$B$BI suppose it doesn\'t matter.  Help us make quick work of them.  We\'ll show them what we Gilneans are made of!', 'Prince Liam Greymane wants you to slay 6 Rampaging Worgen.', 'It`s no use, $N $B$B! They`re not letting up.', 'Have the worgen been dealt with?', '', 'Return to Prince Liam Greymane at the Merchant Square in Gilneas City.', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34884, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55004, 0, 0, 0, 1, 0, 0, 0, 1134, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);

-- 14098 Evacuate the Merchant Square
REPLACE INTO `quest_template` VALUES (14098, 2, 4755, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14091, 14099, -14093, 0, 6, 0, 0, 0, 'Evacuate the Merchant Square', 'The civilians aren\'t safe here anymore.  Not even inside their homes.$B$BWe\'re doing our best to stop the worgen from getting indoors, but their numbers are too great.$B$BHelp us by evacuating the civilian homes.  My father\'s army in the prison district will be able to better protect them.', 'Evacuate 3 Civilian Homes.', 'Good job, $N.  Thanks to you, many Gilneans will live to see another day.', NULL, '', 'Return to Prince Liam Greymane at the Merchant Square in Gilneas City.', 'Market Homes Evacuated', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35830, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);

-- 14094 Salvage the Supplies
REPLACE INTO `quest_template` VALUES (14094, 2, 4755, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 0, 0, -14093, 0, 6, 0, 0, 0, 'Salvage the Supplies', 'Listen, $N.  We can\'t let our supplies get destroyed.$B$BWith Gilneas walled off from the outside world, we won\'t last through winter if we lose much more of our stock.$B$BPlease help me salvage what you can.', 'Salvage 4 Supply Crates.', 'Excellent!  I\'ll make sure these get taken to a safe place.', 'Have you salvaged the supplies, $N?', '', 'Return to Gwen Armstead at the Merchant Square in Gilneas City.', '', '', '', '', 46896, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52040, 0, 0, 0, 1, 0, 0, 0, 1134, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);

-- 14099 Royal Orders
REPLACE INTO `quest_template` VALUES (14099, 2, 4755, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 786432, 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 'Royal Orders', 'It\'s time for you to leave, $N.  Go to the Military District with the other civilians.$B$BCheck in with Gwen Armstead when you cross the bridge to the southeast... see if everyone\'s okay.$B$BI will stay here with the guards and cover the civilians\' retreat.$B$BGo now.  That is an order!', 'Speak to Gwen Armstead in the Military District to the southeast.', 'We\'re all fine here.  A little shaken... but alive.', NULL, '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 150, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);

-- ##After this line quests are still being added## --
-- Phase 4 Start --
-- A Rejuvenating Touch
REPLACE INTO `quest_template` VALUES (14283, 2, 4755, -1024, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14280, 14291, 0, 14291, 3, 0, 0, 0, 'A Rejuvenating Touch', 'We were driven to the edge of extinction once before, $N. But we druids, keepers of the old ways, saved our people from famine.$B$BWhen we cut ourselves off from the outside world and our crops failed, it was our order who called upon the earth\'s blessings and restored the harvest.$B$BJust as we did then, it is best to put our fate in the hands of a higher power. Join me now and learn what the wild has to teach us.', 'Speak to Celestine of the Harvest and learn Healing Touch. Practice using Healing Touch 2 times on a Wounded Guard.', 'Not bad at all. Perhaps there is still hope for the old ways.', 'The earth speaks to us, $N. It will not abandon us even in these perilous times.', '', '', 'Practice Healing Touch', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47091, 0, 0, 0, 1, 0, 0, 0, 774, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 774, 0, 0, 1);

-- Charge
REPLACE INTO `quest_template` VALUES (14266, 2, 4755, -1, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14265, 14286, 0, 14286, 3, 0, 0, 0, 'Charge', 'You\'re alive, $N! That must mean I did something right.$B$BIt\'s a shame our lessons were cut off a little short. But perhaps there\'s a thing or two I can teach you that might be handy in a time like this.$B$BTry out your new technique against the bloodfang worgen to our west.', 'Speak to Sergeant Cleese and learn Charge. Practice using Charge against a Bloodfang Worgen.', 'Excellent work!', NULL, '', '', 'Practice Charge', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35118, 0, 0, 0, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 100, 0, 0, 1);

-- Eviscerate
REPLACE INTO `quest_template` VALUES (14272, 2, 4755, -8, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14269, 14285, 0, 14285, 3, 0, 0, 0, 'Eviscerate', 'Good to see you alive!$B$BNo, of course I don\'t have that gold I owe you. Now\'s not really the time to bring that up is it?$B$BListen, maybe I can teach you a trick or two that might save your skin with all the carnage going on. I\'d call it more than even then. What do you say?$B$BAfter your lesson is over, try using your new technique against the Bloodfang Worgen to our west.', 'Speak to Loren the Fence and learn Eviscerate. Practice using Eviscerate against a Bloodfang Worgen.', 'Don\'t get ahead of yourself now. Just remember who taught you everything you know.\r\n\r\nAnd now let\'s see if we can get out of this city with our skins attached.', NULL, '', '', 'Practice Eviscerate', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35118, 0, 0, 0, 1, 0, 0, 0, 2098, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 2098, 0, 0, 1);

-- Immolate
REPLACE INTO `quest_template` VALUES (14274, 2, 4755, -256, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14273, 14287, 0, 14287, 3, 0, 0, 0, 'Immolate', 'It is true then! You live!$B$BI never got a chance to share my greatest discovery with you. From the depths of the nigh-indecipherable books of Balcephoth of the felshadows... I\'ve learned the forbidden secrets of...$B$BImmolate!$B$BOf course I will share this knowledge with you... who else around here would appreciate such powerful understanding?$B$BGo now, and practice your new spell against the Bloodfang Worgen to our west.', 'Speak to Vitus Darkwalker and learn Immolate. Practice casting Immolate on a Bloodfang Worgen.', 'Yes! You can feel the power, can\'t you?', 'You\'re doing well, $N.', '', '', 'Practice Immolate', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35118, 0, 0, 0, 1, 0, 0, 0, 348, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 348, 0, 0, 1);

-- Steady Shot
REPLACE INTO `quest_template` VALUES (14276, 2, 4755, -4, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14275, 14290, 0, 14290, 3, 0, 0, 0, 'Steady Shot', 'So I\'ve got good news and bad news.$B$BThe bad news is that there are more worgen in the woods than in here... so we really have no safe place to go to.$B$BThe good news is that I still have a thing or two to teach you. Who knows the sort of skill that might save your life in a time like this.$B$BTry your hand at it against the bloodfang worgen to our west.', 'Speak to Huntsman Blake and learn Steady Shot. Practice using Steady Shot 2 times against a Bloodfang Worg.', 'Excellent work, $N. These worgen will regret ever setting foot in our lands.', 'You\'re a fast learner. We\'ll show these worgen who the real hunters are.', '', '', 'Practice Steady Shot', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35118, 0, 0, 0, 2, 0, 0, 0, 56641, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 56641, 0, 0, 13623);

-- Flash Heal
REPLACE INTO `quest_template` VALUES (14279, 2, 4755, -16, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14278, 14289, 0, 14289, 3, 0, 0, 0, 'Flash Heal', 'You have much to learn, $N. And I\'ve much to teach you.$B$BThese are perilous times, however, and I fear that we might have to accelerate certain lessons.$B$BHave no fear, $g brother:sister;. The Light will guide us through this.', 'Speak to Sister Almyra and learn Flash Heal. Use Flash Heal 2 times on a Wounded Guard.', 'You are blessed, $N. The Light shines upon you, even in these dark times.', 'You are learning swiftly, my dear.', '', '', 'Practice Flash Heal', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47091, 0, 0, 0, 2, 0, 0, 0, 2061, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 2061, 0, 0, 1);

-- Mage
REPLACE INTO `quest_template` VALUES (14277, 2, 4714, -128, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14099, 14281, 0, 0, 5, 0, 0, 0, 'Arcane Inquiries', 'Most of us made it here alive... but there are worgen on this side of the city as well.$B$BWe\'re going to continue heading south once everyone\'s accounted for.$B$BThat reminds me, someone was asking about you.  It was a mage named Myriam.  She mentioned something about you being "ready."', 'Speak to Myriam Spellwaker in the Military District.', 'A disciple of the arcane always finds a way forward. I\'m glad to see you, $N.', NULL, '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);
REPLACE INTO `quest_template` VALUES (14288, 2, 4714, -128, 1, 0, 3, 0, 2098253, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14281, 14157, 0, 14157, 2, 0, 0, 0, 'Safety in Numbers', 'There\'s only so much I can teach right now with all these worgen trying to dismember us.$B$BWe really should think about heading south with the other survivors.  We\'ve been told that King Greymane is there.$B$BIf we stick together our chances of survival will increase... especially if you choose someone nutritious-looking to stand next to.', 'Speak to King Genn Greymane in the military district.', 'You\'ve done well in coming here. If we Gilneans stick together we might yet defeat this terrible enemy.', NULL, '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);
REPLACE INTO `quest_template` VALUES (14281, 2, 4714, -128, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 14277, 14288, 0, 14288, 3, 0, 0, 0, 'Arcane Missiles', 'The path ahead is difficult, $N.  We must devote the entirety of our mental power to the task at hand.$B$BYet sometimes, that is not enough.  Sometimes the situation calls for raw firepower.$B$BI know just the spell for such a situation and I\'ll be more than glad to share it with you. Once you\'ve learned it, practice using it against the Bloodfang Worgen to our west. You\'ll only get the chance to use your new spell after casting a different spell.', 'Speak to Myriam Spellwaker and learn Arcane Missiles. Use Arcane Missiles against a Bloodfang Worgen.', 'You\'ve learned with such speed and ease. Soon you\'ll be the one doing the teaching.', 'I always knew you were a quick study!', '', '', 'Practice Arcane Missiles', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35118, 0, 0, 0, 1, 0, 0, 0, 5143, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 5143, 0, 0, 1);

-- Crowley, Lord Godfrey and King Grenn Greymane
REPLACE INTO `quest_template` VALUES (14157, 2, 4755, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 786432, 0, 0, 0, 0, 0, 0, 28850, 0, 28850, 1, 0, 0, 0, 'Old Divisions', 'Lord Darius Crowley has been called many things.  Rebel.  Traitor.  Terrorist.$B$BBefore the civil war I called him... friend.$B$BI never blamed him for leading an insurrection against me.  His land and people were separated from Gilneas by a stone wall... but we had no choice.$B$BRegardless... Crowley is exactly the type of person we need now.$B$BEnter Stoneward Prison and ask Captain Broderick about Crowley\'s whereabouts.  I\'d send my own men, but there\'s still bad blood.', 'Speak to Captain Broderick inside Stoneward Prison in Gilneas City.', 'Greymane wants to save Crowley? Has he gone mad?', NULL, '', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);
REPLACE INTO `quest_template` VALUES (24930, 2, 4755, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 524288, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 'While You\'re At It', 'Fine by me if King Greymane wants you to risk your life to rescue a known traitor.$B$BDo me a favor and do something useful while you\'re out there and kill these cursed fleabags.', 'Kill 5 Bloodfang Worgen.', 'If I hadn\'t seen you kill a few of the mangy things with my own eyes, I\'d think you did not complete the task I asked of you.$B$BIt looks like we\'re hardly putting a dent in their numbers.', NULL, '', 'Return to Lord Godfrey at the Military District in Gilneas City.', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35118, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 54975, 54978, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1134, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', 0, 0, 890, 878, 0, 0, 0, 1);
 
 
/* 
* sql\updates\world\script_texts.sql 
*/ 
-- Clean up first
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1638999 AND -1638000;

-- Prince Liam Greymane Phase 1
INSERT INTO `script_texts` VALUES (34850, -1638000, 'I want the perimeter secured and the gates manned by two guards at all times. No one gets in, no one gets out.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19615, 0, 0, 1, 'SAY_PRINCE_LIAM_GREYMANE_1 - Say OOC');
INSERT INTO `script_texts` VALUES (34850, -1638001, 'We protected Gilneas from the Scourge. We protected Gilneas during the Northgate rebellion. We will protect Gilneas from whatever this new threat may be.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19616, 0, 0, 25, 'SAY_PRINCE_LIAM_GREYMANE_2 - Say OOC');
INSERT INTO `script_texts` VALUES (34850, -1638002, 'Stand ready, guards! We don\'t know how many intruders we\'re dealing with, but the Headlands are overrun and we\'re cut off from the harbor towns. Expect to be outnumbered.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19614, 0, 0, 1, 'SAY_PRINCE_LIAM_GREYMANE_3 - Say OOC');

-- Prince Liam Greymane Phase 2
INSERT INTO `script_texts` VALUES (34913, -1638025, 'Stand your ground, men!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19617, 1, 0, 0, 'SAY_PRINCE_LIAM_GREYMANE - Phase 2 OOC');
INSERT INTO `script_texts` VALUES (34913, -1638026, 'Defeat these foul beasts!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19618, 1, 0, 0, 'SAY_PRINCE_LIAM_GREYMANE - Phase 2 OOC');
INSERT INTO `script_texts` VALUES (34913, -1638027, 'Protect the civilians!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19619, 1, 0, 0, 'SAY_PRINCE_LIAM_GREYMANE - Phase 2 OOC');
INSERT INTO `script_texts` VALUES (34913, -1638028, 'Push them back!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19620, 1, 0, 0, 'SAY_PRINCE_LIAM_GREYMANE - Phase 2 OOC');
INSERT INTO `script_texts` VALUES (34913, -1638029, 'Take heart, men! We must protect our city!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19621, 1, 0, 0, 'SAY_PRINCE_LIAM_GREYMANE - Phase 2 OOC');

-- Frightened Citizen 34981 with no worgen behind
INSERT INTO `script_texts` VALUES (34981, -1638003, 'Protect me, please!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_1a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638004, 'What in the world? Let\'s get out of here!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_2a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638005, 'Worgen! Worgen everywhere!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_3a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638006, 'Flee! They\'re everywhere!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_4a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638007, 'No time to Waste!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_5a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638008, 'This place isn\'t safe. Let\'s Leave!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_6a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638009, 'Let\'s go!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_7a - No worgen behind');
INSERT INTO `script_texts` VALUES (34981, -1638010, 'Thank you!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 1, 'SAY_FRIGHTENED_CITIZEN_8a - No worgen behind');
-- Frightened Citizen when worgen is behind them
INSERT INTO `script_texts` VALUES (35836, -1638011, 'I don\'t want to die!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 430, 'SAY_FRIGHTENED_CITIZEN_1b - Worgen behind');
INSERT INTO `script_texts` VALUES (35836, -1638012, 'There\'s one after me!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 430, 'SAY_FRIGHTENED_CITIZEN_2b - Worgen behind');
INSERT INTO `script_texts` VALUES (35836, -1638013, 'It\'s coming right for me!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 430, 'SAY_FRIGHTENED_CITIZEN_3b - Worgen behind');
INSERT INTO `script_texts` VALUES (35836, -1638014, 'Help!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 430, 'SAY_FRIGHTENED_CITIZEN_4b - Worgen behind');
INSERT INTO `script_texts` VALUES (35836, -1638015, 'Help me, please!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 430, 'SAY_FRIGHTENED_CITIZEN_5b - Worgen behind');

-- Panicked Citizen at gate
INSERT INTO `script_texts` VALUES (44086, -1638016, 'What\'s going on? I thought I saw something on the rooftops.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_PANICKED_CITIZEN_1 - Phase 1 at gate');
INSERT INTO `script_texts` VALUES (44086, -1638017, 'My children are in Stormglen alone! I have to get to them!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_PANICKED_CITIZEN_2 - Phase 1 at gate');
INSERT INTO `script_texts` VALUES (44086, -1638018, 'You can\'t do this to us!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_PANICKED_CITIZEN_3 - Phase 1 at gate');
INSERT INTO `script_texts` VALUES (44086, -1638019, 'What... what are those things on the rooftops?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_PANICKED_CITIZEN_4 - Phase 1 at gate');

-- Panicked Citizen, millitary distrcit
INSERT INTO `script_texts` VALUES (44086, -1638020, 'We have to get out of here! The howling gets louder every night.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_PANICKED_CITIZEN - Military distrcit');
INSERT INTO `script_texts` VALUES (44086, -1638021, 'They told us Gilneas City was safe...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_PANICKED_CITIZEN - Military distrcit');

-- Gilneas City Guard
INSERT INTO `script_texts` VALUES (34864, -1638022, 'No one\'s allowed to leave. Prince Liam\'s orders.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_GILNEAS_CITY_GUARD_1 - At gate');
INSERT INTO `script_texts` VALUES (34864, -1638023, 'Stay calm. We have everything under control.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_GILNEAS_CITY_GUARD_2 - At gate');
INSERT INTO `script_texts` VALUES (34864, -1638024, 'It isn\'t safe to leave, there\'s something lurking out there in the woods.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_GILNEAS_CITY_GUARD_3 - At gate');
 
 
/* 
* sql\updates\world\smart_scripts.sql 
*/ 
-- Scripted in C++
DELETE FROM `smart_scripts` WHERE `entryorguid` in (34850, 34913);
 
 
/* 
* sql\updates\world\waypoint_data.sql 
*/ 
-- Frightened Citizen, Waypoints to Quest Evacuate the Merchant Square
DELETE FROM `waypoint_data` WHERE `id` IN (349810, 349811);
INSERT INTO `waypoint_data` VALUES (349810, 1, -1544.83, 1429.68, 35.5559, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349810, 2, -1554.44, 1409.34, 35.5559, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349810, 3, -1554.34, 1388.02, 35.5861, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349810, 4, -1557.97, 1361.57, 35.5586, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349810, 5, -1560.59, 1333.97, 35.5571, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349810, 6, -1568.32, 1327.29, 35.5571, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349810, 7, -1577.35, 1317.59, 34.9365, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 1, -1463.96, 1429.41, 35.5573, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 2, -1429.19, 1422.41, 35.5573, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 3, -1419.33, 1419.23, 35.5573, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 4, -1406.9, 1416.03, 35.5573, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 5, -1403.28, 1401.21, 35.5573, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 6, -1407.48, 1375.36, 35.5573, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 7, -1502.08, 1342.68, 35.5574, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 8, -1537.7, 1330.3, 35.5574, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 9, -1562.15, 1319.15, 35.5574, 0, 0, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (349811, 10, -1577.96, 1316.79, 34.497, 0, 0, 0, 100, 0);

-- 44086 Panicked Citizen, running along water channel
DELETE FROM `waypoint_data` WHERE `id` = 44086000;
INSERT INTO `waypoint_data` VALUES (44086000, 1, -1634.19, 1412.11, 21.314, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 2, -1638.53, 1425.77, 21.6238, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 3, -1703.02, 1490.44, 21.0175, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 4, -1704.07, 1533.08, 21.1802, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 5, -1704.42, 1491.51, 20.9115, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 6, -1639.53, 1427.1, 21.6237, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 7, -1634.41, 1400.59, 20.453, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (44086000, 8, -1633.7, 1315.81, 19.7598, 0, 1, 0, 100, 0);

-- 3x 4075 Rat
DELETE FROM `waypoint_data` WHERE `id` = 4075000;
INSERT INTO `waypoint_data` VALUES (4075000, 1, -1433.89, 1421.07, 35.5559, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 2, -1484.9, 1425.92, 35.5559, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 3, -1492, 1424.62, 35.5559, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 4, -1496.78, 1418.42, 35.5559, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 5, -1501.61, 1395.67, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 6, -1502.72, 1352.37, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 7, -1500.34, 1347.83, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 8, -1493.42, 1345.02, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 9, -1408.42, 1370.55, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 10, -1403.66, 1373.63, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 11, -1400.05, 1414.78, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075000, 12, -1402.41, 1419.83, 35.5563, 0, 1, 0, 100, 0);
DELETE FROM `waypoint_data` WHERE `id` = 4075010;
INSERT INTO `waypoint_data` VALUES (4075010, 1, -1543.97, 1339.3, 35.5566, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 2, -1575.49, 1315.81, 35.6644, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 3, -1603.6, 1310.05, 18.2702, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 4, -1630.91, 1306.01, 19.6642, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 5, -1680.47, 1306.06, 19.7822, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 6, -1687.3, 1308.68, 19.7822, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 7, -1689.37, 1313.61, 19.7822, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 8, -1689.67, 1318.43, 19.8998, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 9, -1690.76, 1314.84, 19.7823, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 10, -1689.08, 1310.52, 19.7823, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 11, -1682.82, 1305.83, 19.7823, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 12, -1630.72, 1304.82, 19.663, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 13, -1603.36, 1309.06, 18.2764, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 14, -1575.83, 1315.44, 35.6622, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 15, -1544.38, 1339.52, 35.556, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 16, -1535.73, 1362.11, 36.0049, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075010, 17, -1528.51, 1361.75, 36.0052, 0, 1, 0, 100, 0);
DELETE FROM `waypoint_data` WHERE `id` = 4075020;
INSERT INTO `waypoint_data` VALUES (4075020, 1, -1442.48, 1437.52, 35.8841, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 2, -1448.95, 1439.34, 35.9533, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 3, -1472.77, 1440.34, 35.9766, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 4, -1487.13, 1437.07, 35.8374, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 5, -1505.39, 1437.3, 35.8491, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 6, -1511.07, 1442.2, 35.9948, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 7, -1525.7, 1442.89, 36.0012, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 8, -1551.64, 1435.29, 35.7656, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 9, -1556.61, 1431.64, 35.7314, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 10, -1560.33, 1424.26, 35.7231, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 11, -1560.25, 1400.16, 35.7565, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 12, -1573.95, 1401.09, 36.6264, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 13, -1559, 1400.37, 35.9364, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 14, -1560.23, 1426.14, 35.7563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 15, -1554.55, 1433.96, 35.8007, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 16, -1521.94, 1442.72, 35.9994, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 17, -1511.05, 1442.16, 35.9964, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 18, -1503.64, 1436.9, 35.8283, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 19, -1486.8, 1437.28, 35.8457, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 20, -1471.96, 1440.4, 35.9752, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 21, -1440.7, 1438.21, 35.9115, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (4075020, 22, -1430.61, 1439.22, 35.9444, 0, 1, 0, 100, 0);

-- 8x 34851 Panicked Citizen
DELETE FROM `waypoint_data` WHERE `id` in (34851000, 34851001, 34851002, 34851003, 34851004, 34851005, 34851006, 34851007);

INSERT INTO `waypoint_data` VALUES (34851000, 1, -1545.53, 1436.92, 35.8738, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 2, -1510.18, 1423.15, 35.5558, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 3, -1503.53, 1417.32, 35.5558, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 4, -1500.51, 1388.36, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 5, -1500.5, 1354.6, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 6, -1497.11, 1348.81, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 7, -1491.72, 1346.89, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 8, -1470.55, 1348.53, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 9, -1456.11, 1355.08, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 10, -1449.33, 1360.9, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 11, -1444.05, 1372.03, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 12, -1443.25, 1384.59, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 13, -1443.55, 1398.62, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 14, -1442.89, 1417.76, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 15, -1443.66, 1421.19, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 16, -1446.91, 1425.36, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 17, -1456.57, 1434.86, 35.7614, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851000, 18, -1463.8, 1443.64, 36.2962, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851001, 1, -1566.02, 1390.83, 36.0863, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 2, -1557.28, 1391.35, 35.6436, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 3, -1488.62, 1398.15, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 4, -1461.48, 1398.42, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 5, -1452.01, 1394.58, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 6, -1436.72, 1379.21, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 7, -1421.47, 1368.84, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 8, -1414.97, 1367.67, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 9, -1411.34, 1368.85, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 10, -1406.19, 1374.51, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 11, -1397.7, 1400.74, 35.9615, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851001, 12, -1394.69, 1403.24, 36.3531, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851002, 1, -1557.66, 1333.98, 35.6392, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 2, -1550.83, 1377.78, 35.5634, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 3, -1544.86, 1383.46, 36.005, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 4, -1533.14, 1388.9, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 5, -1463.1, 1390.45, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 6, -1455.05, 1387.38, 35.5609, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 7, -1444.5, 1377.41, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 8, -1442.24, 1368.35, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 9, -1444.45, 1361.21, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 10, -1454.69, 1354.13, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 11, -1475.67, 1345.73, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 12, -1486.48, 1336.21, 35.8587, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851002, 13, -1486.55, 1334.89, 36.2263, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851003, 1, -1475.92, 1355.62, 35.6393, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 2, -1467.99, 1354.19, 35.556, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 3, -1454.91, 1358.01, 35.556, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 4, -1453.42, 1370.94, 35.8678, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 5, -1454.97, 1380.76, 35.9353, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 6, -1461.42, 1388.03, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 7, -1471.52, 1391.36, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 8, -1539.1, 1394.14, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 9, -1548.98, 1392.87, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 10, -1554.03, 1388.89, 35.5768, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 11, -1556.18, 1382.38, 35.6554, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 12, -1557.51, 1371.02, 35.8874, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 13, -1559.2, 1367.96, 35.8418, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 14, -1564.2, 1365.07, 35.742, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 15, -1577.19, 1364.33, 35.7138, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 16, -1581.8, 1362.36, 36.0011, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851003, 17, -1583.35, 1359.47, 36.3651, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851004, 1, -1432.88, 1431.65, 35.6393, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 2, -1532.46, 1420.65, 35.5562, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 3, -1540.52, 1416.54, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 4, -1543.48, 1411.65, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 5, -1543.63, 1405.38, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 6, -1541.16, 1397.55, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 7, -1534.15, 1391.98, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 8, -1526.19, 1391.1, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 9, -1518.72, 1390.27, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 10, -1515.1, 1388.24, 35.5547, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 11, -1508.48, 1380.06, 35.6839, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 12, -1504.49, 1363.41, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 13, -1504.66, 1351.56, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 14, -1506.76, 1346.6, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 15, -1511.78, 1342.43, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 16, -1518.34, 1341.23, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 17, -1523.17, 1339.42, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 18, -1528.8, 1330.39, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851004, 19, -1529.7, 1322.89, 36.4324, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851005, 1, -1476.81, 1439.62, 35.6393, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 2, -1510.52, 1421.3, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 3, -1535.59, 1421.18, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 4, -1540.12, 1418.95, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 5, -1543.3, 1414.24, 35.5564, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 6, -1553.86, 1380.39, 35.5832, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 7, -1559.09, 1341.5, 35.5566, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 8, -1564.45, 1327.5, 35.5566, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 9, -1570.43, 1321.44, 35.5566, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 10, -1575.25, 1318.78, 35.6644, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 11, -1600.01, 1314.83, 20.444, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 12, -1629.99, 1310.51, 19.7879, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 13, -1662.61, 1306.48, 19.7823, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 14, -1671.42, 1308.16, 19.7823, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 15, -1674.89, 1311.18, 20.2952, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851005, 16, -1676.83, 1316.17, 20.7353, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851006, 1, -1398.11, 1431.06, 35.6393, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 2, -1401.68, 1423.42, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 3, -1403.3, 1379.8, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 4, -1404.34, 1376.46, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 5, -1407.16, 1373.54, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 6, -1418.32, 1367.33, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 7, -1576.16, 1318.44, 35.6611, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 8, -1603.62, 1313.61, 18.3221, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 9, -1630.98, 1307.64, 19.6882, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 10, -1662.94, 1305.19, 19.7824, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 11, -1682.23, 1306.13, 19.7824, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 12, -1688.76, 1303.94, 19.7824, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 13, -1691.77, 1299.76, 20.2856, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851006, 14, -1693.32, 1293.03, 21.237, 0, 1, 3485100, 100, 0);

INSERT INTO `waypoint_data` VALUES (34851007, 1, -1517.18, 1358.68, 35.6754, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 2, -1516.59, 1349.48, 35.5786, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 3, -1511.32, 1346.99, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 4, -1460.98, 1356.84, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 5, -1457.32, 1360.09, 35.5563, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 6, -1454.18, 1369.47, 35.7968, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 7, -1451.91, 1381.99, 35.7755, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 8, -1447.38, 1388.62, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 9, -1440.91, 1392.37, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 10, -1437.43, 1395.88, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 11, -1436.4, 1398.35, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 12, -1436.56, 1414.01, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 13, -1434.53, 1417.16, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 14, -1431.34, 1418.43, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 15, -1424.23, 1418.4, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 16, -1421.79, 1416.95, 35.5573, 0, 1, 0, 100, 0);
INSERT INTO `waypoint_data` VALUES (34851007, 17, -1420.83, 1413.46, 36.4777, 0, 1, 3485100, 100, 0);
 
 
/* 
* sql\updates\world\waypoint_scripts.sql 
*/ 
REPLACE INTO `waypoint_scripts` VALUES (3485100, 0, 18, 0, 0, 0, 0, 0, 0, 0, 3485100); 
 
