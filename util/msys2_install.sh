#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
download_dir=~/qmk_utils
util_dir=$(dirname "$0")

echo "Installing dependencies needed for the installation"
pacman --needed --noconfirm --disable-download-timeout -Sy \
    base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-clang git unzip \
    mingw-w64-x86_64-python-pip \
    mingw-w64-x86_64-avr-binutils mingw-w64-x86_64-avr-gcc mingw-w64-x86_64-avr-libc \
    mingw-w64-x86_64-arm-none-eabi-binutils mingw-w64-x86_64-arm-none-eabi-gcc mingw-w64-x86_64-arm-none-eabi-newlib \
    mingw-w64-x86_64-avrdude mingw-w64-x86_64-bootloadhid mingw-w64-x86_64-dfu-programmer mingw-w64-x86_64-dfu-util mingw-w64-x86_64-teensy-loader-cli

source "$dir/win_shared_install.sh"

pip3 install -r "${util_dir}/../requirements.txt"

cp -f "$dir/activate_msys2.sh" "$download_dir/"

if grep "^source ~/qmk_utils/activate_msys2.sh$" ~/.bashrc
then
    echo
    echo "The line source ~/qmk_utils/activate_msys2.sh is already added to your /.bashrc"
    echo "Not adding it twice!"
else
        echo
        echo "Adding 'source ~/qmk_utils/activate_msys2.sh' to the end of your"
        echo ".bashrc file. Without this make won't find the needed utils."
        echo "source ~/qmk_utils/activate_msys2.sh" >> ~/.bashrc;
fi

echo
echo "******************************************************************************"
echo "Installation completed!"
echo "Please close this Window and restart MSYS2 MinGW"
echo "******************************************************************************"
