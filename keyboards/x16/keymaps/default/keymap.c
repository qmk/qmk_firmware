#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │BAC│
     * ├───┼───┼───┤───┤ 
     * │ 4 │ 5 │ 6 │VOU│
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │VOD│
     * ├───┼───┼───┤───┤ 
     * │MO1│ 0 │ . │ENT│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_P7,   KC_P8,   KC_P9,   KC_BSPC,
        KC_P4,   KC_P5,   KC_P6,   KC_VOLU,
        KC_P1,   KC_P2,   KC_P3,   KC_VOLD,
        MO(1),   KC_P0,   KC_DOT,  KC_ENT
    ),
    [1] = LAYOUT_ortho_4x4(
        RESET, KC_TRNS, KC_TRNS, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY
    )
};
