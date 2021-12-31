#!/usr/bin/env bash

DEBIAN_FRONTEND=noninteractive
DEBCONF_NONINTERACTIVE_SEEN=true
export DEBIAN_FRONTEND DEBCONF_NONINTERACTIVE_SEEN

_qmk_install_prepare() {
    sudo apt-get update $SKIP_PROMPT
}

_qmk_install() {
    echo "Installing dependencies"

    sudo apt-get --quiet --yes install \
        build-essential clang-format diffutils gcc git unzip wget zip \
        python3-pip binutils-avr gcc-avr avr-libc binutils-arm-none-eabi \
        gcc-arm-none-eabi libnewlib-arm-none-eabi avrdude dfu-programmer \
        dfu-util teensy-loader-cli libhidapi-hidraw0 libusb-dev

    # RISC-V toolchains with picolibc support are only available for distributions based on Debian 11+.
    if sudo apt-get install --simulate --quiet --yes picolibc-riscv64-unknown-elf gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf > /dev/null 2>&1; then
        sudo apt-get --quiet --yes install picolibc-riscv64-unknown-elf \
            gcc-riscv64-unknown-elf \
            binutils-riscv64-unknown-elf
    fi

    python3 -m pip install --user -r "$QMK_FIRMWARE_DIR"/requirements.txt
}
