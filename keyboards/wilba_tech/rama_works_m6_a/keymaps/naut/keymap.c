#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Base Layer
    [0] = LAYOUT(
        TO(1),   KC_UP,   KC_PGDN,
        KC_LEFT, KC_DOWN, KC_RGHT),

    // Fn1 Layer
    [1] = LAYOUT(
        TO(0),   KC_VOLU, KC_MUTE,
        KC_MRWD, KC_VOLD, KC_MFFD),
};
