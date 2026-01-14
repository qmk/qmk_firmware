// Copyright 2024 CZMAO
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        LT(1, KC_NUM), KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,         KC_P8,   KC_P9,
        KC_P4,         KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,         KC_P2,   KC_P3,
        KC_P0,                  KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT_numpad_5x4(
        KC_TRNS, KC_TRNS, MO(2),   RM_VALU,
        RM_TOGG,  RM_SATU, KC_TRNS,
        RM_HUED, KC_TRNS, RM_HUEU, RM_VALD,
        KC_TRNS, RM_SATD, KC_TRNS,
        RM_NEXT,          KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_numpad_5x4(
        KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS, EE_CLR
    )
};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Num Lock indicator (first LED)
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(0, 0, 255, 255);  // Cyan color
    }

    // Layer indicators
    uint8_t layer = get_highest_layer(layer_state);
    
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(layer) {
            case 1:
                rgb_matrix_set_color(i, 255, 0, 0);      // Red
                break;
            case 2:
                rgb_matrix_set_color(i, 0, 255, 0);      // Green
                break;
            default:
                // Keep default RGB effect for base layer
                break;
        }
    }
    
    return false;
}
#endif
