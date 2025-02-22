// Copyright 2022 Makoto Kurauchi (@MakotoKurauchi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgblite.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_1x1(
    UG_HUEU
  )
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case QK_UNDERGLOW_HUE_UP:
        rgblite_increase_hue();
        break;
    }
  }
  return true;
}

void keyboard_post_init_user(void) {
  rgblite_init();
  rgblite_increase_hue();
}
