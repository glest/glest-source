# BUILD.md

## Set up the repositories locally

If you would like to contribute to development, you will need to
**fork** and then **clone your forks** of these 2 repositories:

* https://github.com/ZetaGlest/zetaglest-source
* https://github.com/ZetaGlest/zetaglest-data

### Procedure for cloning your forks

1. Create a new directory to clone your **zetaglest-source** and
**zetaglest-data** into e.g. call it `ZetaGlest`.

2. Enter (or 'cd') into the new directory (`ZetaGlest` in the example).

3. clone **zetaglest-source** and **zetaglest-data** using the clone
info provided by your fork. (Use the "Clone or Download" link, but
**do** select `clone` **not** `Download Zip`.) Make sure the cloned
repo directories are in the same directory, adjacent to each other (and
**not** in a subdirectory).

### Note

If you have cloned the repositories this way, do not use the
`git_update.sh` provided in the source directory. See
[syncing](https://github.com/ZetaGlest/zetaglest-source/blob/develop/CONTRIBUTING.md#syncing)
for information on how to sync your repo with the main upstream (no,
you can't juse use **_merge_**).

## Dependencies

### Linux

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

### Mac OS X

(Needs editing/updating)

### Windows

(Need editing/updating)

### *BSD

(Need editing/updating)

### Arch Linux

You can install the dependencies using `pacman`:

`pacman -S curl ftgl glew glu icu libgl libircclient libvorbis libx11
lua51 miniupnpc openal sdl2 wxgtk3 xerces-c cmake ftjam git mesa`

### Other (add sections)

(Add other specific operating systems)

## Compiling

### Linux

    ./build-zg.sh

### Mac OS X

    ./build-zg.sh

### Windows

(Need editing/updating)

### BSD

(Need editing/updating)

### Other (add sections)
