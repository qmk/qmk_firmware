#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
download_dir=~/qmk_utils
avrtools=avr8-gnu-toolchain
armtools=gcc-arm-none-eabi
util_dir=$(dirname "$0")

echo "Installing dependencies needed for the installation (quazip)"
pacman --needed --noconfirm --disable-download-timeout -Sy base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-clang git mingw-w64-x86_64-python3-pip unzip

source "$dir/win_shared_install.sh"

function install_avr {
    rm -f -r "$avrtools"
    wget "https://blog.zakkemble.net/download/avr-gcc-8.3.0-x86-mingw.zip"
    echo "Extracting AVR toolchain..."
    unzip -q -d . avr-gcc-8.3.0-x86-mingw.zip
    mv avr-gcc-8.3.0-x86-mingw avr8-gnu-toolchain
    rm avr8-gnu-toolchain/bin/make.exe
    rm avr-gcc-8.3.0-x86-mingw.zip

    # FIXME: As of 2020-05-19, the MSYS2 avrdude cannot flash USBaspLoader devices, for some reason
    # (warning: cannot set sck period)
    # However, the avr-gcc toolchain above contains an avrdude which can, so let's just not install this for now
    #pacman --needed --disable-download-timeout -S mingw-w64-x86_64-avrdude
}

function install_arm {
    rm -f -r "$armtools"
    wget -O gcc-arm-none-eabi-8-2019-q3-update-win32.zip "https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2019q3/RC1.1/gcc-arm-none-eabi-8-2019-q3-update-win32.zip"
    echo "Extracting ARM toolchain..."
    unzip -q -d gcc-arm-none-eabi gcc-arm-none-eabi-8-2019-q3-update-win32.zip
    rm gcc-arm-none-eabi-8-2019-q3-update-win32.zip
}

pushd "$download_dir"

if [ ! -d "$avrtools" ]; then
    echo
    echo "The AVR toolchain is not installed."
    echo "This is needed for building AVR based keyboards."
    install_avr
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
