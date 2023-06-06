#!/usr/bin/env bash

# For those distros that do not package bootloadHID
_qmk_install_bootloadhid() {
    if ! command -v bootloadHID > /dev/null; then
        wget https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz -O - | tar -xz -C /tmp
        pushd /tmp/bootloadHID.2012-12-08/commandline/ > /dev/null
        if make; then
            sudo cp bootloadHID /usr/local/bin
        fi
        popd > /dev/null
    fi
}

# No distros package sonixflasher yet
_qmk_install_sonixflasher() {
    if ! command -v sonixflasher > /dev/null; then
        wget https://github.com/SonixQMK/SonixFlasherC/archive/refs/tags/1.1.0.tar.gz -O - | tar -xz -C /tmp
        pushd /tmp/SonixFlasherC-1.1.0/ > /dev/null
        if make; then
            sudo cp sonixflasher /usr/local/bin
        fi
        popd > /dev/null
    fi
}