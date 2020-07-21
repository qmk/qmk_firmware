#include "ninjonas.h"

//// BEGIN: Advanced Tap Dances
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

// BEGIN: Copy, Paste, NUMPAD
// https://beta.docs.qmk.fm/features/feature_tap_dance#example-6-using-tap-dance-for-momentary-layer-switch-and-layer-toggle-keys
static tap copy_paste_numpad_tap_state = {
  .is_press_action = true,
  .state = 0
};

void copy_paste_numpad_finished (qk_tap_dance_state_t *state, void *user_data) {
  copy_paste_numpad_tap_state.state = cur_dance(state);
  switch (copy_paste_numpad_tap_state.state) {
    case SINGLE_TAP: 
      tap_code16(LGUI(KC_V)); // Tap Cmd + V
      break;
    case SINGLE_HOLD: 
      tap_code16(LGUI(KC_C)); // Hold Cmd + C
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

void copy_paste_numpad_reset (qk_tap_dance_state_t *state, void *user_data) {
  copy_paste_numpad_tap_state.state = 0;
}
// END: Copy, Paste, NUMPAD

// BEGIN: Y, NUMPAD
static tap y_numpad_tap_state = {
  .is_press_action = true,
  .state = 0
};

void y_numpad_finished (qk_tap_dance_state_t *state, void *user_data) {
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

void y_numpad_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (y_numpad_tap_state.state) {
    case SINGLE_HOLD:
      unregister_code16(KC_Y); 
      break;
  }
  y_numpad_tap_state.state = 0;
}
// END: Y, NUMPAD

//// END: Advanced Tap Dances

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_CAPS]     = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
  [TD_LBRC_BACK]    = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, LGUI(KC_LBRC)),
  [TD_RBRC_FWD]     = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, LGUI(KC_RBRC)),
  [TD_TAB_CTRLTAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LCTL(KC_TAB)),
  [TD_GRV_CTRLGRV]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, LGUI(KC_GRV)),
  [TD_GUI_GUISPC]   = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC)),
  [TD_W_CTRLW]      = ACTION_TAP_DANCE_DOUBLE(KC_W, LGUI(KC_W)),
  [TD_Q_GUIQ]       = ACTION_TAP_DANCE_DOUBLE(KC_Q, LGUI(KC_Q)),

  // Advanced Tap Dances
  [TD_COPY_PASTE_NUMPAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_paste_numpad_finished, copy_paste_numpad_reset),
  [TD_Y_NUMPAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y_numpad_finished, y_numpad_reset),
};