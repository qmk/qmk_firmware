// Send `. ~. ```
void tap_dance_grave_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
      SEND_STRING("`");
      break;
    case 2:
      SEND_STRING("~");
      break;
  }
}

void tap_dance_grave_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    SEND_STRING("```");
  } else if (state->count > 3) {
    SEND_STRING("`");
  }
}

