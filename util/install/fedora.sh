#!/usr/bin/env bash

_qmk_install() {
    echo "Installing dependencies"

    # TODO: Check whether devel/headers packages are really needed
    sudo dnf $SKIP_PROMPT install \
        clang diffutils git gcc glibc-headers kernel-devel kernel-headers \
        make unzip wget zip python3 avr-binutils avr-gcc avr-libc \
        arm-none-eabi-binutils-cs arm-none-eabi-gcc-cs arm-none-eabi-newlib \
        avrdude dfu-programmer dfu-util hidapi libusb-devel

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
