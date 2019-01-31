#!/bin/bash
echo
echo "Initializing Glest setup..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
./clone-data.sh
echo
./pull.sh
echo
./build.sh
cd $currentDir