@echo off
Echo Compiling for 32-bit using Visual Studio 2019...
SET VCVARS_PLATFORM=amd64_x86
SET FOLDER_NAME=vs2019-32
call .\build.bat 2019-32 deps "%~1"