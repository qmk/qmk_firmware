#include "sethBarberee.h"
#ifdef RGBLIGHT_ENABLE
#ifdef TAP_DANCE_ENABLE

// Initialize it now
tap caps_status = {
    .toggled = false,
    .toggle_mode = CAPS_LOCK_MODE,
    .normal_mode = NORMAL_MODE
};

void dance_ecap_finished (qk_tap_dance_state_t *state, void *user_data){
    if(state->count == 1){
        register_code(KC_ESC);
    } else {
        register_code(KC_CAPS);
        if(!caps_status.toggled){
            // Toggling caps so indicate
            caps_status.toggled =  true;
            rgblight_mode_noeeprom(caps_status.toggle_mode);
        } else {
            // Turning off so return to normal mode
            caps_status.toggled = false;
            rgblight_mode_noeeprom(caps_status.normal_mode);
        }
    }
}

void dance_ecap_reset (qk_tap_dance_state_t *state, void *user_data){
    if(state->count == 1){
        unregister_code(KC_ESC);
    } else {
        unregister_code(KC_CAPS);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ECAP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ecap_finished, dance_ecap_reset),
// Other declarations would go here, separated by commas, if you have them
};

#endif
#endif
