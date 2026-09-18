// Copyright 2026 gejigeji-com (@gejigeji-com)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        /* SW6   SW7   SW8   SW9   SW10  SW11  SW12  SW13 */
        KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0: // encoder 1
            clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            break;
        case 1: // encoder 2
            clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
            break;
        case 2: // encoder 3
            clockwise ? tap_code(KC_RIGHT) : tap_code(KC_LEFT);
            break;
        case 3: // encoder 4
            clockwise ? tap_code(KC_UP) : tap_code(KC_DOWN);
            break;
    }
    return true;
}
#endif
