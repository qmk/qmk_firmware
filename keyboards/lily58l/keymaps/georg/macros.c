#include QMK_KEYBOARD_H

#include "keymap.h"
#include "settings.h"


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
	switch (keycode) {
		case TOG_DK:
			if (record->event.pressed) {
				user_config.dead_keys = !user_config.dead_keys;
				eeconfig_update_user(user_config.raw);
			}
			return false;
	}
	return true;
}

uint16_t key_timer;
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case CUSTOM_SHIFT_QUOT:  // handle right mod tap shift
			if (record->event.pressed) { 
				key_timer = timer_read(); 
				register_code(KC_RSFT); 
			} else if (key_timer > 0) { 
				unregister_code(KC_RSFT); 
				if (timer_elapsed(key_timer) < TAPPING_TERM) {
					SEND_STRING(SS_TAP(X_QUOT)); 
					if (user_config.dead_keys)
						SEND_STRING(" ");
				}
				key_timer = 0;
			} 
			break;
    case KC_QUOT:  // '
		case KC_DQT:  // "
		case KC_GRAVE:  // `
		case KC_TILDE:  // ~
		case KC_CIRC:  // ^
		  if (record->event.pressed && user_config.dead_keys)
				SEND_STRING(" ");
			break;
		default:
			break;
	}
}
