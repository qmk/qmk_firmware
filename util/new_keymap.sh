#!/bin/sh
# Script to make a new keymap for a keyboard of your choosing

KEYBOARD=$1
USERNAME=$2

if [ -z "$KEYBOARD" ]; then
    printf "Usage:   %s <keyboard_name> <username>\n" "$0"
    printf "Example: %s gh60 yourname\n" "$0"
    exit 1
fi

if [ -z "$USERNAME" ]; then
    printf "Usage:   %s <keyboard_name> <username>\n" "$0"
    printf "Example: %s gh60 yourname\n" "$0"
    exit 1
fi

cd "$(dirname "$0")/.."

if [ ! -d "keyboards/$1" ]; then
	printf "Error! keyboards/%s does not exist!\n" "$1"
	exit 1
fi

if [ -d "keyboards/$1/keymaps/$2" ]; then
	printf "Error! keyboards/%s/%s already exists!\n" "$1" "$2"
	exit 1
fi

cp -r keyboards/$1/keymaps/default keyboards/$1/keymaps/$2

printf "Make your new keymap by typing \n"
printf "   make %s:%s\n" "$1" "$2"
printf "from qmk_firmware\n"