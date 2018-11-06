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
if [ `id -u`'x' == '0x' ] || [ "$1" == "--manually" ]; then
	chmod -R 777 ../../build/
	cd ../../../..
	chmod -R 777 .git/
fi
cd $currentDir
