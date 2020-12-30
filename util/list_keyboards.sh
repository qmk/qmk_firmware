#!/bin/sh
# Temporary shell script to find keyboards
#
# This allows us to exclude keyboards by including a .noci file.

KEYBOARD_FOLDER=${KEYBOARD_DIR:-keyboards}

#>&2 echo "KEYBOARD_FOLDER:$KEYBOARD_FOLDER"

find -L ${KEYBOARD_FOLDER} -type f -name rules.mk | grep -v keymaps | sed 's!'${KEYBOARD_FOLDER}'/\(.*\)/rules.mk!\1!' | while read keyboard; do

	[ "$1" = "noci" -a -e "${KEYBOARD_FOLDER}/${keyboard}/.noci" ] || echo "$keyboard"
done
