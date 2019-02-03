#!/bin/sh
echo
echo "Initializing Glest setup..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
bash ./build-deps.sh
echo
bash ./build.sh
cd $currentDir