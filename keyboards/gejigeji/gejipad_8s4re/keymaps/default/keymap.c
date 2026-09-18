// Copyright 2026 gejigeji-com (@gejigeji-com)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        /* SW6   SW7   SW8   SW9   SW10  SW11  SW12  SW13 */
        KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
        ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),
        ENCODER_CCW_CW(KC_DOWN, KC_UP)
    },
};
#endif
