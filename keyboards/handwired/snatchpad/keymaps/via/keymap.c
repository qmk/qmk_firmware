// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC , KC_SPC , MO(2)  ,
    KC_MPRV, KC_MNXT, KC_ENT ,
    KC_MUTE,          KC_MPLY
  ),
  [1] = LAYOUT(
    KC_LOCK, KC_UP  , _______,
    KC_LEFT, KC_DOWN, KC_RGHT,
    KC_BTN1,          KC_BTN2
  ),
  [2] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    TO(0)  ,          TO(1)
  ),
  [3] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______,          _______
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t layer = biton32(layer_state);


  if (index == 0) { /* First encoder */
    switch(layer) {

      default:
        if (clockwise) {
          tap_code(KC_MS_L);
        } else {
          tap_code(KC_MS_R);
        }
        return false;

      case 0:
        if (clockwise) {
          tap_code_delay(KC_VOLU, 10);
        } else {
          tap_code_delay(KC_VOLD, 10);
        }
        return false;

      case 2:
        if (clockwise) {
          tap_code16(LCTL(KC_Y);
        } else {
          tap_code16(LCTL(KC_Z);
        }
        return false;


    }

  } else if (index == 1) { /* Second encoder */
    switch(layer) {

      default:
        if (clockwise) {
          tap_code(KC_MS_D);
        } else {
          tap_code(KC_MS_U);
        }
        return false;

      case 0:
        if (clockwise) {
          tap_code(KC_MFFD);
        } else {
          tap_code(KC_MRWD);
        }
        return false;

      case 2:
        if (clockwise) {
          tap_code(KC_WH_D);
        } else {
          tap_code(KC_WH_U);
        }
        return false;



    }
  }
  return false;
}
