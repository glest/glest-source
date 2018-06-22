@echo off
setlocal EnableDelayedExpansion

echo Deleting build files...
echo.
cd .\src
SET "MYPATH=."
for /d %%a in ("%mypath%\*") do (
	echo.
	set branch=master
	cd %%~nxa
	CALL :DELETE
	if "%%~nxa" NEQ "jpeg" (del /S *.obj)
	cd ..
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