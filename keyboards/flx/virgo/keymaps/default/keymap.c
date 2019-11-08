#include "virgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_ESC, KC_F1, KC_F3, KC_F5, KC_F7, KC_F9, KC_F11, KC_PSCR, KC_PAUS, 
		KC_F2, KC_F4, KC_F6, KC_F8, KC_F10, KC_F12, KC_SLCK, 
		KC_GRV, KC_2, KC_4, KC_6, KC_8, KC_0, KC_EQL, KC_INS, KC_PGUP, 
		KC_1, KC_3, KC_5, KC_7, KC_9, KC_MINS, KC_BSPC, KC_HOME, 
		KC_TAB, KC_W, KC_R, KC_Y, KC_I, KC_P, KC_RBRC, KC_DEL, KC_PGDN, 
		KC_Q, KC_E, KC_T, KC_U, KC_O, KC_LBRC, KC_BSLS, KC_END, 
		KC_CAPS, KC_S, KC_F, KC_H, KC_K, KC_SCLN, KC_BSPC, 
		KC_A, KC_D, KC_G, KC_J, KC_L, KC_QUOT, KC_ENT, 
		KC_LSFT, KC_Z, KC_C, KC_B, KC_M, KC_DOT, KC_RSFT, 
		KC_BSLS, KC_X, KC_V, KC_N, KC_COMM, KC_SLSH, KC_RSFT, KC_UP, 
		KC_LCTL, KC_LALT, KC_B, KC_RGUI, KC_LEFT, KC_RGHT, 
		KC_LGUI, KC_SPC, KC_SPC, KC_RALT, KC_RCTL, KC_DOWN),
	
	KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_1, KC_3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_4, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_8, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_7, KC_9, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

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
		DDRE |= (1 << 6); PORTE &= ~(1 << 6);
	} else {
		DDRE &= ~(1 << 6); PORTE &= ~(1 << 6);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		DDRB |= (1 << 2); PORTB &= ~(1 << 2);
	} else {
		DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}