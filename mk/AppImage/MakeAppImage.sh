#!/bin/bash

. /etc/os-release
if [[ $ID != "ubuntu" || $VERSION_ID != "18.04" ]];
then
    echo "Ubuntu 18.04 is required! System found: $ID $VERSION_ID"
fi;

mkdir Glest
mkdir deps

echo "\nGetting build deps..."
sudo ../linux/build-deps.sh

echo "\nGetting and installing required libs..."
sudo apt clean
sudo apt --download-only --reinstall install famfamfam-flag-png p7zip-full libcurl4 libfontconfig1 libfribidi0 libftgl2 libgcc1 libgl1-mesa-glx libgl1 libglew2.0 libglu1-mesa libircclient1 libjpeg8 liblua5.3-0 libminiupnpc10 libopenal1 libpng16-16 libsdl2-2.0-0 libstdc++6 libvorbisfile3 libwxbase3.0-0v5 libwxgtk3.0-0v5 libx11-6 libpulse0
cp /var/cache/apt/archives/*.deb deps

mkdir curdep
cd curdep
for f in ../deps/*.deb;
do
    ar x $f
    tar -xf data.tar.* -C ../Glest
    rm *
done;
cd ..
rm -rf curdep deps

echo "\nBuilding and installing Glest..."
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_MAP_EDITOR=OFF -DBUILD_MODEL_VIEWER=OFF -DINSTALL_DIR_BIN=/usr/bin/ -DINSTALL_DIR_DATA=/usr/share/glest/ ../../..
make -j$(nproc) DESTDIR=../Glest
rm -r *

echo "\n Getting and installing data..."
git clone https://github.com/glest/glest-data.git
mkdir build && cd build
cmake -DINSTALL_DIR_BIN=/usr/bin/ -DINSTALL_DIR_DATA=/usr/share/glest/ -DINSTALL_DIR_DESKTOP=/usr/share/applications/ -DINSTALL_DIR_ICON=/usr/share/icons/hicolor/256x256/ glest-data
make -j$(nproc) DESTDIR=../Glest
cd ..
rm -rf build
