#!/bin/bash

util_dir=$(dirname "$0")

echo "Installing dependencies needed for the installation"
pacman --needed --noconfirm --disable-download-timeout -Sy \
    base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-clang git unzip \
    mingw-w64-x86_64-python-pip \
    mingw-w64-x86_64-avr-binutils mingw-w64-x86_64-avr-gcc mingw-w64-x86_64-avr-libc \
    mingw-w64-x86_64-arm-none-eabi-binutils mingw-w64-x86_64-arm-none-eabi-gcc mingw-w64-x86_64-arm-none-eabi-newlib \
    mingw-w64-x86_64-avrdude mingw-w64-x86_64-bootloadhid mingw-w64-x86_64-dfu-programmer mingw-w64-x86_64-dfu-util mingw-w64-x86_64-teensy-loader-cli

echo "Installing drivers"
tmpdir=$(mktemp -d)
cp "${util_dir}/drivers.txt" $tmpdir
pushd $tmpdir > /dev/null
wget "https://github.com/qmk/qmk_driver_installer/releases/download/v1.01/qmk_driver_installer.exe"
cmd.exe //c "qmk_driver_installer.exe --all --force drivers.txt"
popd > /dev/null
rm -r $tmpdir

pip3 install -r "${util_dir}/../requirements.txt"
