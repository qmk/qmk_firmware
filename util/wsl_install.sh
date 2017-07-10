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

echo 
echo "Creating a softlink to the utils directory as ~/qmk_utils."
echo "This is needed so that the the make system can find all utils it need."
read -p "Press any key to continue (ctrl-c to abort)"
ln -sfn "$dir" ~/qmk_utils

if grep "^source ~/qmk_utils/activate_wsl.sh$" ~/.bashrc
then
    echo
    echo "The line source ~/qmk_utils/activate_wsl.sh is already added to your /.bashrc"
    echo "Not adding it twice"
else
    while true; do
        echo
        echo "Do you want to add 'source ~/qmk_utils/activate_wsl.sh' to the end of you .bashrc file?"
        echo "Without this make won't find the needed utils, so if you don't want to do it automatically,"
        echo "then you have to do it manually."
        read -p "(Y/N)? " res
        case $res in
            [Yy]* ) echo "source ~/qmk_utils/activate_wsl.sh" >> ~/.bashrc; break;;
            [Nn]* ) break;;
            * ) echo "Invalid answer";;
        esac
    done
fi

while true; do
    echo
    echo "Do you want to add a symlink to the QMK repository in your home directory for convenience?"
    echo "This will create a folder 'qmk_firmware' in your home directory."
    echo "In the future you can use this folder instead of the full path on your windows file system"
    read -p "(Y/N)? " res
    case $res in
        [Yy]* ) ln -sfn "$dir/.." ~/qmk_firmware; break;;
        [Nn]* ) break;;
        * ) echo "Invalid answer";;
    esac
done

echo
echo "******************************************************************************"
echo "Installation completed!"
echo "You need to open a new batch command prompt for all the utils to work properly"
echo "******************************************************************************"

popd > /dev/null
