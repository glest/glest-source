#!/bin/bash
#
# git_update.sh: update the ZetaGlest source and data repos. Use this
# script if you've cloned from the master repositories, not if you're
# a fork.
#
# FIXME: there should be a way to check if this is a clone of the
# main repo, or a fork. If it's a fork, this shouldn't be run. Mentioned
# in the docs, but it would be good to have a catch in this script.

export LANG=C

cd "$(dirname $(readlink -f $0))" &&

echo $PWD

git pull &&

echo $PWD

cd ../zetaglest-data &&
git pull &&

exit 0
