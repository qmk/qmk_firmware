#include QMK_KEYBOARD_H

/* This keyboard/layout is used to test community layout discovery/compilation. */

#define _DEFAULT 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DEFAULT] = LAYOUT (
    KC_B
),
};
