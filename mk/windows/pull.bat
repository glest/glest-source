@echo off
setlocal
echo This will update all changes from the corresponding GitHub repositories.
SET /P AREYOUSURE=Are you sure you want to do this? ([y]/n) 
IF /I "%AREYOUSURE%"=="n" GOTO END
IF /I "%AREYOUSURE%"=="N" GOTO END

cd dependencies\src

echo Updating curl...
cd curl
git pull
cd ..
Echo.

echo Updating freetype...
cd freetype
git pull
cd ..
Echo.

echo Updating fribidi...
cd fribidi
git pull
cd ..
Echo.

echo Updating ftgl...
cd ftgl
git pull
cd ..
Echo.

echo Updating glew...
cd glew
git pull
cd ..
Echo.

echo Updating glut...
cd glut
git pull
cd ..
Echo.

echo Updating irc...
cd irc
git pull
cd ..
Echo.

echo Updating jpeg...
cd jpeg
git pull
cd ..
Echo.

echo Updating lua...
cd lua
git pull
cd ..
Echo.

echo Updating ogg...
cd ogg
git pull
cd ..
Echo.

echo Updating openal...
cd openal
git pull
cd ..
Echo.

echo Updating png...
cd png
git pull
cd ..
Echo.

echo Updating sdl2...
cd sdl2
git pull
cd ..
Echo.

echo Updating vorbis...
cd vorbis
git pull
cd ..
Echo.

echo Updating wxwidgets...
cd wxwidgets
git pull
cd ..
Echo.

echo Updating xerces...
cd xerces
git pull
cd ..
Echo.

echo Updating zlib...
cd zlib
git pull
cd ..
Echo.

echo Updating zetaglest-code...
cd ..\..
cd ..\..
git pull
Echo.

echo Updating zetaglest-data...
cd data
git pull
cd ..\
Echo.

cd mk\windows

:END
endlocal