#define TD_SHIFT_CAPS    1
#define TD_ESC_FUNC      2
#define TD_GARAKE1       3
#define TD_GARAKE2       4
#define TD_GARAKE3       5
#define TD_GARAKE4       6
#define TD_GARAKE5       7
#define TD_GARAKE6       8
#define TD_GARAKE7       9
#define TD_GARAKE8       10
#define TD_GARAKE9       11
#define TD_GARAKE0_RAISE 12

#define send_keycode(key) { register_code(key); unregister_code(key); }

typedef enum { NONE, INTERRUPTED, SINGLE_TAP, SINGLE_HOLD, DOUBLE_TAP, DOUBLE_HOLD } dance_action_t;

dance_action_t dance_state_to_action (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else if (state->interrupted) return INTERRUPTED;
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else return NONE; //magic number. At some point this method will expand to work for more presses
}

/* ---- */

/** Enhanced "Shift"
 * - Single tap to capitalize the next character
 * - Double tap to CapsLock
 * - Hold (or interrupt) to "Shift"
 */

dance_action_t shift_action;

void shift_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (shift_action == DOUBLE_TAP) {
        unregister_code(KC_LSFT);
        shift_action = NONE;
       #ifdef RGBLIGHT_ENABLE
        rgb_unoverride_color();
       #endif
        return;
    }
    switch (shift_action = dance_state_to_action(state)) {
      case SINGLE_HOLD: case INTERRUPTED:
       register_code(KC_LSFT);
       break;
      case SINGLE_TAP:
       unregister_code(KC_LSFT);
       set_oneshot_mods(MOD_LSFT);
       break;
      case DOUBLE_TAP:
       register_code(KC_LSFT);
      #ifdef RGBLIGHT_ENABLE
       rgb_override_color(250, 135, 250, 135);
      #endif
       break;
      default: break;
    }
}

void shift_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (shift_action) {
      case SINGLE_HOLD: case INTERRUPTED: unregister_code(KC_LSFT); break;
      default: break;
    }
}

/* ---- */

/** Enhanced "Esc"
 * - Tap to "Esc + Lang2" (escape then turn off the IME)
 * - Hold (or interrupt) to "FN"
 */

dance_action_t esc_action;

void esc_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (esc_action = dance_state_to_action(state)) {
   case SINGLE_HOLD: case INTERRUPTED: layer_on(FUNCTION); break;
   case SINGLE_TAP: send_keycode(KC_ESC); send_keycode(KC_LANG2); break;
   default: break;
  }
}

void esc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (esc_action) {
   case SINGLE_HOLD: case INTERRUPTED: layer_off(FUNCTION); break;
   default: break;
  }
}

/* ---- */

/** Garake keys
 * - Provides garake-like keys
 * - Example:
 *   - Tap garake8 once (within TAPPING_TERM) to send "a"
 *   - Tap garake8 twice (within TAPPING_TERM) to send "b"
 *   - Tap garake8 three (within TAPPING_TERM) times to send "c"
 */

void garake7 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: register_code(KC_LSFT); send_keycode(KC_2); unregister_code(KC_LSFT); break; /* @ */
   case 2: register_code(KC_LSFT); send_keycode(KC_3); unregister_code(KC_LSFT); break; /* # */
   case 0: register_code(KC_LSFT); send_keycode(KC_7); unregister_code(KC_LSFT); break; /* & */
   default: break;
  }
}

void garake8 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: send_keycode(KC_A); break;
   case 2: send_keycode(KC_B); break;
   case 0: send_keycode(KC_C); break;
   default: break;
  }
}

void garake9 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: send_keycode(KC_D); break;
   case 2: send_keycode(KC_E); break;
   case 0: send_keycode(KC_F); break;
   default: break;
  }
}

void garake4 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: send_keycode(KC_G); break;
   case 2: send_keycode(KC_H); break;
   case 0: send_keycode(KC_I); break;
   default: break;
  }
}

void garake5 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: send_keycode(KC_J); break;
   case 2: send_keycode(KC_K); break;
   case 0: send_keycode(KC_L); break;
   default: break;
  }
}

void garake6 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: send_keycode(KC_M); break;
   case 2: send_keycode(KC_N); break;
   case 0: send_keycode(KC_O); break;
   default: break;
  }
}

void garake1 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 4) {
   case 1: send_keycode(KC_P); break;
   case 2: send_keycode(KC_Q); break;
   case 3: send_keycode(KC_R); break;
   case 0: send_keycode(KC_S); break;
   default: break;
  }
}

void garake2 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 3) {
   case 1: send_keycode(KC_T); break;
   case 2: send_keycode(KC_U); break;
   case 0: send_keycode(KC_V); break;
   default: break;
  }
}

void garake3 (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count % 4) {
   case 1: send_keycode(KC_W); break;
   case 2: send_keycode(KC_X); break;
   case 3: send_keycode(KC_Y); break;
   case 0: send_keycode(KC_Z); break;
   default: break;
  }
}

/* ---- */

/** garake0 works as "garake-raise" when held */

bool garake0_raised = false;

void garake0_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed || state->interrupted) {
    layer_on(GARARAISE);
    garake0_raised = true;
    return;
  }
  switch (state->count % 4) {
   case 1: send_keycode(KC_DOT); break;
   case 2: send_keycode(KC_COMM); break;
   case 3: register_code(KC_LSFT); send_keycode(KC_1); unregister_code(KC_LSFT); break; /* ! */
   case 0: register_code(KC_LSFT); send_keycode(KC_SLSH); unregister_code(KC_LSFT); break; /* ? */
   default: break;
  }
}

void garake0_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (garake0_raised) {
    return layer_off(GARARAISE);
    garake0_raised = false;
  }
}

/* ---- */

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished,  shift_reset),
    [TD_ESC_FUNC]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished,  esc_reset),
    [TD_GARAKE7]       = ACTION_TAP_DANCE_FN(garake7),
    [TD_GARAKE8]       = ACTION_TAP_DANCE_FN(garake8),
    [TD_GARAKE9]       = ACTION_TAP_DANCE_FN(garake9),
    [TD_GARAKE4]       = ACTION_TAP_DANCE_FN(garake4),
    [TD_GARAKE5]       = ACTION_TAP_DANCE_FN(garake5),
    [TD_GARAKE6]       = ACTION_TAP_DANCE_FN(garake6),
    [TD_GARAKE1]       = ACTION_TAP_DANCE_FN(garake1),
    [TD_GARAKE2]       = ACTION_TAP_DANCE_FN(garake2),
    [TD_GARAKE3]       = ACTION_TAP_DANCE_FN(garake3),
    [TD_GARAKE0_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, garake0_finished, garake0_reset)
};
