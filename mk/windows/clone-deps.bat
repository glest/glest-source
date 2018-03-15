@echo off
setlocal
echo This will clone all dependencies from the corresponding GitHub repositories.
SET /P AREYOUSURE=Are you sure you want to do this? (y/[n]) 
IF /I "%AREYOUSURE%" NEQ "y" GOTO END
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

Echo.
git clone https://github.com/ZetaGlest/openssl.git dependencies/openssl
Echo.
git clone https://github.com/ZetaGlest/curl.git dependencies/src/curl
Echo.
git clone https://github.com/ZetaGlest/freetype.git dependencies/src/freetype
Echo.
git clone https://github.com/ZetaGlest/fribidi.git dependencies/src/fribidi
Echo.
git clone https://github.com/ZetaGlest/ftgl-2.1.3.git dependencies/src/ftgl
Echo.
git clone https://github.com/ZetaGlest/glew.git dependencies/src/glew
Echo.
git clone https://github.com/ZetaGlest/freeglut.git dependencies/src/glut
Echo.
git clone https://github.com/ZetaGlest/libircclient.git dependencies/src/irc
Echo.
git clone https://github.com/ZetaGlest/libjpeg-turbo.git dependencies/src/jpeg
Echo.
git clone https://github.com/ZetaGlest/lua.git dependencies/src/lua
Echo.
git clone https://github.com/ZetaGlest/ogg.git dependencies/src/ogg
Echo.
git clone https://github.com/ZetaGlest/openal-soft.git dependencies/src/openal
Echo.
git clone https://github.com/ZetaGlest/libpng.git dependencies/src/png
Echo.
git clone https://github.com/ZetaGlest/sdl-mirror.git dependencies/src/sdl2
Echo.
git clone https://github.com/ZetaGlest/vorbis.git dependencies/src/vorbis
Echo.
git clone https://github.com/ZetaGlest/wxWidgets-2.9.git dependencies/src/wxwidgets
Echo.
git clone https://github.com/ZetaGlest/xerces-c.git dependencies/src/xerces
Echo.
git clone https://github.com/ZetaGlest/zlib.git dependencies/src/zlib
Echo.
git clone https://github.com/ZetaGlest/zetaglest-data.git ..\..\data
Echo.

:END
endlocal