#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_1,  KC_2, KC_3,
        KC_4,  KC_5, KC_6,
        KC_VOLD,  KC_VOLU, MO(1)
    ),
    [1] = LAYOUT(
        KC_7, KC_8, KC_9,
        KC_0, KC_MINUS, KC_PLUS,
        RESET, KC_AT , KC_TRNS
    ),
};


