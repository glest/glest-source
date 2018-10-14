@echo off
setlocal EnableDelayedExpansion
echo Updating repositories...
echo.
cd .\openssl
git pull origin master -X theirs
cd ..\src
SET "MYPATH=."
for /d %%a in ("%mypath%\*") do (
	echo.
	set branch=master
	if "%%~nxa" == "glut" (set branch=git_master)
	cd %%~nxa
    git pull origin !branch! -X theirs
	cd ..
)