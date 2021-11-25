#!/bin/bash

if [[ -z $1 ]] ; then
    echo "Usage: $0 planck/rev6:default"
    exit 1
fi

keyboard_target=$1

function build_executor() {
    git rev-list --oneline --no-merges 0.11.0...upstream/develop ^upstream/master | while IFS= read -r line ; do
        revision=$(echo $line | cut -d' ' -f1)

        make distclean >/dev/null 2>&1
        git checkout $revision >/dev/null 2>&1
        make -j $keyboard_target >/dev/null 2>&1
        file_size=$(arm-none-eabi-size .build/*.elf | awk '/elf/ {print $1}')

        printf "%8d -- %s\n" "$file_size" "$line"
    done
}

# The actual execution of all the builds needs to be the last command in the entire script
# - During builds, this script file will disappear, so we need the entire script to be
#   loaded into the script interpreter at the time of execution. Do not refactor.
build_executor