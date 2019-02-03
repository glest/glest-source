#!/bin/bash
echo
echo "Initializing Glest setup..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
./build-deps.sh
echo
./build.sh
cd $currentDir