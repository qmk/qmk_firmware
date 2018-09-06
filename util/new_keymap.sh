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


if [ ! -d "keyboards/$1" ]; then
	printf "Error! keyboards/%s does not exist!\n" "$1"
	exit 1
fi