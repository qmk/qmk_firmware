// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

bool potentiometer_update_user(uint8_t index, uint16_t value) {
    uprintf("ADC:%u\n", value);
    return false;
}

void keyboard_post_init_user(void) {
    debug_enable=true;
}
