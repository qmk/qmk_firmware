#define TD_SHIFT_CAPS 1
#define TD_ESC_FUNC   2

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

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished,  shift_reset),
    [TD_ESC_FUNC]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished,  esc_reset)
};
