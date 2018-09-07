#!/bin/sh
# Use this script to improve configuration of '.desktop' files.
# ----------------------------------------------------------------------------
# 2014 Written by filux <heross(@@)o2.pl>
# Copyright (c) 2014-2016 under GNU GPL v3.0+
LANG=C

CURRENTDIR="$(dirname "$(readlink -f "$0")")"
cd "$CURRENTDIR"; prmtr="Icon="; prmtr2="Exec="
if [ -f "zetaglest.desktop" ] && [ -f "zetaglest.png" ] && [ -f "zetaglest" ] \
    && [ -f "start_zetaglest" ] && [ ! -f "glest-dev.ini" ]; then
    desktop_location="$CURRENTDIR/zetaglest.desktop"; icon_location="$CURRENTDIR/zetaglest.png"
    exec_location="$CURRENTDIR/start_zetaglest"
    sed -i -e "s#$prmtr.*#$prmtr$icon_location#" -e "s#$prmtr2.*#$prmtr2\"$exec_location\"#" \
	"$desktop_location"
    chmod +x "$desktop_location"
fi
if [ -f "zetaglest_editor.desktop" ] && [ -f "zetaglest.png" ] && [ -f "zetaglest_editor" ] \
    && [ -f "start_zetaglest_mapeditor" ] && [ ! -f "glest-dev.ini" ]; then
    desktop_location="$CURRENTDIR/zetaglest_editor.desktop"
    icon_location="$CURRENTDIR/zetaglest.png"; exec_location="$CURRENTDIR/start_zetaglest_mapeditor"
    sed -i -e "s#$prmtr.*#$prmtr$icon_location#" -e "s#$prmtr2.*#$prmtr2\"$exec_location\"#" \
	"$desktop_location"
    chmod +x "$desktop_location"
fi
if [ -f "zetaglest_g3dviewer.desktop" ] && [ -f "zetaglest.png" ] && [ -f "zetaglest_g3dviewer" ] \
    && [ -f "start_zetaglest_g3dviewer" ] && [ ! -f "glest-dev.ini" ]; then
    desktop_location="$CURRENTDIR/zetaglest_g3dviewer.desktop"
    icon_location="$CURRENTDIR/zetaglest.png"; exec_location="$CURRENTDIR/start_zetaglest_g3dviewer"
    sed -i -e "s#$prmtr.*#$prmtr$icon_location#" -e "s#$prmtr2.*#$prmtr2\"$exec_location\"#" \
	"$desktop_location"
    chmod +x "$desktop_location"
fi
