#!/bin/bash

set -e

localtag=$(git describe --tags --abbrev=0)
TAG=${1-$localtag}-ryodeushii
echo "=============================="
echo "      Version tag: $TAG       "
echo "=============================="


echo ""
echo ""
echo "===== VIA variant ====="
echo ""

echo "Switch to wired variant"
sed -i 's/WORK_MODE THREE_MODE/WORK_MODE USB_MODE/' keyboards/nuphy/gem80/ansi/config.h
echo ""
echo ""

echo "[via] Compiling for wired"
make clean
qmk compile --compiledb -j 0 -e TARGET="wired_via_$TAG" -kb nuphy/gem80/ansi -km via

echo "[default] Compiling for wired"
make clean
qmk compile --compiledb -j 0 -e TARGET="wired_default_$TAG" -kb nuphy/gem80/ansi -km default

echo "Switch to wired variant"
sed -i 's/WORK_MODE USB_MODE/WORK_MODE THREE_MODE/' keyboards/nuphy/gem80/ansi/config.h
echo ""
echo ""

echo "[via] Compiling for three-mode"
make clean
qmk compile --compiledb -j 0 -e TARGET="threemode_via_$TAG" -kb nuphy/gem80/ansi -km via

echo "[default] Compiling for three-mode"
make clean
qmk compile --compiledb -j 0 -e TARGET="threemode_default_$TAG" -kb nuphy/gem80/ansi -km default

