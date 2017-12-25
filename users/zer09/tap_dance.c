#include "tap_dance.h"
#include "lights.h"

qk_tap_dance_action_t tap_dance_actions[] = {
        [DA_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lctl_finished,
                                                 dance_lctl_reset),
        [DA_LSPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lspr_finished,
                                                 dance_lspr_reset),
        [DA_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rctl_finished,
                                                 dance_rctl_reset),
        [DA_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ralt_finished,
                                                 dance_ralt_reset),
        [DA_EGRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_egrv_finished,
                                                 dance_egrv_reset),
};

int cur_dance(qk_tap_dance_state_t *state) {
  switch (state->count) {
  case 1:
    return state->pressed ? SINGLE_HOLD : SINGLE_TAP;
  case 2:
    return state->pressed ? DOUBLE_HOLD : DOUBLE_TAP;
  case 3:
    return state->pressed ? TRIPLE_HOLD : TRIPLE_TAP;
  default:
    return state->pressed ? DEFAULT_HOLD : DEFAULT_TAP;
  }
}

void dance_lctl_finished(qk_tap_dance_state_t *state, void *user_data) {
  rbw_led_keys[RBW_LCTL].status = ENABLED;
  register_code(KC_LCTRL);
};

void dance_lctl_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_LCTRL);
  rbw_led_keys[RBW_LCTL].status = DISABLED;
};

void dance_lspr_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    rbw_led_keys[RBW_LSPR].status = ENABLED;
    register_code(KC_LALT);
    break;
  default:
    register_code(KC_LGUI);
    break;
  }
};

void dance_lspr_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    unregister_code(KC_LALT);
    rbw_led_keys[RBW_LSPR].status = DISABLED;
    break;
  default:
    unregister_code(KC_LGUI);
    break;
  }
};

void dance_rctl_finished(qk_tap_dance_state_t *state, void *user_data) {
  rbw_led_keys[RBW_RCTL].status = ENABLED;
  register_code(KC_RCTRL);
};

void dance_rctl_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_RCTRL);
  rbw_led_keys[RBW_RCTL].status = DISABLED;
};

void dance_ralt_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    rbw_led_keys[RBW_RALT].status = ENABLED;
    register_code(KC_RGUI);
    break;
  default:
    register_code(KC_RALT);
    break;
  }
};

void dance_ralt_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    unregister_code(KC_RGUI);
    rbw_led_keys[RBW_RALT].status = DISABLED;
    break;
  default:
    unregister_code(KC_RALT);
    break;
  }
};

void dance_egrv_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    register_code(KC_GRAVE);
    break;
  default:
    register_code(KC_ESCAPE);
    break;
  }
};

void dance_egrv_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
  case DOUBLE_TAP:
  case DOUBLE_HOLD:
    unregister_code(KC_GRAVE);
    break;
  default:
    unregister_code(KC_ESCAPE);
    break;
  }
};
