#!/bin/bash

function export_variables {
    local util_dir=~/qmk_utils
    export PATH=$PATH:$util_dir
    export PATH=$PATH:$util_dir/avr8-gnu-toolchain/bin
    export PATH=$PATH:$util_dir/gcc-arm-none-eabi/bin
}

export_variables
