#!/bin/bash
# Use this script to build ZetaGlest Binary Archive for a Version Release
# ----------------------------------------------------------------------------
# Written by Mark Vejvoda <mark_vejvoda@hotmail.com>
# Copyright (c) 2011 Mark Vejvoda under GNU GPL v3.0+
LANG=C

CURRENTDIR="$(dirname "$(readlink -f "$0")")"
# set this to non 0 to skip building the binary
skipbinarybuild=0
if [ "$1" = "-CI" ] || ( [ "$1" = "--installer" ] && \
    [ "$(find "$CURRENTDIR" -maxdepth 1 -name 'zetaglest' -mmin -60)" ] ); then
    skipbinarybuild=1
fi

# Consider setting this for small packages if there's plenty of RAM and CPU available:
#export XZ_OPT="$XZ_OPT -9e"

if [ "$1" = "-CI" ] || [ "$1" = "--installer" ] || [ "$(echo "$1" | grep '\--show-result-path')" != "" ]; then
    if [ "$2" != "" ]; then SOURCE_BRANCH="$2"; fi
fi

cd "$CURRENTDIR"
VERSION=`./mg-version.sh --version`
kernel=`uname -s | tr '[A-Z]' '[a-z]'`
architecture=`uname -m  | tr '[A-Z]' '[a-z]'`

RELEASEDIR_ROOT="$CURRENTDIR/../../../release/"
PROJDIR="$CURRENTDIR/"
REPODIR="$CURRENTDIR/../../"
REPO_DATADIR="$REPODIR../zetaglest-data"
if [ -d "$REPODIR/.git" ] && [ "$(which git 2>/dev/null)" != "" ]; then
    cd "$REPODIR"
    if [ "$SOURCE_BRANCH" = "" ]; then SOURCE_BRANCH="$(git branch | awk -F '* ' '/^* / {print $2}')"; fi
    SOURCE_COMMIT="$(echo "[$(git rev-list HEAD --count).$(git log -1 --format=%h --abbrev=7)]")"
fi
ARCHIVE_TYPE="tar.xz"
SNAPSHOTNAME="mg-binary-$kernel-$architecture"
SN_PACKAGE="$SNAPSHOTNAME-$VERSION-$SOURCE_BRANCH.$ARCHIVE_TYPE"
RELEASENAME="zetaglest-binary-$kernel-$architecture"
PACKAGE="$RELEASENAME-$VERSION.$ARCHIVE_TYPE"
if [ "$SOURCE_BRANCH" != "" ] && [ "$SOURCE_BRANCH" != "master" ] && [ "$(echo "$VERSION" | grep '\-dev$')" != "" ]; then
    RELEASENAME="$SNAPSHOTNAME"; PACKAGE="$SN_PACKAGE"
fi
RELEASEDIR="${RELEASEDIR_ROOT}/${RELEASENAME-$VERSION}"
if [ "$1" = "--show-result-path" ]; then echo "${RELEASEDIR_ROOT}/$PACKAGE"; exit 0
elif [ "$1" = "--show-result-path2" ]; then echo "${RELEASEDIR_ROOT}/$RELEASENAME"; exit 0; fi

echo "Creating binary package in $RELEASEDIR"
if [ "$SOURCE_BRANCH" != "" ]; then echo "Detected parameters for source repository: branch=[$SOURCE_BRANCH], commit=$SOURCE_COMMIT"; fi

[[ -d "$RELEASEDIR" ]] && rm -rf "$RELEASEDIR"
mkdir -p "$RELEASEDIR"

if [ $skipbinarybuild = 0 ]
then
  # build the binaries
  echo "building binaries ..."
  cd $PROJDIR
  [[ -d "build" ]] && rm -rf "build"
  ./build-zg.sh
  if [ $? -ne 0 ]; then
    echo 'ERROR: "./build-zg.sh" failed.' >&2; exit 1
  fi
else
  echo "SKIPPING build of binaries ..."
fi

cd $PROJDIR
mkdir -p "$RELEASEDIR/lib"

if [ -d "lib" ]; then rm -rf "lib"; fi
echo "building binary dependencies ..."
for zg_bin in zetaglest zetaglest_editor zetaglest_g3dviewer; do
    ./makedeps_folder.sh "$zg_bin"
    if [ "$?" -ne "0" ]; then echo "ERROR: \"./makedeps_folder.sh $zg_bin\" failed." >&2; exit 2; fi
done

