// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, LT(1, KC_9)),
    [1] = LAYOUT_ortho_3x3(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, LT(0, KC_I)),
};

enum layer_names { _MAC_DEFAULT, _MAC_CODE, _MAC_NUM, _MAC_FUNC };

// OLED
#ifdef OLED_ENABLE

// Rotate OLED
// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     return OLED_ROTATION_90;
// }

// Draw to OLED
bool oled_task_user() {
    // Set cursor position
    oled_set_cursor(0, 1);

    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case _MAC_DEFAULT:
            oled_write("Main Layer", false);
            break;
        case _MAC_CODE:
            oled_write("Code Layer", false);
            break;
        case _MAC_NUM:
            oled_write("Number Layer", false);
            break;
        case _MAC_FUNC:
            oled_write("Function Layer", false);
            break;
    }

    return false;
}

#endif

// Encode Knob
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

// Encoder switch
bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_move(1);
            } else {
                layer_move(0);
            }
            break;
        }
    return true;
}
