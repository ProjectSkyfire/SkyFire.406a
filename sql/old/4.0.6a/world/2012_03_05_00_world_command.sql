DELETE FROM command WHERE name='note';
INSERT INTO `command` (`name`,`security`,`help`) VALUES
('note', 1, 'Syntax: .note  .note to make a note in the GM logs');
