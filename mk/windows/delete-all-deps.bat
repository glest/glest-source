@echo off
setlocal
echo This will delete /dependencies/openssl and /dependencies/src.
SET /P AREYOUSURE=Are you sure you want to do this? (y/[n]) 
IF /I "%AREYOUSURE%" NEQ "y" GOTO END
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END
del /f /s /q /AH .\dependencies\openssl
del /f /s /q /AH .\dependencies\src
ROBOCOPY . . /S /MOVE
ROBOCOPY . . /S /MOVE
ROBOCOPY . . /S /MOVE

:END
endlocal