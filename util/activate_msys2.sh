#!/bin/bash

function export_variables {
    local util_dir=~/qmk_utils
    export PATH=$PATH:$util_dir
    export PATH=$PATH:$util_dir/dfu-programmer
    export PATH=$PATH:$util_dir/dfu-util-0.9-win64
    export PATH=$PATH:$util_dir/flip/bin
    export PATH=$PATH:$util_dir/avr8-gnu-toolchain/bin
    export PATH=$PATH:$util_dir/gcc-arm-none-eabi/bin
    export PATH=$PATH:/mingw64/bin
}

export_variables




