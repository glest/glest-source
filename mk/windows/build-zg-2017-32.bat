@echo off
Echo Compiling for 32-bit using Visual Studio 2017...
SET VCVARS_PLATFORM=amd64_x86
SET FOLDER_NAME=vs2017-32
call .\build-zg.bat 2017-32