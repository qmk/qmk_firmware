#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_F1, 	KC_F2,  	KC_ESC,  KC_1,   KC_2, 	KC_3,    KC_4, 	KC_5, 	KC_6, 	KC_7, 	KC_8, 	KC_9,  KC_0, 	KC_MINS, KC_EQL,  KC_BSPC, 		KC_NLCK, 	KC_SLCK, 	MO(1), 
		KC_F3, 	KC_F4,  	KC_TAB,  KC_Q,   KC_W, 	KC_E,    KC_R, 	KC_T, 	KC_Y, 	KC_U, 	KC_I, 	KC_O,  KC_P, 	KC_LBRC, KC_RBRC, KC_ENT,		KC_P7,   KC_P8,   KC_P9, 	KC_PAST,
		KC_F5, 	KC_F6,  	KC_LCTRL,KC_A,   KC_S, 	KC_D,    KC_F, 	KC_G, 	KC_H, 	KC_J, 	KC_K, 	KC_L,  KC_SCLN, KC_QUOT,   						KC_P4, 	 KC_P5,   KC_P6, 	KC_PMNS,
		KC_F7, 	KC_F8,  	KC_LSFT, KC_Z,   KC_X, 	KC_C,    KC_V, 	KC_B, 	KC_N, 	KC_M, 	KC_COMM,KC_DOT,KC_SLSH, KC_RSFT, KC_BSLS, 				KC_P1,   KC_P2,   KC_P3,    KC_PPLS,
		KC_F9, 	KC_F10, 	KC_LALT, KC_GRV, 							KC_SPC, 					 		 				 KC_CAPS, 					KC_P0,   KC_PDOT
		),

	LAYOUT(
		_______, _______, 	 RESET,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 		_______, 	_______,  _______, 
		_______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 		_______, _______, _______, _______,
		_______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 				 		_______, _______, _______, _______,
		_______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 		 		_______, _______, _______, _______,
		_______, _______, 	_______, _______, 								_______, 										_______,				 				_______,  	_______
		),

	LAYOUT_z150_tkl(
		KC_F1, 	KC_F2, 		KC_ESC,  KC_1, 	  KC_2,   KC_3, 	 KC_4, 	KC_5, 	KC_6, KC_7, KC_8, 	 KC_9, 	 KC_0, 	  KC_MINS, KC_EQL, 	KC_BSPC, 		KC_INS,  KC_HOME, KC_PGUP, 
		KC_F3, 	KC_F4, 		KC_TAB,  KC_Q, 	  KC_W,   KC_E, 	 KC_R, 	KC_T, 	KC_Y, KC_U, KC_I, 	 KC_O, 	 KC_P, 	  KC_LBRC, KC_RBRC, KC_BSLS, 		KC_DEL,  KC_END,  KC_PGDN, 
		KC_F5, 	KC_F6, 		KC_CAPS, KC_A, 	  KC_S,   KC_D, 	 KC_F, 	KC_G, 	KC_H, KC_J, KC_K, 	 KC_L, 	 KC_SCLN, KC_QUOT, KC_ENT, 			 		XXXXXXX, XXXXXXX, XXXXXXX, 
		KC_F7, 	KC_F8, 		KC_LSFT, KC_BSLS, KC_Z,   KC_X,      KC_C, 	KC_V, 	KC_B, KC_N, KC_M,    KC_COMM,KC_DOT,  KC_SLSH, KC_RSFT, MO(1), 			XXXXXXX, KC_UP,   XXXXXXX, 
		KC_F9, 	KC_F10,		KC_LCTL, KC_LGUI, KC_LALT,		 		KC_SPC, 							 KC_RALT, KC_RGUI, KC_MENU, KC_RCTL, 			KC_LEFT, KC_DOWN, KC_RGHT
		),

	LAYOUT_z150_tkl(
		_______, _______, 	 RESET,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 			_______, _______, _______, 
		_______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 			_______, _______, _______, 
		_______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 					_______, _______, _______, 
		_______, _______, 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 					_______, _______, _______, 
		_______, _______, 	_______, _______, _______, _______, 		_______,                            		_______, _______, _______, _______, 			_______, _______, _______
		),
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
  DDRB |= (1 << 0);
  DDRE |= (1 << 6) | (1 << 7);

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    PORTE |= (1 << 7);
  } else {
    PORTE &= ~(1 << 7);
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    PORTB |= (1 << 0);
  } else {
    PORTB &= ~(1 << 0);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    PORTE |= (1 << 6);
  } else {
    PORTE &= ~(1 << 6);
  }
}