@ECHO OFF
@title SkyFireEMU AuthServer
CLS
ECHO Initializing Authenication server (auth-server)...
:1
start "SkyFireEMU AuthServer" /B /MIN /WAIT authserver.exe -c authserver.conf
if %errorlevel% == 0 goto end
goto 1
:end