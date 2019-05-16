#include "tap_dances.h"

void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    // Reset the keyboard if you tap the key more than three times
    reset_keyboard();
    reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
  [TD_SPC]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_4),
  [TD_NUM1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_4),
  [TD_NUM2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_5),
  [TD_NUM3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_6),
  [TD_OSW] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, MC_QT1),
};
