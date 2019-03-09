static struct {
  int state;
} function_state = {0};

// Send semi-colon + enter on two taps
void tap_dance_function_finished(qk_tap_dance_state_t *state, void *user_data) {
  function_state.state = hold_cur_dance(state);
  switch (function_state.state) {
    case SINGLE_HOLD: layer_on(_ADJUST); break;
  }
}

void tap_dance_function_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (function_state.state) {
    case SPECIAL: reset_keyboard(); break;
    case SINGLE_HOLD: layer_off(_ADJUST); break;
  }
  function_state.state = 0;
}
