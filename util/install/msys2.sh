#!/usr/bin/env bash

_qmk_install_prepare() {
    pacman -Syu $MSYS2_CONFIRM
}

_qmk_install() {
    echo "Installing dependencies"

    pacman --needed --noconfirm --disable-download-timeout -S pactoys
    pacboy sync --needed --noconfirm --disable-download-timeout \
        base-devel: toolchain:x clang:x python-qmk:x hidapi:x \
        avr-binutils:x avr-gcc:x avr-libc:x \
        arm-none-eabi-binutils:x arm-none-eabi-gcc:x arm-none-eabi-newlib:x \
        avrdude:x bootloadhid:x dfu-programmer:x dfu-util:x hid-bootloader-cli:x mdloader:x teensy-loader-cli:x wb32-dfu-updater:x

    _qmk_install_drivers
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
