#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_horizontal(
		KC_VOLU , _______ , _______ , _______ ,
        KC_MUTE , KC_MPRV , KC_MPLY , KC_MNXT ,
        KC_VOLD , _______ , _______ , _______
    )
};
