// Tap Dances
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

void dance_esc_tab (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return register_code16(KC_ESC);
    else return register_code16(KC_TAB);
  }
}

void dance_esc_tab_reset (qk_tap_dance_state_t *state, void *user_data) {
  unregister_code16(KC_ESC);
  unregister_code16(KC_TAB);
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
    * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
    * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
    * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }

  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap atap_state = {
  .is_press_action = true,
  .state = 0
};

void a_finished (qk_tap_dance_state_t *state, void *user_data) {
  atap_state.state = cur_dance(state);
  switch (atap_state.state) {
    case SINGLE_TAP: register_code16(KC_A); break;
    case SINGLE_HOLD: register_code16(KC_LCTRL); break;
    case DOUBLE_TAP: register_code16(LCTL(KC_A)); break;
    case DOUBLE_HOLD: register_code16(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code16(KC_A); unregister_code16(KC_A); register_code16(KC_A);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void a_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (atap_state.state) {
    case SINGLE_TAP: unregister_code16(KC_A); break;
    case SINGLE_HOLD: unregister_code16(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code16(LCTL(KC_A)); break;
    case DOUBLE_HOLD: unregister_code16(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_A);
  }
  atap_state.state = 0;
}

static tap slshtap_state = {
  .is_press_action = true,
  .state = 0
};

void slsh_finished (qk_tap_dance_state_t *state, void *user_data) {
  slshtap_state.state = cur_dance(state);
  switch (slshtap_state.state) {
    case SINGLE_TAP: register_code16(KC_SLSH); break;
    case SINGLE_HOLD: register_code16(KC_RSFT); break;
    case DOUBLE_TAP: register_code16(KC_ENT); break;
    case DOUBLE_HOLD: register_code16(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code16(KC_SLSH); unregister_code16(KC_SLSH); register_code16(KC_SLSH);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void slsh_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (slshtap_state.state) {
    case SINGLE_TAP: unregister_code16(KC_SLSH); break;
    case SINGLE_HOLD: unregister_code16(KC_RSFT); break;
    case DOUBLE_TAP: unregister_code16(KC_ENT); break;
    case DOUBLE_HOLD: unregister_code16(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLSH);
  }
  slshtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TAB_ESC]   = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_esc_tab, dance_esc_tab_reset),
  [TD_Q_ESC]     = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [TD_QUES_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, slsh_finished, slsh_reset,200),
  [TD_CTRL_Z]    = ACTION_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
  [TD_CTRL_Y]    = ACTION_TAP_DANCE_DOUBLE(KC_Y, LCTL(KC_Y)),
  [TD_CTRL_C]    = ACTION_TAP_DANCE_DOUBLE(KC_C, LCTL(KC_C)),
  [TD_CTRL_V]    = ACTION_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),
  [TD_CTRL_A]    = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, a_finished, a_reset, 175),
  [TD_O_BSLS]    = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_BSLS),
  [TD_QUOTE]     = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DQT),
  [TD_QCOL]      = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_SCLN),
  [TD_WTAB]      = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_TAB)
};

/* Per key tapdance configs */
uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case RSFT_T(KC_DOT):
      return 150;
    case KC_NUM_SPC:
      return 225;
    case LCTL_T(KC_TAB):
      return 120;
    case LSFT_T(KC_T):
      return 200;
    case LALT_T(KC_C):
      return 200;
	case RGUI_T(KC_O):
	  return 350;
	case LGUI_T(KC_A):
	  return 300;
    default:
      return TAPPING_TERM;
  }
};

bool get_ignore_mod_tap_interrupt(uint16_t keycode) {
  switch (keycode) {
    case KC_Z_SF:
      return true;
    case LSFT_T(KC_T):
      return false;
    default:
      return false;
  }
}

bool get_tapping_force_hold(uint16_t keycode) {
  switch (keycode) {
    case KC_Z_SF:
      return false;
    case TD(TD_QUES_ENT):
      return false;
    default:
      return false;
  }
}

bool get_permissive_hold(uint16_t keycode) {
  switch (keycode) {
    case RGUI_T(KC_O):
      return true;
    case LGUI_T(KC_A):
        return true;
    default:
      return false;
  }
}
