//Tap Dance
#include "talljoe.h"

// Send semi-colon + enter on two taps
void tap_dance_semicolon_each(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
    case 1:
      SEND_STRING(";");
      break;
    default: // two or more taps
    {
      uint8_t mods = get_mods();
      if (mods) {
        clear_mods();
      }

      SEND_STRING("\n");

      if (mods) {
        set_mods(mods);
      }
      break;
    }
  }
}


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


qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMICOLON]  = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_semicolon_each, NULL, NULL),
  [TD_GRAVE]  = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_grave_each, tap_dance_grave_finished, NULL),
};
