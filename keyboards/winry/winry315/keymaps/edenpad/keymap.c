// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RGB,
    _MOUSE,
};

// Shorter defines for some QMK keycodes (to keep the keymap aligned)
//#define U_LTESC LT(_RGB, KC_ESC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [_BASE] = LAYOUT_top(
                KC_LCTL,     KC_SPC,     KC_DEL,
    C(A(KC_0)),C(A(KC_1)),C(A(KC_2)),C(A(KC_3)),C(A(KC_4)),
       C(KC_B),C(A(KC_C)), C(KC_I)  ,C(S(KC_Z)),C(KC_U),
       FN_MO13,C(A(KC_V)), KC_LSFT  ,  C(KC_Z) , TG(2)
    ),

    // RGB configuration
    [_RGB] = LAYOUT_top(
            RGB_M_P,      RGB_M_B,     RGB_M_R,
        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
        RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
        KC_TRNS, RGB_M_P, RGB_TOG, RGB_M_B, KC_TRNS
    ),

    // Mouse and F Layer
    [_MOUSE] = LAYOUT_top(
            KC_MS_BTN1,   KC_MS_BTN3,     KC_MS_BTN2,
        KC_F1,   KC_F2,   KC_F3,       KC_F4, KC_F5,
        KC_F6,   KC_F7,   KC_F8,       KC_F9, KC_F10,
        KC_TRNS, KC_F11,KC_MS_ACCEL1, KC_F12, KC_TRNS
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

            } else if (layer == _MOUSE) {
                tap_code(clockwise ? KC_MS_DOWN: KC_MS_UP);
            } else {
                tap_code(clockwise ? KC_DOWN : KC_UP);
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
            } else if (layer == _MOUSE) {
                tap_code_delay(clockwise ? KC_VOLD: KC_VOLU, 10);
            } else {
                tap_code(clockwise ? KC_PGDN : KC_PGUP);
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
            } else if (layer == _MOUSE) {
                tap_code(clockwise ? KC_MS_RIGHT: KC_MS_LEFT);
            }else {
                tap_code(clockwise ? C(KC_RIGHT) : C(KC_LEFT));
            }
            break;
    }
    return false;
}
