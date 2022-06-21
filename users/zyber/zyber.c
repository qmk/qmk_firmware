#include "zyber.h"


__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) { key_timer = timer_read(); }
	if (!process_caps_word(keycode, record)) { return false; }

	switch(keycode) {
		case CTRL_C_UP:
			if (record->event.pressed) {
				register_mods(MOD_BIT(KC_LCTRL));
			} else {
				unregister_mods(MOD_BIT(KC_LCTRL));
				if (timer_elapsed(key_timer) < TAPPING_TERM) {
					tap_code16(C(KC_UP));
				}
			}
			return false;
			break;

		case L1_EXPL:
			if (record->event.pressed) {
				layer_on(1);
			} else {
				layer_off(1);
				if (timer_elapsed(key_timer) < TAPPING_TERM) {
					tap_code16(C(KC_UP));
				}
			}
			return false;
			break;

		case CMD_SRH:
			if (record->event.pressed) {
				register_mods(MOD_BIT(KC_LCMD));
			} else {
				unregister_mods(MOD_BIT(KC_LCMD));
				if (timer_elapsed(key_timer) < TAPPING_TERM) {
					tap_code16(G(KC_SPC));
				}
			}
			return false;
			break;
	}
	//return true;
	return process_record_keymap(keycode, record);
}

/* Screenshoot */
void dance_SSHT_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		register_code(KC_LGUI);
		register_code(KC_LCTRL);
		register_code(KC_LSHIFT);
		register_code(KC_4);
		unregister_code(KC_LGUI);
		unregister_code(KC_LCTRL);
		unregister_code(KC_LSHIFT);
		unregister_code(KC_4);
	} else {
		register_code(KC_4);
		unregister_code(KC_4);
	}
}
void dance_SSHT_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		unregister_code(KC_LGUI);
		unregister_code(KC_LCTRL);
		unregister_code(KC_LSHIFT);
		unregister_code(KC_4);
	} else {
		unregister_code(KC_4);
	}
}

/* Å */
void dance_LBRC_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		register_code(KC_LALT);
		register_code(KC_LBRC);
		unregister_code(KC_LALT);
		unregister_code(KC_LBRC);
	} else {
		register_code(KC_LBRC);
		unregister_code(KC_LBRC);
	}
}
void dance_LBRC_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		unregister_code(KC_LALT);
		unregister_code(KC_LBRC);
	} else {
		unregister_code(KC_LBRC);
	}
}

/* Ö */
void dance_SCLN_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		register_code(KC_LALT);
		register_code(KC_SCLN);
		unregister_code(KC_LALT);
		unregister_code(KC_SCLN);
	} else {
		register_code(KC_SCLN);
		unregister_code(KC_SCLN);
	}
}
void dance_SCLN_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		unregister_code(KC_LALT);
		unregister_code(KC_SCLN);
	} else {
		unregister_code(KC_SCLN);
	}
}

/* Ä */
void dance_QUOT_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		register_code(KC_LALT);
		register_code(KC_QUOT);
		unregister_code(KC_LALT);
		unregister_code(KC_QUOT);
	} else {
		register_code(KC_QUOT);
		unregister_code(KC_QUOT);
	}
}
void dance_QUOT_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
		unregister_code(KC_LALT);
		unregister_code(KC_QUOT);
	} else {
		unregister_code(KC_QUOT);
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[SSHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_SSHT_finished, dance_SSHT_reset),
	[LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LBRC_finished, dance_LBRC_reset),
	[SCLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_SCLN_finished, dance_SCLN_reset),
	[QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_QUOT_finished, dance_QUOT_reset),
	[END_HOME] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_LEFT), LGUI(KC_RIGHT))
};
