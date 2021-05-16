#!/bin/bash

_qmk_install_prepare() {
    echo "Checking Homebrew installation"

    if ! brew --version >/dev/null 2>&1; then
        echo "Error! Homebrew is broken or not installed."
        echo "Please run \`brew doctor\` or follow the installation instructions at https://brew.sh/, then re-run this script."
        return 1
    fi

    echo "Fetching the newest version of homebrew"

    brew update 2>&1>/dev/null

    package_list=$(brew upgrade --dry-run)
    bold=$(tput bold)
    normal=$(tput sgr0)
    if ! [ -z "$package_list" ]; then
        echo "Brew will upgrade the following packages:"
        echo "$package_list"
        echo "Type ${bold}y/Y${normal}(recommended) to ${bold}upgrade${normal} and any other key to continue without upgrading"
        read consent
        if ! [ -z "$consent" ] && ([ $consent == 'y' ] || [ $consent == 'Y' ]); then
            brew upgrade --ignore-pinned
        else
            echo "Continuing installation without updating dependencies"
        fi
    else
        echo "No packages needs upgrading. Continuing installation"
    fi
}

_qmk_install() {
    echo "Installing dependencies"

    # All macOS dependencies are managed in the Homebrew package:
    # https://github.com/qmk/homebrew-qmk
    brew install qmk/qmk/qmk

    brew link --force avr-gcc@8
    brew link --force arm-gcc-bin@8

    python3 -m pip install -r $QMK_FIRMWARE_DIR/requirements.txt
}
