#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_all(
        KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_2, KC_2, KC_Q, KC_W, KC_E,
        KC_3, KC_Q, KC_3, KC_R, KC_T,
        KC_4, KC_W, KC_R, KC_4, KC_Y,
        KC_5, KC_E, KC_T, KC_Y, KC_5
    )
};
