#!/bin/bash

set -e


TAG=$(git describe --tags --abbrev=0)
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
qmk compile --compiledb -j 0 -e TARGET="gem80_wired_via_$TAG" -kb nuphy/gem80/ansi -km via

echo "[default] Compiling for wired"
make clean
qmk compile --compiledb -j 0 -e TARGET="gem80_wired_default_$TAG" -kb nuphy/gem80/ansi -km default

echo "Switch to wired variant"
sed -i 's/WORK_MODE USB_MODE/WORK_MODE THREE_MODE/' keyboards/nuphy/gem80/ansi/config.h
echo ""
echo ""

echo "[via] Compiling for three-mode"
make clean
qmk compile --compiledb -j 0 -e TARGET="gem80_threemode_via_$TAG" -kb nuphy/gem80/ansi -km via

echo "[default] Compiling for three-mode"
make clean
qmk compile --compiledb -j 0 -e TARGET="gem80_threemode_default_$TAG" -kb nuphy/gem80/ansi -km default


echo "[halo75v2:via] Compiling"
make clean
qmk compile --compiledb -j 0 -e TARGET="halo75v2_via_$TAG" -kb nuphy/halo75v2/ansi -km via

echo "[halo75v2:default] Compiling"
make clean
qmk compile --compiledb -j 0 -e TARGET="halo75v2_default_$TAG" -kb nuphy/halo75v2/ansi -km default
