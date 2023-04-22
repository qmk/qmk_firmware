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
        RGB_M_R,    KC_TRNS, RGB_SPD, RGB_SPI,
                    RGB_TOG, RGB_HUD, RGB_HUI,
        RGB_M_B,    RGB_M_P, RGB_SAD, RGB_SAI,
                    KC_NO,   RGB_VAD, RGB_VAI,
        RGB_M_P,    KC_NUM,  RGB_RMOD,RGB_MOD
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =  { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)  },
    [_RGB] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)  },
};
#endif
