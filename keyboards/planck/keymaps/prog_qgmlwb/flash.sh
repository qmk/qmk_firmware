#!/bin/bash

# Go to root of
pushd .
cd ../../../../

# Set default keyboard
# qmk config user.keyboard=planck/rev5

# Set default keymap
# qmk config user.keymap=prog_qgmlwb

# Compile
qmk compile

# Flash
sudo make planck/rev5:prog_qgmlwb:dfu

popd
