#include "AT101_Blackheart.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_ESC, 		KC_F2, 			KC_F4, 			KC_F6, 			KC_F8, 			KC_F10, 		KC_F12, 		KC_SLCK, 		KC_PMNS, 
				KC_F1, 			KC_F3, 			KC_F5, 			KC_F7, 			KC_F9, 			KC_F11, 		KC_PSCR, 		KC_PAUS, 		KC_PPLS, 
		KC_GRV, 		KC_2, 			KC_4, 			KC_6, 			KC_8, 			KC_0, 			KC_EQL, 		KC_INS, 		KC_PGUP, 		KC_PSLS, 
				KC_1, 			KC_3, 			KC_5, 			KC_7, 			KC_9, 			KC_MINS, 		KC_BSPC, 		KC_HOME, 		KC_NLCK, 		KC_PAST, 
		KC_TAB, 		KC_W, 			KC_R, 			KC_Y, 			KC_I, 			KC_P, 			KC_RBRC, 		KC_DEL, 		KC_PGDN, 		KC_P8, 
				KC_Q, 			KC_E, 			KC_T, 			KC_U, 			KC_O, 			KC_LBRC, 		KC_BSLS, 		KC_END, 		KC_P7, 			KC_P9, 
		KC_CAPS, 		KC_S, 			KC_F, 			KC_H, 			KC_K, 			KC_SCLN, 		KC_ENT, 		KC_P4, 			KC_P6, 
				KC_A, 			KC_D, 			KC_G, 			KC_J, 			KC_L, 			KC_QUOT, 		KC_P5, 			KC_PEQL, 
		KC_LSFT, 		KC_X, 			KC_V, 			KC_N, 			KC_COMM, 		KC_SLSH, 		MO(1), 			KC_UP, 			KC_P1, 			KC_P3, 
				KC_Z, 			KC_C, 			KC_B, 			KC_M, 			KC_DOT, 		KC_LSFT, 		KC_P2, 			KC_PENT, 
		KC_LCTL, 		KC_LALT, 		KC_RALT, 		KC_MENU, 		KC_LEFT, 		KC_RGHT, 		KC_PDOT, 
				KC_LGUI, 		KC_BSLS, 		KC_SPC, 		KC_RGUI, 		KC_RCTL, 		KC_DOWN, 		KC_P0),

	KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
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

void led_set_kb(uint8_t usb_led) {
  DDRB |= (1 << 4);
  DDRD |= (1 << 6) | (1 << 7);

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    PORTD |= (1 << 7);
  } else {
    PORTD &= ~(1 << 7);
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    PORTB |= (1 << 4);
  } else {
    PORTB &= ~(1 << 4);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    PORTD |= (1 << 6);
  } else {
    PORTD &= ~(1 << 6);
  }
}