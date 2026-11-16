#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "../adaptive_keys.h"
#include "../skip_repeat.h"

enum combo_events {
  CE_RL,
  CE_OI
};

const uint16_t PROGMEM punc_layer_combo[] = {KC_SPC, KC_E, COMBO_END};
const uint16_t PROGMEM rl_combo[] = {KC_R, KC_L, COMBO_END};
const uint16_t PROGMEM oi_combo[] = {KC_O, KC_I, COMBO_END};

combo_t key_combos[] = {
  [CE_RL] = COMBO_ACTION(rl_combo),
  [CE_OI] = COMBO_ACTION(oi_combo),
  COMBO(punc_layer_combo, OSL(5))
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CE_RL:
      if (pressed) {
        tap_code16(KC_R);
        tap_code16(KC_L);
      }
      break;
    case CE_OI:
      if (pressed) {
        tap_code16(KC_O);
        tap_code16(KC_I);
      }
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_adaptive_swap(keycode, record)) { return false; }
    if (!process_adaptive_magic(keycode, record)) { return false; }
    if (!process_skip_repeat(keycode, record)) { return false; }
    return true;
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    if (!remember_last_key_adaptive(keycode, record, remembered_mods)) { return false; }
    if (!remember_last_key_skip_repeat(keycode, record, remembered_mods)) { return false; }

    return true;
}
