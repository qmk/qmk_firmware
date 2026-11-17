#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "../adaptive_keys.h"

const uint16_t PROGMEM punc_layer_combo[] = {KC_SPC, KC_E, COMBO_END};

combo_t key_combos[] = {
  COMBO(punc_layer_combo, OSL(5))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_adaptive_swap(keycode, record)) { return false; }
    if (!process_adaptive_magic(keycode, record)) { return false; }
    return true;
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    if (!remember_last_key_adaptive(keycode, record, remembered_mods)) { return false; }
    return true;
}
