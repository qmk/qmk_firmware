#!/bin/bash

USAGE="Usage: $0 [keyboard[:keymap[:target]]]"

# Check preconditions
if [[ $* =~ "--help" ]]; then
    echo "$USAGE"
    exit 0
elif [[ $# -gt 1 ]]; then
    echo "$USAGE" >&2
    exit 1
elif [[ ! $(command -v docker) ]]; then
    echo "Error: docker not found" >&2
    echo "See https://docs.docker.com/install/#supported-platforms for installation instructions" >&2
    exit 2
fi

# Determine arguments
if [[ $# -eq 0 ]]; then
    read -rp "keyboard=" keyboard
    [[ -n $keyboard ]] && read -rp "keymap=" keymap
    [[ -n $keymap   ]] && read -rp "target=" target
else
    IFS=':' read -ra args <<< "$1"
    if [[ ${#args[@]} -gt 3 ]]; then
        echo "$USAGE" >&2
        exit 1
    fi
    keyboard=${args[0]}
    keymap=${args[1]}
    target=${args[2]}
fi
dir=$(pwd -W 2>/dev/null) || dir=$PWD  # Use Windows path if on Windows

# Run container and build firmware
docker run --rm -v "$dir":/qmk_firmware qmkfm/qmk_firmware \
    make "$keyboard${keymap:+:$keymap}${target:+:$target}"
