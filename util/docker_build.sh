#!/bin/bash

IMAGE=edasque/qmk_firmware
IMAGE_DIR=/qmk

# Check preconditions
if [[ $# -gt 2 ]]; then
    echo "Usage: $0 [keyboard [keymap]]" >&2
    echo "       $0 keyboard:keymap" >&2
    exit 1
elif [[ ! $(command -v docker) ]]; then
    echo "Error: docker not found" >&2
    echo "See https://docs.docker.com/install/#supported-platforms for installation instructions" >&2
    exit 2
fi

# Compute arguments
if [[ $# -eq 1 && $1 == *:* ]]; then
    # keyboard:keymap form
    IFS=':' read -ra args <<< "$1"
    keyboard=${args[0]}
    keymap=${args[1]}
else
    # [keyboard [keymap]] form
    keyboard=${1-$(read -rp "keyboard=" kb; echo $kb)}
    keymap=${2-$(read -rp "keymap=" km; echo $km)}
fi
dir=$(pwd -W 2>/dev/null) || dir=$PWD  # Use Windows path if on Windows

# Run container and build firmware
docker run --rm -e keyboard=$keyboard -e keymap=$keymap -v $dir:$IMAGE_DIR:rw $IMAGE
