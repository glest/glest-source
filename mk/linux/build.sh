#!/bin/bash
# Use this script to build Glest using cmake
# ----------------------------------------------------------------------------
# Written by Mark Vejvoda <mark_vejvoda@hotmail.com>
# Copyright (c) 2011-2013 Mark Vejvoda under GNU GPL v3.0+

currentDir=$PWD
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR
bash ./build-deps.sh
echo
bash ./build-nodeps.sh
cd $currentDir
