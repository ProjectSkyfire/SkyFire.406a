@ECHO OFF
SET ver=4.0.6a
TITLE SkyFireEMU %ver% Simple Project Building Tool
COLOR 0A
rem Credits to:
rem MangosR2 and to /Dev/RSA for the base installer
rem SkyFireEMU's current version by Aptiva.
:TOP
CLS
ECHO.
ECHO          ษออออออออออออออออออออออออออออออออป
ECHO          บ                                บ
ECHO          บ       SkyFireEMU (%ver%)       บ
ECHO          บ     Simple Project Build       บ
ECHO          บ            and                 บ
ECHO          บ      Installation Tool         บ
ECHO          บ                                บ
ECHO          ศออออออออออออออออออออออออออออออออผ
ECHO.
ECHO.
ECHO    EDIT THE SETTINGS IN THIS BATCH, IF YOUR HAVING ISSUES USING IT! ...
ECHO.
REM *****************************************************************************************
REM     Make Sure you Edit config feature's for your specific build.
REM     this fixes native pre-builds for VC10 (MS Visual studio 10 Pro)
REM     and VC11 (MS Visual studio 11 or 2012 Pro/Ultimate)
REM     Warning! VS Express edition is not supported!
SET compiler=VC11
REM Install path for SkyFireEMU (in this be created ./bin and ./etc folders)
SET INSTALL_PATH="C:\\GAMES\\SkyFireEMU"
rem
rem This Setting is for Build platform configuration. (Check Dir paths!)
rem     Options: Win32, Win64. (Warning! Win64 build possible only on 64-bit main OS)!
SET BUILD_PLATFORM=Win32
rem
rem This Setting is For Multi-Core Processor configurations(core Count)for speedup only
SET CORE_NUMBER=4
rem
rem "TODO: Add-ins for Memory Manager(s)"
REM *****************************************************************************************
if %compiler%==VC11 goto :vc11
if %compiler%==VC10 goto :vc10
goto :help
REM *****************************************************************************************
:vc11
SET COMPILER="Visual Studio 11"
if %BUILD_PLATFORM%==Win64 (SET COMPILER="Visual Studio 11 Win64")
SET COMPILER_PATH="C:/Program Files (x86)/Microsoft Visual Studio 11.0/VC/bin/cl.exe"
SET LINKER_PATH="C:/Program Files (x86)/Microsoft Visual Studio 11.0/VC/bin/link.exe"
SET VC_VARS="C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\"
goto :common
REM *****************************************************************************************
:vc10
SET COMPILER="Visual Studio 10"
if %BUILD_PLATFORM%==Win64 (SET COMPILER="Visual Studio 10 Win64")
SET COMPILER_PATH="C:/Program Files/Microsoft Visual Studio 10.0/VC/bin/cl.exe"
SET LINKER_PATH="C:/Program Files/Microsoft Visual Studio 10.0/VC/bin/link.exe"
SET VC_VARS="C:\\Program Files\\Microsoft Visual Studio 10.0\\VC\\"
goto :common
REM *****************************************************************************************
:help
echo "Set up parameters in this bat file!"
exit
REM *****************************************************************************************
:common
SET RESULT_CONF=Release
SET C_FLAGS="/DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR"
goto :begin
REM *****************************************************************************************

:begin
if not exist build (
    mkdir build
)

if not exist %INSTALL_PATH% (
mkdir %INSTALL_PATH%
    if not exist %INSTALL_PATH% (
    echo Please, make output directory %INSTALL_PATH%
    exit
    )
)

if %BUILD_PLATFORM%==Win32 goto :win32
if %BUILD_PLATFORM%==Win64 goto :win64
goto :help

REM *****************************************************************************************
:win32
cd build
cmake -G %COMPILER% -DPCH=1 -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_CXX_FLAGS=%C_FLAGS% -DCMAKE_C_FLAGS=%C_FLAGS% -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_INSTALL_PREFIX=%INSTALL_PATH% -DTOOLS=%INSTALL_PATH% ..
call %VC_VARS%vcvarsall.bat
MSBuild INSTALL.vcxproj /m:%CORE_NUMBER% /t:Rebuild /p:Configuration=%RESULT_CONF%;Platform=%BUILD_PLATFORM%
goto :end
REM *****************************************************************************************
:win64
cd build
cmake -G %COMPILER% -DPCH=1 -DPLATFORM=X64 -DCMAKE_CXX_FLAGS=%C_FLAGS% -DCMAKE_C_FLAGS=%C_FLAGS% -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_INSTALL_PREFIX=%INSTALL_PATH% -DTOOLS=%INSTALL_PATH% ..
call %VC_VARS%vcvarsall.bat
MSBuild INSTALL.vcxproj /m:%CORE_NUMBER%  /t:Rebuild /p:Configuration=%RESULT_CONF%;Platform=x64
goto :end
REM *****************************************************************************************

:end
cd ..
