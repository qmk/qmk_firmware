#!/bin/bash

_qmk_install() {
    echo "Installing dependencies"

    sudo xbps-install $SKIP_PROMPT \
        gcc git make wget unzip zip \
        python3-pip \
        avr-binutils avr-gcc avr-libc \
        cross-arm-none-eabi-binutils cross-arm-none-eabi-gcc cross-arm-none-eabi-newlib \
        avrdude dfu-programmer dfu-util teensy_loader_cli \
        libusb-compat-devel

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
