 /* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
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
                // Toggling caps so indicate
                caps_status.toggled =  true;
#ifdef RGBLIGHT_ENABLE
                // Save mode we can from
                caps_status.normal_mode = rgblight_get_mode();
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
