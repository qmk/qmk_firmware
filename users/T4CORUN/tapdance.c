#include "tap_dance.h"

void dance_left_brackets(tap_dance_state_t *state, void *user_data) {
  //sends (, [, or { depending on the number of taps
  if (state->count == 1) {
    register_code(KC_LSFT);
    tap_code(KC_9);
    unregister_code(KC_LSFT);
  } else if (state->count == 2) {
    tap_code(KC_LBRC);
  } else if (state->count == 3) {
    register_code(KC_LSFT);
    tap_code(KC_LBRC);
    unregister_code(KC_LSFT);
  }
  reset_tap_dance(state);
}

void dance_right_brackets(tap_dance_state_t *state, void *user_data) {
  //sends ), ], or } depending on the number of taps
  if (state->count == 1) {
    register_code(KC_LSFT);
    tap_code(KC_0);
    unregister_code(KC_LSFT);
  } else if (state->count == 2) {
    tap_code(KC_RBRC);
  } else if (state->count == 3) {
    register_code(KC_LSFT);
    tap_code(KC_RBRC);
    unregister_code(KC_LSFT);
  }
  reset_tap_dance(state);
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFTBRACKETS]   = ACTION_TAP_DANCE_FN(dance_left_brackets),
  [TD_RIGHTBRACKETS]  = ACTION_TAP_DANCE_FN(dance_right_brackets)
};