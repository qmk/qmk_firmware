#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_right_all(
        KC_ESC,  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_PGUP, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_PGDN, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LALT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LGUI, KC_P0,   KC_P0,   KC_PDOT, KC_PENT
    )
};
// clang-format on
