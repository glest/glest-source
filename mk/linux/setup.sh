#!/bin/bash
echo
echo "Initializing Glest setup..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
bash ./clone-data.sh
echo
bash ./pull.sh
echo
bash ./build.sh
cd $currentDir
