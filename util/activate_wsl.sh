#!/bin/bash

function export_variables {
    local util_dir=~/qmk_utils
    local download_dir=$util_dir/wsl_downloaded

    export DFU_PROGRAMMER=$download_dir/dfu-programmer/dfu-programmer.exe
    export DFU_UTIL=$download_dir/dfu-util-0.9-win64/dfu-util.exe
    export TEENSY_LOADER_CLI=$download_dir/teensy_loader_cli.exe
    export BOOTLOADHID_PROGRAMMER=$download_dir/bootloadHID.2012-12-08/commandline/bootloadHID.exe
}

export_variables
