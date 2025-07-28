uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(NAV_LMAGIC):
        case TD(XTRA_RMAGIC):
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

typedef struct {
  uint16_t tap;
  uint16_t hold;
  uint16_t held;
  void (*custom_function)(void);
} tap_dance_tap_hold_t;

int is_valid_layer_explicit(int value) {
  int count = sizeof(valid_tap_dance_layers) / sizeof(valid_tap_dance_layers[0]);
  for (int i = 0; i < count; i++) {
    if (valid_tap_dance_layers[i] == value) return 1;
  }
  return 0;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

  if (state->pressed) {
    if (state->count == 1
#ifndef PERMISSIVE_HOLD
        && !state->interrupted
#endif
    ) {
      if (is_valid_layer_explicit(tap_hold->hold)) {
        layer_move(tap_hold->hold);
      } else {
        register_code16(tap_hold->hold);
      }
      tap_hold->held = tap_hold->hold;
    }
  } else {
    if (tap_hold->custom_function != NULL) {
      tap_hold->custom_function();
      // process_left_magic(get_last_keycode(), get_last_mods());
      set_last_keycode(KC_SPC);
    } else {
      register_code16(tap_hold->tap);
    }
    tap_hold->held = tap_hold->tap;
  }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

  if (tap_hold->held) {
    layer_move(_COLEMAK);
    unregister_code16(tap_hold->held);
    tap_hold->held = 0;
  }
}
 /**
  * This macro defines a tap dance action that performs a tap action, a custom function, or a hold action.
  * - `tap`: The keycode to send when the key is tapped.
  * - `custom_function`: A pointer to a function to call when the key is tapped.
  * - `hold`: The keycode to send or layer to switch to when the key is held.
  *
  * - If the key is held and not interrupted (when PERMISSIVE_HOLD is not defined),
  *   it performs the hold action. If the hold action corresponds to a valid layer,
  *   it moves to that layer; otherwise, it registers the hold keycode.
  * - If the key is tapped, it performs the tap action or calls the custom function
  *   if one is defined.
  *
  * The macro initializes a `tap_dance_tap_hold_t` structure with the provided
  * `tap`, `custom_function`, and `hold` values. It also specifies the functions
  * to handle the tap dance action's finished and reset states.
  */
#define ACTION_TAP_DANCE_TAPFUNCTION_HOLD(tap, custom_function, hold)                \
  {                                                                                  \
      .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset},           \
      .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0, custom_function}), \
  }

  /**
   * This macro defines a tap dance action that performs a tap action or a hold action.
   * - `tap`: The keycode to send when the key is tapped.
   * - `hold`: The keycode to send or layer to switch to when the key is held.
   *
   *  - If the key is held and not interrupted (when PERMISSIVE_HOLD is not defined),
   *   it performs the hold action. If the hold action corresponds to a valid layer,
   *   it moves to that layer; otherwise, it registers the hold keycode.
   *
   * The macro initializes a `tap_dance_tap_hold_t` structure with the provided
   * `tap` and `hold` keycodes, and sets the `custom_function` to `NULL`.
   * It also specifies the functions to handle the tap dance action's finished
   * and reset states.
   */
#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                               \
  {                                                                        \
      .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
      .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0, NULL}),  \
  }
// Tap Dance Hold logic end

// external call for 'tap dance hold'
// static void process_tap_dance_hold(uint16_t keycode, keyrecord_t *record) {
//   tap_dance_action_t *action;

//   action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
//   if (!record->event.pressed && action->state.count && !action->state.finished) {
//     tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
//     tap_code16(tap_hold->tap);
//   }
// }
