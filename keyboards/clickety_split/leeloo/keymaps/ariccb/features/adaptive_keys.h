#include QMK_KEYBOARD_H
#include "layer_lock.h"

static uint8_t prior_saved_mods = 0;
static uint16_t prior_keycode =
    KC_NO;
static uint32_t prior_keydown =
    0;
static bool tabbing = false;
static uint16_t tabtimer;
#define TABBING_TIMER 1150

bool process_adaptive_key(uint16_t keycode, const keyrecord_t *record) {

  bool return_state = true;

  if (record->event.pressed) {
    uint8_t saved_mods = get_mods();
    if (saved_mods & MOD_MASK_CAG) {
      // don't interfere if modifiers are involved
      return true;
    }
    if ((timer_elapsed32(prior_keydown) < ADAPTIVE_TERM)) {
      return_state = true;
      unregister_code(KC_LSFT);
      unregister_code(KC_RSFT);
      keycode = keycode & 0xFF;
      uint16_t first = KC_NO;
      uint16_t second = KC_NO;
      switch (prior_keycode) {
      case KC_NO:
        switch (keycode) {

#define AK_BOTH_START(key, def_key)                                            \
  default:                                                                     \
    return_state = true;                                                       \
    tap_code16(first);                                                           \
    }                                                                          \
    break;                                                                     \
  case key:                                                                    \
    first = def_key;                                                           \
    return_state = false;                                                      \
    switch (keycode) {

#define AK_SND_ONLY_START(key) AK_BOTH_START(key, KC_NO)

#define R_BTH(second_key, replaced_key_1, replaced_key_2)                      \
  case second_key:                                                             \
    first = replaced_key_1;                                                    \
    second = replaced_key_2;                                                   \
    break;

#define R_FST(second_key, replaced_key) R_BTH(second_key, replaced_key, keycode)

#define R_SND(second_key, replaced_key)                                        \
  case second_key:                                                             \
    second = replaced_key;                                                     \
    break;

#include "adaptive_keys.def"
        default:
          return_state = true;
          tap_code16(first);
        }
      }
      if (return_state) {
        set_mods(saved_mods);
      } else {
        set_mods(prior_saved_mods);
        tap_code16(first);
        // uncomment below if it doesn't work to fix the missing caps when adaptive keys are pressed while SHIFT is held
        clear_mods();
        set_mods(prior_saved_mods);
        tap_code16(second);
      }
    }
    switch (keycode) {
#undef AK_BOTH_START
#undef AK_SND_ONLY_START
#undef R_BTH
#undef R_FST
#undef R_SND
#define AK_BOTH_START(key, ...)                                                \
  case key:                                                                    \
    return_state = false;                                                      \
    break;
#define AK_SND_ONLY_START(...)
#define R_BTH(...)
#define R_FST(...)
#define R_SND(...)
#include "adaptive_keys.def"
    }
    // Restore mods
    prior_saved_mods = saved_mods;

    prior_keycode = keycode;        // this keycode is stripped of mods+taps
    prior_keydown = timer_read32(); // (re)start prior_key timing
  }
  return return_state;
}

void matrix_scan_user(void) {
  layer_lock_task();
  if (timer_elapsed32(prior_keydown) >= ADAPTIVE_TERM) { // 30 seconds
    switch (prior_keycode) {
#undef AK_BOTH_START
#define AK_BOTH_START(key, default_key)                                        \
  case key:                                                                    \
    tap_code16(default_key);                                                     \
    break;

#include "adaptive_keys.def"
    }
    prior_keydown = timer_read32();
    prior_keycode = KC_NO;
  }
  if(tabbing) {
    if (timer_elapsed(tabtimer) > TABBING_TIMER) {
      unregister_code(KC_LALT);
      tabbing = false;
    }
  }
}

#undef AK_BOTH_START
#undef AK_SND_ONLY_START
#undef R_BTH
#undef R_FST
#undef R_SND