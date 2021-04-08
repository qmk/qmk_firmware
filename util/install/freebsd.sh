#!/bin/bash

_qmk_install_prepare() {
    sudo pkg update
}

_qmk_install() {
    echo "Installing dependencies"

    sudo pkg install -y \
        git wget gmake gcc zip unzip diffutils \
        python3 \
        avr-binutils avr-gcc avr-libc \
        arm-none-eabi-binutils arm-none-eabi-gcc arm-none-eabi-newlib \
        avrdude dfu-programmer dfu-util

    sudo python3 -m pip install -r $QMK_FIRMWARE_DIR/requirements.txt
}
