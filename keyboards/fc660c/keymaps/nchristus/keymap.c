#include QMK_KEYBOARD_H
#include "nchristus.h"

#define CTRLESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = KEYMAP_wrapper(
    KC_GESC, ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,   KC_BSLS, KC_INS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSPC, KC_DEL,
    CTRLESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
    KC_CAPS, KC_LALT, KC_LGUI, KC_SPC,  KC_RALT, KC_RCTL, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [1] = KEYMAP_wrapper(
    _______, _________________FUNC_LEFT_________________, _________________FUNC_RIGHT________________, KC_F11,  KC_F12,   _______, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______, _______,  _______, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

const uint16_t PROGMEM fn_actions[] = {
};
