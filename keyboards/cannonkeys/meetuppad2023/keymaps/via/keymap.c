// Copyright 2023 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    MYMACRO = QK_KB_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    MYMACRO, KC_1,
    KC_2, KC_3,
    KC_4, KC_5,
    KC_6, MO(1)
  ),

  [1] = LAYOUT(
    QK_BOOT, KC_7,
    KC_8, KC_9,
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MYMACRO:
        if (record->event.pressed) {
            SEND_STRING("I went to the CannonKeys 2023 meetup and all I got was this macropad");
        }
        break;
    }
    return true;
};
