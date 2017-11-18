#include "splinter.h"
#include "tap_dance.h"

tap ts[CT_SAFE_END] = {};

void init_tap_dance(void) {
  for (int i = CT_SAFE_START + 1; i < CT_SAFE_END; i++){
    static tap t = {
      .is_press_action = true,
      .state = 0
    };

    ts[i] = t;
  }
}

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
  ts[CT_N_TILDE].state = cur_dance(state);
  switch (ts[CT_N_TILDE].state) {
  case SINGLE_TAP:
    SEND_STRING("n");
    break;
  case SINGLE_HOLD:
    register_code(KC_RSFT);
    break;
  case DOUBLE_TAP:
    SEND_STRING(SS_LCTRL(SS_LSFT("u")));
    SEND_STRING("f1 ");
    break;
  case DOUBLE_HOLD:
    register_code(KC_RSFT);
    break;
  case TRIPLE_TAP:
    SEND_STRING(SS_LCTRL(SS_LSFT("u")));
    SEND_STRING("d1 ");
    break;
  case TRIPLE_HOLD:
    register_code(KC_RSFT);
    break;
  }
}

void n_tilde_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (ts[CT_N_TILDE].state) {
  case SINGLE_HOLD:
  case DOUBLE_HOLD:
  case TRIPLE_HOLD:
    unregister_code(KC_RSFT);
    break;
  }

  ts[CT_N_TILDE].state = 0;
}

void esc_grv_finished(qk_tap_dance_state_t *state, void *user_data) {
  ts[CT_ESC_GRV].state = cur_dance(state);
  switch (ts[CT_ESC_GRV].state) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    register_code(KC_GRV);
    break;
  default:
    register_code(KC_ESCAPE);
    break;
  }
}

void esc_grv_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (ts[CT_ESC_GRV].state) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    unregister_code(KC_GRV);
    break;
  default:
    unregister_code(KC_ESCAPE);
    break;
  }

  ts[CT_ESC_GRV].state = 0;
}
