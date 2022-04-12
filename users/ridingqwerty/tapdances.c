#include "ridingqwerty.h"
#include "tapdances.h"

void braces_finished (qk_tap_dance_state_t *state, void *user_data) {
    if ((state->count == 1) || (state->count == 3)) {
        register_code(KC_LSFT);
    }
}

void braces_reset (qk_tap_dance_state_t *state, void *user_data) {
  // two or three taps for "[]"/"{}"
  if ((state->count == 2) || (state->count == 3)) {
    tap_code(KC_LBRC);
    tap_code(KC_RBRC);
  }
  // one tap for "()"
  else if (state->count == 1) {
    tap_code(KC_9);
    tap_code(KC_0);
  }

  // unregister the shift unconditionally
  unregister_code(KC_LSFT);

  // move back one space, inside the braces
  if (state->count <= 3) {
    tap_code(KC_LEFT);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_BRACES] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, braces_finished, braces_reset)
};
