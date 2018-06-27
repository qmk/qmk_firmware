#!/bin/sh
# Script to make a new quantum project
# Jack Humbert 2015

KEYBOARD=$1
KEYBOARD_TYPE=$2

if [ -z "$KEYBOARD" ]; then
    echo "Usage:   $0 <keyboard_name> <keyboard_type>"
    echo "Example: $0 gh60 avr"
    echo "Example: $0 bfake ps2avrgb"
    exit 1
elif [ -z "$KEYBOARD_TYPE" ]; then
  KEYBOARD_TYPE=avr
fi

if [ $KEYBOARD_TYPE != "avr" -a $KEYBOARD_TYPE != "ps2avrgb" ]; then
  echo "Invalid keyboard type target"
  exit 1
fi

if [ -e "keyboards/$1" ]; then
	echo "Error! keyboards/$1 already exists!"
	exit 1
fi

cd "$(dirname "$0")/.."

KEYBOARD_UPPERCASE=$(echo $1 | awk '{print toupper($0)}')
KEYBOARD_NAME=$(basename $1)
KEYBOARD_NAME_UPPERCASE=$(echo $KEYBOARD_NAME | awk '{print toupper($0)}')


cp -r quantum/template/base keyboards/$KEYBOARD
cp -r quantum/template/$KEYBOARD_TYPE/. keyboards/$KEYBOARD

mv keyboards/${KEYBOARD}/template.c keyboards/${KEYBOARD}/${KEYBOARD_NAME}.c
mv keyboards/${KEYBOARD}/template.h keyboards/${KEYBOARD}/${KEYBOARD_NAME}.h
find keyboards/${KEYBOARD} -type f -exec sed -i '' -e "s;%KEYBOARD%;${KEYBOARD_NAME};g" {} \;
find keyboards/${KEYBOARD} -type f -exec sed -i '' -e "s;%KEYBOARD_UPPERCASE%;${KEYBOARD_NAME_UPPERCASE};g" {} \;

echo "######################################################"
echo "# /keyboards/$KEYBOARD project created. To start"
echo "# working on things, cd into keyboards/$KEYBOARD"
echo "######################################################"
