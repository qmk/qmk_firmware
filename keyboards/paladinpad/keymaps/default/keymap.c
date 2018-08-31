#include "paladinpad.h"

const uint16_t PROGMEM fn_actions[] = {};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* DEFAULT */
	KEYMAP(
		MO(1), KC_PEQL, KC_PSLS, KC_PAST,
		KC_P7, KC_P8, KC_P9, KC_PMNS, 
		KC_P4, KC_P5, KC_P6, KC_PPLS,
		KC_P1, KC_P2, KC_P3, KC_NO,
		KC_P0, KC_NO, KC_PDOT, KC_PENT), 

    /* FUNCTION */
	KEYMAP(
		KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS,
        RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS,
        RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, RESET, KC_NLCK)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	// keyevent_t event = record->event;

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}


