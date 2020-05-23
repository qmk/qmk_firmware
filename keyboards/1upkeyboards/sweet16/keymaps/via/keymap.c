#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,   KC_ASTR,
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_MINS,
        KC_0, KC_ENT, KC_DOT, MO(1)
    ),

    [1] = LAYOUT_ortho_4x4(
        RESET, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS
    ),

    [2] = LAYOUT_ortho_4x4(
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS
    ),

    [3] = LAYOUT_ortho_4x4(
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS
    ),

};




