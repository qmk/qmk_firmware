#!/bin/bash

function install_utils {
    rm -f -r "$download_dir"
    mkdir "$download_dir"

    pushd "$download_dir"

    echo "Downloading the QMK driver installer"
    wget -qO- https://api.github.com/repos/qmk/qmk_driver_installer/releases | grep browser_download_url | head -n 1 | cut -d '"' -f 4 | wget -i -

    rm -f *.zip

    popd > /dev/null
}

function install_drivers {
    pushd "$download_dir"
    cp -f "$dir/drivers.txt" .
    echo
    cmd.exe //c "qmk_driver_installer.exe $1 $2 drivers.txt"
    popd > /dev/null
}

pushd "$dir"

if [ ! -d "$download_dir" ]; then
    install_utils
else
    while true; do
        echo
        echo "The utils seem to already be downloaded."
        read -p "Do you want to re-download them and update to the newest version (Y/N) " res
        case $res in
            [Yy]* ) install_utils; break;;
            [Nn]* ) break;;
            * ) echo "Invalid answer";;
        esac
    done
fi

while true; do
    echo
    echo "Which USB drivers do you want to install?"
    echo "(A)ll - All supported drivers will be installed"
    echo "(C)onnected - Only drivers for connected keyboards (in bootloader/flashing mode)"
    echo "              will be installed"
    echo "(F)orce - Like all, but will also override existing drivers for connected"
    echo "           keyboards"
    echo "(N)one - No drivers will be installed,"
    echo "         flashing your keyboard will most likely not work"
    read -p "(a/c/f/N)? " res
    case $res in
        [AaYy]* ) install_drivers --all; break;;
        [Cc]* ) install_drivers; break;;
        [Ff]* ) install_drivers --all --force; break;;
        [Nn]* | "" ) break;;
        * ) echo "Invalid answer";;
    esac
done


popd > /dev/null
