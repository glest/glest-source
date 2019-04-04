@echo off
Echo Compiling for 64-bit using Visual Studio 2019...
SET VCVARS_PLATFORM=amd64
SET FOLDER_NAME=vs2019-64
call .\build.bat 2019-64 deps "%~1"