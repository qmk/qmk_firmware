// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off

#define U_LTESC LT(1, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_top(
            KC_HOME,           KC_MUTE,           KC_MPLY,
             KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
             U_LTESC, KC_TAB,  KC_SPC,  KC_BSPC, KC_ENT
    ),
    [1] = LAYOUT_top(
            RGB_M_P,           RGB_M_B,           RGB_M_R,
             RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
             RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
             KC_TRNS, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R
    ),
    [2 ... 7] = LAYOUT_top(
            KC_TRNS,           KC_TRNS,           KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =        { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [1] =        { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI), ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [2 ... 7] =  { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif

// The enum values are assumed to match the layout option values used by VIA.
void via_set_layout_options_kb(uint32_t value) {
    winry315_set_orientation(value & 0x03);
}
