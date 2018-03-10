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

gcc g++ cmake libsdl2-dev libalut-dev libgl1-mesa-dev libglu1-mesa-dev libvorbis-dev
 libx11-dev liblua5.2-dev libjpeg-dev libpng-dev libcurl4-gnutls-dev libircclient-dev
 libglew-dev libftgl-dev libfribidi-dev libcppunit-dev libminiupnpc-dev libfreetype6-dev
libgnutls28-dev libkrb5-dev libkrb5-dev libnghttp2-dev libopenal-dev libldap2-dev
libwxgtk3.0-dev librtmp-dev libvlccore-dev libvlc-dev

Additionally for map editor and model viewer:

libwxgtk3.0-dev libxml2-dev

### Mac OS X

(Needs editing/updating)
[Current Status](https://github.com/ZetaGlest/zetaglest-source/issues/25)

### Windows

<!--

#### Temporary build instructions for Windows (subject to change):

1. Make sure Visual Studio 2015 is installed.

2. Make sure Git for Windows is installed.

3. Make sure regular MegaGlest is installed.

4. Open the command line from the directory you want to store the
source code, and enter:

    git clone https://github.com/ZetaGlest/zetaglest-source.git

(if you think you may be contributing in the future, it's recommended
to subsitute the URL listed above with the address of your fork)

5. Now navigate to the source code directory, and in /mk/windows there
is "build-mg-2015.bat". Run it.

6. Copy the MegaGlest folder from Program Files or Program Files (x86)
to somewhere else, and rename the copied folder to ZetaGlest.

7. When the script is finished, there is megaglestx64.exe in
/mk/windows. Rename it to zetaglest.exe.

8. Copy zetaglest.exe, glest.ini and glestkeys.ini (which is in
/mk/shared) into the ZetaGlest folder.

9. From the same ZetaGlest folder, delete all directories except for
the "blender" directory. Basically all that should be left is:
   the blender folder, and the following files:

    * 7z.dll
    * 7z.exe
    * glest.ini
    * glestkeys.ini
    * megaglest.ico
    * megaglest_editorx64.exe
    * megaglest_g3dviewerx64.exe
    * megaglestx64.exe
    * NetworkThrottleFix.reg
    * OpenAL64.dll
    * servers.ini
    * uninstall.exe

10. Create yet another temporary directory anywhere, open the command
line from there and enter: "git clone
https://github.com/ZetaGlest/zetaglest-data.git"

11. After all the data is cloned into the temporary directory, copy all
of its contents (the folders are: data, docs, maps...etc, and the files
are MODS.md, README.md...etc) into the working ZetaGlest folder, right
beside the executable.

12. Run zetaglest.exe and enjoy! -->

We are in the process of improving and updating the Windows build
process. Please subscribe to the ticket below for updates:

[Current Status](https://github.com/ZetaGlest/zetaglest-source/issues/37)

We expect to have the Windows build process completed by Tuesday March 13, 2018

### *BSD

(Need editing/updating)
[Current Status](https://github.com/ZetaGlest/zetaglest-source/issues/56)

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
