#include "nstickney.h"

// Tap Dancing
void dance_layer (qk_tap_dance_state_t *state, void *user_data) {
	switch (state -> count) {
		case 1: tap_code(KC_APP); break;
		case 2: layer_invert(NUMP); break;
		case 3: layer_invert(SYMB); break;
		case 4: layer_invert(SYSH); break;
		default: break;
	}
};

void dance_lock_finished (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1: register_code(KC_LGUI); break;
		case 2: register_code(KC_NLCK); break;
		case 3: register_code(KC_CAPS); break;
		case 4: register_code(KC_SLCK); break;
		default: break;
	}
};

void dance_lock_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1: unregister_code(KC_LGUI); break;
		case 2: unregister_code(KC_NLCK); break;
		case 3: register_code(KC_CAPS); break;
		case 4: register_code(KC_SLCK); break;
		default: break;
	}
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[LOCKS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lock_finished, dance_lock_reset),
	[LAYERS] = ACTION_TAP_DANCE_FN(dance_layer)
};

void eeconfig_init_user (void) {
	set_unicode_input_mode(UC_LNX); // Linux
	//set_unicode_input_mode(UC_OSX); // Mac OSX
	//set_unicode_input_mode(UC_WIN); // Windows (with registry key, see wiki)
	//set_unicode_input_mode(UC_WINC); // Windows (with WinCompose, see wiki)
};