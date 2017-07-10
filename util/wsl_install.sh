#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
pushd "$dir";

if [[ $dir != /mnt/* ]];
then
    echo
    echo "You need to clone the qmk_firmware repository outside the linux filesystem."
    echo "Otherwise the windows executables can't be run."
    exit 1
fi


while true; do
    echo
    echo "Do you want to install all toolchain dependencies needed for compiling QMK?"
    echo "This will run install_dependencies.sh, which calls apt-get upgrade."
    echo "If you don't want that, you can install the dependencies manually."
    read -p "(Y/N) " res
    case $res in
        [Yy]* ) sudo ./install_dependencies.sh; break;;
        [Nn]* ) break;;
        * ) echo "Invalid answer";;
    esac
done

echo "Installing dependencies needed for the installation (unzip, wget)"
echo "This will ask for the sudo password"
sudo apt-get install unzip wget
source "$dir/win_shared_install.sh"

popd > /dev/null
