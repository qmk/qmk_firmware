#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        LT(1, KC_MPRV), KC_MNXT, KC_MPLY,
        KC_VOLD,        KC_UP,   KC_VOLU,
        KC_LEFT,        KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_ortho_3x3(
        KC_ESC,  KC_MPLY, QK_BOOT,
        KC_P7,   KC_P1,   KC_F1,
        KC_F2,   KC_F3,   KC_F4
    )
};
