// Copyright 2024 Stephen Onnen (@onnenon)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_MUTE)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
};
#endif

// Enable the power pin for the Xiao Seeed rp2040 onboard NeoPixel
void matrix_init_kb(void) {
    gpio_set_pin_output(GP11);
    gpio_write_pin_high(GP11);
}
