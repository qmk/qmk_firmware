#!/usr/bin/env bash

_qmk_install_prepare() {
    echo "Checking Homebrew installation"

    if ! brew --version >/dev/null 2>&1; then
        echo "Error! Homebrew is broken or not installed."
        echo "Please run \`brew doctor\` or follow the installation instructions at https://brew.sh/, then re-run this script."
        return 1
    fi

    # Conflicts with arm-none-eabi toolchain from osx-cross
    brew uninstall --ignore-dependencies --cask gcc-arm-embedded >/dev/null 2>&1
    brew uninstall --ignore-dependencies homebrew/core/arm-none-eabi-gcc >/dev/null 2>&1
    brew uninstall --ignore-dependencies homebrew/core/arm-none-eabi-binutils >/dev/null 2>&1
    brew uninstall --ignore-dependencies osx-cross/arm/arm-gcc-bin@8 >/dev/null 2>&1

    brew update && brew upgrade --formulae
}

_qmk_install() {
    echo "Installing dependencies"

    # All macOS & Python dependencies are managed in the Homebrew package:
    #   https://github.com/qmk/homebrew-qmk
    brew install qmk/qmk/qmk

    # Keg-only, so need to be manually linked
    brew link --force avr-gcc@8
    brew link --force arm-none-eabi-binutils
    brew link --force arm-none-eabi-gcc@8
}
