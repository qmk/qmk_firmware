#include "stanrc85.h"

static td_state_t td_state;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}

// handle the possible states for each tapdance keycode you define:
void ctl_copy_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      SEND_STRING(SS_LCTRL("c"));
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTRL("v"));
  }
}

void ctl_copy_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_TAP:
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_CAD, KC_LOCK),
  [TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
  [TD_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_copy_finished, ctl_copy_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_MAKE:
    if (!record->event.pressed) {
      uint8_t mods = get_mods();
      clear_mods();
      send_string_with_delay_P(PSTR("qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP "\n"), 10); //New way
        if (mods & MOD_MASK_SHIFT) {
          send_string(SS_LGUI());
          send_string("qmk toolbox\n");
          reset_keyboard();
        }
      set_mods(mods);
      }
    break;
  case KC_RDP: //Opens Windows RDP
    if (!record->event.pressed) {
      register_code(KC_LGUI);
      tap_code(KC_R);
      unregister_code(KC_LGUI);
      wait_ms(200);
      send_string_with_delay_P(PSTR("mstsc"), 10);
      send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
    }
    break;
  }
  return process_record_keymap(keycode, record);
}
