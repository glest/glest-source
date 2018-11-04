#!/bin/bash
# Use this script to build ZetaGlest using cmake
# ----------------------------------------------------------------------------
# Written by Mark Vejvoda <mark_vejvoda@hotmail.com>
# Copyright (c) 2011-2013 Mark Vejvoda under GNU GPL v3.0+

currentDir=$PWD
cd /usr/share
git clone https://github.com/ZetaGlest/zetaglest-data.git zetaglest
cd $currentDir
./pull.sh
./build-zg.sh
chmod -R 777 build/
