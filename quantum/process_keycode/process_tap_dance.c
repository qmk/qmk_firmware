#include "quantum.h"

static qk_tap_dance_state_t qk_tap_dance_state;

void qk_tap_dance_pair_finished (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 1) {
    register_code (pair->kc1);
  } else if (state->count == 2) {
    register_code (pair->kc2);
  }
}

void qk_tap_dance_pair_reset (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 1) {
    unregister_code (pair->kc1);
  } else if (state->count == 2) {
    unregister_code (pair->kc2);
  }
}

static inline void _process_tap_dance_action_fn (qk_tap_dance_state_t *state,
                                          void *user_data,
                                          qk_tap_dance_user_fn_t fn)
{
  if (fn) {
    fn(state, user_data);
  }
}

static inline void process_tap_dance_action_on_each_tap (qk_tap_dance_action_t action)
{
  _process_tap_dance_action_fn (&qk_tap_dance_state, action.user_data, action.fn.on_each_tap);
}

static inline void process_tap_dance_action_on_dance_finished (qk_tap_dance_action_t action)
{
  _process_tap_dance_action_fn (&qk_tap_dance_state, action.user_data, action.fn.on_dance_finished);
}

static inline void process_tap_dance_action_on_reset (qk_tap_dance_action_t action)
{
  _process_tap_dance_action_fn (&qk_tap_dance_state, action.user_data, action.fn.on_reset);
}

bool process_tap_dance(uint16_t keycode, keyrecord_t *record) {
  bool r = true;
  uint16_t idx = keycode - QK_TAP_DANCE;
  qk_tap_dance_action_t action;

  switch(keycode) {
  case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
    action = tap_dance_actions[idx];

    process_tap_dance_action_on_each_tap (action);
    if (qk_tap_dance_state.keycode && qk_tap_dance_state.keycode != keycode) {
      process_tap_dance_action_on_dance_finished (action);
    } else if (qk_tap_dance_state.active && qk_tap_dance_state.pressed) {
      reset_tap_dance (&qk_tap_dance_state);
    } else {
      r = false;
    }

    qk_tap_dance_state.active = true;
    qk_tap_dance_state.pressed = record->event.pressed;
    if (record->event.pressed) {
      qk_tap_dance_state.keycode = keycode;
      qk_tap_dance_state.timer = timer_read ();
      qk_tap_dance_state.count++;
    }
    break;

  default:
    if (qk_tap_dance_state.keycode) {
      // if we are here, the tap dance was interrupted by a different key
      idx = qk_tap_dance_state.keycode - QK_TAP_DANCE;
      action = tap_dance_actions[idx];

      process_tap_dance_action_on_each_tap (action);
      process_tap_dance_action_on_dance_finished (action);
      reset_tap_dance (&qk_tap_dance_state);
      qk_tap_dance_state.active = false;
    }
    break;
  }

  return r;
}

void matrix_scan_tap_dance () {
  if (qk_tap_dance_state.active && timer_elapsed (qk_tap_dance_state.timer) > TAPPING_TERM) {
    // if we are here, the tap dance was timed out
    uint16_t idx = qk_tap_dance_state.keycode - QK_TAP_DANCE;
    qk_tap_dance_action_t action = tap_dance_actions[idx];

    process_tap_dance_action_on_dance_finished (action);
    reset_tap_dance (&qk_tap_dance_state);
  }
}

void reset_tap_dance (qk_tap_dance_state_t *state) {
  uint16_t idx = state->keycode - QK_TAP_DANCE;
  qk_tap_dance_action_t action;

  if (state->pressed)
    return;

  action = tap_dance_actions[idx];
  process_tap_dance_action_on_reset (action);

  state->keycode = 0;
  state->count = 0;
  state->active = false;
}
