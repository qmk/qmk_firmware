#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ - │ / │ * │
     * ├───┼───┼───┤
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 1 │ 2 │ 3 │
     * ├───┼───┼───┤
     * │ 0 │00 │ . │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x3(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I,
        KC_L, KC_M, KC_N,
        KC_0, KC_P, KC_Q
    )
};
