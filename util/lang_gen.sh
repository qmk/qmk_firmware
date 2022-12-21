#!/bin/bash

for lang in $(find data/constants/keycodes/extras/ -type f -printf "%f\n" | sed "s/keycodes_//g" | sed "s/_[0-9].*//"); do
  data=$(qmk generate-keycode-extras --version latest --lang $lang)
  if [ "$?" == "0" ]; then
    echo "$data" > quantum/keymap_extras/keymap_$lang.h
  fi
done
