@ECHO OFF
title Simple Extractor
COLOR 0A

CLS
ECHO.
ECHO    ______  __  __  __  __  ______ __  ______  ______ 
ECHO   /\  ___\/\ \/ / /\ \_\ \/\  ___/\ \/\  __ \/\  ___\
ECHO   \ \___  \ \  _'-\ \____ \ \  __\ \ \ \ \__ \ \  __\
ECHO    \/\_____\ \_\ \_\/\_____\ \_\  \ \_\ \_\ \_\ \_____\
ECHO     \/_____/\/_/\/_/\/_____/\/_/   \/_/\/_/ /_/\/_____/
ECHO.
ECHO.
ECHO   Project SkyFireEmu 2012(c) Open-sourced Game Emulation
ECHO             http://www.projectskyfire.org/
ECHO.
ECHO.
ECHO          Simple Map/dbc/vmap/mmaps Extraction
ECHO.
ECHO.
PAUSE

CLS
COLOR 4f
ECHO.
ECHO.
ECHO       Before Continuing, PLEASE check to ensure your 
ECHO.
ECHO   Config.wtf and Launcher.wtf are BOTH set at accounttype "CT"
ECHO.
ECHO     (They should be located in: "\World of Warcraft\WTF\")
ECHO.
ECHO.
PAUSE

CLS
ECHO.
ECHO.
ECHO Please take this time to copy the file "libmysql.dll" from your 
ECHO mysql installation directory to your wow client directory
ECHO (Usually located at: C:\Program Files\MySQL\MySQL Server 5.5\lib\)
ECHO.
ECHO NOTE: It will be C:\Program Files(x86)\ if 32bit MySQL installed on 
ECHO 64bit system
ECHO.
ECHO.
PAUSE

CLS
COLOR FC
ECHO.
ECHO.
ECHO                             ***NOTE*** 
ECHO This entire process will take anywhere from 4 hours to 20 hours or MORE, 
ECHO                depending upon the speed of your machine.
ECHO.
ECHO To continue the extraction process, enter 1, else, enter X to exit.
SET /p v= 		Enter a char:
IF %v%==1 GOTO Extract
IF %v%==x GOTO EXIT
IF %v%==X GOTO EXIT

:Extract
CLS
COLOR 0A
ECHO.
ECHO Now extracting dbcs and maps, please do not exit the program!
ECHO.
RMDIR /s /q .\buildings
RMDIR /s /q .\vmaps
RMDIR /s /q .\maps
RMDIR /s /q .\mmaps
RMDIR /s /q .\dbc
extractor.exe
ECHO.
ECHO Dbcs and maps are finished extracting... Now extracting vmaps...
ECHO.
vmap3extractor.exe
ECHO.
ECHO Vmaps are now extracted... Now assembling vmaps...
ECHO.
MKDIR vmaps
vmap3assembler.exe Buildings vmaps
ECHO.
ECHO.
ECHO Vmaps are now assembled... Now ready to build mmaps...
ECHO.
ECHO.
MKDIR mmaps
MOVE .\buildings\* .\vmaps
mmaps_generator.exe
PAUSE

CLS
ECHO.
ECHO All maps/dbcs/vmaps/mmaps completed!
ECHO.
ECHO You will now need to move the folders dbc, vmaps, maps, and mmaps to your server directory. 
ECHO.
ECHO NOTE: It is also a good idea to use the "libmysql.dll" file from your MySQL installation
ECHO directory in your server directory as it will likely work much better with less errors.
ECHO.
ECHO.
PAUSE
:EXIT