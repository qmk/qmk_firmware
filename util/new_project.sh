#!/bin/sh
# Script to make a new quantum project
# Jack Humbert 2015

if [ -z "$1" ]; then
	echo "Usage: $0 <keyboard_name>"
	exit 1
fi

KEYBOARD=$1
KEYBOARD_UPPERCASE=$(echo $1 | awk '{print toupper($0)}')

mkdir keyboards/$1
mkdir keyboards/$1/keymaps
mkdir keyboards/$1/keymaps/default
sed -e "s;%KEYBOARD%;$KEYBOARD;g" -e "s;%KEYBOARD_UPPERCASE%;$KEYBOARD_UPPERCASE;g" quantum/template/template.h > keyboards/$KEYBOARD/$KEYBOARD.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/template.c > keyboards/$KEYBOARD/$KEYBOARD.c
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/config.h > keyboards/$KEYBOARD/config.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/README.md > keyboards/$KEYBOARD/README.md
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/Makefile > keyboards/$KEYBOARD/Makefile
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/keymaps/default/keymap.c > keyboards/$KEYBOARD/keymaps/default/keymap.c

echo "######################################################"
echo "# keyboards/$KEYBOARD project created. To start"
echo "# working on things, use the following command:"
echo "# cd keyboards/$KEYBOARD"
echo "######################################################"
