// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BL 0
#define _FL 1
#define _SL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT(
        KC_F7,   KC_F8,   KC_F9,
        KC_F4,   KC_F5,   KC_F6,
        KC_F1,   KC_F2,   KC_F3
    )

};

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: ", false));

    switch (get_highest_layer(layer_state)) {
    case _FN:
        oled_write_ln_P(PSTR("Function", false))
        break;
    
    default:
        oled_write_ln_P(PSTR("Undefined"), false);
        break;
    }

    return false;
}

#endif