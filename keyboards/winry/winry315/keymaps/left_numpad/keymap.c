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
    /* Base */
    [_BASE] = LAYOUT_left(
        KC_MPLY,    U_LTESC, KC_BSPC, KC_PENT,
                    KC_P7,   KC_P8,   KC_P9,
        KC_MUTE,    KC_P4,   KC_P5,   KC_P6,
                    KC_P1,   KC_P2,   KC_P3,
        KC_HOME,    KC_P0,   KC_P0,   KC_PDOT
    ),

    /* RGB configuration */
    [_RGB] = LAYOUT_left(
        RGB_M_R,    KC_TRNS, RM_SPDD, RM_SPDU,
                    RM_TOGG, RM_HUED, RM_HUEU,
        RGB_M_B,    RGB_M_P, RM_SATD, RM_SATU,
                    KC_NO,   RM_VALD, RM_VALU,
        RGB_M_P,    KC_NUM,  RM_PREV, RM_NEXT
    ),
};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    switch (index) {
        case 0:
            // Bottom encoder (left in the default orientation)
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
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
            // Top encoder (right in the default orientation)
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
            } else {
                tap_code_delay(clockwise ? KC_MNXT : KC_MPRV, 10);
            }
            break;
    }
    return false;
}
