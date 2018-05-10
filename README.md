[![Build Status](https://travis-ci.org/ZetaGlest/zetaglest-source.svg?branch=develop)](https://travis-ci.org/ZetaGlest/zetaglest-source)

**This is the game engine source code repository.**

[ZetaGlest](https://zetaglest.github.io/docs/) is a fork of [MegaGlest](http://megaglest.org/),
a libre software cross platform real-time strategy game.

ZetaGlest is an entertaining free (freeware and free software) and open
source cross-platform 3D real-time strategy (RTS) game, where you
control the armies of one of eight different factions: Tech, Magic,
Egypt, Indians, Norsemen, Persian, Elves or Romans. The game is played
in one of 17 naturally looking settings, which, like the unit models,
are crafted with great attention to detail. A lot of additional game
data can be downloaded from within the game at no cost.

**[System Requirements](https://zetaglest.github.io/docs/system_requirements.html)**

**[Screenshots](https://github.com/ZetaGlest/screenshots)**

Open games and [Server list and player stats](https://zetaglest.dreamhosters.com/)

[Detailed information about units in the game](https://zetaglest.github.io/)

## Stay Informed (Updates)

* [ChangeLog.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/ChangeLog.md)<br >
* [![RSS](rss_23x23.jpeg)](https://github.com/ZetaGlest/zetaglest-source/commits/develop.atom)
[Recent Commits to zetaglest-source:develop](https://github.com/ZetaGlest/zetaglest-source/commits/develop.atom)<br >
* [![RSS](rss_23x23.jpeg)](https://github.com/ZetaGlest/zetaglest-data/commits/develop.atom)
[Recent Commits to zetaglest-data:develop](https://github.com/ZetaGlest/zetaglest-data/commits/develop.atom)<br >
* [![RSS](rss_23x23.jpeg)](https://github.com/ZetaGlest/zetaglest.github.io/commits/master.atom)
[Recent Commits to the web site](https://github.com/ZetaGlest/zetaglest.github.io/commits/master.atom)

## Why this fork? (Project Goals)

ZetaGlest forked from MegaGlest at v3.13.0-dev

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

See [Build instructions](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md)

### Try the game without contributing

Use these commands:

    mkdir ZetaGlest
    cd ZetaGlest
    git clone https://github.com/ZetaGlest/zetaglest-source.git
    git clone https://github.com/ZetaGlest/zetaglest-data.git

Afterward, to
[build](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md),
change to the zetaglest-source/mk/ directory, select your operating system and run

    ./build-zg.sh

To execute the game:

    ./zetaglest

To run your own headless (dedicated) server:

    Forward TCP ports 61357-61368
    ./zetaglest --headless-server-mode

To start a server and host a game:

    Forward TCP ports 61357-61368
    Enter the ZetaGlest lobby and click "Host Game"

### Note

When serving a running game, a headless ZG server uses almost the
same amount of computer resources as a running game. Therefore, it is
recommended not to try connecting your ZG client to a headless server
running on the same computer.

### Extra Tech trees, mods, tilesets, scenarious (not yet available on the ZetaGlest server)

* [MODS.md](https://github.com/ZetaGlest/zetaglest-data/blob/develop/MODS.md)
* [TILESETS.md](https://github.com/ZetaGlest/zetaglest-data/blob/develop/TILESETS.md)
* [SCENARIOS.md](https://github.com/ZetaGlest/zetaglest-data/blob/develop/SCENARIOS.md)

### Contributing and Testing

If you'll be contributing code or changes to data, the procedures for
forking and cloning are outlined in [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)

Please see [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)
for extended, important instructions and guidelines for contributing.

## Contact

* [Discord](https://discord.gg/WaAaXS7)
* email: andy400-dev@yahoo.com
