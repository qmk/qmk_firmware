#include "process_records.h"

#ifdef TAP_DANCE_ENABLE
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [COMM_QUOT]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUOT),
  [BACKSPACE] = ACTION_TAP_DANCE_DOUBLE (KC_BSPACE, LCTL(KC_BSPACE)),
  [DELETE] = ACTION_TAP_DANCE_DOUBLE (KC_DELETE, LCTL(KC_DELETE))
};
#endif

#if defined(RGB_MATRIX_ENABLE)
extern void eeconfig_update_rgb_matrix_default(void);
#endif

#ifdef TRILAYER_ENABLED
uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
#endif

#ifndef TAP_DANCE_ENABLE
static uint16_t td_keycode;
static uint16_t td_timer;

const uint16_t PROGMEM td_keymaps[TD_MAX - TD_MIN][2] = {
    [TD_COMM - TD_MIN]  = { KC_COMM, KC_QUOT },
    [TD_BSPC - TD_MIN]  = { KC_BSPACE, LCTL(KC_BSPACE) },
    [TD_DEL - TD_MIN]  = { KC_DELETE, LCTL(KC_DELETE) },
    [TD_DOT - TD_MIN]  = { KC_DOT, KC_GRAVE }
};

void do_tap_dance_double(uint16_t keycode, keyrecord_t *record)
{
  if (td_keycode != keycode || timer_read() - td_timer < 0x8000) {
    td_keycode = keycode;
    td_timer = timer_read() + TAPPING_TERM;
    return;
  }

  tap_code16(pgm_read_word(&td_keymaps[td_keycode - TD_MIN][1]));
  td_keycode = KC_TRANSPARENT;
  td_timer = timer_read() + TAPPING_TERM;
}

void matrix_scan_user(void) {
  if (td_keycode != KC_TRANSPARENT && timer_read() - td_timer < 0x8000) {
    tap_code16(pgm_read_word(&td_keymaps[td_keycode - TD_MIN][0]));
    td_keycode = KC_TRANSPARENT;
    td_timer = timer_read() + TAPPING_TERM;
  }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t reset_timer;

#ifndef TAP_DANCE_ENABLE
  if (TD_MIN <= keycode && keycode < TD_MAX) {
    if (record->event.pressed) {
      do_tap_dance_double(keycode, record);
    }

#ifdef RGB_MATRIX_ENABLE
    process_rgb_matrix(keycode, record);
#endif
    return false;
  }

  if (td_keycode != KC_TRANSPARENT) {
    tap_code16(pgm_read_word(&td_keymaps[td_keycode - TD_MIN][0]));
    td_keycode = KC_TRANSPARENT;
    td_timer = timer_read() + TAPPING_TERM;
  }
#endif

  switch (keycode) {
    case RGBRST: {
#if defined(RGBLIGHT_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
#elif defined(RGB_MATRIX_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
        }
        process_rgb_matrix(keycode, record);
#endif
      }
      return false;
    case RESET: {
        if (record->event.pressed) {
          reset_timer = timer_read() + 500;
        } else {
          if (timer_read() - reset_timer < 0x8000) {
            reset_keyboard();
          }
        }
#ifdef RGB_MATRIX_ENABLE
        process_rgb_matrix(keycode, record);
#endif
      }
      return false;
  }

  return process_record_keymap(keycode, record);
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
