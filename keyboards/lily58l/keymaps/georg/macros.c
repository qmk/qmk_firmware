#include QMK_KEYBOARD_H

#include "keymap.h"

uint16_t key_timer;

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case CUSTOM_SHIFT_QUOT:  // handle right mod tap shift
			if (record->event.pressed) { 
				key_timer = timer_read(); 
				register_code(KC_RSFT); 
			} else if (key_timer > 0) { 
				key_timer = 0;
				unregister_code(KC_RSFT); 
				if (timer_elapsed(key_timer) / 1000 < TAPPING_TERM) 
					SEND_STRING(SS_TAP(X_QUOT)" "); 
			} 
			break;
    case KC_QUOT:  // '
		case KC_DQT:  // "
		case KC_GRAVE:  // `
		case KC_TILDE:  // ~
		case KC_CIRC:  // ^
		  if (record->event.pressed)
				SEND_STRING(" ");
		default:
			break;
	}
}
