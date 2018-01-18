#!/bin/bash
export LANG=C

cd "$(dirname $(readlink -f $0))"

git pull &&

cd data &&
git pull &&

cd .. &&

cd source/masterserver &&
git pull &&

cd ../.. &&

cd mk/linux/tools-for-standalone-client/installer/mojosetup
git pull &&

exit 0
