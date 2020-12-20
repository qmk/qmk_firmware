#!/bin/bash

_qmk_install_prepare() {
    case $(grep ID /etc/os-release) in
        *15.1*)
            REPO_RELEASE=Leap_15.1;;
        *15.2*)
            REPO_RELEASE=Leap_15.2;;
        *)
            #REPO_RELEASE=Tumbleweed;;
            echo "ERROR: Tumbleweed is currently not supported."
            exit 1
    esac

    sudo zypper addrepo https://download.opensuse.org/repositories/devel:gcc/openSUSE_$REPO_RELEASE/devel:gcc.repo
    sudo zypper addrepo https://download.opensuse.org/repositories/hardware/openSUSE_$REPO_RELEASE/hardware.repo
    sudo zypper --gpg-auto-import-keys refresh
}

_qmk_install() {
    echo "Installing dependencies"

    sudo zypper install -y \
        make clang gcc unzip wget zip \
        python3-pip \
        cross-avr-binutils cross-avr-gcc8 avr-libc \
        cross-arm-binutils cross-arm-none-gcc8 cross-arm-none-newlib-devel \
        avrdude dfu-programmer dfu-util

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
