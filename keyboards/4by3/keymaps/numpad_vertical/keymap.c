#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Change 'LAYOUT_vertical_right' to 'LAYOUT_vertical_left'
       to change the side where the pro micro usb port is. */
	[0] = LAYOUT_vertical_right(
		KC_P1   , KC_P2   , KC_P3   ,
        KC_P4   , KC_P5   , KC_P6   ,
        KC_P7   , KC_P8   , KC_P9   ,
        KC_BSPC , KC_P0   , KC_ENT
    ),
};
