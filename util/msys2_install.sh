#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
download_dir=~/qmk_utils
avrtools=avr8-gnu-toolchain
armtools=gcc-arm-none-eabi
installflip=false
util_dir=$(dirname "$0")

echo "Installing dependencies needed for the installation (quazip)"
pacman --needed -Sy base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-clang msys/git msys/p7zip msys/python3 msys/unzip

source "$dir/win_shared_install.sh"

function install_avr {
    rm -f -r "$avrtools"
    wget "https://blog.zakkemble.net/download/avr-gcc-8.3.0-x86-mingw.zip"
    echo "Extracting AVR toolchain..."
	unzip -q -d . avr-gcc-8.3.0-x86-mingw.zip
    mv avr-gcc-8.3.0-x86-mingw avr8-gnu-toolchain
    rm avr-gcc-8.3.0-x86-mingw.zip
    pacman --needed -S mingw-w64-x86_64-avrdude
}

function install_arm {
    rm -f -r "$armtools"
    wget -O gcc-arm-8.3-2019.03-i686-mingw32-arm-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu-a/8.3-2019.03/binrel/gcc-arm-8.3-2019.03-i686-mingw32-arm-eabi.tar.xz?revision=ee19688c-d795-49c3-9937-f9b2e5a49b6b&la=en"
    echo "Extracting ARM toolchain..."
    tar -xf gcc-arm-8.3-2019.03-i686-mingw32-arm-eabi.tar.xz -C .
    mv gcc-arm-8.3-2019.03-i686-mingw32-arm-eabi gcc-arm-none-eabi
    rm gcc-arm-8.3-2019.03-i686-mingw32-arm-eabi.tar.xz
}

function extract_flip {
    rm -f -r flip
    7z -oflip x FlipInstaller.exe
}

pushd "$download_dir"

if [ -f "FlipInstaller.exe" ]; then
    echo
    echo "Extracting flip"
    extract_flip
fi

if [ ! -d "$avrtools" ]; then
    echo
    echo "The AVR toolchain is not installed."
    echo "This is needed for building AVR based keboards."
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

pip3 install -r ${util_dir}/../requirements.txt

cp -f "$dir/activate_msys2.sh" "$download_dir/"

if grep "^source ~/qmk_utils/activate_msys2.sh$" ~/.bashrc
then
    echo
    echo "The line source ~/qmk_utils/activate_msys2.sh is already added to your /.bashrc"
    echo "Not adding it twice!"
else
        echo
        echo "Adding 'source ~/qmk_utils/activate_msys2.sh' to the end of your"
        echo ".bashrc file? Without this make won't find the needed utils."
        echo "source ~/qmk_utils/activate_msys2.sh" >> ~/.bashrc;
fi

echo
echo "******************************************************************************"
echo "Installation completed!"
echo "Please close this Window and restart MSYS2 MinGW"
echo "******************************************************************************"
