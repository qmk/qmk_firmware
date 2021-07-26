#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        MO(1),   KC_MPLY, BL_STEP,
        KC_VOLD, KC_MUTE, KC_VOLU,
        KC_KP_1, KC_KP_2, KC_KP_3
    ),

    [1] = LAYOUT_ortho_3x3(
        _______, _______, MO(2),
        _______, _______, _______,
        _______, _______, _______
    ),

    [2] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, MO(3)
    ),

    [3] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        RESET,   _______, _______
    )
};
