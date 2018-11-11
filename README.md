[![Build Status](https://travis-ci.org/ZetaGlest/zetaglest-source.svg?branch=develop)](https://travis-ci.org/ZetaGlest/zetaglest-source)

# ZetaGlest

**Official Website: https://zetaglest.github.io**

[ZetaGlest](https://zetaglest.github.io) is a fork of [MegaGlest](http://megaglest.org/),
a libre software cross platform real-time strategy game.

ZetaGlest is a network multi-player real-time strategy game engine.
It's shipped with the ZetaPack mod, which includes several factions,
each one consisting of many 3d characters. The factions are loosely
based on historical empires with added elements of fantasy, such as
mummies produced by Egyptian priests, Indian shamans who summon
thunderbirds for air assaults, and Norsemen who can build flying
valkries and "Thors". Start the game by harvesting natural resources,
then use the cash to produce an army. Single-player mode against the
CPU is also available.

![ZetaGlest ScreenShot](https://zetaglest.github.io/docs/assets/screenshots/screen147.jpg)

## Downloading the game

On Windows, the easiest way to get started is to [download and run the
installer](https://github.com/ZetaGlest/windows-installer). If you want
to contribute with the code on Windows, [please follow these
instructions](https://github.com/ZetaGlest/zetaglest-source/blob/develop/mk/windows/README.md).

For other operating systems, you must [**build and install from
source**](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md)
(Later, we'll be providing binary packages).

## Quick Build Guide for Linux

For Linux, run the following command:

    git clone https://github.com/ZetaGlest/zetaglest-source.git zetaglest && sudo zetaglest/mk/linux/setup.sh

Then run the following command to start the game:

    zetaglest/mk/linux/build/zetaglest

**README Contents**

* [Stay Informed (Updates)](https://github.com/ZetaGlest/zetaglest-source#stay-informed-updates)
* [Project Goals](https://github.com/ZetaGlest/zetaglest-source#why-this-fork-project-goals)
* [FAQ](https://github.com/ZetaGlest/zetaglest-source#faq)
* [Compiling](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md)
* [Contributing and Testing](https://github.com/ZetaGlest/zetaglest-source#contributing-and-testing)
* [Contact](https://github.com/ZetaGlest/zetaglest-source#contact)

**[System Requirements](https://zetaglest.github.io/docs/system_requirements.html)**

**[Screenshots](https://github.com/ZetaGlest/screenshots)**

Open games and [Server list and player stats](http://master.megaglest.org/)

[Detailed information about units in the game](https://zetaglest.github.io/)

## Stay Informed (Updates)

* [ZetaGlest Change Log](https://github.com/ZetaGlest/zetaglest-source/blob/develop/ChangeLog.md)<br >
* [![RSS](rss_23x23.jpeg)](https://zetaglest.github.io/feed.xml)
[The ZetaGlest Blog](https://zetaglest.github.io/blog/)<br >
* [![RSS](rss_23x23.jpeg)](https://github.com/ZetaGlest/zetaglest-source/commits/develop.atom)
[Recent Commits to zetaglest-source:develop](https://github.com/ZetaGlest/zetaglest-source/commits/develop.atom)<br >
* [![RSS](rss_23x23.jpeg)](https://github.com/ZetaGlest/zetaglest-data/commits/develop.atom)
[Recent Commits to zetaglest-data:develop](https://github.com/ZetaGlest/zetaglest-data/commits/develop.atom)<br >
* [![RSS](rss_23x23.jpeg)](https://github.com/ZetaGlest/zetaglest.github.io/commits/master.atom)
[Recent Commits to the web site](https://github.com/ZetaGlest/zetaglest.github.io/commits/master.atom)

## Why this fork? (Project Goals)

Because we love MegaGlest! We wanted to take the project into a
slightly different direction, and therefore we forked MegaGlest into
the ZetaGlest project.

## FAQ

The FAQ is located at
[https://zetaglest.github.io/docs/faq.html](https://zetaglest.github.io/docs/faq.html).

### Extra Tech trees, mods, tilesets, scenarios (not yet available on the ZetaGlest server)

* [MODS.md](https://github.com/ZetaGlest/zetaglest-data/blob/develop/MODS.md)
* [TILESETS.md](https://github.com/ZetaGlest/zetaglest-data/blob/develop/TILESETS.md)
* [SCENARIOS.md](https://github.com/ZetaGlest/zetaglest-data/blob/develop/SCENARIOS.md)

### Contributing and Testing

If you'll be contributing code or changes to data, the procedures for
forking and cloning are outlined in [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)

Please see [CONTRIBUTING.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md)
for extended, important instructions and guidelines for contributing.

To run your own headless (dedicated) server, see [the FAQ](https://zetaglest.github.io/docs/faq.html#headlessserver).

## Contact

* [Discord](https://discord.gg/WaAaXS7)
* [Message Board](https://groups.google.com/forum/#!forum/zetaglest)
* Email: zetaglest@gmail.com
