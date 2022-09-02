#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │F13│F14│F15│F16│
     * ├───┼───┼───┼───┤
     * │ - │ * │ / │Num│
     * ├───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │
     * │ + ├───┼───┤───│
     * │   │ 4 │ 5 │ 6 │
     * ├───┼───┼───┼───┤
     * │   │ 1 │ 2 │ 3 │
     * │Ent├───┼───┴───│
     * │   │ . │   0   │
     * └───┴───┴───────┘
     */
    [0] = LAYOUT_numpad_6x4_southpaw(
        KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_PMNS, KC_PAST, KC_PSLS, KC_NUM,
        KC_PPLS, KC_P7,   KC_P8,   KC_P9,
                 KC_P4,   KC_P5,   KC_P6,
        KC_PENT, KC_P1,   KC_P2,   KC_P3,
                 KC_PDOT, KC_P0
    )
};
