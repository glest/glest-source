#!/bin/bash
cd ../..
git pull
currentDir=$PWD
cd /usr/share/zetaglest
git pull
cd $currentDir
