#include "soy20.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_PMNS, KC_PAST, KC_PSLS, TG(1),
		KC_PPLS, KC_P9, KC_P8, KC_P7,
		KC_PPLS, KC_P6, KC_P5, KC_P4,
		KC_PENT, KC_P3, KC_P2, KC_P1,
		KC_PENT, KC_PDOT, KC_P0, KC_P0),

	[1] = LAYOUT(
	    KC_NLCK, KC_TRNS, KC_PSCR, KC_TRNS,
		KC_TRNS, KC_PGUP, KC_UP, KC_HOME,
		KC_TRNS, KC_RGHT, KC_NO, KC_LEFT,
		KC_TRNS, KC_PGDN, KC_DOWN, KC_END,
		RESET, KC_DEL, KC_INS, KC_INS),

	[2] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
