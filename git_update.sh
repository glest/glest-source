#!/bin/bash
export LANG=C

cd "$(dirname $(readlink -f $0))" &&

echo $PWD &&

git pull &&

cd data &&
git pull &&

exit 0
