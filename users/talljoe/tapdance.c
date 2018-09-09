//Tap Dance
#include "talljoe.h"

// Send semin-colon + enter on two taps
void tap_dance_semicolon(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
      register_code(KC_SCLN);
      unregister_code(KC_SCLN);
      break;
    case 2:
      register_code(KC_SCLN);
      unregister_code(KC_SCLN);

      uint8_t mods = get_mods();
      if (mods) {
        clear_mods();
      }

      register_code(KC_ENT);
      unregister_code(KC_ENT);

      if (mods) {
        set_mods(mods);
      }

      reset_tap_dance(state);
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMICOLON]  = ACTION_TAP_DANCE_FN(tap_dance_semicolon),
};
