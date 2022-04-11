#!/bin/bash

main() {
    . config.sh

    pre="{\"keyboard\":\"$keyboard_type\",\"keymap\":\"$keymap\",\"layout\":\"$layout\",\"layers\":"
    mid="$(cat $build_layers)"
    post=',"author":"","notes":""}'

    echo -e "$pre\n$mid\n$post" >$build_import
}

pushd . >/dev/null
cd $(dirname ${BASH_SOURCE[0]})
main $@
popd >/dev/null
