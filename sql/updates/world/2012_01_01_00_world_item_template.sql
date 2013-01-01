-- Fix for hierloom item scalingStats
UPDATE item_template SET ScalingStatValue = 1 WHERE ScalingStatDistribution != 0;
