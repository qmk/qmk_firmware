#include "../../m6_a.h"

// Define Layers
#define _BASE 0
#define _FNX  1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base Layer
    [_BASE] = KEYMAP(
		  TO(1),  KC_UP, KC_PGDN,
        KC_LEFT,KC_DOWN,KC_RGHT),

// Fn Layer
    [_FNX] = KEYMAP(
		  TO(0),KC_VOLU,KC_MPLY,
        KC_MRWD,KC_VOLD,KC_MFFD)
};