#include "tap_dance.h"

void dance_left_paren_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code(KC_LSFT);
    register_code(KC_9);
    break;
  case 2:
    register_code(KC_LBRC);
    break;
  case 3:
    register_code(KC_LSFT);
    register_code(KC_LBRC);
    break;
  }
  //reset_tap_dance(state);
}

void dance_left_paren_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    unregister_code(KC_LSFT);
    unregister_code(KC_9);
    break;
  case 2:
    unregister_code(KC_LBRC);
    break;
  case 3:
    unregister_code(KC_LSFT);
    unregister_code(KC_LBRC);
    break;
  }
  //if(state->count >= 3){
  //  reset_tap_dance(state);
  //}
}

void dance_right_paren_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code(KC_LSFT);
    register_code(KC_0);
    break;
  case 2:
    register_code(KC_RBRC);
    break;
  case 3:
    register_code(KC_LSFT);
    register_code(KC_RBRC);
    break;
  }
  //reset_tap_dance(state);
}

void dance_right_paren_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    unregister_code(KC_LSFT);
    unregister_code(KC_0);
    break;
  case 2:
    unregister_code(KC_RBRC);
    break;
  case 3:
    unregister_code(KC_LSFT);
    unregister_code(KC_RBRC);
    break;
  }
  //if (state->count >= 3) {
  //  reset_tap_dance(state);
  //}
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Once for (, twice for [, three times for {
  [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_paren_finished, dance_left_paren_reset),
  // Once for ), twice for ], three times for }
  [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_paren_finished, dance_right_paren_reset),
  [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};
