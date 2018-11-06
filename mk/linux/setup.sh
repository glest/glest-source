#!/bin/bash
# Use this script to build ZetaGlest using cmake
# ----------------------------------------------------------------------------
# Written by Mark Vejvoda <mark_vejvoda@hotmail.com>
# Copyright (c) 2011-2013 Mark Vejvoda under GNU GPL v3.0+

echo "Initializing ZetaGlest setup..."
echo
echo "Downloading game data..."
mkdir build
cd build
git clone https://github.com/ZetaGlest/zetaglest-data.git data
cd ..
./pull.sh
./build-zg.sh
if [ `id -u`'x' == '0x' ] || [ "$1" == "--manually" ]; then
	chmod -R 777 build/
fi
