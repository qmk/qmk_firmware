#!/bin/bash

# Customize according to your pcb version
pcb="rev5"
bootloader="dfu"

keyboard="planck"
keyboard_type="$keyboard/$pcb"
keymap="prog_qgmlwb"
layout="LAYOUT_ortho_4x12"

build_dir="../build"
build_hex="$build_dir/keymap.hex"
build_import="$build_dir/import.json"
build_layers="$build_dir/layers.json"
