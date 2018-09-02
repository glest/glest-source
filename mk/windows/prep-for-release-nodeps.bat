@echo off
call build-zg-2015-32.bat nopause
call build-zg-2015-64.bat nopause
call build-zg-2017-32.bat nopause
call build-zg-2017-64.bat nopause
Echo Replacing glest.ini with glest_release.ini...
copy /y glest_release.ini bin\vs2015\glest.ini
copy /y glest_release.ini bin\vs2017\glest.ini
Echo.
ECHO ...and done
Echo.
if NOT "%~1"=="nopause" pause