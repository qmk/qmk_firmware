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
  )
};

