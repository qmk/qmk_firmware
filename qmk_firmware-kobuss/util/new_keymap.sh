#!/bin/sh
# Script to make a new keymap for a keyboard of your choosing
# This script automates the copying of the default keymap into
# your own keymap

KB_PATH=$(echo "$1" | tr 'A-Z' 'a-z')
USERNAME=$(echo "$2" | tr 'A-Z' 'a-z')

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

cd "$(dirname "$0")/.."

if [ ! -d "keyboards/$KB_PATH" ]; then
	printf "Error! keyboards/%s does not exist!\n" "$KB_PATH"
	exit 1
fi

if [ -d "keyboards/$KB_PATH/keymaps/$USERNAME" ]; then
	printf "Error! keyboards/%s/keymaps/%s already exists!\n" "$KB_PATH" "$USERNAME"
	exit 1
fi

# Recursively copy the chosen keyboard's default keymap
cp -r keyboards/"$KB_PATH"/keymaps/default keyboards/"$KB_PATH"/keymaps/"$USERNAME"

printf "%s keymap directory created in: qmk_firmware/keyboards/%s/keymaps/\n\n" "$USERNAME" "$KB_PATH"

printf "Compile a firmware file with your new keymap by typing: \n"
printf "   make %s:%s\n" "$KB_PATH" "$USERNAME"
printf "from the qmk_firmware directory\n"
