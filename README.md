[![Build Status](https://travis-ci.org/ZetaGlest/zetaglest-source.svg?branch=develop)](https://travis-ci.org/ZetaGlest/zetaglest-source)

**This is the game engine source code repository.**

[ZetaGlest](https://github.com/ZetaGlest) is a fork of [MegaGlest](http://megaglest.org/),
a libre software cross platform real-time strategy game.

ZetaGlest is an entertaining free (freeware and free software) and open
source cross-platform 3D real-time strategy (RTS) game, where you
control the armies of one of seven different factions: Tech, Magic,
Egypt, Indians, Norsemen, Persian or Romans. The game is played in one
of 17 naturally looking settings, which, like the unit models, are
crafted with great attention to detail. A lot of additional game data
can be downloaded from within the game at no cost.

## Download executable files

No binary packages of the ZetaGlest fork have been released yet. If you
have no desire to compile software and would only like a binary
(executable), we suggest trying the [MegaGlest](http://megaglest.org/)
game; binary package downloads for various operating systems are
available on their web site.

## To Build (Compile) and Run

### Dependencies

On Debian, Ubuntu, Fedora, Opensuse and even more Linux distributions,
after you clone the source repository, you may use

    cd mk/linux
    sudo ./setupBuildDeps.sh

which will run your package manager and attempt to install the needed packages.

(These may vary based on your operating system or Linux distribution;
we will attempt to document dependencies in more detail)

Below is a list of most dependencies you will need. This document needs
to indicate better which are optional and which are required.

gcc gcc-c++ cmake libsdl2-dev libalut-dev libgl1-mesa-dev
libglu1-mesa-dev libvorbis-dev libx11-dev liblua-dev libjpeg-dev
libpng-dev libcurl-gnutls-dev libircclient-dev libglew-dev libftgl-dev
libfribidi-dev libcppunit-dev libminiupnpc-dev libfreetype6-dev
libgnutls28-dev libkrb5-dev libkrb5-dev libnghttp2-dev libopenal-dev
libldap2-dev libwxgtk3.0-dev librtmp-dev libvlccore-dev libvlc-dev

Additionally for map editor and model viewer:

libwxgtk3.0-dev libxml2-dev

### Try the game without contributing

Use this command:

    git clone --recursive https://github.com/ZetaGlest/zetaglest-source.git

Afterward, to build, change to the mk/ directory, select your operating
system and run

    ./build-zg.sh

To execute the game:

    ./zetaglest

### Contributing and Testing

If you would like to contribute to development, you will need to fork and
then clone your forks of these 3 repositories:

* https://github.com/ZetaGlest/zetaglest-source
* https://github.com/ZetaGlest/zetaglest-data
* https://github.com/ZetaGlest/zetaglest-masterserver

Hint: make a `ZetaGlest` directory, then clone from there. Afterward, you
will have these 3 directories in `ZetaGlest`

    zetaglest-data
    zetaglest-masterserver
    zetaglest-source

Afterward, to build, change to the zetaglest-source/mk/<OS> directory, and run:

    ./build-zg.sh

To run the game, you will need to specify the data path:

    ./zetaglest --data-path=<path to data repository>zetaglest-data/

If you don't provide the data path, you will receive an error message
when the game starts.

Please see [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)
for extended, important instructions and guidelines for contributing.

## Contact

* IRC: [Freenode/#zetaglest-dev](http://webchat.freenode.net?channels=%23zetaglest-dev&uio=d4)
* email: andy400-dev@yahoo.com
* (Suggest alternate methods of communication)
