#include "tap_dance.h"
#include "lights.h"

tap_dance_action_t tap_dance_actions[] = {
    [DA_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lctl_finished,
                                             dance_lctl_reset),
    [DA_LSPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lspr_finished,
                                             dance_lspr_reset),
    [DA_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rctl_finished,
                                             dance_rctl_reset),
    [DA_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ralt_finished,
                                             dance_ralt_reset),
    [DA_UPLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_uply_finished,
                                             dance_uply_reset),
    [DA_DWLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dwly_finished,
                                             dance_dwly_reset),
};

volatile uint8_t active_layer = _BL;
volatile uint8_t gm_layer_act = false;
static tap upltap_state = {.state = 0};
static tap dwltap_state = {.state = 0};
static tap lsprtap_state = {.state = 0};
static tap ralttap_state = {.state = 0};

void layer_switcher_tap(uint8_t new_layer) {
  if (gm_layer_act == true) {
    layer_off(active_layer);
    if (new_layer == _BL) {
      layer_on(_GM);
      active_layer = _GM;
    } else {
      layer_on(new_layer);
      active_layer = new_layer;
    }
  } else {
    layer_off(active_layer);
    layer_on(new_layer);
    active_layer = new_layer;
  }
}

int cur_dance(tap_dance_state_t *state) {
  switch (state->count) {
  case 1:
    return state->pressed == 0 ? SINGLE_TAP : SINGLE_HOLD;
  case 2:
    return state->pressed == 0 ? DOUBLE_TAP : DOUBLE_HOLD;
  case 3:
    return state->pressed == 0 ? TRIPLE_TAP : TRIPLE_HOLD;
  default:
    return state->pressed == 0 ? DEFAULT_TAP : DEFAULT_HOLD;
  }
}

void dance_lctl_finished(tap_dance_state_t *state, void *user_data) {
  rbw_led_keys[RBW_LCTL].status = ENABLED;
  register_code(KC_LCTL);
};

void dance_lctl_reset(tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_LCTL);
  rbw_led_keys[RBW_LCTL].status = DISABLED;
};

void dance_lspr_finished(tap_dance_state_t *state, void *user_data) {
  lsprtap_state.state = cur_dance(state);

  switch (lsprtap_state.state) {
  case DOUBLE_HOLD:
    rbw_led_keys[RBW_LSPR].status = ENABLED;
    register_code(KC_LALT);
    break;
  default:
    register_code(KC_LGUI);
    break;
  }
};

void dance_lspr_reset(tap_dance_state_t *state, void *user_data) {
  switch (lsprtap_state.state) {
  case DOUBLE_HOLD:
    unregister_code(KC_LALT);
    rbw_led_keys[RBW_LSPR].status = DISABLED;
    break;
  default:
    unregister_code(KC_LGUI);
    break;
  }
};

void dance_rctl_finished(tap_dance_state_t *state, void *user_data) {
  rbw_led_keys[RBW_RCTL].status = ENABLED;
  register_code(KC_RCTL);
};

void dance_rctl_reset(tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_RCTL);
  rbw_led_keys[RBW_RCTL].status = DISABLED;
};

void dance_ralt_finished(tap_dance_state_t *state, void *user_data) {
  ralttap_state.state = cur_dance(state);

  switch (ralttap_state.state) {
  case DOUBLE_HOLD:
    rbw_led_keys[RBW_RALT].status = ENABLED;
    unregister_code(KC_LGUI);
    break;
  default:
    register_code(KC_RALT);
    break;
  }
};

void dance_ralt_reset(tap_dance_state_t *state, void *user_data) {
  switch (ralttap_state.state) {
  case DOUBLE_HOLD:
    unregister_code(KC_RGUI);
    rbw_led_keys[RBW_RALT].status = DISABLED;
    break;
  default:
    unregister_code(KC_RALT);
    break;
  }
};

void dance_uply_finished(tap_dance_state_t *state, void *user_data) {
  upltap_state.state = cur_dance(state);

  switch (upltap_state.state) {
  case SINGLE_TAP:
    if (active_layer == _UL) {
      layer_switcher_tap(_BL);
    } else {
      layer_switcher_tap(_UL);
    }
    break;
  case SINGLE_HOLD:
    layer_switcher_tap(_UL);
    break;
  default:
    layer_switcher_tap(_BL);
    break;
  }
}

void dance_uply_reset(tap_dance_state_t *state, void *user_data) {
  switch (upltap_state.state) {
  case SINGLE_TAP:
    break;
  case SINGLE_HOLD:
  default:
    layer_switcher_tap(_BL);
    break;
  }
  upltap_state.state = 0;
}

void dance_dwly_finished(tap_dance_state_t *state, void *user_data) {
  dwltap_state.state = cur_dance(state);

  switch (dwltap_state.state) {
  case SINGLE_TAP:
    if (active_layer == _DL) {
      layer_switcher_tap(_BL);
    } else {
      layer_switcher_tap(_DL);
    }
    break;
  case SINGLE_HOLD:
    layer_switcher_tap(_DL);
    break;
  case DOUBLE_HOLD:
    layer_switcher_tap(_AL);
    break;
  case TRIPLE_TAP:
    if (gm_layer_act == true) {
      gm_layer_act = false;
      layer_switcher_tap(_BL);
    } else {
      gm_layer_act = true;
      layer_switcher_tap(_GM);
    }
  default:
    layer_switcher_tap(_BL);
    break;
  }
}

void dance_dwly_reset(tap_dance_state_t *state, void *user_data) {
  switch (dwltap_state.state) {
  case SINGLE_TAP:
    break;
  case SINGLE_HOLD:
  case DOUBLE_HOLD:
  case TRIPLE_TAP:
  default:
    layer_switcher_tap(_BL);
    break;
  }
  dwltap_state.state = 0;
}
