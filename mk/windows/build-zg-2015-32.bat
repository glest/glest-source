@echo off
Echo Compiling for 32-bit using Visual Studio 2015...
SET VCVARS_PLATFORM=amd64_x86
SET FOLDER_NAME=vs2015-32
call .\build-zg.bat 2015-32