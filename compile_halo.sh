#!/bin/bash

set -e

localtag=$(git describe --tags --abbrev=0)
TAG=${1-$localtag}-ryodeushii

echo "=============================="
echo "      Version tag: $TAG       "
echo "=============================="


echo "[halo75v2:via] Compiling"
make clean
qmk compile --compiledb -c -j 0 -e TARGET="via_$TAG" -kb nuphy/halo75v2/ansi -km via

echo "[halo75v2:default] Compiling"
make clean
qmk compile --compiledb -c -j 0 -e TARGET="default_$TAG" -kb nuphy/halo75v2/ansi -km default
