#!/usr/bin/env bash

_qmk_install() {
    echo "Installing dependencies"

    . /etc/os-release
    if [ "$VERSION_ID" == "39" ]; then
        sudo dnf $SKIP_PROMPT copr enable erovia/dfu-programmer
    fi

    # TODO: Check whether devel/headers packages are really needed
    sudo dnf $SKIP_PROMPT install \
        clang diffutils git gcc glibc-headers kernel-devel kernel-headers \
        make unzip wget zip python3 avr-binutils avr-gcc avr-gcc-c++ avr-libc \
        arm-none-eabi-binutils-cs arm-none-eabi-gcc-cs arm-none-eabi-gcc-cs-c++ \
        arm-none-eabi-newlib avrdude dfu-programmer dfu-util hidapi

    # Handle discrepancies between different Fedora versions
    sudo dnf $SKIP_PROMPT install libusb-devel \
        || sudo dnf $SKIP_PROMPT install libusb1-devel libusb-compat-0.1-devel \
        || sudo dnf $SKIP_PROMPT install libusb0-devel

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
