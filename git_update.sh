#!/bin/bash
export LANG=C

cd "$(dirname $(readlink -f $0))"

cd git pull &&

cd data &&
git pull &&

cd source/masterserver &&
git pull &&

cd mk/linux/tools-for-standalone-client/installer/mojosetup
git pull

