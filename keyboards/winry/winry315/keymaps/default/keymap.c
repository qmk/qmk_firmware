// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RGB,
};

// Shorter defines for some QMK keycodes (to keep the keymap aligned)
#define U_LTESC LT(_RGB, KC_ESC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [_BASE] = LAYOUT_top(
            KC_HOME,      KC_MUTE,     KC_MPLY,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        U_LTESC, KC_TAB,  KC_SPC,  KC_BSPC, KC_ENT
    ),

    // RGB configuration
    [_RGB] = LAYOUT_top(
            RGB_M_P,      RGB_M_B,     RGB_M_R,
        RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU,
        RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD,
        KC_TRNS, RM_TOGG, RGB_M_P, RGB_M_B, RGB_M_R
    ),
};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    switch (index) {
        case 0:
            // Left encoder
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
            } else {
                tap_code(clockwise ? KC_PGDN : KC_PGUP);
            }
            break;

        case 1:
            // Center encoder
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
            } else {
                tap_code_delay(clockwise ? KC_VOLU : KC_VOLD, 10);
            }
            break;

        case 2:
            // Right encoder
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
            } else {
                tap_code_delay(clockwise ? KC_MNXT : KC_MPRV, 10);
            }
            break;
    }
    return false;
}
