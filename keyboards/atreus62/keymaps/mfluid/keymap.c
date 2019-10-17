#include QMK_KEYBOARD_H

#include "action_layer.h"

#define OOOOOOO KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,                      KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,                      KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,  KC_F,  KC_G,                      KC_H,   KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSPO, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,                      KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT, MO(3), MO(1), KC_BSPC, KC_RCTL, KC_ENT,  KC_SPC, MO(2), KC_DEL,  KC_EQL, KC_LBRC, KC_RBRC 
  ),

  [1] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,                   _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,                   _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, KC_PGUP,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                   _______, KC_P0,   KC_PDOT, KC_PENT, KC_PPLS, KC_PGDN,
    _______, _______, _______, _______, OOOOOOO, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
  ),

  [2] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,
    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
    _______, _______, KC_MPLY, KC_MRWD, KC_MFFD, _______,                   _______, KC_BTN1, KC_BTN2, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, OOOOOOO, _______, _______, _______, _______ 
  ),

  [3] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______,  _______,  _______,
    _______, _______, _______, _______, _______, _______,                   KC_COPY, KC_PGUP, _______, _______,  KC_PASTE, KC_DEL,
    _______, _______, _______, KC_PGDN, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,  _______,
    _______, _______, KC_CUT,  _______, _______, _______,                   _______, _______, _______, _______,  _______,  _______,
    _______, _______, _______, OOOOOOO, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______ 
  )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch (id) {
  case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
    }
    else {
      unregister_code(KC_RSFT);
    }
    break;
  }
  return MACRO_NONE;
};

