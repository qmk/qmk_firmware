//Tap Dance
#include "talljoe.h"

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  SPECIAL = 8
};

static struct {
  int quote;
  int semicolon;
} tap_state = {0};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      //     if (!state->pressed) return SINGLE_TAP;
      //need "permissive hold" here.
      //     else return SINGLE_HOLD;
      //If the interrupting key is released before the tap-dance key, then it is a single HOLD
      //However, if the tap-dance key is released first, then it is a single TAP
      //But how to get access to the state of the interrupting key????
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return SPECIAL;
}

int hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return SPECIAL;
}

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


void tap_dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.quote = hold_cur_dance(state);
  switch (tap_state.quote) {
    case SINGLE_TAP: case DOUBLE_HOLD: register_code(KC_QUOT); break;
    case SINGLE_HOLD: layer_on(_NAV); break;
  }
}

void tap_dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.quote) {
    case SINGLE_TAP: case DOUBLE_HOLD: unregister_code(KC_QUOTE); break;
    case DOUBLE_TAP: SEND_STRING("\""); break;
    case TRIPLE_TAP: layer_invert(_NAV); break;
    case SINGLE_HOLD: layer_off(_NAV); break;
  }
  tap_state.quote = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMICOLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_semicolon_finished, tap_dance_semicolon_reset),
  [TD_GRAVE]     = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_grave_each, tap_dance_grave_finished, NULL),
  [TD_QUOTE]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_quote_finished, tap_dance_quote_reset),
};
