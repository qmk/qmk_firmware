#include QMK_KEYBOARD_H
#include "nchristus.h"

#define RAISE LT(_RAISE, KC_ENT)
#define LOWER LT(_LOWER, KC_SPC)

#define _QWRTY 0
#define _LOWER 1
#define _RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWRTY] = KEYMAP_wrapper(
    KC_TAB,  __________________QWERTYL1_________________, __________________QWERTYR1_________________, KC_BSPC,
    CTL_ESC, __________________QWERTYL2_________________, __________________QWERTYR2_________________, KC_QUOT,
    KC_LSFT, __________________QWERTYL3_________________, __________________QWERTYR3_________________, KC_RSFT,
    _______, KC_LCTL, KC_LALT, KC_LGUI, RAISE,   RAISE,   LOWER,   LOWER,   KC_RGUI, KC_RALT, KC_RCTL, _______
  ),
  [_LOWER] = KEYMAP_wrapper(
    KC_GRV,  _________________LOWER_L1__________________, _________________LOWER_R1__________________, _______,
    _______, _________________LOWER_L2__________________, _________________LOWER_R2__________________, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, RESET
  ),
  [_RAISE] = KEYMAP_wrapper(
    KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, _______,
    _______, _________________RAISE_L2__________________, _________________RAISE_R2__________________, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    RESET,   ___________________BLANK___________________, ___________________BLANK___________________, _______
  ),
  [_ARROW] = KEYMAP_wrapper(
    _______, _______, KC_UP,   _______, _______, _______, ___________________BLANK___________________, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, _______, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
  ),
  [_ADJST] = KEYMAP_wrapper(
    C_O_ESC, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    _______, _______, _______, OPW_CPY, OPW_OPN, _______, _______, SCR_FLL, SCR_CRP, _______, _______, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    RESET,   ___________________BLANK___________________, ___________________BLANK___________________, RESET
  ),
};

const uint16_t PROGMEM fn_actions[] = {
};

uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJST);
  return state;
}

