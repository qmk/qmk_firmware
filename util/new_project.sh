#!/bin/sh
# Script to make a new quantum project
# Jack Humbert 2015

if [ -z "$1" ]; then
	echo "Usage: $0 <keyboard_name>"
	exit 1
fi

cd "$(dirname "$0")/.."

KEYBOARD=$1
KEYBOARD_UPPERCASE=$(echo $1 | awk '{print toupper($0)}')

mkdir keyboards/$1
mkdir keyboards/$1/keymaps
mkdir keyboards/$1/keymaps/default
sed -e "s;%KEYBOARD%;$KEYBOARD;g" -e "s;%KEYBOARD_UPPERCASE%;$KEYBOARD_UPPERCASE;g" quantum/template/template.h > keyboards/$KEYBOARD/$KEYBOARD.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/template.c > keyboards/$KEYBOARD/$KEYBOARD.c
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/config.h > keyboards/$KEYBOARD/config.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/readme.md > keyboards/$KEYBOARD/readme.md
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/Makefile > keyboards/$KEYBOARD/Makefile
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/keymaps/default/config.h > keyboards/$KEYBOARD/keymaps/default/config.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/keymaps/default/keymap.c > keyboards/$KEYBOARD/keymaps/default/keymap.c
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/keymaps/default/Makefile > keyboards/$KEYBOARD/keymaps/default/Makefile
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/keymaps/default/readme.md > keyboards/$KEYBOARD/keymaps/default/readme.md

echo "######################################################"
echo "# /keyboards/$KEYBOARD project created. To start"
echo "# working on things, cd into keyboards/$KEYBOARD"
echo "######################################################"
