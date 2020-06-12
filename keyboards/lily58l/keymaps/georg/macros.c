#include QMK_KEYBOARD_H

#include "keymap.h"
#include "settings.h"

bool handle_key_swap(uint16_t keycode, keyrecord_t* record);

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
	switch (keycode) {
		case TOG_DK:
			if (record->event.pressed) {
				user_config.dead_keys = !user_config.dead_keys;
				eeconfig_update_user(user_config.raw);
			}
			return false;
    case TOG_SCE:
      if (record->event.pressed) {
        user_config.switch_caps_esc = !user_config.switch_caps_esc;
        eeconfig_update_user(user_config.raw);
      }
      return false;
	}

	if (!handle_key_swap(keycode, record))
		return false;

	return true;
}

bool key_swap_helper(uint16_t new_key, uint16_t keycode, keyrecord_t* record) {
	if (user_config.switch_caps_esc) {
		if (keycode >> 13) {
			if (record->event.pressed)
				tap_code(new_key);
		} else if (record->event.pressed)
			register_code(new_key);
		else
			unregister_code(new_key);
		return false;
	}
	return true;
}

bool handle_key_swap(uint16_t keycode, keyrecord_t* record) {
	if ((keycode >> 13) && !record->tap.count)
		return true;

	switch (keycode & 0xFF) {
    case KC_ESC:
      return key_swap_helper(KC_CAPS, keycode, record);
    case KC_CAPS:
			return key_swap_helper(KC_ESC, keycode, record);
	}

	return true;
}


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint16_t code = keycode & ((keycode >> 13) ? 0xFF : 0x1FFF);

	switch (code) {
    case KC_QUOT:  // '
		case KC_DQT:  // "
		case KC_GRAVE:  // `
		case KC_TILDE:  // ~
		case KC_CIRC:  // ^
			if (user_config.dead_keys && record->event.pressed 
				&& ((keycode >> 13) != 0b011 || record->tap.count > 0))
				SEND_STRING(" ");
			break;
		default:
			break;
	}
}
