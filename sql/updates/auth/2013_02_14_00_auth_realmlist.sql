ALTER TABLE `realmlist`
  ADD `localAddress` VARCHAR(255) NOT NULL DEFAULT '127.0.0.1' AFTER `address`,
  ADD `localSubnetMask` VARCHAR(255) NOT NULL DEFAULT '255.255.255.0' AFTER `localAddress`;
    