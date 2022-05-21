#!/usr/bin/env bash

_qmk_install_prepare() {
    echo "Before you continue, please ensure that your user is added to sudoers and that sboinstall is configured."
    read -p "Proceed? [y/N] " res

    case $res in
        [Yy]*)
            ;;
        *)
            return 1;;
    esac
}

_qmk_install() {
    echo "Installing dependencies"

    sudo sboinstall \
        avr-binutils avr-gcc avr-libc \
        arm-binutils arm-gcc newlib \
        python3 \
        avrdude dfu-programmer dfu-util teensy_loader_cli

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
