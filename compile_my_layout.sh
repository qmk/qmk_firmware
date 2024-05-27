#!/usr/bin/env bash

make git-submodule
qmk compile -e CONVERT_TO=liatris -kb splitkb/kyria/rev3 -km my_kyria_layout
