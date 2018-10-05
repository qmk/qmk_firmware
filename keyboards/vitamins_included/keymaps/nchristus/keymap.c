#include QMK_KEYBOARD_H
#include "nchristus.h"

#define RAISE LT(_RAISE, KC_ENT)
#define LOWER LT(_LOWER, KC_SPC)

#define _QWRTY 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWRTY] = KEYMAP_wrapper(
    KC_TAB,  __________________QWERTYL1_________________, __________________QWERTYR1_________________, KC_BSPC,
    CTL_ESC, __________________QWERTYL2_________________, __________________QWERTYR2_________________, KC_QUOT,
    KC_LSFT, __________________QWERTYL3_________________, __________________QWERTYR3_________________, KC_RSFT,
    _______, KC_LCTL, KC_LALT, KC_LGUI, RAISE,   RAISE,   LOWER,   LOWER,   KC_RGUI, KC_RALT, KC_RCTL, _______
  )
};

