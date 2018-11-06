#!/bin/bash
echo "Updating source code..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
cd ../..
git pull
echo "Updating game data..."
cd mk/linux
mkdir build
cd build
mkdir data
cd data
git pull
cd $currentDir
