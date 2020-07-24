#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 
		KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC, 
		KC_ESC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 
		KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, 
		KC_PGUP, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, 
		KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, 
		KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 
		KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, 
		KC_LCTL, KC_LALT, KC_SPC, LT(1, KC_SPC), 
		KC_SPC, KC_RALT, KC_RCTL),

	[_FN] = LAYOUT(
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F5, KC_F6, KC_F7, 
		KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_RGHT, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS),
};



void matrix_init_user(void) {
//  CapsLock LED 
  setPinOutput(D6);
  writePinLow(D6);
//  NumLock LED
  setPinOutput(D7);
  writePinLow(D7);
//  ScrollLock LED to output and low
  setPinOutput(D4);
  writePinLow(D4);
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(D7);
  } else {
    writePinLow(D7);
  }
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(D6);
  } else {
    writePinLow(D6);
  }

  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(D4);
  } else {
    writePinLow(D4);
  }

}


void encoder_update_user(uint8_t index, bool clockwise) 
{
    if (index == 0) 
	{ /* First encoder */
        	if (clockwise) 
		{
            		tap_code(KC_DOWN);
        	} 
		else 
		{
            		tap_code(KC_UP);
        	}
        } 
    else if (index == 1) 
	{ /* Second encoder */  
        	if (clockwise) 
		{
            		tap_code(KC_DOWN);
        	} 
		else 
		{
            		tap_code(KC_UP);
        	}
    	}
}
