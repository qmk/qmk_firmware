#!/bin/sh

docker run --mount type=bind,source="${PWD}",target=/usr/src/app keymapbeautifier:1.0 ./KeymapBeautifier.py $*
