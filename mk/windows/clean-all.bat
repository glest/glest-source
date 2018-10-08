@echo off
setlocal
echo This will recursively delete all .lib, .exe, .dll, .db, .iobj, .opendb, .pdb, .ipdb, .map, .ncb, .bsc, .cache, .lastbuildstate, .log, .tlog, .exp, .pch and .ipch files in dependencies/src and in vs2015 and vs2017.
SET /P AREYOUSURE=Are you sure you want to do this? (y/[n]) 
IF /I "%AREYOUSURE%" NEQ "y" GOTO END
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

IF EXIST .\dependencies (
	cd .\dependencies
	CALL .\clean-deps.bat
	cd ..\
)

IF EXIST .\vs2015-32 (
	cd .\vs2015-32
	CALL :DELETE
	del /S *.obj
	cd ..\
)

IF EXIST .\vs2015-64 (
	cd .\vs2015-64
	CALL :DELETE
	del /S *.obj
	cd ..\
)

IF EXIST .\vs2017-32 (
	cd .\vs2017-32
	CALL :DELETE
	del /S *.obj
	cd ..\
)

IF EXIST .\vs2017-64 (
	cd .\vs2017-64
	CALL :DELETE
	del /S *.obj
	cd ..\
)

IF EXIST .\bin (
	cd .\bin
	CALL :DELETE
	cd ..\
)

IF EXIST ..\..\external\libircclient (
	cd ..\..\external\libircclient
	CALL :DELETE
	cd ..\..\..\mk\windows
)

ROBOCOPY . . /S /MOVE
ROBOCOPY . . /S /MOVE
ROBOCOPY . . /S /MOVE

GOTO END

:DELETE
del /S *.lib
del /S *.exe
del /S *.dll
del /S *.db
del /S *.iobj
del /S *.opendb
del /S *.pdb
del /S *.ipdb
del /S *.map
del /S *.ncb
del /S *.bsc
del /S *.log
del /S *.tlog
del /S *.cache
del /S *.lastbuildstate
del /S *.exp
del /S *.ipch
del /S *.pch
del /S *.res
del /S *.user
EXIT /B

:END
endlocal