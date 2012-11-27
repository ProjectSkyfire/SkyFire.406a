CLS
@ECHO OFF
SET /p db="Database name (optionally, table name too): "
echo Exporting...
mysqldump --host=localhost --user=root --password=mangos %db% > %HOMEPATH%\Desktop\%db%.sql
echo Done.
pause
