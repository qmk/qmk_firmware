#include "ninjonas.h"

//// BEGIN: Advanced Tap Dances
int cur_dance (tap_dance_state_t *state) {
   if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

// BEGIN: Copy, Paste, Apps
// https://beta.docs.qmk.fm/features/feature_tap_dance#example-6-using-tap-dance-for-momentary-layer-switch-and-layer-toggle-keys
static tap copy_paste_app_tap_state = {
  .is_press_action = true,
  .state = 0
};

void copy_paste_app_finished (tap_dance_state_t *state, void *user_data) {
  copy_paste_app_tap_state.state = cur_dance(state);
  switch (copy_paste_app_tap_state.state) {
    case SINGLE_TAP: 
      tap_code16(LGUI(KC_V)); // Tap Cmd + V
      break;
    case SINGLE_HOLD: 
      tap_code16(LGUI(KC_C)); // Hold Cmd + C
      break;
    case DOUBLE_TAP: 
      SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI));
      wait_ms(250);
      SEND_STRING("line\n");
      break;
    case TRIPLE_TAP: 
      SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI));
      wait_ms(250);
      SEND_STRING("itunes\n");
      break;
  }
}

void copy_paste_app_reset (tap_dance_state_t *state, void *user_data) {
  copy_paste_app_tap_state.state = 0;
}
// END: Copy, Paste, Apps

// BEGIN: Y, NUMPAD
static tap y_numpad_tap_state = {
  .is_press_action = true,
  .state = 0
};

void y_numpad_finished (tap_dance_state_t *state, void *user_data) {
  y_numpad_tap_state.state = cur_dance(state);
  switch (y_numpad_tap_state.state) {
    case SINGLE_TAP: 
      tap_code(KC_Y); 
      break;
    case SINGLE_HOLD: 
      register_code16(KC_Y);
      break;
    case DOUBLE_TAP: 
      if (layer_state_is(_NUMPAD)) {
        layer_off(_NUMPAD);
      } else { 
        layer_on(_NUMPAD);
      }
      break;
  }
}

void y_numpad_reset (tap_dance_state_t *state, void *user_data) {
  switch (y_numpad_tap_state.state) {
    case SINGLE_HOLD:
      unregister_code16(KC_Y); 
      break;
  }
  y_numpad_tap_state.state = 0;
}
// END: Y, NUMPAD

//// END: Advanced Tap Dances

tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_CAPS]     = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
  [TD_LBRC_BACK]    = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, LGUI(KC_LBRC)),
  [TD_RBRC_FWD]     = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, LGUI(KC_RBRC)),
  [TD_TAB_CTRLTAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LCTL(KC_TAB)),
  [TD_GRV_CTRLGRV]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, LGUI(KC_GRV)),
  [TD_GUI_GUISPC]   = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC)),

  // Advanced Tap Dances
  [TD_COPY_PASTE_APP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_paste_app_finished, copy_paste_app_reset),
  [TD_Y_NUMPAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y_numpad_finished, y_numpad_reset),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_COPY_PASTE_APP):
        case TD(TD_Y_NUMPAD):
            return 300;
        default:
            return TAPPING_TERM;
    }
}
