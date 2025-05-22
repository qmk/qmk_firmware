#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		UG_TOGG,        UG_SATU,        UG_VALU,
		        UG_HUED,        UG_HUEU,
		UG_NEXT,        UG_SATD,        UG_VALD,
		BL_STEP,
		KC_NO,  KC_NO,  KC_NO
	)
};

const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {255, 170, 85};
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {255, 170, 85};
