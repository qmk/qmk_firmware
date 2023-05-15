#include "kb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_1, KC_2, 
		KC_3, KC_4),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	keyevent_t event = record->event;

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