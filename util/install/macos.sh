#!/usr/bin/env bash

_qmk_install_prepare() {
    echo "Checking Homebrew installation"

    if ! brew --version >/dev/null 2>&1; then
        echo "Error! Homebrew is broken or not installed."
        echo "Please run \`brew doctor\` or follow the installation instructions at https://brew.sh/, then re-run this script."
        return 1
    fi

    brew update && brew upgrade --formulae --ignore-pinned
}

_qmk_install() {
    echo "Installing dependencies"

    # All macOS dependencies are managed in the Homebrew package:
    # https://github.com/qmk/homebrew-qmk
    brew install qmk/qmk/qmk

    # Conflicts with new toolchain formulae
    brew uninstall --ignore-dependencies arm-gcc-bin@8 >/dev/null 2>&1

    # Keg-only, so need to be manually linked
    brew link --force avr-gcc@8
    brew link --force arm-none-eabi-binutils
    brew link --force arm-none-eabi-gcc@8

    python3 -m pip install -r $QMK_FIRMWARE_DIR/requirements.txt
}
