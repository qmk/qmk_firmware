#!/bin/bash

path=$(pwd -W 2>/dev/null) || path=$PWD  # Use Windows path if on Windows

docker run --rm \
    -e keyboard=${1-$(read -p "keyboard=" kb; echo $kb)} \
    -e keymap=${2-$(read -p "keymap=" km; echo $km)} \
    -v $path:/qmk:rw \
    edasque/qmk_firmware
