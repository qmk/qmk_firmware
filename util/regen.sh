#!/bin/bash
set -e

qmk generate-rgb-breathe-table -o quantum/rgblight/rgblight_breathe_table.h
qmk generate-keycodes --version latest -o quantum/keycodes.h
qmk generate-keycodes-tests --version latest -o tests/test_common/keycode_table.cpp

for lang in $(find data/constants/keycodes/extras/ -type f -exec basename '{}' \; | sed "s/keycodes_\(.*\)_[0-9].*/\1/"); do
  qmk generate-keycode-extras --version latest --lang $lang -o quantum/keymap_extras/keymap_$lang.h
done
