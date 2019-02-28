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

if [ "$KEYBOARD_TYPE" != "avr" ] && [ "$KEYBOARD_TYPE" != "ps2avrgb" ]; then
  echo "Invalid keyboard type target"
  exit 1
fi

if [ -e "keyboards/$1" ]; then
	echo "Error! keyboards/$1 already exists!"
	exit 1
fi

cd "$(dirname "$0")/.." || exit

KEYBOARD_NAME=$(basename "$1")
KEYBOARD_NAME_UPPERCASE=$(echo "$KEYBOARD_NAME" | awk '{print toupper($0)}')
NEW_KBD=keyboards/${KEYBOARD}


cp -r quantum/template/base "$NEW_KBD"
cp -r "quantum/template/$KEYBOARD_TYPE/." "$NEW_KBD"

mv "${NEW_KBD}/template.c" "${NEW_KBD}/${KEYBOARD_NAME}.c"
mv "${NEW_KBD}/template.h" "${NEW_KBD}/${KEYBOARD_NAME}.h"
find "${NEW_KBD}" -type f -exec sed -i '' -e "s;%KEYBOARD%;${KEYBOARD_NAME};g" {} \;
find "${NEW_KBD}" -type f -exec sed -i '' -e "s;%KEYBOARD_UPPERCASE%;${KEYBOARD_NAME_UPPERCASE};g" {} \;

GIT=$(whereis git)
if [ "$GIT" != "" ]; then
  IS_GIT_REPO=$($GIT log >>/dev/null 2>&1; echo $?)
  if [ "$IS_GIT_REPO" -eq 0 ]; then
    ID="$($GIT config --get user.name)"
    read -rp "What is your name? [$ID] " YOUR_NAME
    if [ -n "$YOUR_NAME" ]; then
      ID=$YOUR_NAME
    fi
    echo "Using $ID as user name"

    for i in "$NEW_KBD/config.h" \
             "$NEW_KBD/$KEYBOARD_NAME.c" \
             "$NEW_KBD/$KEYBOARD_NAME.h" \
             "$NEW_KBD/keymaps/default/config.h" \
             "$NEW_KBD/keymaps/default/keymap.c"
    do
      awk -v id="$ID" '{sub(/%YOUR_NAME%/,id); print}' < "$i" > "$i.$$"
      mv "$i.$$" "$i"
    done
  fi
fi

cat <<-EOF
######################################################
# $NEW_KBD project created. To start
# working on things, cd into $NEW_KBD
######################################################
EOF
