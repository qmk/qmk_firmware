#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_ortho_3x3(
    KC_MPLY, KC_HOME, KC_MUTE,
    MO(1),   KC_UP,   KC_END,
    KC_LEFT, KC_DOWN, KC_RGHT
),

[1] = LAYOUT_ortho_3x3(
    RESET,   _______, KC_STOP,
    _______, KC_HOME, _______,
    KC_MPRV, KC_END , KC_MNXT
),

[2] = LAYOUT_ortho_3x3(
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
),

[3] = LAYOUT_ortho_3x3(
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
)

};
