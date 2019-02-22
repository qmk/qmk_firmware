#include "kb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

KEYMAP(
		LT(1, KC_F1), LT(2, KC_F2), LT(3, KC_F3), LT(4, KC_F4)  ),

	KEYMAP(
	    KC_TRNS, KC_MPRV , KC_MPLY,KC_MNXT),

	KEYMAP(
		KC_MUTE, KC_TRNS, KC_VOLD, KC_VOLU),

	KEYMAP(
		RGB_VAD, RGB_VAI, KC_TRNS, RGB_TOG),

	KEYMAP(
		RGB_HUD, RGB_HUI, RGB_MOD, KC_TRNS),


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
