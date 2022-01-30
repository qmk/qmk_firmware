// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_INS , KC_HOME, KC_PGUP,
        KC_DEL , KC_END , KC_PGDN,
        KC_KB_MUTE, KC_MEDIA_PLAY_PAUSE
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_MS_L);
    } else {
      tap_code(KC_MS_R);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_MS_D);
    } else {
      tap_code(KC_MS_U);
    }
  }
  return false;
}
