static struct {
  int state;
} lock_state = {0};

// Send semi-colon + enter on two taps
void tap_dance_lock_finished(qk_tap_dance_state_t *state, void *user_data) {
  lock_state.state = cur_dance(state);
  switch (lock_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: macro_lock(); break;
  }
}

void tap_dance_lock_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (lock_state.state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
  }
  lock_state.state = 0;
}
