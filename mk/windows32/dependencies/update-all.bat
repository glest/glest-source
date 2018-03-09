@echo off
setlocal EnableDelayedExpansion
cd .\src
echo Updating repositories...
SET "MYPATH=."
for /d %%a in ("%mypath%\*") do (
	echo.
	set branch=master
	if "%%~nxa" == "xerces" (set branch=trunk)
	if "%%~nxa" == "glut" (set branch=git_master)
	cd %%~nxa
    ..\..\bin\git pull origin !branch! -X theirs
	cd ..
)