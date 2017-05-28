#!/bin/bash

download_dir = wsl_downloaded

function install_utils {
    rm -f -r $download_dir
    mkdir $download_dir

    pushd $download_dir

    echo "Installing dfu-programmer"
    wget 'http://downloads.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip'
    7z x -odfu-programmer dfu-programmer-win-0.7.2.zip

    echo "Installing dfu-util"
    wget 'http://dfu-util.sourceforge.net/releases/dfu-util-0.9-win64.zip'
    7z x dfu-util-0.9-win64.zip

    echo "Installing teensy_loader_cli"
    wget 'https://www.pjrc.com/teensy/teensy_loader_cli_windows.zip'
    7z x teensy_loader_cli_windows.zip

    echo "Installing Atmel Flip"
    wget 'http://www.atmel.com/images/Flip%20Installer%20-%203.4.7.112.exe'
    7z x -oFlip Flip\ Installer\ -\ 3.4.7.112.exe

    echo "Downloading the QMK driver installer"
    wget -qO- https://api.github.com/repos/qmk/qmk_driver_installer/releases | grep browser_download_url | head -n 1 | cut -d '"' -f 4 | wget -i -

    rm -f *.zip
    rm Flip\ Installer\ -\ 3.4.7.112.exe

    popd > /dev/null
}

function make_environment {
}

echo "Installing dependencies (p7zip-full, wget)"
echo "This will ask for the sudo password"
sudo apt-get install p7zip-full wget

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)

if [[ $dir != /mnt/* ]];
then
    echo
    echo "You need to clone the qmk_firmware repository outside the linux filesystem."
    echo "Otherwise the windows executables can't be run."
    exit 1
fi

pushd "$dir"

#install_utils

popd > /dev/null

