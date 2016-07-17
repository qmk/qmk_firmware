#include "quantum.h"

static qk_tap_dance_state_t qk_tap_dance_state;

static void _process_tap_dance_action_pair (qk_tap_dance_state_t *state,
                                            uint16_t kc1, uint16_t kc2) {
  uint16_t kc;

  if (state->count == 0)
    return;

  kc = (state->count == 1) ? kc1 : kc2;

  register_code (kc);
  unregister_code (kc);

  if (state->count >= 2) {
    reset_tap_dance (state);
  }
}

static void _process_tap_dance_action_fn (qk_tap_dance_state_t *state,
                                          qk_tap_dance_user_fn_t fn)
{
  fn(state);
}

void process_tap_dance_action (uint16_t keycode)
{
  uint16_t idx = keycode - QK_TAP_DANCE;
  qk_tap_dance_action_t action;

  action = tap_dance_actions[idx];

  switch (action.type) {
  case QK_TAP_DANCE_TYPE_PAIR:
    _process_tap_dance_action_pair (&qk_tap_dance_state,
                                    action.pair.kc1, action.pair.kc2);
    break;
  case QK_TAP_DANCE_TYPE_FN:
    _process_tap_dance_action_fn (&qk_tap_dance_state, action.fn);
    break;

  default:
    break;
  }
}

bool process_tap_dance(uint16_t keycode, keyrecord_t *record) {
  bool r = true;

  switch(keycode) {
  case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
    if (qk_tap_dance_state.keycode && qk_tap_dance_state.keycode != keycode) {
      process_tap_dance_action (qk_tap_dance_state.keycode);
    } else {
      r = false;
    }

    if (record->event.pressed) {
      qk_tap_dance_state.keycode = keycode;
      qk_tap_dance_state.timer = timer_read ();
      qk_tap_dance_state.count++;
    }
    break;

  default:
    if (qk_tap_dance_state.keycode) {
      process_tap_dance_action (qk_tap_dance_state.keycode);

      reset_tap_dance (&qk_tap_dance_state);
    }
    break;
  }

  return r;
}

void matrix_scan_tap_dance () {
  if (qk_tap_dance_state.keycode && timer_elapsed (qk_tap_dance_state.timer) > TAPPING_TERM) {
    process_tap_dance_action (qk_tap_dance_state.keycode);

    reset_tap_dance (&qk_tap_dance_state);
  }
}

void reset_tap_dance (qk_tap_dance_state_t *state) {
  state->keycode = 0;
  state->count = 0;
}
