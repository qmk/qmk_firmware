#!/bin/bash

if [ $# -gt 2 ]; then
    echo "Usage: $0 [KEYBOARD [KEYMAP]]"
    exit 1
elif [ ! "$(command -v docker)" ]; then
    echo "Error: docker not found"
    echo "See https://docs.docker.com/install/#supported-platforms for installation instructions"
    exit 2
fi

path=$(pwd -W 2>/dev/null) || path=$PWD  # Use Windows path if on Windows

docker run --rm \
    -e keyboard=${1-$(read -rp "keyboard=" kb; echo $kb)} \
    -e keymap=${2-$(read -rp "keymap=" km; echo $km)} \
    -v $path:/qmk:rw \
    edasque/qmk_firmware
