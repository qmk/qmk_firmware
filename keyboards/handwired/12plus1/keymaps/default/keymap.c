#include QMK_KEYBOARD_H

# define BASE 0
# define NAV 1
# define NUM 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        RESET,   KC_COPY, KC_PASTE, KC_VOLU,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
        TO(NAV),   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE
    ),

    [NAV] = LAYOUT(
        RESET,   _______, _______, _______,
        KC_PGUP, KC_UP,   _______, KC_PGUP,
        TO(NUM),   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
    ),

    [NUM] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        TO(BASE),   KC_9,    KC_0,    XXXXXXX, RESET
    ),

};
