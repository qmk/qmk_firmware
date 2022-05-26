#!/bin/bash

# Customize according to your pcb version
pcb="rev5"
bootloader="dfu"

keyboard="planck"
keyboard_type="$keyboard/$pcb"
keymap="prog_qgmlwb"
layout="LAYOUT_ortho_4x12"

repo="$(realpath $PWD/../../../../..)"
build_dir="../build"
build_hex="$build_dir/keymap.hex"

col_reset="\e[m"
col_yellow="\e[33m"
col_green="\e[32m"
