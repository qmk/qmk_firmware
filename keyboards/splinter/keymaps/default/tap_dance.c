#include "splinter.h"
#include "tap_dance.h"

static tap n_tilde_tap_state = {
  .is_press_action = true,
  .state = 0
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || state->pressed == 0) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    if (state->pressed) {
      return DOUBLE_HOLD;
    } else {
      return DOUBLE_TAP;
    }
  } else if (state->count == 3) {
    if (state->pressed) {
      return TRIPLE_HOLD;
    } else {
      return TRIPLE_TAP
    }
  }
}

void n_tilde_finished(qk_tap_dance_state_t *state, void *user_data) {
  n_tilde_tap_state.state = cur_dance(state);
  switch (n_tilde_tap_state.state) {
  case SINGLE_TAP:
    register_code(KC_N);
    break;
  case SINGLE_HOLD:
    register_code(KC_LSFT);
    break;
  case DOUBLE_TAP:
    SEND_STRING(SS_LCTRL(SS_LSFT("u")));
    SEND_STRING("f1 ");
  case DOUBLE_HOLD:
    register_code(KC_LSFT);
    break;
  case TRIPLE_TAP:
    SEND_STRING(SS_LCTRL(SS_LSFT("u")));
    SEND_STRING("d1 ");
  case TRIPLE_HOLD:
    register_code(KC_LSFT);
    break;
  }
}

void n_tilde_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (n_tilde_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_N);
    break;
  case SINGLE_HOLD:
  case DOULBE_HOLD:
  case TRIPLE_HOLD:
    unregister_code(KC_LSFT);
  }
}