# copy binary info
cd $PROJDIR
echo "copying binaries ..."
cp -r lib/* "$RELEASEDIR/lib"
if [ $? != 0 ]; then
    exit $?
fi

cp ../shared/*.ico {../shared/,}*.ini "$RELEASEDIR/"
if [ $? != 0 ]; then
    exit $?
fi

if [ -e "$RELEASEDIR/glest-dev.ini" ]; then
    rm -f "$RELEASEDIR/glest-dev.ini"
    if [ $? != 0 ]; then
        exit $?
    fi
fi

cd $REPO_DATADIR/others/icons
if [ $? != 0 ]; then
    exit $?
fi

cp *.bmp *.png *.xpm "$RELEASEDIR/"
if [ $? != 0 ]; then
    exit $?
fi

if [ "$1" != "--installer" ]; then
    cd $REPO_DATADIR/others/desktop
    if [ $? != 0 ]; then
        exit $?
    fi

    cp *.desktop "$RELEASEDIR/"
    if [ $? != 0 ]; then
        exit $?
    fi
fi

cd $PROJDIR
if [ $? != 0 ]; then
    exit $?
fi

cp zetaglest zetaglest_editor zetaglest_g3dviewer start_zetaglest_gameserver "$RELEASEDIR/"
if [ $? != 0 ]; then
    exit $?
fi

cd "$CURRENTDIR/tools-for-standalone-client"

if [ $? != 0 ]; then
    exit $?
fi

cp start_zetaglest start_zetaglest_mapeditor start_zetaglest_g3dviewer "$RELEASEDIR/"
if [ $? != 0 ]; then
    exit $?
fi

if [ "$1" != "--installer" ]; then
    cp zetaglest-configure-desktop.sh "$RELEASEDIR/"
    if [ $? != 0 ]; then
        exit $?
    fi
fi

if [ "$(echo "$VERSION" | grep -v '\-dev$')" != "" ]; then
    ./prepare-mini-update.sh --only_script; sleep 0.5s

    cp zetaglest-mini-update.sh "$RELEASEDIR/"
    if [ $? != 0 ]; then
        exit $?
    fi

    if [ -e "zetaglest-mini-update.sh" ]; then
        rm -f "zetaglest-mini-update.sh"
        if [ $? != 0 ]; then
            exit $?
        fi
    fi

    cd $CURRENTDIR
    if [ -e "zetaglest" ] && [ "$1" != "--installer" ]; then
	ldd_log="$(echo "$VERSION - $kernel - $architecture - $(date +%F)")"
	ldd_log="$(echo -e "$ldd_log\n\nzetaglest:\n$(ldd zetaglest | awk '{print $1}')")"
	if [ -e "zetaglest_editor" ]; then
	    ldd_log="$(echo -e "$ldd_log\n\nzetaglest_editor:\n$(ldd zetaglest_editor | awk '{print $1}')")"
	fi
	if [ -e "zetaglest_g3dviewer" ]; then
	    ldd_log="$(echo -e "$ldd_log\n\nzetaglest_g3dviewer:\n$(ldd zetaglest_g3dviewer | awk '{print $1}')")"
	fi
	echo "$ldd_log" > "$RELEASEDIR/ldd-zetaglest.log"
    fi
    echo "$(date -u)" > "$RELEASEDIR/build-time.log"
fi

mkdir -p "$RELEASEDIR/blender/"
if [ $? != 0 ]; then
    exit $?
fi

cp "$CURRENTDIR/../../source/tools/glexemel/"*.py "$RELEASEDIR/blender/"
if [ $? != 0 ]; then
    exit $?
fi

if [ "$1" != "--installer" ]; then
    echo "creating $PACKAGE"
    cd $CURRENTDIR
    if [ $? != 0 ]; then
        exit $?
    fi

    [[ -f "${RELEASEDIR_ROOT}/$PACKAGE" ]] && rm -f "${RELEASEDIR_ROOT}/$PACKAGE"
    cd $RELEASEDIR
    if [ $? != 0 ]; then
        exit $?
    fi

    tar -cf - * | xz > ../$PACKAGE
    if [ $? != 0 ]; then
        exit $?
    fi

    cd $CURRENTDIR
    if [ $? != 0 ]; then
        exit $?
    fi

    ls -la ${RELEASEDIR_ROOT}/$PACKAGE
    if [ $? != 0 ]; then
        exit $?
    fi
fi
if [ "$1" = "-CI" ] && [ -d "$RELEASEDIR" ]; then
    rm -rf "$RELEASEDIR"
    if [ $? != 0 ]; then
        exit $?
    fi
fi
