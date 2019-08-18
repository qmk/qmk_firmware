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
#define TD_CTL_LANG1     13
#define TD_SFT_LANG2     14

#define send_keycode(key) { register_code(key); unregister_code(key); }

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
    layer_off(GARARAISE);
    garake0_raised = false;
  }
}

/* ---- */

bool ctl_pressed = false;

void garake_ctl_lang1 (qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed || state->interrupted) {
    register_code(KC_LCTL);
    layer_off(TENKEY);
    ctl_pressed = true;
    return;
  } else {
    send_keycode(KC_LANG1);
  }
}

void garake_ctl_lang1_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (ctl_pressed) {
    unregister_code(KC_LCTL);
    ctl_pressed = false;
  }
}

/* ---- */

bool sft_pressed = false;

void garake_sft_lang2 (qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed || state->interrupted) {
    register_code(KC_LSFT);
    layer_off(TENKEY);
    sft_pressed = true;
    return;
  } else {
    send_keycode(KC_LANG2);
  }
}

void garake_sft_lang2_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (ctl_pressed) {
    unregister_code(KC_LSFT);
    sft_pressed = false;
  }
}

/* ---- */

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GARAKE7]       = ACTION_TAP_DANCE_FN(garake7),
    [TD_GARAKE8]       = ACTION_TAP_DANCE_FN(garake8),
    [TD_GARAKE9]       = ACTION_TAP_DANCE_FN(garake9),
    [TD_GARAKE4]       = ACTION_TAP_DANCE_FN(garake4),
    [TD_GARAKE5]       = ACTION_TAP_DANCE_FN(garake5),
    [TD_GARAKE6]       = ACTION_TAP_DANCE_FN(garake6),
    [TD_GARAKE1]       = ACTION_TAP_DANCE_FN(garake1),
    [TD_GARAKE2]       = ACTION_TAP_DANCE_FN(garake2),
    [TD_GARAKE3]       = ACTION_TAP_DANCE_FN(garake3),
    [TD_GARAKE0_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, garake0_finished, garake0_reset),
    [TD_CTL_LANG1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, garake_ctl_lang1, garake_ctl_lang1_reset),
    [TD_SFT_LANG2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, garake_sft_lang2, garake_sft_lang2_reset)
};
