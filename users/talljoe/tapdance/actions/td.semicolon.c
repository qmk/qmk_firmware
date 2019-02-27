static struct {
  int semicolon;
} tap_state = {0};

// Send semi-colon + enter on two taps
void tap_dance_semicolon_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.semicolon = hold_cur_dance(state);
  switch (tap_state.semicolon) {
    case SINGLE_TAP: case DOUBLE_HOLD: register_code(KC_SCLN); break;
    case SINGLE_HOLD: layer_on(_NUM); break;
  }
}

void tap_dance_semicolon_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.semicolon) {
    case SINGLE_TAP: case DOUBLE_HOLD: unregister_code(KC_SCLN); break;
    case DOUBLE_TAP: {
      if (get_mods()) {
        SEND_STRING(";;"); // send normal when mods are pressed
      }
      else {
        SEND_STRING(";\n");
      }
      break;
    }
    case TRIPLE_TAP: {
      SEND_STRING(";\n\n");
    }
    case SPECIAL: layer_invert(_NUM); break;
    case SINGLE_HOLD: layer_off(_NUM); break;
  }
  tap_state.semicolon = 0;
}
