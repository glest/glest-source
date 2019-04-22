[![Build Status](https://travis-ci.org/glest/glest-source.svg?branch=master)](https://travis-ci.org/glest/glest-source)
[![Snap Status](https://build.snapcraft.io/badge/glest/glest-source.svg)](https://build.snapcraft.io/user/glest/glest-source)

# Glest

**Official Website: https://glest.io**

[Glest](https://glest.io) is a network multi-player real-time strategy game engine.
It includes several factions, each one consisting of many 3d characters. The factions are loosely
based on historical empires with added elements of fantasy, such as
mummies produced by Egyptian priests, shamans who summon
thunderbirds for air assaults, and Norsemen who can build flying
valkries and "Thors". Start the game by harvesting natural resources,
then use the cash to produce an army. Single-player mode against the
CPU is also available.

![Glest Screenshot](https://glest.io/docs/assets/screenshots/screen147.jpg)

## Download for Windows

#### [Download Glest from here](https://codeload.github.com/glest/windows-installer/zip/master).

Additionally, if you want
to contribute with the code on Windows, [please follow these
instructions](https://github.com/Glest/glest-source/blob/master/mk/windows/README.md).

## Downloads for linux

Three distro-agnostic options are available for Glest on linux:

1. [![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/glest)

2. Download the AppImage here: https://github.com/glest/glest-source/releases
       To run, set the `.AppImage` file to executable with `chmod +x Glest.AppImage`, then just execute it.

3. Install using Flatpak: https://github.com/glest/io.glest.Glest

## Quick Build Guide for Linux

Using the build script:

       git clone https://github.com/Glest/glest-source.git glest; sudo glest/mk/linux/setup.sh

Then run the following command to start the game:

       glest/mk/linux/build/glest

3. Building manually using CMake: https://github.com/glest/glest-source/blob/master/BUILD.md

For other operating systems, you must [**build and install from
source**](https://github.com/Glest/glest-source/blob/master/BUILD.md)
(Later, we'll be providing binary packages).

## Links

* **[Screenshots](https://github.com/Glest/screenshots)**
* **[Join us on Discord](https://discord.gg/es3EyBB)**
* **[Server list and player stats](http://master.glest.org)**
* [FAQ](https://glest.io/docs/faq.html)
* [Compiling](https://github.com/Glest/glest-source/blob/master/BUILD.md)
* [Contributing and Testing](https://github.com/Glest/glest-source#contributing-and-testing)
* [Updating](https://github.com/Glest/glest-source/blob/master/UPDATING.md)
* [ChangeLog](https://github.com/Glest/glest-source/blob/master/ChangeLog.md)

### Extra Tech trees, mods, tilesets, scenarios

* [MODS.md](https://github.com/Glest/glest-data/blob/master/MODS.md)
* [TILESETS.md](https://github.com/Glest/glest-data/blob/master/TILESETS.md)
* [SCENARIOS.md](https://github.com/Glest/glest-data/blob/master/SCENARIOS.md)

### Contributing and Testing

If you'll be contributing code or changes to data, the procedures for
forking and cloning are outlined in [CONTRIBUTING.md](https://github.com/Glest/glest-source/blob/master/CONTRIBUTING.md)

To run your own headless (dedicated) server, see [the FAQ](https://glest.io/docs/faq.html#headlessserver).
