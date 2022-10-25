#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐
     * │ 1 │ 2 │ 3 │ 4 │ 5 │
     * ├───┼───┼───┼───┼───┤
     * │ Q │ W │ E │ R │ T │
     * ├───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │
     * ├───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │
     * ├───┼───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 4 │ 5 │
     * └───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x5(
        KC_M1,   KC_M2,   KC_M3,   KC_M4,   KC_M5,
        KC_M1,   KC_M2,   KC_M3,   KC_M4,   KC_M5,
        KC_M1,   KC_M2,   KC_M3,   KC_M4,   KC_M5,
        KC_M1,   KC_M2,   KC_M3,   KC_M4,   KC_M5,
        KC_M1,   KC_M2,   KC_M3,   KC_M4,   KC_M5,
    )
};
