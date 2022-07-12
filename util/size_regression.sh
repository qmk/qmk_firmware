#!/bin/bash

# Copyright 2021 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

set -eEuo pipefail

job_count=$(getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)
source_ref="0.11.0"
dest_ref="develop"
ignore_ref="master"
unset skip_zero

export SIZE_REGRESSION_EXECUTING=1

function usage() {
    echo "Usage: $(basename "$0") [-h] [-j <jobs>] [-s <source>] [-d <dest>] [-n] planck/rev6:default"
    echo "    -h           : Shows this usage page."
    echo "    -j <threads> : Change the number of threads to execute with. Defaults to \`$job_count\`."
    echo "    -s <source>  : Use source commit, branch, tag, or sha1 to start the search. Defaults to \`$source_ref\`."
    echo "    -d <dest>    : Use destination commit, branch, tag, or sha1 to end the search. Defaults to \`$dest_ref\`."
    echo "    -i <ignore>  : The branch to ignore refs from. Defaults to \`$ignore_ref\`."
    echo "    -n           : Skips printing changes if the delta is zero."
    exit 1
}

if [[ ${#} -eq 0 ]]; then
    usage
    exit 0
fi

unset cleanup_completed
_internal_cleanup() {
    if [[ -z "${cleanup_completed:-}" ]] ; then
        echo
        echo
        echo 'Your git repository is in an indeterminate state!' >&2
        echo 'Make sure you swap to your intended branch.' >&2
        echo
        unset SIZE_REGRESSION_EXECUTING
    fi
    cleanup_completed=1
}
trap _internal_cleanup EXIT HUP INT

while getopts "hj:s:d:i:n" opt "$@" ; do
    case "$opt" in
        h) usage; exit 0;;
        j) job_count="${OPTARG:-}";;
        s) source_ref="${OPTARG:-}";;
        d) dest_ref="${OPTARG:-}";;
        i) ignore_ref="${OPTARG:-}";;
        n) skip_zero=1;;
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

        git checkout -f $revision >/dev/null 2>&1 || { echo "Failed to check out revision ${revision}" >&2 ; exit 1 ; }
        make -j${job_count} $keyboard_target >/dev/null 2>&1 || true
        file_size=$(arm-none-eabi-size .build/*.elf 2>/dev/null | awk '/elf/ {print $1}' 2>/dev/null || true)

        if [[ "$last_size" == 0 ]] ; then last_size=$file_size ; fi
        if [[ -z "$file_size" ]] ; then file_size=0 ; fi

        if [[ -n "$last_line" ]] ; then
            size_delta=$(( $last_size - $file_size ))
            if { [[ -n "${skip_zero:-}" ]] && [[ $size_delta -ne 0 ]] ; } || [[ -z "${skip_zero:-}" ]] || [[ $file_size -eq 0 ]] ; then
                printf "Size: %8d, delta: %+6d -- %s\n" "$last_size" "$size_delta" "$last_line"
            fi
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
