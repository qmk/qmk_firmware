#!/bin/sh
# Script to make a new quantum project
# Jack Humbert 2015

KEYBOARD=$1
KEYBOARD_UPPERCASE=$(echo $1 | awk '{print toupper($0)}')

mkdir keyboard/$1
mkdir keyboard/$1/keymaps
sed -e "s;%KEYBOARD%;$KEYBOARD;g" -e "s;%KEYBOARD_UPPERCASE%;$KEYBOARD_UPPERCASE;g" quantum/template/template.h > keyboard/$KEYBOARD/$KEYBOARD.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/template.c > keyboard/$KEYBOARD/$KEYBOARD.c
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/config.h > keyboard/$KEYBOARD/config.h
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/README.md > keyboard/$KEYBOARD/README.md
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/Makefile > keyboard/$KEYBOARD/Makefile
sed -e "s;%KEYBOARD%;$KEYBOARD;g" quantum/template/keymaps/default.c > keyboard/$KEYBOARD/keymaps/default.c

echo "######################################################"
echo "# keyboard/$KEYBOARD project created. To start"
echo "# working on things, use the following command:"
echo "# cd keyboard/$KEYBOARD"
echo "######################################################"
