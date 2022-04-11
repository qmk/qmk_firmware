#!/bin/bash

do_init_qmk=false
do_compile=true
do_flash_cli=false

main() {
    . config.sh
    . flash_util.sh
    parse_args $@

    $do_init_qmk && init_qmk
    ! $do_compile && return
    if $do_flash_cli; then
        flash_cli
    else
        compile
        flash_toolbox
    fi
}

init_qmk() {
    cd $repo

    # Set default keyboard
    qmk config user.keyboard=$keyboard_type
    # Set default keymap
    qmk config user.keymap=$keymap

    # Initialize libraries
    qmk setup

    cd - >/dev/null
}

compile() {
    qmk compile
}

flash_cli() {
    qmk flash
}

flash_toolbox() {
    build="$repo/.build/${keyboard}_${pcb}_$keymap.hex"
    cp $build build/out.hex
    out="$(echo "$(pwd)/build/out.hex")"
    echo -e "\n\e[1mOpen file in qmk toolbox:\e[m\n$out"

}

pushd . >/dev/null
cd $(dirname ${BASH_SOURCE[0]})
main $@
popd >/dev/null
