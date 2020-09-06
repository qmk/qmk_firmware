#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
download_dir=~/qmk_utils
armtools=gcc-arm-none-eabi
util_dir=$(dirname "$0")

echo "Installing dependencies needed for the installation"
pacman --needed --noconfirm --disable-download-timeout -Sy base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-clang git mingw-w64-x86_64-python3-pip unzip

source "$dir/win_shared_install.sh"

function install_avr {
    pacman --needed --noconfirm --disable-download-timeout -S \
        mingw-w64-x86_64-avr-binutils mingw-w64-x86_64-avr-gcc mingw-w64-x86_64-avr-libc \
        mingw-w64-x86_64-avrdude mingw-w64-x86_64-bootloadhid mingw-w64-x86_64-dfu-programmer mingw-w64-x86_64-teensy-loader-cli
}

function install_arm {
    rm -f -r "$armtools"
    wget -O gcc-arm-none-eabi-8-2019-q3-update-win32.zip "https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2019q3/RC1.1/gcc-arm-none-eabi-8-2019-q3-update-win32.zip"
    echo "Extracting ARM toolchain..."
    unzip -q -d gcc-arm-none-eabi gcc-arm-none-eabi-8-2019-q3-update-win32.zip
    rm gcc-arm-none-eabi-8-2019-q3-update-win32.zip

    pacman --needed --noconfirm --disable-download-timeout -S mingw-w64-x86_64-dfu-util
}

pushd "$download_dir"

install_avr

if [ ! -d "$armtools" ]; then
    echo
    echo "The ARM toolchain is not installed."
    echo "This is needed for building ARM based keyboards."
    install_arm
else
    while true; do
        echo
        echo "The ARM toolchain is already installed"
        read -p "Do you want to reinstall? (Y/N) " res
        case $res in
            [Yy]* ) install_arm; break;;
            [Nn]* ) break;;
            * ) echo "Invalid answer";;
        esac
    done
fi
popd

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
