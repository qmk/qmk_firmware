// Copyright 2026 silly group (@stwupid)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q, KC_W, KC_E,
        KC_A, KC_S, KC_D,
        KC_Z, KC_X, KC_C
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Display MeowyPad logo/text
    oled_write_ln_P(PSTR("MeowyPad"), false);
    oled_write_ln_P(PSTR("by silly group"), false);
    oled_write_ln_P(PSTR(""), false);
    
    // Display current layer
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln_P(PSTR("0"), false);
    
    return false;
}
#endif
