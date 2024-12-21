#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_5,   KC_6, 
        KC_7,   KC_8,   KC_9
    ),

    [1] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______, 
        _______, _______, _______
    ),

    [2] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______, 
        _______, _______, _______
    ),

    [3] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______, 
        _______, _______, _______
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
