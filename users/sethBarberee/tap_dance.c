#include "tap_dance.h"

// Shamelessly stolen from QMK Docs
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}


// Initialize it now
tap caps_status = {
    .toggled = false,
    .state = 0
};


void dance_ecap_finished (qk_tap_dance_state_t *state, void *user_data){
    caps_status.state = cur_dance(state);
    switch(caps_status.state){
        case SINGLE_TAP:
            tap_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTRL);
            break;
        case DOUBLE_TAP:
            tap_code(KC_CAPS);
            if(!caps_status.toggled){
                // Save mode we can from
                caps_status.normal_mode = rgblight_get_mode();
                // Toggling caps so indicate
                caps_status.toggled =  true;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode_noeeprom(CAPS_LOCK_MODE);
#endif
            } else {
                // Turning off so return to normal mode
                caps_status.toggled = false;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode_noeeprom(caps_status.normal_mode);
#endif
            }
            break;
    }
}

void dance_ecap_reset (qk_tap_dance_state_t *state, void *user_data){
    if(caps_status.state == SINGLE_HOLD){
        unregister_code(KC_LCTRL);
    }
    caps_status.state = 0;
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ECAP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ecap_finished, dance_ecap_reset),
// Other declarations would go here, separated by commas, if you have them
};
