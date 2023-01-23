#include QMK_KEYBOARD_H

#ifdef AUDIO_ENABLE
	float mushroom[][2] = SONG(MARIO_MUSHROOM);
#endif


extern keymap_config_t keymap_config;

// Complex Tapdance hoopla
typedef struct {
	bool is_press_action;
	int state;
} tap;

enum {
	SINGLE_TAP = 1,
	SINGLE_HOLD = 2,
	DOUBLE_TAP = 3,
	DOUBLE_HOLD = 4,
	TRIPLE_TAP = 5,
	TRIPLE_HOLD = 6,
};

// Tap dance enums
enum {
	X_AT_FUN = 0,
	RSHIFT,
	LSHIFT,
	TD_S,
	SLASH	
};

int cur_dance (qk_tap_dance_state_t *state);

void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);
void lshift_finished (qk_tap_dance_state_t *state, void *user_data);
void lshift_reset(qk_tap_dance_state_t *state, void *user_data);


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Modified Programmer Dvorak enums

enum planck_layers {
	_PDVORAK,
	_UPPER,
	_LOWER,
	_FUNCTION,
};

enum custom_keycodes {
	PDVK = SAFE_RANGE,
	KC_LAST,
	ALT_TAB
};

// For getting the last arg in shell line (SUPER THANKS to Drashna over on Discord)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t macro_timer;

  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }

  switch (keycode){
    case KC_LAST:
      if(record->event.pressed){
        macro_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTL));
        if (timer_elapsed(macro_timer) < 150) {
          SEND_STRING("!$");
        }
      }
    return false;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code16(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

#define PDVORAK MO(_PDVORAK)
#define LOWER MO(_LOWER)
#define UPPER MO(_UPPER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


	/* Programmer Dvorak */
	[_PDVORAK] = LAYOUT_planck_grid(
		  QK_GESC, KC_SCLN, KC_COMMA, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC,
   		KC_LAST, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, TD(TD_S), TD(SLASH),
   		TD(LSHIFT), KC_QUOT, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, TD(RSHIFT),
    	TD(X_AT_FUN), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, ALT_TAB, KC_SPACE, KC_ENTER, MT(MOD_LCTL | MOD_LSFT, KC_LGUI), KC_PGUP, KC_PGDN, LT(_LOWER, KC_PLUS)
   	),
	
	[_UPPER] = LAYOUT_planck_grid(
		KC_GRAVE, KC_AMPR, KC_PERC, KC_NO, KC_NO, KC_EQL, KC_ASTR, KC_NO, KC_NO, KC_EXLM, KC_HASH, KC_TRNS,
		KC_PLUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS
	),

	[_LOWER] = LAYOUT_planck_grid(
		KC_DLR, KC_7, KC_5, KC_3, KC_1, KC_9, KC_0, KC_2, KC_4, KC_6, KC_8, KC_TRNS,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, CK_DOWN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS
	),

	[_FUNCTION] = LAYOUT_planck_grid(
		KC_F11, KC_F7, KC_F5, KC_F3, KC_F1, KC_F9, KC_F12, KC_F2, KC_F4, KC_F6, KC_F8, QK_BOOT,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS
	),
};


// Super crazy tap dancing stuff - see quad dance in feature_tap_dance.md

int cur_dance (qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		// key not interrupted, but still held sends 'HOLD'
		else return SINGLE_HOLD;
	}
	else if (state->count == 2) {
		if (state->interrupted || !state->pressed) return DOUBLE_TAP;
		else return DOUBLE_HOLD;
	}
	else if (state->count == 3) {
		if (state->interrupted || !state->pressed)return TRIPLE_TAP;
		else return TRIPLE_HOLD;
	}
	else return 8; // magic number that i dont believe works. 
}

// instance of tap for the 'X' dance.
static tap xtap_state = {
	.is_press_action = true,
	.state = 0
};

// registering keypresses
void x_finished (qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch (xtap_state.state) {
		case SINGLE_TAP: register_code16(KC_AT); break;
		case SINGLE_HOLD: set_oneshot_layer(_UPPER, ONESHOT_START); break;
		case DOUBLE_TAP: set_oneshot_layer(_FUNCTION, ONESHOT_START); break;
		case DOUBLE_HOLD: reset_keyboard(); break;
	}
}

void lshift_finished (qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch (xtap_state.state) {
		case SINGLE_TAP: register_code16(KC_LSFT); register_code16(KC_9); break;
		case SINGLE_HOLD: register_code16(KC_LSFT); break;
		case DOUBLE_TAP: register_code16(KC_LBRC); break;
		case TRIPLE_TAP: register_code16(KC_LSFT); register_code16(KC_LBRC); break;
	}
}
void s_finished (qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch (xtap_state.state) {
		case SINGLE_TAP: register_code16(KC_S); break;
		case DOUBLE_TAP: register_code16(KC_MINUS); break;
		case TRIPLE_TAP: register_code16(KC_LSFT); register_code16(KC_MINUS); break;
	}
}

void rshift_finished (qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch (xtap_state.state) {
		case SINGLE_TAP: register_code16(KC_LSFT); register_code16(KC_0); break;
		case SINGLE_HOLD: register_code16(KC_RSFT); break;
		case DOUBLE_TAP: register_code16(KC_RBRC); break;
		case TRIPLE_TAP: register_code16(KC_LSFT); register_code16(KC_RBRC); break;
	}
}

// forgetting keypresses

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (xtap_state.state) {
		case SINGLE_TAP: unregister_code16(KC_AT); break;
		case SINGLE_HOLD: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
		case DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
		case DOUBLE_HOLD: reset_keyboard(); break;
	}
	xtap_state.state = 0;
}
void lshift_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (xtap_state.state) {
		case SINGLE_TAP: unregister_code16(KC_9); unregister_code16(KC_LSFT); break;
		case SINGLE_HOLD: unregister_code16(KC_LSFT); break;
		case DOUBLE_TAP: unregister_code16(KC_LBRC); break;
		case TRIPLE_TAP: unregister_code16(KC_LBRC); unregister_code16(KC_LSFT); break;
	}
	xtap_state.state = 0;
}

void rshift_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (xtap_state.state) {
		case SINGLE_TAP: unregister_code16(KC_0); unregister_code16(KC_LSFT); break;
		case SINGLE_HOLD: unregister_code16(KC_RSFT); break;
		case DOUBLE_TAP: unregister_code16(KC_RBRC); break;
		case TRIPLE_TAP: unregister_code16(KC_RBRC); unregister_code16(KC_LSFT); break;
	}
	xtap_state.state = 0;
}
void s_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (xtap_state.state) {
		case SINGLE_TAP: unregister_code16(KC_S); break;
		case DOUBLE_TAP: unregister_code16(KC_MINUS); break;
		case TRIPLE_TAP: unregister_code16(KC_MINUS); unregister_code16(KC_LSFT);  break;
	}
	xtap_state.state = 0;
}
qk_tap_dance_action_t tap_dance_actions[] = {
	[X_AT_FUN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
	[LSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
	[RSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),
	[TD_S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_finished, s_reset),
	[SLASH] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BSLS),

};

void shutdown_user(void) { clear_keyboard(); }
