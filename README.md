[![Build Status](https://travis-ci.org/ZetaGlest/zetaglest-source.svg?branch=develop)](https://travis-ci.org/ZetaGlest/zetaglest-source)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/16606/badge.svg)](https://scan.coverity.com/projects/zetaglest)

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

**README Contents**

* [Stay Informed (Updates)](https://github.com/ZetaGlest/zetaglest-source#stay-informed-updates)
* [Project Goals](https://github.com/ZetaGlest/zetaglest-source#why-this-fork-project-goals)
* [Download executable files](https://github.com/ZetaGlest/zetaglest-source#download-executable-files)
* [Running](https://github.com/ZetaGlest/zetaglest-source#running)
* [Extra Tech trees, mods, tilesets, scenarious (not yet available on the ZetaGlest server)](https://github.com/ZetaGlest/zetaglest-source#extra-tech-trees-mods-tilesets-scenarious-not-yet-available-on-the-zetaglest-server)
* [Contributing and Testing](https://github.com/ZetaGlest/zetaglest-source#contributing-and-testing)
* [Contact](https://github.com/ZetaGlest/zetaglest-source#contact)

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

ZetaGlest forked from MegaGlest at v3.13.0-dev ([12998eb](https://github.com/ZetaGlest/zetaglest-source/commit/12998eb10f6447ac89a45d1e6d76f17946647b7a))

Because we love MegaGlest! We wanted to take the project into a
slightly different direction, and therefore we forked MegaGlest into
the ZetaGlest project.

## Download executable files

On Windows, the easiest way to get started is to [download and run the
installer](https://github.com/ZetaGlest/windows-installer). If you want
to contribute with the code on Windows, [please follow these
instructions](https://github.com/ZetaGlest/zetaglest-source/blob/develop/mk/windows/README.md).

For other operating systems, you must **[build and install from
source]**(https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md)
(Later, we'll be providing binary packages).

(The ETA for the first official release can be viewed from the [development
milestone](https://github.com/ZetaGlest/zetaglest-source/milestone/1).)

## Running

    ./zetaglest (if you didn't install)

OR

    zetaglest (if you installed and the binary is in your PATH)

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
* [Message Board](https://groups.google.com/forum/#!forum/zetaglest)
* Email: zetaglest@gmail.com
