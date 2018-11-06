#!/bin/bash
echo "Updating source code..."
cd ../..
git pull
echo "Updating game data..."
cd mk/linux
mkdir build
cd build
mkdir data
cd data
git pull
cd ../..
