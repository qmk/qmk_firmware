#!/bin/bash

set -eEuo pipefail

source_ref="0.11.0"
dest_ref="develop"
ignore_ref="master"

function usage() {
    echo "Usage: $(basename "$0") [-s <source>] [-d <dest>] [-u] planck/rev6:default"
    echo "    -s <source> : use source commit, branch, tag, or sha1 to start the search"
    echo "                  defaults to \`$source_ref\`."
    echo "    -d <dest>   : use destination commit, branch, tag, or sha1 to end the search"
    echo "                  defaults to \`$dest_ref\`."
    echo "    -i <ignore> : the branch to ignore refs from"
    echo "                  defaults to \`$ignore_ref\`."
    exit 1
}

if [[ ${#} -eq 0 ]]; then
   usage
fi

while getopts "s:d:i:" opt "$@" ; do
    case "$opt" in
        s) source_ref="${OPTARG:-}";;
        d) dest_ref="${OPTARG:-}";;
        i) ignore_ref="${OPTARG:-}";;
        \?) usage >&2; exit 1;;
    esac
done

# Work out the target board
shift $((OPTIND-1))
keyboard_target=$1

last_size=0
last_line=""
function build_executor() {
    git rev-list --oneline --no-merges ${source_ref}...${dest_ref} ^${ignore_ref} | while IFS= read -r line ; do
        revision=$(echo $line | cut -d' ' -f1)

        make distclean >/dev/null 2>&1
        git checkout $revision >/dev/null 2>&1 || { echo "Failed to check out revision ${revision}" >&2 ; exit 1 ; }
        make -j $keyboard_target >/dev/null 2>&1 || true
        file_size=$(arm-none-eabi-size .build/*.elf 2>&1 | awk '/elf/ {print $1}' 2>&1 || true)

        if [[ "$last_size" == 0 ]] ; then last_size=$file_size ; fi
        if [[ -z "$file_size" ]] ; then file_size=0 ; fi

        if [[ -n "$last_line" ]] ; then
            size_delta=$(( $last_size - $file_size ))
            printf "Size: %8d, delta: %+6d -- %s\n" "$last_size" "$size_delta" "$last_line"
        fi

        last_size=$file_size
        last_line=$line
    done

    if [ -n "$last_line" ] ; then
        size_delta=0
        printf "Size: %8d, delta: %+6d -- %s\n" "$last_size" "$size_delta" "$last_line"
    fi
}

# The actual execution of all the builds needs to be the last command in the entire script
# - During builds, this script file will disappear, so we need the entire script to be
#   loaded into the script interpreter at the time of execution. Do not refactor.
build_executor
