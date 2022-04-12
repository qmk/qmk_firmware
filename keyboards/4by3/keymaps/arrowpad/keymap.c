#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Change 'LAYOUT_vertical_right' to 'LAYOUT_vertical_left'
       to change the side where the pro micro usb port is. */
    [0] = LAYOUT_vertical_right(
		KC_INS  , KC_HOME , KC_PGUP ,
        KC_DEL  , KC_END  , KC_PGDN ,
        KC_PSCR , KC_UP   , KC_PAUS ,
        KC_LEFT , KC_DOWN , KC_RGHT
    )
};
