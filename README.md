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

### Try the game without contributing

Use this command:

    git clone --recursive https://github.com/ZetaGlest/zetaglest-source.git

Afterward, to build, change to the mk/ directory, select your operating
system and run

    ./build-mg.sh

### Contributing and Testing

If you would like to contribute to development, you will need to fork and
clone these 3 repositories:

    mkdir ZetaGlest
    git clone https://github.com/ZetaGlest/zetaglest-source
    git clone https://github.com/ZetaGlest/zetaglest-data
    git clone https://github.com/ZetaGlest/zetaglest-masterserver

Afterward, to build, change to the zetaglest-source/mk/<OS> directory, and run:

    ./build-mg.sh

To run the game, you will need to specify the data path:

    ./megaglest --data-path=<path to data repository>zetaglest-data/

If you don't provide the data path, you will receive an error message
when the game starts.

Please see [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)
for extended, important instructions and guidelines for contributing.

## Contact

* IRC: Freenode/#zetaglest-dev
* email: andy400-dev@yahoo.com
