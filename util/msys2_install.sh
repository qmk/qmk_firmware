#!/bin/bash

dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)

echo "Installing dependencies needed for the installation (quazip)"
pacman --needed -S msys/unzip

export download_dir=~/qmk_utils

source "$dir/win_shared_install.sh"

echo
echo "******************************************************************************"
echo "Installation completed!"
echo "You need to open a new batch command prompt for all the utils to work properly"
echo "******************************************************************************"