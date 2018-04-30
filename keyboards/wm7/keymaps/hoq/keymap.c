// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "wm7.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NML 0
#define _FUN 1

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NML] = KEYMAP(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,            KC_BSPC, KC_ESC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSLS, KC_INS, \
  KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,  KC_DEL, \
  KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_FUN), KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, KC_UP, \
  KC_LCTL,          KC_LALT, KC_SPC,  MO(_FUN),                           KC_SPC, KC_RALT,                   KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT),

[_FUN] = KEYMAP(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           _______, _______, \
  _______, RGB_TOG, RGB_MOD, RGB_VAI, RESET,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, \
  _______,          _______, _______, _______,                            _______, _______,                   _______, KC_HOME, KC_PGDN, KC_END),
};

const uint16_t PROGMEM fn_actions[] = {
};
