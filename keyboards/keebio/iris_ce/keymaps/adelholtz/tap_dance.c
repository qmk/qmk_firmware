enum {
  SPACE_TAB,
  TDH_U_UE,
  // TDH_O_OE,
  // TDH_A_AE,
};

// Tap Dance Hold logic start
typedef struct {
  uint16_t tap;
  uint16_t hold;
  uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

  if (state->pressed) {
    if (state->count == 1
#ifndef PERMISSIVE_HOLD
        && !state->interrupted
#endif
    ) {
      register_code16(tap_hold->hold);
      tap_hold->held = tap_hold->hold;
    }
  } else {
    register_code16(tap_hold->tap);
    tap_hold->held = tap_hold->tap;
  }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

  if (tap_hold->held) {
    unregister_code16(tap_hold->held);
    tap_hold->held = 0;
  }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                               \
  {                                                                        \
      .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
      .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),        \
  }
// Tap Dance Hold logic end


// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [SPACE_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_TAB),
    [TDH_U_UE] = ACTION_TAP_DANCE_TAP_HOLD(DE_U, DE_UDIA),
    // [TDH_O_OE] = ACTION_TAP_DANCE_TAP_HOLD(DE_O, DE_ODIA),
    // [TDH_A_AE] = ACTION_TAP_DANCE_TAP_HOLD(DE_A, DE_ADIA),
};

// external call for 'tap dance hold'
static void process_tap_dance_hold(uint16_t keycode, keyrecord_t *record) {
  tap_dance_action_t *action;

  action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
  if (!record->event.pressed && action->state.count &&
      !action->state.finished) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
    tap_code16(tap_hold->tap);
  }
}
