#!/bin/bash

_qmk_install_prepare() {
    pacman -Syu
}

_qmk_install() {
    echo "Installing dependencies"

    pacman --needed --noconfirm --disable-download-timeout -S pactoys-git
    pacboy sync --needed --noconfirm --disable-download-timeout \
        base-devel: toolchain:x clang:x git: unzip: \
        python3-pip:x \
        avr-binutils:x avr-gcc:x avr-libc:x \
        arm-none-eabi-binutils:x arm-none-eabi-gcc:x arm-none-eabi-newlib:x \
        avrdude:x bootloadhid:x dfu-programmer:x dfu-util:x teensy-loader-cli:x

    _qmk_install_drivers

    python3 -m pip install -r "$QMK_FIRMWARE_DIR/requirements.txt"
}

_qmk_install_drivers() {
    echo "Installing drivers"

    tmpdir=$(mktemp -d)
    cp "$QMK_FIRMWARE_UTIL_DIR/drivers.txt" $tmpdir
    pushd $tmpdir > /dev/null

    wget "https://github.com/qmk/qmk_driver_installer/releases/download/v1.01/qmk_driver_installer.exe"

    cmd.exe //c "qmk_driver_installer.exe --all --force drivers.txt"

    popd > /dev/null
    rm -r $tmpdir
}
