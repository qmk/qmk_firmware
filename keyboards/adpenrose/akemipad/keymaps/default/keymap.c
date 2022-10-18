// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Setting up the LED matrix */
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0, 1, 2, 3, NO_LED },
  { 4, 5, 6, 7, NO_LED },
  { 8, 9, 10, 11, 12 },
  { 13, 14, 15, 16, NO_LED },
  { 17, 18, 19, 20, 21 },
  { 22, 23, 24, 25, 26 },
}, {
  // LED Index to Physical Position
  {  0,0  }, { 37,0  }, { 74,0  }, {111,0  }, {  0,34 }, { 37,34 }, { 74,34 }, {111,34 }, {  0,62 }, { 37,62 }, 
  { 74,62 }, {111,62 }, {120,75 }, {  0,89 }, { 37,89 }, { 74,89 }, {111,89 }, {  0,117}, { 37,117}, { 74,117}, 
  {111,117}, {120,130}, {  0,137}, { 18,144}, { 37,137}, { 74,144}, {111,144}
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };

/* Keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                  MO(1),    MO(2),     MO(3),     KC_DEL,
                  KC_NUM,   KC_PSLS,   KC_PAST,   KC_PMNS,
                  KC_P7,    KC_P8,     KC_P9,     KC_PPLS,
                  KC_P4,    KC_P5,     KC_P6,     KC_PPLS,
                  KC_P1,    KC_P2,     KC_P3,     KC_PENT,
        KC_MUTE,  KC_P0,    KC_P0,     KC_PDOT,   KC_PENT 
    ),
    [1] = LAYOUT_all(
                  KC_TRNS,  CK_DOWN,   CK_UP,     CK_RST,
                  MU_TOG,   MU_MOD,    KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        CK_TOGG,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [2] = LAYOUT_all(
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [3] = LAYOUT_all(
                  QK_BOOT,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif
