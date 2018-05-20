@echo off
Echo Compiling for 64-bit using Visual Studio 2017...
SET VCVARS_PLATFORM=amd64
SET FOLDER_NAME=vs2017-64
call .\build-zg.bat 2017-64 nodeps "%~1"