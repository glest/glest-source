# Installing Glest

You can install from source or download Installers or packages for your
operating system.

## Binary Packages

## Windows

* [Glest Windows Installer](https://github.com/Glest/windows-installer)
* [Build and Install from source code](https://github.com/Glest/glest-source/blob/master/mk/windows/README.md)

## Linux, Mac OS, BSD

Review the dependency information and instructions for [building from
source](https://github.com/Glest/glest-source/blob/master/BUILD.md).

From the top of the project source directory:

    mkdir build
    cd build

**Note:** Using the paths specified below, you will need super-user
privileges when you run `make install`.

`cmake` On **Linux or Mac OS**

    cmake .. -DCMAKE_INSTALL_PREFIX=/usr

`cmake` on **BSD**. Setting the 2 variables before the cmake command tells
cmake to use the correct compiler.

    CC=`which egcc` CXX=`which eg++` cmake .. -DCMAKE_INSTALL_PREFIX=/usr

Make and install the program:

    make
    make install

The binaries will be installed to CMAKE_INSTALL_PREFIX/games (i.e. /usr/games)

Before you run `make`, you can confirm the installation directories by
entering `cmake .. -LH`. For example, These are the destination
directories when `-DCMAKE_INSTALL_PREFIX=/home/andy/local` is used:

```
// The installation path for binaries
INSTALL_DIR_BIN:PATH=/home/andy/local/games

// The installation path for data files
INSTALL_DIR_DATA:PATH=/home/andy/local/share/glest

// The installation path for desktop files
INSTALL_DIR_DESKTOP:PATH=/home/andy/local/applications

// The installation path for icon files
INSTALL_DIR_ICON:PATH=/home/andy/local/share/pixmaps

// The installation path for manpage files
INSTALL_DIR_MAN:PATH=/home/andy/local/share/man/man6
```

If you wish to install to a location that does not require super-user
privileges, change '/usr' to a location to which you have write access.

See [running](https://github.com/Glest/glest-source#running) for
detailed information about running a server or hosting a game.

The value for INSTALL_DIR_DATA is written to the game when compiled,
therefore if you ever move your data directory, you will have to
recompile Glest.

After you run `cmake` for the first time, you won't need to specify any
options unless you want to change previously-used options. Just use

    cmake ..

(You'll need to run `make` and `make install` to rebuild.)

If you want to completely erase your previously-used options, remove
`build/CMakeCache.txt`.

If your build doesn't seem to be using the options you gave it, first
try removing CMakeCache.txt and rebuilding.

**Note:** The majority of the game data is not installed during the
steps above. The files from the glest-data repo must be copied into
CMAKE_INSTALL_PREFIX/share/glest, or specify an existing path to
data by adding this option to cmake:

    `-DINSTALL_DIR_DATA=<absolute-path-to-data>`

#### Uninstalling

Makefiles generated with cmake do not have an 'uninstall' option. There
is a [discussion at this
link](https://stackoverflow.com/questions/41471620/cmake-support-make-uninstall)
on how to do that.

Instead of using `make install`, you may wish to install using a
distribution package. Later, you could uninstall using your package
manager.
