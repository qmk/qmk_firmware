#!/bin/bash

set -e


TAG=$(git describe --tags --abbrev=0)
echo "=============================="
echo "= Version tag: $TAG   ="
echo "=============================="


echo "Compiling for wired"
sed -i 's/WORK_MODE THREE_MODE/WORK_MODE USB_MODE/' keyboards/nuphy/gem80/ansi/config.h
make clean
qmk compile --compiledb -j 0 -e TARGET="gem80_wired_$TAG" -kb nuphy/gem80/ansi -km via

echo "Compiling for three-mode"
sed -i 's/WORK_MODE USB_MODE/WORK_MODE THREE_MODE/' keyboards/nuphy/gem80/ansi/config.h
qmk compile --compiledb -j 0 -e TARGET="gem80_threemode_$TAG" -kb nuphy/gem80/ansi -km via
