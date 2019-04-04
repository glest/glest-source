@echo off
call ./group-binaries.bat
Echo Replacing glest.ini with glest_release.ini...
copy /y glest_release.ini bin\vs2015\glest.ini
copy /y glest_release.ini bin\vs2017\glest.ini
copy /y glest_release.ini bin\vs2019\glest.ini
Echo.
ECHO ...and done