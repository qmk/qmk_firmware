#include "snowkuma.h"

// qk_tap_dance_action_t tap_dance_actions[] = {
//   [TD_ESC_CAPS]     = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
//   [TD_TAB_CTRLTAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LCTL(KC_TAB)),
//   [TD_GRV_CTRLGRV]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, LGUI(KC_GRV)),
//   [TD_GUI_GUISPC]   = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC)),
//   [TD_W_CTRLW]      = ACTION_TAP_DANCE_DOUBLE(KC_W, LGUI(KC_W)),
//   [TD_Q_GUIQ]       = ACTION_TAP_DANCE_DOUBLE(KC_Q, LGUI(KC_Q)),
// };


// Tap Dance Definitions
void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >=3) {
		// Reset the keyboard if you tap the key more than three times
		reset_keyboard();
		reset_tap_dance(state);
	}
};

void zoom_toggle(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    register_code(KC_A);
    unregister_code(KC_A);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
  } else if (state->count >= 2) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
  }
}

void copy_cut(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >= 2) {
		register_code(KC_LGUI);
		register_code(KC_X);
		unregister_code(KC_X);
		unregister_code(KC_LGUI);
	} else {
		register_code(KC_LGUI);
		register_code(KC_C);
		unregister_code(KC_C);
		unregister_code(KC_LGUI);
	}
};

void tilde_home(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count > 2) {
		register_code(KC_LSFT);
		register_code(KC_GRV);
	}
	else {
		register_code(KC_LSFT);
		register_code(KC_GRV);
		if (state->count > 1) {
			// Outputs ~/ if tilde tapped twice
			unregister_code(KC_GRV);
			unregister_code(KC_LSFT);
			register_code(KC_SLSH);
		}
	}
} 

void tilde_reset(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 2) {
		unregister_code(KC_SLSH);
	} else {
		unregister_code(KC_GRV);
		unregister_code(KC_LSFT);
	}
}


qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_COPYCUT]    = ACTION_TAP_DANCE_FN (copy_cut),
  [TD_LBRC_BACK]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, LGUI(KC_LBRC)),
  [TD_RBRC_FWD]   = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, LGUI(KC_RBRC)),
	[TD_RESET]      = ACTION_TAP_DANCE_FN (safe_reset),
	[TD_TILD]       = ACTION_TAP_DANCE_FN_ADVANCED (NULL, tilde_home, tilde_reset),
  [TD_ZOOM]       = ACTION_TAP_DANCE_FN (zoom_toggle) 
};
