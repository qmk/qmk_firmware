#include "stanrc85.h"

static td_state_t td_state;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// determine the tapdance state to return
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}

// handle the possible states for each tapdance keycode you define:
void ctl_copy_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      SEND_STRING(SS_LCTL("c"));
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTL("v"));
  }
}

void ctl_copy_reset (tap_dance_state_t *state, void *user_data) {
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

#if defined(HAS_ROTARY)
  bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
  }
#endif

#if defined(HAS_INDICATORS)
  static uint8_t led_user = 0;
#endif

void lock_unlock (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP: // Ctl + Alt + Del to unlock workstation
    tap_code16(KC_CAD);
    #if defined(HAS_INDICATORS)
      led_user = 0;
      #if defined(KEYBOARD_sneakbox_aliceclone) || defined(KEYBOARD_mechlovin_adelais_standard_led_arm_rev4_stm32f303)
        led_user = 1;
      #endif
      writePin(INDICATOR_PIN_0, !led_user);
      wait_ms(200);
      writePin(INDICATOR_PIN_1, !led_user);
      wait_ms(200);
      writePin(INDICATOR_PIN_2, !led_user);
    #endif
      break;
    case SINGLE_HOLD:
      break;
    case DOUBLE_TAP: //Lock workstation
    tap_code16(KC_LOCK);
    #if defined(HAS_INDICATORS)
      led_user = 1;
      #if defined(KEYBOARD_sneakbox_aliceclone) || defined(KEYBOARD_mechlovin_adelais_standard_led_arm_rev4_stm32f303)
        led_user = 0;
      #endif
      writePin(INDICATOR_PIN_2, !led_user);
      wait_ms(200);
      writePin(INDICATOR_PIN_1, !led_user);
      wait_ms(200);
      writePin(INDICATOR_PIN_0, !led_user);
    #endif
      break;
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_WIN] = ACTION_TAP_DANCE_FN(lock_unlock),
  [TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
  [TD_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_copy_finished, ctl_copy_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_MAKE:
    if (!record->event.pressed) {
      uint8_t mods = get_mods();
      clear_mods();
        if (mods & MOD_MASK_SHIFT) {
          send_string_with_delay_P(PSTR("qmk flash -j 6 -kb " QMK_KEYBOARD " -km " QMK_KEYMAP "\n"), 10); //New way
          reset_keyboard();
        }
        else
          send_string_with_delay_P(PSTR("qmk compile -j 6 -kb " QMK_KEYBOARD " -km " QMK_KEYMAP "\n"), 10); //New way
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
