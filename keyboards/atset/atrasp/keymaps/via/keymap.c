
#include QMK_KEYBOARD_H


enum {
    L1,
    L2
} keyboard_layers;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L1] = LAYOUT(
        KC_MUTE, KC_MPLY
    ),
    [L2] = LAYOUT(
        KC_MUTE, KC_MPLY
    )
};

