// Copyright 2025 RyanDam (https://github.com/RyanDam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MPLY,   KC_MPRV,   KC_MUTE,   KC_MNXT,
    KC_PGUP,   KC_ESC,    KC_UP,     KC_ENT,
    KC_PGDN,   KC_LEFT,   KC_DOWN,   KC_RIGHT
  ),
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif
