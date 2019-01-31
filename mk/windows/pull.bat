@echo off
setlocal
echo This will update all changes from the corresponding GitHub repositories.
SET /P AREYOUSURE=Are you sure you want to do this? ([y]/n) 
IF /I "%AREYOUSURE%"=="n" GOTO END
IF /I "%AREYOUSURE%"=="N" GOTO END

cd dependencies
call .\update-all.bat
cd ..

echo.
echo Updating glest-code...
cd ..\..
git pull
Echo.

echo Updating glest-data...
cd data
git pull
cd ..\
Echo.

cd mk\windows

:END
endlocal