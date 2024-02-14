#!/bin/sh

docker run --mount type=bind,source="${PWD}",target=/usr/src/app --name keymapbeautifier --rm keymapbeautifier:1.0 ./KeymapBeautifier.py $*
