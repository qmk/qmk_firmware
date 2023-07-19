#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,   KC_7,    KC_7, KC_7, KC_7, KC_7, KC_7,
        RGB_MODE_BREATHE,   RGB_MODE_FORWARD,   KC_P7,   KC_7,      KC_7,    KC_7, KC_7, KC_7, KC_7, KC_7,
        RGB_MODE_SNAKE,   KC_P7,   KC_P7,   KC_7,      KC_7,    KC_7, KC_7, KC_7, KC_7, KC_7,
        KC_P7,   KC_P7,   KC_P7,   KC_7,      QK_BOOT,    KC_7, KC_7, KC_7, KC_7, KC_7
    )
};