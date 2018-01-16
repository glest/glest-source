[![Build Status](https://travis-ci.org/ZetaGlest/zetaglest-source.svg?branch=develop)](https://travis-ci.org/ZetaGlest/zetaglest-source)

**This is the game engine source code repository.**

[ZetaGlest](https://github.com/ZetaGlest) is a fork of [MegaGlest](http://megaglest.org/),
a libre software cross platform real-time strategy game.

ZetaGlest is an entertaining free (freeware and free software) and open
source cross-platform 3D real-time strategy (RTS) game, where you
control the armies of one of eight different factions: Tech, Magic,
Egypt, Indians, Norsemen, Persian, Elves or Romans. The game is played
in one of 17 naturally looking settings, which, like the unit models,
are crafted with great attention to detail. A lot of additional game
data can be downloaded from within the game at no cost.

## Why this fork? (Project Goals)

ZetaGlest forked from MegaGlest at v3.13.0

I noticed that there were some good feature requests in the MegaGlest
forum, as well as some mods, but it seemed that implementing and
testing had a pace that I was uncomfortable with. After talking about
this with another player, I decided to fork the project and see if I
could assemble regular contributors and players who had similar
feelings about the speed of progress, adding artwork, promoting mods
made by contributors, and code enhancements. I would like to encourage
contributions, no matter how small, in the hopes of improving an
already fun game and making the experience even more fun that it has
been for me.

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

If you'll be contributing code or changes to data, the procedures for
forking and cloning are outlined in [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)

Please see [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)
for extended, important instructions and guidelines for contributing.

## Contact

* IRC: [Freenode/#zetaglest-dev](http://webchat.freenode.net?channels=%23zetaglest-dev&uio=d4)
* [Discord](https://discord.gg/WaAaXS7)
* email: andy400-dev@yahoo.com
