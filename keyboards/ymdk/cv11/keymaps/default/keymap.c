// SPDX-License-Identifier: BSD-2-Clause

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE,           // Rotary Encoder Button
        KC_ESC,            // Top-Right Key (right of encoder)

        // 3x3 Grid
        KC_1, KC_2,  KC_3,  // Top Row: 1, 2, 3
        KC_4, KC_5,  KC_6,  // Middle Row: 4, 5, 6
        KC_7, KC_8,  KC_9   // Bottom Row: 7, 8, 9
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif
