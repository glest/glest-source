#!/bin/bash
# script for use with travis and on linux only
#
# Copyright (c) 2015-2016 MegaGlest Team under GNU GPL v3.0+
#
# Copyright (c) 2018
# modified for ZetaGlest <https://github.com/ZetaGlest>
# ZetaGlest Team

# This only needs to be changed when Travis updates the Ubuntu version
# it's using.
codename=trusty

Compiler_name="$1"; Compiler_version="$2"
Compiler_version_grep="$(echo "$Compiler_version" | sed 's/\./\\./g')"

set -x
if [ "$Compiler_version" != "" ] && [ "$Compiler_version" != "default" ]; then
  # UPDATE REPOS
  sudo apt-get update -qq
  sudo apt-get install -y -qq

  set +x
  if [ "$Compiler_name" = "gcc" ]; then
    VersionAvByDefault="$(apt-cache search ^g[c+][c+]-[0-9] | grep -v '[0-9]-[a-zA-Z]' | grep "^gcc-$Compiler_version_grep")"
  elif [ "$Compiler_name" = "clang" ]; then
    VersionAvByDefault="$(apt-cache search ^clang-[0-9] | grep -v '[0-9]-[a-zA-Z]' | grep "^clang-$Compiler_version_grep")"
  fi
  set -x
  if [ "$VersionAvByDefault" = "" ]; then
    # ubuntu test toolchain needed for more recent version of gcc and clang-6.0
    sudo add-apt-repository --yes "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu ${codename} main"
  fi
fi

if [ "$VersionAvByDefault" = "" ]; then
  # UPDATE REPOS
  sudo apt-get update -qq
  sudo apt-get install -y -qq
fi
set -e

if [ "$Compiler_version" != "" ] && [ "$Compiler_version" != "default" ]; then
  if [ "$Compiler_name" = "gcc" ]; then
    set +ex
    Gcc_AvSepGpp="$(apt-cache search ^g[c+][c+]-[0-9] | grep -v '[0-9]-[a-zA-Z]' | grep "^g++-$Compiler_version_grep")"
    set -ex
    if [ "$Gcc_AvSepGpp" = "" ]; then
      sudo apt-get --allow-unauthenticated install -qq --force-yes gcc-${Compiler_version}
    else
      sudo apt-get --allow-unauthenticated install -qq --force-yes gcc-${Compiler_version} g++-${Compiler_version}
    fi
  elif [ "$Compiler_name" = "clang" ]; then
    # llvm-toolchain needed for more recent version of clang
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
    sudo -E apt-add-repository "deb http://apt.llvm.org/trusty/ llvm-toolchain-trusty-6.0 main"
    sudo -E apt-get -yq update &>> ~/apt-get-update.log
    sudo -E apt-get -yq --no-install-suggests --allow-unauthenticated \
        --no-install-recommends $TRAVIS_APT_OPTS install clang-${Compiler_version}
  fi
fi

# what available versions we can use
set +x
apt-cache search ^g[c+][c+]-[0-9] | grep -v '[0-9]-[a-zA-Z]'
apt-cache search ^clang-[0-9] | grep -v '[0-9]-[a-zA-Z]'
set -x

# INSTALL OUR DEPENDENCIES

# These 2 don't get installed automatically, but are required for libsdl2-dev
sudo apt-get install -y -q libegl1-mesa-dev libgles2-mesa-dev

sudo mk/linux/setupBuildDeps.sh --quiet
