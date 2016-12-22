#! /bin/bash
FILES=./*.sql
USER="USER"
PASSWORD="PASSWORD"
for f in $FILES
do
echo "Applying Update $f"
mysql -u $USER -p"$PASSWORD" world < $f
done 
echo "All Updates Applied"
