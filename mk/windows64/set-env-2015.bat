@echo off
rem https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line
SET VCVARS_PLATFORM=amd64
SET MSBUILD_CONFIG=Release
SET PLATFORM=x64
SET TOOLSET=v140
SET FOLDER_NAME=vs2015

ECHO Setting up Visual Studio 2015 environment vars...
SET Platform=
if "%DevEnvDir%." == "." goto SETVCVARS
GOTO GITSECTION

:SETVCVARS
IF EXIST "%ProgramFiles%\Microsoft Visual Studio 14.0\"      GOTO VC_32_15
IF EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\" GOTO VC_64_15
goto GITSECTION

:VC_32_15
ECHO 32 bit Windows detected...
call "%ProgramFiles%\Microsoft Visual Studio 14.0\vc\vcvarsall.bat" %VCVARS_PLATFORM%
SET MSBUILD_PATH="%ProgramFiles%\MSBuild\Microsoft.Cpp\v4.0\V140\"
goto GITSECTION

:VC_64_15
ECHO 64 bit Windows detected...
call "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\vc\vcvarsall.bat" %VCVARS_PLATFORM%
SET MSBUILD_PATH="%ProgramFiles(x86)%\MSBuild\Microsoft.Cpp\v4.0\V140\"
goto GITSECTION

:GITSECTION
set CL=/MP
SET BuildInParallel=false
if %NUMBER_OF_PROCESSORS% GTR 2 (
                SET NumberOfProcessesToUseForBuild=%NUMBER_OF_PROCESSORS%
                SET BuildInParallel=true
				SET msBuildMaxCPU=/maxcpucount)

ECHO Found CPU Count [%NUMBER_OF_PROCESSORS%]
ECHO Finished setting up environment