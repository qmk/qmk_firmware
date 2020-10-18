#!/bin/bash

_qmk_install_prepare() {
    case $(grep ID /etc/os-release) in
        *15.1*)
            REPO_RELEASE=Leap_15.1;;
        *15.2*)
            REPO_RELEASE=Leap_15.2;;
        *)
            REPO_RELEASE=Tumbleweed;;
    esac

    # ARM support is currently very lacking - no arm-none-eabi-size, and newlib causes linking errors (on Tumbleweed at least) when USE_FPU = yes! >:(
    #sudo zypper ar https://download.opensuse.org/repositories/devel:gcc/openSUSE_$REPO_RELEASE/devel:gcc.repo
    sudo zypper ar https://download.opensuse.org/repositories/CrossToolchain:avr/openSUSE_$REPO_RELEASE/CrossToolchain:avr.repo
    sudo zypper ar https://download.opensuse.org/repositories/hardware/openSUSE_$REPO_RELEASE/hardware.repo
    sudo zypper refresh
}

_qmk_install() {
    echo "Installing dependencies"

    sudo zypper install \
        make clang gcc unzip wget zip \
        python3-pip \
        cross-avr-binutils cross-avr-gcc8 avr-libc \
        avrdude dfu-programmer dfu-util
        #cross-arm-binutils cross-arm-none-gcc8 cross-arm-none-newlib-devel

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
