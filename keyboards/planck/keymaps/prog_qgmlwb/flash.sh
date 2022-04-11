#!/bin/bash

do_init_qmk=false
do_compile=true
flash_cli=false

keyboard="planck/rev5"
keymap="prog_qgmlwb"
bootloader="dfu"
out="build/out.hex"

main() {
    repo="$(
        cd ../../../..
        pwd
    )"

    $do_init_qmk && init_qmk
    compile
    flash
}

init_qmk() {
    cd $repo

    # Set default keyboard
    qmk config user.keyboard=$keyboard
    # Set default keymap
    qmk config user.keymap=$keymap

    # Initialize libraries
    qmk setup

    cd - /dev/null
}

compile() {
    qmk compile
}

flash() {
    if $flash_cli; then
        sudo make $keyboard:$keymap:$bootloader
    else
        keyboard_build="$(tr '/' '_' <<<"$keyboard")"
        build="$repo/.build/${keyboard_build}_$keymap.hex"
        cp $build build/out.hex
        out="$(echo "$(pwd)/build/out.hex")"
        echo -e "\n\e[1mOpen file in qmk toolbox:\e[m\n$out"
    fi
}

pushd . >/dev/null
cd $(dirname ${BASH_SOURCE[0]})
main $@
popd >/dev/null
