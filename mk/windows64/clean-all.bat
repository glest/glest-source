@echo off
setlocal
echo This will recursively delete all .lib, .exe, .dll, .db, .pdb, .map, .ncb, .bsc, .lastbuildstate, .log, .tlog, .exp, .pch and .ipch files in dependencies/src and in vs2015 and vs2017.
SET /P AREYOUSURE= Are you sure you want to do this? (y/[n]) 
IF /I "%AREYOUSURE%" NEQ "y" GOTO END
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

cd .\dependencies\src
del /S *.lib
del /S *.exe
del /S *.dll
del /S *.db
del /S *.pdb
del /S *.map
del /S *.ncb
del /S *.bsc
del /S *.log
del /S *.tlog
del /S *.lastbuildstate
del /S *.exp
del /S *.ipch
del /S *.pch
cd ..\..\

cd .\vs2015
del /S *.lib
del /S *.exe
del /S *.dll
del /S *.db
del /S *.pdb
del /S *.map
del /S *.ncb
del /S *.bsc
del /S *.log
del /S *.tlog
del /S *.lastbuildstate
del /S *.exp
del /S *.ipch
del /S *.pch
cd ..\

cd .\vs2017
del /S *.lib
del /S *.exe
del /S *.dll
del /S *.db
del /S *.pdb
del /S *.map
del /S *.ncb
del /S *.bsc
del /S *.log
del /S *.tlog
del /S *.lastbuildstate
del /S *.exp
del /S *.ipch
del /S *.pch
cd ..\

:END
endlocal