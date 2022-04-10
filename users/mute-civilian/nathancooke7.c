#include "nathancooke7.h"

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
           return TAPPING_TERM - 100;
        case RSFT_T(KC_J):
            return TAPPING_TERM - 100;
        case LT(_SYMBOLS, KC_ENT):
            return TAPPING_TERM - 75;
        case LT(_NAV, KC_SPC):
            return TAPPING_TERM - 75;
        default:
           return TAPPING_TERM;
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (IS_LAYER_ON(_NAV)) {
      if (clockwise) {
        tap_code(KC_MS_WH_UP);
      } else {
        tap_code(KC_MS_WH_DOWN);
     }
    } else if (IS_LAYER_ON(_SYMBOLS)) {
      if (clockwise) {
        tap_code(KC_MS_WH_LEFT);
      } else {
        tap_code(KC_MS_WH_RIGHT);
     }
    } else if (IS_LAYER_ON(_MISC)){
      if (clockwise) {
        tap_code(KC_NO);
      } else {
        tap_code(KC_NO);
     }
    } else {
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
   }
  }
  return true;
}
#endif

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_AMPERSAND:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}
