#include QMK_KEYBOARD_H

#define _______ KC_TRNS

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

enum custom_keycodes {
	KX_UMLAUT_A = SAFE_RANGE,
	KX_UMLAUT_O,
	KX_UMLAUT_U,
	KX_UMLAUT_S,
	KX_EURO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_F1,   KC_F2,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_NO,
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSPC,
    KC_F5,   KC_F6,   MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,  KC_ENT,
    KC_F7,   KC_F8,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  MO(2),
    KC_F9,   KC_F10,  KC_LCTL, KC_NO,   KC_LALT,                                     KC_SPC,                             KC_RALT, KC_NO,    KC_RCTL
  ),
   [1] = LAYOUT(
    KC_F11,  KC_F12,  KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______,  RESET,
    _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, KC_PGDN, _______, _______, _______,                                     _______,                            _______, _______,  _______
  ),
  [2] = LAYOUT(
    KX_NAVYSEAL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______, KX_EURO, _______, _______, _______, KX_UMLAUT_U, _______, KX_UMLAUT_O, KC_PSCR, _______, _______,  KC_DEL,
    _______, _______, _______, KX_UMLAUT_A, KX_UMLAUT_S, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______,                                     _______,                            _______, _______,  _______
  ),

};

bool g_bOsNumLockOn = false;

void led_set_user(uint8_t usb_led) {
	
	// Update saved numlock state
	
	if (usb_led & (1<<USB_LED_NUM_LOCK)) 
	{
		g_bOsNumLockOn = true;
	} 
	else 
	{
		g_bOsNumLockOn = false;
	}
}

void send_altcode(uint16_t mask, keyrecord_t *record) {
	
	/* Sends the "alt code" defined in mask, i.e. send_altcode(1234) 
	holds left alt while sending KP_1, KP_2, KP_3 and KP_4 taps, 
	then releases left alt if it wasn't being held by the user. 
	
	NOTE: If your alt code starts with a 0, leave that out, else the
	mask will be treated as octal and your firmware won't compile.
	send_altcode(123) will output KP_0, KP_1, KP_2 and KP_3. */
	
	// Check & save mod state
	
	static uint8_t lalt_mask;
	lalt_mask = keyboard_report->mods & KC_LALT;
	
	// Check & save numlock state
	
	bool bNumLockWasOn = g_bOsNumLockOn;
	
	// Split up the mask into its 4 decimals
	
	static uint16_t kp[4];
	
	kp[0] = mask / 1000;
	kp[1] = mask / 100 - kp[0] * 100;
	kp[2] = mask / 10 - kp[0] * 1000 - kp[1] * 10;
	kp[3] = mask - kp[0] * 1000 - kp[1] * 100 - kp[2] * 10;
	
	// Convert to keycodes
	
	for (uint8_t i=0; i<=3; i++) {
		switch(kp[i]) {
			case 0:
				kp[i] = KC_KP_0; break;
			case 1:
				kp[i] = KC_KP_1; break;
			case 2:
				kp[i] = KC_KP_2; break;
			case 3:
				kp[i] = KC_KP_3; break;
			case 4:
				kp[i] = KC_KP_4; break;
			case 5:
				kp[i] = KC_KP_5; break;
			case 6:
				kp[i] = KC_KP_6; break;
			case 7:
				kp[i] = KC_KP_7; break;
			case 8:
				kp[i] = KC_KP_8; break;
			case 9:
				kp[i] = KC_KP_9; break;
		}
	}
	
	// Put ALT into pressed state
	
	if (!lalt_mask) {
		register_code(KC_LALT);
		send_keyboard_report();
	}
	
	// If not enabled, enable numlock
	
	if (!bNumLockWasOn) {
			register_code(KC_LNUM);
			send_keyboard_report();
	}
	
	// The send_keyboard_report() spam is not pretty, but necessary.
	
	add_key(kp[0]);
	send_keyboard_report();
	del_key(kp[0]);
	send_keyboard_report();
	add_key(kp[1]);
	send_keyboard_report();		
	del_key(kp[1]);
	send_keyboard_report();
	add_key(kp[2]);
	send_keyboard_report();		
	del_key(kp[2]);
	send_keyboard_report();
	add_key(kp[3]);
	send_keyboard_report();
	del_key(kp[3]);
	send_keyboard_report();
	
	// If user wasn't pressing ALT, release it
	
	if (!lalt_mask) {
		unregister_code(KC_LALT);
	}
	
	send_keyboard_report();
	
	// If it wasn't enabled before, disable numlock
	
	if (!bNumLockWasOn) {
			unregister_code(KC_LNUM);
			send_keyboard_report();
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static uint8_t shift_mask;
	shift_mask = get_mods()&MODS_SHIFT_MASK;
	
	if (record->event.pressed) {
		switch(keycode) {
		case KX_UMLAUT_A:
			if (shift_mask) { // We want a capital version of the German A Umlaut 'cause shift is pressed
				unregister_code(KC_LSFT); // Gotta temporarily disable both shift keys, else this whole thing may behave oddly
				unregister_code(KC_RSFT);
				send_keyboard_report();
				
				send_altcode(196, record); // This is where the magic happens
				
				if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT); // Restore shift keys to previous state
				if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
				
				send_keyboard_report();
			} else {
				send_altcode(228, record); // ä
			}
			return false;
			break;
		case KX_UMLAUT_O:
			if (shift_mask) {
				unregister_code(KC_LSFT);
				unregister_code(KC_RSFT);
				send_keyboard_report();
				
				send_altcode(214, record); // Ö
				
				if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
				if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
				
				send_keyboard_report();
			} else {
				send_altcode(246, record); // ö
			}
			return false;
			break;
		case KX_UMLAUT_U:
			if (shift_mask) {
				unregister_code(KC_LSFT);
				unregister_code(KC_RSFT);
				send_keyboard_report();
				
				send_altcode(220, record); // Ü
				
				if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
				if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
				
				send_keyboard_report();
			} else {
				send_altcode(252, record); // ü
			}
			return false;
			break;
		case KX_UMLAUT_S:
			send_altcode(223, record); // ß
			return false;
			break;
		case KX_EURO:
			send_altcode(128, record); // ß
			return false;
			break;
		}
	}
	
	return true;
}

void matrix_scan_user(void) {

//Layer LED indicators
    uint32_t layer = layer_state;

    if (layer & (1<<1)) {
        _60xt_fn_led_on();
    } else {
        _60xt_fn_led_off();
    }

};