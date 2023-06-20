// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later


 #include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                                   KC_MUTE,
        MO(1), KC_PSLS, KC_PAST, KC_BSPC,
        KC_P7, KC_P8,   KC_P9,   KC_PMNS,        
        KC_P4, KC_P5,   KC_P6,   KC_PPLS,        
        KC_P1, KC_P2,   KC_P3,   KC_PENT,        
        KC_P0, RGB_TOG, KC_PDOT, KC_PENT     
        ),
    [_FN1] = LAYOUT(
                                    RGB_TOG,
        _______,  _______, _______, _______,
        _______,  _______, _______, _______,
        RGB_RMOD, _______, RGB_MOD, _______,
        _______,  _______, _______, _______,
        _______,  _______, KC_NUM,  _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
