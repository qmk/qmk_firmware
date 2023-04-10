#include "tap_dances.h"

void dance_left_brackets(tap_dance_state_t *state, void *user_data) {
  //sends (, [, {, or < depending on the taps
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
  } else if (state->count == 4) {
    register_code(KC_LSFT);
    tap_code(KC_COMM);
    unregister_code(KC_LSFT);
  }
  reset_tap_dance(state);
}

void dance_right_brackets(tap_dance_state_t *state, void *user_data) {
  //sends ), ], }, or > depending on the taps
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
  } else if (state->count == 4) {
    register_code(KC_LSFT);
    tap_code(KC_DOT);
    unregister_code(KC_LSFT);
  }
  reset_tap_dance(state);
}

void dance_quotes(tap_dance_state_t *state, void *user_data) {
  //sends ' or " depending on the taps
  if (state->count == 1) {
    tap_code(KC_QUOT);
  } else if (state->count == 2) {
    register_code(KC_LSFT);
    tap_code(KC_QUOT);
    unregister_code(KC_LSFT);
  }
  reset_tap_dance(state);
}

void dance_colons(tap_dance_state_t *state, void *user_data) {
  //sends ; or : depending on number of taps
  if (state->count == 1) {
    tap_code(KC_SCLN);
  } else if (state->count == 2) {
    register_code(KC_LSFT);
    tap_code(KC_SCLN);
    unregister_code(KC_LSFT);
  }
  reset_tap_dance(state);
}


tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFTBRACKETS]   = ACTION_TAP_DANCE_FN(dance_left_brackets),
  [TD_RIGHTBRACKETS]  = ACTION_TAP_DANCE_FN(dance_right_brackets),
  [TD_QUOTES]         = ACTION_TAP_DANCE_FN(dance_quotes),
  [TD_COLONS]         = ACTION_TAP_DANCE_FN(dance_colons)
};