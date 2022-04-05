#pragma once
#include QMK_KEYBOARD_H
#include <stdio.h>

#include "features/caps_word.h"
#include "features/pointing.h"
#include "process_records.h"

enum userspace_layers{
  _BASE,
  _MOUSE,
  _MISC,
  _NAV,
  _SYMBOLS,
  _WORDS
};

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
