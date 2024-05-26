#!/usr/bin/env bash

make git-submodule
qmk flash -kb splitkb/kyria/rev3 -km my_kyria_layout
