#!/bin/sh
# Script to make a new keymap for a keyboard of your choosing
# This script automates the copying of the default keymap into
# your own keymap

KB_PATH=$1
USERNAME=$2

if [ -z "$KB_PATH" ]; then
    printf "Usage:   %s <keyboard_path> <username>\n" "$0"
    printf "Example: %s 1upkeyboards/1up60hse yourname\n" "$0"
    exit 1
fi

if [ -z "$USERNAME" ]; then
    printf "Usage:   %s <keyboard_path> <username>\n" "$0"
    printf "Example: %s 1upkeyboards/1up60hse yourname\n" "$0"
    exit 1
fi

cd ..

if [ ! -d "keyboards/$KB_PATH" ]; then
	printf "Error! keyboards/%s does not exist!\n" "$KB_PATH"
	exit 1
fi

if [ -d "keyboards/$KB_PATH/keymaps/$USERNAME" ]; then
	printf "Error! keyboards/%s/%s already exists!\n" "$KB_PATH" "$USERNAME"
	exit 1
fi

# Recursively copy the chosen keyboard's default keymap
cp -r keyboards/"$KB_PATH"/keymaps/default keyboards/"$KB_PATH"/keymaps/"$USERNAME"

printf "keymap directory created at: qmk_firmware/keymaps/%s\n\n" "$KB_PATH"

printf "Compile a firmware file with your new keymap by typing: \n"
printf "   make %s:%s\n" "$KB_PATH" "$USERNAME"
printf "from the qmk_firmware directory\n"