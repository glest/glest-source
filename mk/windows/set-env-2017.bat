@echo off
rem https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line
SET MSBUILD_CONFIG=Release
SET PLATFORM=x64
SET TOOLSET=v141

ECHO Setting up Visual Studio 2017 environment vars...
if "%DevEnvDir%." == "." goto SETVCVARS
GOTO GITSECTION

:SETVCVARS
IF EXIST "%ProgramFiles%\Microsoft Visual Studio\2017\"      GOTO VC_32_17
IF EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\" GOTO VC_64_17
goto GITSECTION

:VC_32_17
ECHO 32 bit Windows detected...
IF EXIST "%ProgramFiles%\Microsoft Visual Studio\2017\Community\" (
  set EDITION=Community
)
IF EXIST "%ProgramFiles%\Microsoft Visual Studio\2017\Professional\" (
  set EDITION=Professional
)
IF EXIST "%ProgramFiles%\Microsoft Visual Studio\2017\Enterprise\" (
  set EDITION=Enterprise
)
call "%ProgramFiles%\Microsoft Visual Studio\2017\%EDITION%\VC\Auxiliary\Build\vcvarsall.bat" %VCVARS_PLATFORM%
SET MSBUILD_PATH="%ProgramFiles%\Microsoft Visual Studio\2017\%EDITION%\Common7\IDE\VC\VCTargets\Microsoft.Cpp.Default.props"
goto GITSECTION

:VC_64_17
ECHO 64 bit Windows detected...
IF EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\" (
  set EDITION=Community
)
IF EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\" (
  set EDITION=Professional
)
IF EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\" (
  set EDITION=Enterprise
)
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\%EDITION%\VC\Auxiliary\Build\vcvarsall.bat" %VCVARS_PLATFORM%
SET MSBUILD_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\%EDITION%\Common7\IDE\VC\VCTargets\Microsoft.Cpp.Default.props"
goto GITSECTION

:GITSECTION
IF "%EDITION%" == "" (
	echo Visual Studio 2017 edition not found.
	ECHO ... End.
	if not "%1" == "nopause" pause
	exit
) ELSE (
	ECHO Visual Studio 2017 %EDITION% edition detected...
)
set CL=/MP
set msBuildMaxCPU=
SET BuildInParallel=false
if %NUMBER_OF_PROCESSORS% GTR 2 (
                SET NumberOfProcessesToUseForBuild=%NUMBER_OF_PROCESSORS%
                SET BuildInParallel=true
				SET msBuildMaxCPU=/maxcpucount)

ECHO Found CPU Count [%NUMBER_OF_PROCESSORS%]
ECHO Finished setting up environment

