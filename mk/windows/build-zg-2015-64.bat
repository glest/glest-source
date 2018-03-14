@echo off
Echo Compiling for 64-bit using Visual Studio 2015...
SET VCVARS_PLATFORM=amd64
SET FOLDER_NAME=vs2015-64
call .\build-zg.bat 2015-64