@echo off
setlocal
echo This will clone all dependencies from the corresponding GitHub repositories.
SET /P AREYOUSURE=Are you sure you want to do this? (y/[n]) 
IF /I "%AREYOUSURE%" NEQ "y" GOTO END
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

Echo.
git clone https://github.com/Glest/openssl.git dependencies/openssl
Echo.
git clone https://github.com/Glest/curl.git dependencies/src/curl
Echo.
git clone https://github.com/Glest/freetype.git dependencies/src/freetype
Echo.
git clone https://github.com/Glest/fribidi.git dependencies/src/fribidi
Echo.
git clone https://github.com/Glest/ftgl-2.1.3.git dependencies/src/ftgl
Echo.
git clone https://github.com/Glest/glew.git dependencies/src/glew
Echo.
git clone https://github.com/Glest/freeglut.git dependencies/src/glut
Echo.
git clone https://github.com/Glest/libjpeg-turbo.git dependencies/src/jpeg
Echo.
git clone https://github.com/Glest/lua.git dependencies/src/lua
Echo.
git clone https://github.com/Glest/ogg.git dependencies/src/ogg
Echo.
git clone https://github.com/Glest/openal-soft.git dependencies/src/openal
Echo.
git clone https://github.com/Glest/libpng.git dependencies/src/png
Echo.
git clone https://github.com/Glest/sdl-mirror.git dependencies/src/sdl2
Echo.
git clone https://github.com/Glest/vorbis.git dependencies/src/vorbis
Echo.
git clone https://github.com/Glest/wxWidgets-2.9.git dependencies/src/wxwidgets
Echo.
git clone https://github.com/Glest/zlib.git dependencies/src/zlib
Echo.
git clone https://github.com/Glest/glest-data.git ..\..\data
Echo.

:END
endlocal