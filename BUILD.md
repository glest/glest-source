# BUILD.md

The Mac build may need attention. If you are interested in helping us
test that the build completes and the game runs, please post or
subscribe to this ticket: [Current
Status](https://github.com/ZetaGlest/zetaglest-source/issues/25)

* **Getting the code:**
  * [Set up the repositories locally](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#set-up-the-repositories-locally)
  * [cloning](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#procedure-for-cloning)
  * [Extra options for compiling](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#extra-options-for-compiling)

* **Dependencies**
  * [Windows](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#windows)
  * [Linux, Mac OS, *BSD](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#linux)
  * [Arch Linux](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#arch-linux)
  * [Mac OS](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#mac-os)
  * [BSD](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#bsd)

* [Installing](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#installing)

* **Compiling**
  * [Windows](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#windows)
  * [Linux, Mac OS, *BSD](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md#windows-1)

## Set up the repositories locally

If you think you may be contributing to development, we suggest
[**forking**](https://github.com/ZetaGlest/zetaglest-source#fork-destination-box)
and then **cloning your forks** of these 2 repositories. If you only
want to build and test out the game, and have no plans of submitting
patches, you don't need to worry about using the fork option (You can
fork later if you change your mind).

* https://github.com/ZetaGlest/zetaglest-source
* https://github.com/ZetaGlest/zetaglest-data

### Procedure for cloning

1. Create a new directory to clone your **zetaglest-source** and
**zetaglest-data** into e.g. call it `ZetaGlest`.

2. Enter (or 'cd') into the new directory (`ZetaGlest` in the example).

3. clone **zetaglest-source** and **zetaglest-data** using the clone
info provided by your fork or the main repos. (Use the "Clone or Download" link, but
**do** select `clone` **not** `Download Zip`.) Make sure the cloned
repo directories are in the same directory, adjacent to each other (and
**not** in a subdirectory).

### Note

If you have cloned the repositories using your forks, do not use the
`git_update.sh` provided in the source directory. See
[syncing](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md#syncing)
for information on how to sync your repo with the main upstream (no,
you can't juse use **_merge_**).

## Extra Options for compiling

Most people will never have to change the options when running `cmake`.

Some options you may want to change are:

To view models outside the game:

    BUILD_MODEL_VIEWER=ON (off by default)

To edit maps:

    BUILD_MAP_EDITOR=ON (off by default)

The **wxWidgets (libwxgtk3.0-dev on some systems)** and **libxml2-dev*
dependencies (mentioned below) is only required if you enable those
options.

To view all available options, use `cmake .. -LH` while in the build directory.

## Dependencies

### Windows

Follow the
[instructions](https://github.com/ZetaGlest/zetaglest-source/blob/develop/mk/windows/README.md)
listed in the `Windows` directory.

### Linux

On Debian, Ubuntu, Fedora, Opensuse and even more Linux distributions,
after you clone the source repository, you may use

    cd mk/linux
    sudo ./setupBuildDeps.sh

which will run your package manager and attempt to install the needed packages.

On Windows simply run `setup.bat` in `\mk\windows`.

(These may vary based on your operating system or Linux distribution;
we will attempt to document dependencies in more detail)

Below is a list of most dependencies you will need. This document needs
to indicate better which are optional and which are required.

gcc g++ cmake libsdl2-dev libalut-dev libgl1-mesa-dev libglu1-mesa-dev libvorbis-dev
 libx11-dev liblua5.2-dev libjpeg-dev libpng-dev libcurl4-gnutls-dev libircclient-dev
 libglew-dev libftgl-dev libfribidi-dev libcppunit-dev libminiupnpc-dev libfreetype6-dev
 libgnutls28-dev libkrb5-dev libkrb5-dev libnghttp2-dev libopenal-dev libldap2-dev
 librtmp-dev

[Current Status](https://github.com/ZetaGlest/zetaglest-source/issues/25)

### Mac OS

You can install the dependencies with [brew](https://brew.sh/)

    brew install sdl2 lua freetype ftgl libogg glew libvorbis cppunit glib fribidi miniupnpc wxmac
    brew outdated cmake || brew upgrade cmake; brew outdated pkgconfig || brew upgrade pkgconfig
    brew install Caskroom/cask/xquartz

### BSD

Below is a list of most of dependencies you will need.

A C++11 compiler is mandatory, so base (or package) **eg++** and **egcc**

You can install the dependencies using `pkg_add`:

`pkg_add cmake curl freealut ftgl glew gnutls icu4c jpeg lua libircclient libvorbis
miniupnpc nghttp2 openal png sdl2 wxWidgets xerces-c`

### Arch Linux

You can install the dependencies using `pacman`:

`pacman -S curl ftgl glew glu icu libgl libircclient libvorbis libx11
lua51 miniupnpc openal sdl2 wxgtk3 xerces-c cmake ftjam git mesa`

### Other (add sections)

(Add other specific operating systems)

## Installing

Now that you have the source code and the dependencies, you can either
compile ZetaGlest and run it without installing, or you can set options
to install it. If you plan to **install**, then you can **skip the sections below**
and read
[INSTALL.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/INSTALL.md)

## Compiling

### Windows

    ./build-zg.bat

### Linux, Mac OS, BSD

From the top of the project source directory:

    mkdir build
    cd build

(`cmake` On Linux or Mac OS)

    cmake .. -DINSTALL_DIR_DATA=<absolute-path-to-data>

(`cmake` on BSD. Setting the 2 variables before the cmake command tells
cmake to use the correct compiler)

    CC=`which egcc` CXX=`which eg++` cmake .. -DINSTALL_DIR_DATA=<absolute-path-to-data>

Now that the build configuration has been set, run make:

    make

The zetaglest binaries will be in the `build/` directory. Run
'./zetaglest' to start the game.

<!-- This needs to be duplicated in the BUILD.md and INSTALL.md doc -->
See [running](https://github.com/ZetaGlest/zetaglest-source#running) for
detailed information about running a server or hosting a game.

The value for INSTALL_DIR_DATA is written to the game when compiled,
therefore if you ever move your data directory, you will have to
recompile ZetaGlest.

After you run `cmake` for the first time, you won't need to specify any
options unless you want to change previously-used options. Just use

    cmake ..

(You'll need to run `make` and `make install` to rebuild.)

If you want to completely erase your previously-used options, remove
`build/CMakeCache.txt`.

If your build doesn't seem to be using the options you gave it, first
try removing CMakeCache.txt and rebuilding.
<!-- end duplication -->

### Other (add sections)
