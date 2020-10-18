#!/bin/bash

_qmk_install_prepare() {
    sudo eopkg ur
}

_qmk_install() {
    echo "Installing dependencies"

    sudo eopkg it -c \
        system.devel git wget zip unzip \
        python3 \
        avr-binutils avr-gcc avr-libc \
        arm-none-eabi-binutils arm-none-eabi-gcc arm-none-eabi-newlib \
        avrdude dfu-programmer dfu-util

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
