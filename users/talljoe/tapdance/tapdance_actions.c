#include "../talljoe.h"
#include "actions/td.grave.c"
#include "actions/td.lock.c"
#include "actions/td.semicolon.c"

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMICOLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_semicolon_finished, tap_dance_semicolon_reset),
  [TD_LOCK]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_lock_finished, tap_dance_lock_reset),
  [TD_GRAVE]     = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_grave_each, tap_dance_grave_finished, NULL),
};
