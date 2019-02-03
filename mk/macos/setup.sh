#!/bin/sh
echo
echo "Initializing Glest setup..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
sh ./build-deps.sh
echo
sudo sh ./build.sh
cd $currentDir