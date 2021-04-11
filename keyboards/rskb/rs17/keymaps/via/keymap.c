#include "rs17.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		MO(1), KC_PSLS, KC_PAST, KC_PMNS, 
		KC_P7, KC_P8, KC_P9, 
		KC_P4, KC_P5, KC_P6, KC_PPLS, 
		KC_P1, KC_P2, KC_P3, 
		KC_P0, KC_PDOT, KC_PENT),

	KEYMAP(
		KC_TRNS, RGB_TOG, RGB_MOD, KC_VOLD, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_BSPC, RESET, KC_MUTE)

};

