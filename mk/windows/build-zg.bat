@echo off
setlocal EnableDelayedExpansion
if NOT "%~1"=="" GOTO SETENV
SET /P PLATFORM_SELECT=Compile ZetaGlest for 64-bit Windows ('n' for 32-bit)? ([y]/n): 
IF /I "%PLATFORM_SELECT%"=="y" GOTO SIXTYFOUR
IF /I "%PLATFORM_SELECT%"=="Y" GOTO SIXTYFOUR
IF /I "%PLATFORM_SELECT%"=="" GOTO SIXTYFOUR
GOTO THIRTYTWO

:THIRTYTWO
SET VCVARS_PLATFORM=amd64_x86
ECHO 32-bit selected...
Echo.
GOTO CHOOSE

:SIXTYFOUR
ECHO 64-bit selected...
Echo.
SET VCVARS_PLATFORM=amd64
GOTO CHOOSE

:CHOOSE
Echo Choose Visual Studio version to compile with (must be installed):
Echo.
Echo 1. Visual Studio 2015
Echo 2. Visual Studio 2017
Echo.
SET QUERY=""
SET /P QUERY=Choose compiler (1 or 2): 
IF /I "%QUERY%"=="1" (
	call .\set-env-2015.bat
	IF /I "%VCVARS_PLATFORM%"=="amd64_x86" SET FOLDER_NAME=vs2015-32
	IF /I "%VCVARS_PLATFORM%" NEQ "amd64_x86" SET FOLDER_NAME=vs2015-64
)
IF /I "%QUERY%"=="2" (
	call .\set-env-2017.bat
	IF /I "%VCVARS_PLATFORM%"=="amd64_x86" SET FOLDER_NAME=vs2017-32
	IF /I "%VCVARS_PLATFORM%" NEQ "amd64_x86" SET FOLDER_NAME=vs2017-64
)
IF /I "%QUERY%" NEQ "1" (
	IF /I "%QUERY%" NEQ "2" (
		Echo Invalid choice.
		Echo.
		GOTO CHOOSE
	)
)

GOTO CHECKDEPS

:SETENV
SET TEMPLOL=%~1
call .\set-env-%TEMPLOL:~0,4%.bat
GOTO CHECKDEPS

:CHECKDEPS
if "%~2"=="deps" GOTO COMPILEDEPS
if "%~2"=="nodeps" GOTO COMPILEZG
Echo.
SET /P BUILD_DEPS=Compile dependencies as well? If first time, choose 'y' ([y]/n): 
IF /I "%BUILD_DEPS%"=="n" GOTO COMPILEZG
IF /I "%BUILD_DEPS%"=="N" GOTO COMPILEZG
GOTO COMPILEDEPS

:COMPILEDEPS
ECHO --------------------------------
Echo Compiling dependencies (this will take a long time)...

cd .\dependencies\src

Echo Building zlib...
cd .\zlib\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% zlib.sln
cd ..\..

Echo Building freetype...
cd .\freetype\builds\windows\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% freetype.sln
cd ..\..\..\..

Echo Building fribidi...
cd .\fribidi\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% libfribidi.sln
cd ..\..

Echo Building glew...
cd .\glew\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% glew.sln
cd ..\..

Echo Building glut...
cd .\glut\freeglut\freeglut\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% freeglut.sln
cd ..\..\..\..

Echo Building irc...
cd .\irc\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% libircclient.sln
cd ..\..

Echo Building jpeg...
cd .\jpeg\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% libjpeg-turbo.sln
cd ..\..

Echo Building lua...
cd .\lua\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% lua.sln
cd ..\..

Echo Building ogg...
cd .\ogg\win32\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% libogg_static.sln
cd ..\..\..

Echo Building openal...
cd .\openal\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% openal.sln
cd ..\..

Echo Building png...
cd .\png\projects\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% vstudio.sln
cd ..\..\..

Echo Building ftgl...
cd .\ftgl\msvc\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% ftgl.sln
cd ..\..\..

Echo Building sdl2...
cd .\sdl2\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% sdl2.sln
cd ..\..

Echo Building vorbis...
cd .\vorbis\win32\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% vorbis_static.sln
cd ..\..\..

Echo Building xerces...
cd .\xerces\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% xerces-c.sln
cd ..\..

Echo Building curl...
cd .\curl\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% Curl.sln
cd ..\..

Echo Building wxwidgets...
cd .\wxwidgets\build\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% wx.sln
cd ..\..\..

cd ..\..

GOTO COMPILEZG

:COMPILEZG
ECHO --------------------------------
Echo Building ZetaGlest...
cd .\%FOLDER_NAME%\
msbuild.exe /p:Configuration=%MSBUILD_CONFIG%;Platform=%PLATFORM%;PlatformToolset=%TOOLSET% ZetaGlest.sln
cd ..\
ECHO.
ECHO Copying binaries...
ECHO.
call .\group-binaries.bat
ECHO ... Done.
ECHO.
ECHO If build was successful, then output is in bin folder, otherwise scroll up a little to view error messages.
ECHO Thanks for trying out ZetaGlest!
ECHO.
pause