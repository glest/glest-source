#!/bin/bash
echo
echo "Initializing ZetaGlest setup..."
./clone-data.sh
echo
./pull.sh
echo
./build-zg.sh
