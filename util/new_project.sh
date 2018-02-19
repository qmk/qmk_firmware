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

cp -r quantum/template keyboards/$KEYBOARD
mv keyboards/$KEYBOARD/template.c keyboards/$KEYBOARD/$KEYBOARD.c
mv keyboards/$KEYBOARD/template.h keyboards/$KEYBOARD/$KEYBOARD.h
find keyboards/${KEYBOARD} -type f -exec sed -i'' -e "s;%KEYBOARD%;$KEYBOARD;g" {} \;
find keyboards/${KEYBOARD} -type f -exec sed -i'' -e "s;%KEYBOARD_UPPERCASE%;$KEYBOARD_UPPERCASE;g" {} \;

echo "######################################################"
echo "# /keyboards/$KEYBOARD project created. To start"
echo "# working on things, cd into keyboards/$KEYBOARD"
echo "######################################################"
