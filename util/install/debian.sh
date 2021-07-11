#!/usr/bin/env bash

DEBIAN_FRONTEND=noninteractive
DEBCONF_NONINTERACTIVE_SEEN=true
export DEBIAN_FRONTEND DEBCONF_NONINTERACTIVE_SEEN

_qmk_install_prepare() {
    sudo apt-get update
}

_qmk_install() {
    echo "Installing dependencies"

    sudo apt-get -yq install \
        build-essential clang-format diffutils gcc git unzip wget zip \
<<<<<<< HEAD
        python3-pip binutils-avr gcc-avr avr-libc binutils-arm-none-eabi \
        gcc-arm-none-eabi libnewlib-arm-none-eabi avrdude dfu-programmer \
        dfu-util teensy-loader-cli libhidapi-hidraw0 libusb-dev
=======
        python3-pip \
        binutils-avr gcc-avr avr-libc \
        binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi \
        avrdude dfu-programmer dfu-util teensy-loader-cli libusb-dev
>>>>>>> 382a8faad674a6b9a7b8966c4452eabafbf84eba

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
