#!/bin/sh

# Export the source code

PACKAGE=libircclient
BINARYFILE="libircclient.dll"

FILE_VERSION="src/params.h"

# Get current version
VERSION_MAJOR=`sed -n 's/^\#define\s\+LIBIRC_VERSION_HIGH\s\+\([0-9]\+\)/\1/p' $FILE_VERSION`
VERSION_MINOR=`sed -n 's/^\#define\s\+LIBIRC_VERSION_LOW\s\+\([0-9]\+\)/\1/p' $FILE_VERSION`
CURRENTVER="$VERSION_MAJOR.$VERSION_MINOR"

BUILDDIR="build"
RELEASEDIR="release/$CURRENTVER"
PKGDIR="$PACKAGE-$CURRENTVER"

if [ -d "$BUILDDIR" ]; then
	rm -rf "$BUILDDIR"
fi

if [ ! -d "$RELEASEDIR" ]; then
	mkdir -p $RELEASEDIR
fi

if [ -d "$PKGDIR" ]; then
	rm -rf "$PKGDIR"
fi

# Export the build directory to build the documentation
svn export . "$BUILDDIR/" || exit 1

# Build the documentation
(cd $BUILDDIR/doc && make singlehtml && make man && make latexpdf) || exit 1

# Package the documentations
cp $BUILDDIR/doc/_build/latex/Libircclient.pdf $RELEASEDIR/$PKGDIR.pdf || exit 1
(cd $BUILDDIR/doc/_build/singlehtml && zip -r ../$PKGDIR-html.zip .)
mv $BUILDDIR/doc/_build/$PKGDIR-html.zip $RELEASEDIR/ || exit 1

# Source package
svn export . "$PKGDIR/" || exit 1
mkdir $PKGDIR/man
cp $BUILDDIR/doc/_build/man/libircclient.1 $PKGDIR/man/ || exit 1
tar zcf "$RELEASEDIR/$PKGDIR.tar.gz" $PKGDIR/ || exit 1
rm -rf $PKGDIR/*

# win32
export PATH=$PATH:/usr/toolchains/windows-x86-complete/bin/
(cd $BUILDDIR && ./configure --enable-shared --host=i686-w64-mingw32.static && make)  || exit 1

BINDIR="$PKGDIR/bin"
mkdir -p $BINDIR
cp $BUILDDIR/src/libircclient.dll $BINDIR/ || exit 1
cp $BUILDDIR/src/libircclient.lib $BINDIR/  || exit 1
mkdir "$PKGDIR/include"
cp include/*.h "$PKGDIR/include"  || exit 1
mkdir "$PKGDIR/examples"
cp examples/*.c* $PKGDIR/examples  || exit 1
mkdir "$PKGDIR/doc"
cp $RELEASEDIR/$PKGDIR.pdf "$PKGDIR/doc/" || exit 1

zip -r $RELEASEDIR/$PKGDIR-win32-dll.zip $PKGDIR || exit 1

# And the SSL version
(cd $BUILDDIR && make distclean && ./configure --enable-shared --host=i686-w64-mingw32.static --enable-openssl && make clean && make)  || exit 1
cp $BUILDDIR/src/libircclient.dll $BINDIR/  || exit 1
cp $BUILDDIR/src/libircclient.lib $BINDIR/  || exit 1

zip -r $RELEASEDIR/$PKGDIR-win32-dll-openssl.zip $PKGDIR || exit 1

rm -rf "$BUILDDIR" "$PKGDIR"
echo "Done! Version $CURRENTVER released!"
