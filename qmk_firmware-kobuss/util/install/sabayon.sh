#!/bin/bash

_qmk_install() {
    echo "Installing dependencies"

    sudo equo install \
        app-arch/unzip app-arch/zip net-misc/wget dev-vcs/git sys-devel/clang sys-devel/gcc sys-devel/crossdev \
        dev-python/pip \
        dev-embedded/avrdude dev-embedded/dfu-programmer app-mobilephone/dfu-util

    sudo crossdev -s4 --stable --g \<9 --portage --verbose --target avr
    sudo crossdev -s4 --stable --g \<9 --portage --verbose --target arm-none-eabi

    python3 -m pip install --user -r $QMK_FIRMWARE_DIR/requirements.txt
}
