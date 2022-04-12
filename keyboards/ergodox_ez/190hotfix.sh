#!/bin/bash
#a tool to fix broken keymaps as a result of pull request #190 
#changing the declaration of matrix_scan_user() and matrix_init_user()
#
#This script will save a copy of the specified keymap as keymap.c.bak
#and then create a new keymap.c with the definion corrected.
#this script must be run from the ergodox_ez directory
if [ $# -ne 1 ]; then
    echo $0: usage: ./190hotfix keymap_name
    exit 1
fi

echo Saving backup as ./keymaps/$1/keymap.c.bak ...
mv ./keymaps/$1/keymap.c ./keymaps/$1/keymap.c.bak

echo Modifying ./keymaps/$1/keymap.c ...
cat ./keymaps/$1/keymap.c.bak | sed -r 's/^void \* matrix_/void matrix_/'>./keymaps/$1/keymap.c

echo Complete!
