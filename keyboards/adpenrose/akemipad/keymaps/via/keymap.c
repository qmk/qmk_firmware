// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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
