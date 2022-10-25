#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │ / │
     * ├───┼───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │ / │
     * ├───┼───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │ / │
     * ├───┼───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │ / │
     * ├───┼───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │ / │
     * └───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x5(
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,
        KC_LEFT_CTRL,   KC_LEFT_SHIFT,   KC_LEFT_GUI,   KC_RIGHT_CTRL,   KC_RIGHT_SHIFT
    )
};
