#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
download_dir=~/qmk_utils
avrtools=avr8-gnu-toolchain

echo "Installing dependencies needed for the installation (quazip)"
pacman --needed -S msys/unzip msys/p7zip



source "$dir/win_shared_install.sh"

function install_avr {
    rm -f -r "$avrtools"
    wget "http://www.atmel.com/images/avr8-gnu-toolchain-installer-3.5.4.91-win32.any.x86.exe"
    7z x avr8-gnu-toolchain-installer-3.5.4.91-win32.any.x86.exe
    rm avr8-gnu-toolchain-installer-3.5.4.91-win32.any.x86.exe
}

pushd "$download_dir"


if [ ! -d "$avrtools" ]; then
    while true; do
        echo
        echo "The AVR toolchain is not installed."
        echo "This is needed for building AVR based keboards."
        read -p "Do you want to install it? (Y/N) " res
        case $res in
            [Yy]* ) install_avr; break;;
            [Nn]* ) break;;
            * ) echo "Invalid answer";;
        esac
    done
else
    while true; do
        echo
        echo "The AVR toolchain is already installed"
        read -p "Do you want to reinstall? (Y/N) " res
        case $res in
            [Yy]* ) install_avr; break;;
            [Nn]* ) break;;
            * ) echo "Invalid answer";;
        esac
    done
fi
popd

echo
echo "******************************************************************************"
echo "Installation completed!"
echo "You need to open a new batch command prompt for all the utils to work properly"
echo "******************************************************************************"