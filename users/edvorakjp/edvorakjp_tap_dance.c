#include "edvorakjp.h"
#include "process_keycode/process_tap_dance.h"

enum tap_state {
  NONE = 0,
  SINGLE_TAP = 1,
  DOUBLE_TAP = 2,
  HOLD
};

typedef struct {
  uint8_t lower;
  uint8_t raise;
} td_status_t;
static td_status_t td_status = {NONE, NONE};

int cur_dance(qk_tap_dance_state_t *state) {
  if (state->interrupted || !state->pressed) {
    return state->count == 1 ? SINGLE_TAP : DOUBLE_TAP;
  } else {
    return HOLD;
  }
}

void td_lower_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_status.lower = cur_dance(state);
  switch(td_status.lower) {
    case SINGLE_TAP:
      set_japanese_mode(false);
      break;
    case DOUBLE_TAP:
      set_japanese_mode(false);
      register_code(KC_ESC);
      break;
    case HOLD:
      break;
  }
  layer_on(_LOWER);
}

void td_lower_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (td_status.lower == DOUBLE_TAP) {
    unregister_code(KC_ESC);
  }
  layer_off(_LOWER);
  td_status.lower = NONE;
}

void td_raise_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_status.raise = cur_dance(state);
  switch(td_status.raise) {
    case DOUBLE_TAP:
      // same as single
    case SINGLE_TAP:
      set_japanese_mode(true);
      break;
    case HOLD:
      break;
  }
  layer_on(_RAISE);
}

void td_raise_reset(qk_tap_dance_state_t *state, void *user_data) {
  layer_off(_RAISE);
  td_status.raise = NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LOWER] =
    ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_lower_finished, td_lower_reset, 100),
  [TD_RAISE] =
    ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_raise_finished, td_raise_reset, 100)
};
