#include "edvorakjp.h"

#if TAP_DANCE_ENABLE != yes
static uint16_t time_on_pressed;
#endif
/*
 * Each process_record_* methods defined here are
 * return false if handle edvorak_keycodes, or return true others.
 */
bool process_record_edvorakjp_swap_scln(uint16_t keycode, keyrecord_t *record) {
#ifdef SWAP_SCLN
  static const uint8_t shift_bits = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);
  static uint8_t last_mods_status;
  if (keycode == KC_SCLN) {
    if (record->event.pressed) {
      last_mods_status = get_mods();

      // invert shift_bits
      if (last_mods_status & shift_bits) {
        set_mods(last_mods_status & ~shift_bits);
      } else {
        set_mods(last_mods_status | MOD_BIT(KC_LSFT));
      }
    } else {
      set_mods(last_mods_status);
      last_mods_status = 0;
    }
  }
#endif
  return true;
}

bool process_record_edvorakjp_config(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAC:
    case KC_WIN:
      if (record->event.pressed) {
        set_enable_kc_lang(keycode == KC_MAC);
      }
      return false;
  }
  return true;
}

bool process_record_layer(uint16_t keycode, keyrecord_t *record) {
#if TAP_DANCE_ENABLE != yes
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_LOWER);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          set_japanese_mode(false);
        }
        time_on_pressed = 0;
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_RAISE);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          set_japanese_mode(true);
        }
        time_on_pressed = 0;
      }
      return false;
  }
#endif
  return true;
}

bool process_record_ime(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_JPN:
    case KC_ENG:
      if (record->event.pressed) {
        set_japanese_mode(keycode == KC_JPN);
      }
      return false;
  }
  return true;
}
