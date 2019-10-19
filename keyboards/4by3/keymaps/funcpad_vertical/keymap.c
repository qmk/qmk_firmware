#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Change 'LAYOUT_vertical_right' to 'LAYOUT_vertical_left'
       to change the side where the pro micro usb port is. */
	[0] = LAYOUT_vertical_right(
		KC_F1   , KC_F2   , KC_F3   ,
        KC_F4   , KC_F5   , KC_F6   ,
        KC_F7   , KC_F8   , KC_F9   ,
        KC_F10  , KC_F11  , KC_F12
    )
};
