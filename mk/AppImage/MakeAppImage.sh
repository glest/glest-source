#!/bin/bash

. /etc/os-release
if [[ $ID != "ubuntu" || $VERSION_ID != "18.04" ]];
then
    echo "Ubuntu 18.04 is required! System found: $ID $VERSION_ID"
fi;

rm -rf Glest
mkdir Glest

echo
echo "Getting build deps..."
sudo ../linux/build-deps.sh

echo
echo "Building and installing Glest..."
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_MAP_EDITOR=OFF -DBUILD_MODEL_VIEWER=OFF ../../..
make -j$(nproc) && make install DESTDIR=../Glest
rm -r *

echo
echo "Getting and installing data..."
../../linux/clone-data.sh

cmake -DCMAKE_INSTALL_PREFIX=/usr ../../linux/build/data
make && make install DESTDIR=../Glest
cd ..
rm -rf build
# Remove useless metainfo.
rm Glest/usr/share/metainfo/io.glest.Editor.appdata.xml

wget -c "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage"

echo
echo "Creating the AppImage..."

# Path to pulseaudio libs.
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/pulseaudio/
:/usr/lib/i386-linux-gnu/pulseaudio/:$LD_LIBRARY_PATH

chmod +x linuxdeploy-x86_64.AppImage
./linuxdeploy-x86_64.AppImage --appdir=Glest --output appimage
chmod +x Glest*.AppImage

echo
echo "Done!"
