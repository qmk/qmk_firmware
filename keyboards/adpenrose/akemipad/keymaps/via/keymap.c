// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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
    {  0,0  }, { 56,0  }, {112,0  }, {168,0  }, 
{  0,15 }, { 56,15 }, {112,15 }, {168,15 }, 
{  0,27 }, { 56,27 }, {112,27 }, {168,27 }, 
{224,27 }, {  0,40 }, { 56,40 }, {112,40 }, 
{168,40 }, {  0,52 }, { 56,52 }, {112,52 }, 
{168,52 }, {224,52 }, {  0,64 }, { 56,64 }, 
{112,64 }, {168,64 }, {224,64 },
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                  KC_ESC,   MO(1),   MO(2),   MO(3),
                  KC_NUM_LOCK,   KC_KP_SLASH,   KC_KP_ASTERISK,   KC_KP_MINUS,
                  KC_KP_7,  KC_KP_8,  KC_KP_9,   KC_KP_PLUS,
                  KC_KP_4,  KC_KP_5,  KC_KP_6, KC_DEL,
                  KC_KP_1,  KC_KP_2,  KC_KP_3, KC_KP_ENTER,
        KC_MUTE,  KC_KP_0, MU_MOD, KC_KP_DOT, MU_TOG 
    ),
    [1] = LAYOUT_all(
                  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
                  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS 
    ),
    [2] = LAYOUT_all(
                      KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                      KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                      KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
                      KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
                      KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS 
    ),
    [3] = LAYOUT_all(
                      QK_BOOT,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                      KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                      KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
                      KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
                      KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS 
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
