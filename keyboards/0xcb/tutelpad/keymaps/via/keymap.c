#include QMK_KEYBOARD_H

#define _____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_1,    KC_2,           KC_3,           KC_4,
        KC_5,    LT(1, KC_6),    LT(1, KC_7),    LT(1, KC_8)
    ),

    [1] = LAYOUT(
        _____,    _____,    _____,    _____,
        _____,    _____,    _____,    _____
    ),
    
    [2] = LAYOUT(
        _____,    _____,    _____,    _____,
        _____,    _____,    _____,    _____
    ),
    
    [3] = LAYOUT(
        _____,    _____,    _____,    _____,
        _____,    _____,    _____,    _____
    ),
};