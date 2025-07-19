// Tap Dance Hold logic start
typedef struct {
  uint16_t tap;
  uint16_t hold;
  uint16_t held;
} tap_dance_tap_hold_t;

int is_valid_layer_explicit(int value) {
  int count = sizeof(valid_tap_dance_layers) / sizeof(valid_tap_dance_layers[0]);
  for (int i = 0; i < count; i++) {
    if (valid_tap_dance_layers[i] == value)
      return 1;
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
      if (is_valid_layer_explicit(tap_hold->hold)){
        layer_move(tap_hold->hold);
      }else {
        register_code16(tap_hold->hold);
      }
      tap_hold->held = tap_hold->hold;
    }
  } else {
    if (tap_hold->tap == RMAGIC){
        process_right_magic(get_last_keycode(), get_last_mods());
        set_last_keycode(KC_SPC);
    }else if (tap_hold->tap == LMAGIC){
        process_left_magic(get_last_keycode(), get_last_mods());
        set_last_keycode(KC_SPC);
    }else{
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

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                               \
  {                                                                        \
      .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
      .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),        \
  }
// Tap Dance Hold logic end

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [SPACE_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_TAB),
    [NAV_LMAGIC] = ACTION_TAP_DANCE_TAP_HOLD(LMAGIC, _NAVIGATION),
    [XTRA_RMAGIC] = ACTION_TAP_DANCE_TAP_HOLD(RMAGIC, _EXTRA)
};


// external call for 'tap dance hold'
// static void process_tap_dance_hold(uint16_t keycode, keyrecord_t *record) {
//   tap_dance_action_t *action;

//   action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
//   if (!record->event.pressed && action->state.count && !action->state.finished) {
//     tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
//     tap_code16(tap_hold->tap);
//   }
// }
