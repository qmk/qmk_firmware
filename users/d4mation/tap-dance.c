#include "tap-dance.h"

qk_tap_dance_action_t tap_dance_actions[] = {
  /* Tap once/hold for Shift, tap twice for Caps Lock */
  [SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE( KC_LSFT, KC_CAPS )
};