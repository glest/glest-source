#!/bin/bash
echo "Downloading game data..."
currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

cd $DIR
mkdir build
cd build
git clone https://github.com/ZetaGlest/zetaglest-data.git data --branch 1.0
cd ..

if [ `id -u`'x' == '0x' ] || [ "$1" == "--manually" ]; then
	chmod -R 777 build/
fi

cd $currentDir
