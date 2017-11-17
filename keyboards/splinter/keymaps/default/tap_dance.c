#include "splinter.h"
#include "tap_dance.h"

static tap n_tilde_tap_state = {
  .is_press_action = true,
  .state = 0
};

int cur_dance (qk_tap_dance_state_t *state) {
  switch (state->count) {
  case 1:
    return state->pressed ? SINGLE_HOLD : SINGLE_TAP;
  case 2:
    return state->pressed ? DOUBLE_HOLD : DOUBLE_TAP;
  case 3:
    return state->pressed ? TRIPLE_HOLD : TRIPLE_TAP;
  default:
    return NO_TAP;
  }
}

void n_tilde_finished(qk_tap_dance_state_t *state, void *user_data) {
  n_tilde_tap_state.state = cur_dance(state);
  switch (n_tilde_tap_state.state) {
  case SINGLE_TAP:
    SEND_STRING("n");
    break;
  case SINGLE_HOLD:
    register_code(KC_LSFT);
    break;
  case DOUBLE_TAP:
    SEND_STRING(SS_LCTRL(SS_LSFT("u")));
    SEND_STRING("f1 ");
    break;
  case DOUBLE_HOLD:
    register_code(KC_LSFT);
    break;
  case TRIPLE_TAP:
    SEND_STRING(SS_LCTRL(SS_LSFT("u")));
    SEND_STRING("d1 ");
    break;
  case TRIPLE_HOLD:
    register_code(KC_LSFT);
    break;
  }
}

void n_tilde_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (n_tilde_tap_state.state) {
  case SINGLE_HOLD:
  case DOUBLE_HOLD:
  case TRIPLE_HOLD:
    unregister_code(KC_LSFT);
    break;
  }
}
