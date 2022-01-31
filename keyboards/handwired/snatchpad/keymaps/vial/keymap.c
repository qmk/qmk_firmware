// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
  TOGGLE_RESET = USER00,
  TOGGLE_M1 = USER01,
  TOGGLE_M2 = USER02,
  TOGGLE_M3 = USER03
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MRWD, KC_MFFD, TG(1)  ,
    KC_MPRV, KC_MNXT, KC_MPLY,
    KC_MUTE,          KC_RSFT
  ),
  [1] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______,          _______
  ),
  [2] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______,          _______
  ),
  [3] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______,          _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case TOGGLE_RESET:
      if (record->event.pressed) {
        unregister_code(KC_BTN1);
        unregister_code(KC_BTN2);
        unregister_code(KC_BTN3);
      }
      return false;

    case TOGGLE_M1:
      if (record->event.pressed) {
        static bool toggled_m1;
        toggled_m1 ^= 1;
        if (toggled_m1) {
          register_code(KC_BTN1);
        } else {
          unregister_code(KC_BTN1);
        }
      }
      return false;

    case TOGGLE_M2:
      if (record->event.pressed) {
        static bool toggled_m2;
        toggled_m2 ^= 1;
        if (toggled_m2) {
          register_code(KC_BTN2);
        } else {
          unregister_code(KC_BTN2);
        }
      }
      return false;

    case TOGGLE_M3:
      if (record->event.pressed) {
        static bool toggled_m3;
        toggled_m3 ^= 1;
        if (toggled_m3) {
          register_code(KC_BTN3);
        } else {
          unregister_code(KC_BTN3);
        }
      }
      return false;

    default:
      return true; // Process all other keycodes normally
  }
}
