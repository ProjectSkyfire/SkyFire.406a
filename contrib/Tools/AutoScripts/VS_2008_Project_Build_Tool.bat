@ECHO OFF
SET ver=4.0.6a
TITLE SkyFireEMU %ver% Simple Project Building Tool
COLOR 0A
rem Credits to:
rem MangosR2 and to /Dev/RSA for the base installer
rem SkyFireEMU's current version by Aptiva.
rem VS2008 updates by AlterEgo
:TOP
CLS
ECHO.
ECHO          ษออออออออออออออออออออออออออออออออป
ECHO          บ                                บ
ECHO          บ      SkyFireEMU (%ver%)       บ
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
REM     This version is only for VS 9 "2008"
REM Install path for SkyFireEMU (in this be created ./bin and ./etc folders)
SET INSTALL_PATH="C:\\GAMES\\SkyFireEMU"
rem
rem This Setting is for Build platform configuration. (Check Dir paths!)
rem     Options: Win32, Win64. (Warning! Win64 build possible only on 64-bit main OS)!
SET BUILD_PLATFORM=Win64
rem
rem This Setting is For Multi-Core Processor configurations(core Count)for speedup only
SET CORE_NUMBER=4
rem
rem Build map extractors. 1=Yes or 0=No.
SET TOOLS=1
rem
rem "TODO: Add-ins for Memory Manager(s)"
REM *****************************************************************************************
SET COMPILER="Visual Studio 9 2008"
if %BUILD_PLATFORM%==Win64 (SET COMPILER="Visual Studio 9 2008 Win64")
if %TOOLS%==0 (SET TOOL="")
if %TOOLS%==1 (SET TOOL="-DTOOLS=%INSTALL_PATH%")
SET COMPILER_PATH="C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/cl.exe"
SET LINKER_PATH="C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/link.exe"
SET VC_VARS="C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\"
goto :common
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
cmake -G %COMPILER% -DPCH=1 -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_CXX_FLAGS=%C_FLAGS% -DCMAKE_C_FLAGS=%C_FLAGS% -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_INSTALL_PREFIX=%INSTALL_PATH% %TOOL% ..
call %VC_VARS%vcvarsall.bat
MSBuild SkyFireEMU.sln /m:%CORE_NUMBER% /t:Rebuild /p:Configuration=%RESULT_CONF%;Platform=%BUILD_PLATFORM%
goto :end
REM *****************************************************************************************
:win64
cd build
cmake -G %COMPILER% -DPCH=1 -DPLATFORM=X64 -DCMAKE_CXX_FLAGS=%C_FLAGS% -DCMAKE_C_FLAGS=%C_FLAGS% -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_CXX_COMPILER=%COMPILER_PATH% -DCMAKE_INSTALL_PREFIX=%INSTALL_PATH% %TOOL% ..
call %VC_VARS%vcvarsall.bat
MSBuild SkyFireEMU.sln /m:%CORE_NUMBER%  /t:Rebuild /p:Configuration=%RESULT_CONF%;Platform=x64
goto :end
REM *****************************************************************************************


:end
cd ..