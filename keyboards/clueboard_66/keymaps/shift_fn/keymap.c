#include "clueboard_66.h"

// Helpful defines
#define _______ KC_TRNS

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _CL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = KEYMAP(
  KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,  KC_BSPC,          KC_PGUP, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,                   KC_PGDN, \
  KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,                             \
  MO(_FL), KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_RO,    KC_RSFT,          KC_UP,            \
  KC_LCTL, KC_LGUI, KC_LALT,KC_MHEN,          KC_SPC, KC_SPC,                        KC_HENK,  KC_RALT,  KC_RGUI,  KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_GRV, KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,    KC_F6,    KC_F7,  KC_F8,  KC_F9,     KC_F10,    KC_F11,    KC_F12,    S(KC_GRV), KC_DEL,           BL_STEP,    \
  S(KC_TAB), S(KC_Q),   S(KC_W),S(KC_E),S(KC_R),S(KC_T),  S(KC_Y),  S(KC_U),S(KC_I),S(KC_O),   S(KC_P),   S(KC_LBRC),S(KC_RBRC),S(KC_BSLS),                  S(KC_PGDN), \
  S(KC_LCTL),S(KC_A),   MO(_CL),S(KC_D),S(KC_F),S(KC_G),  S(KC_H),  S(KC_J),S(KC_K),S(KC_L),   S(KC_SCLN),S(KC_QUOT),S(KC_NUHS),S(KC_ENT),                               \
  MO(_FL),   S(KC_NUBS),S(KC_Z),S(KC_X),S(KC_C),S(KC_V),  S(KC_B),  S(KC_N),S(KC_M),S(KC_COMM),S(KC_DOT), S(KC_SLSH),S(KC_RO),  KC_RSFT,           KC_PGUP,             \
  KC_LCTL,   KC_LALT,   KC_LGUI,KC_MHEN,        S(KC_SPC),S(KC_SPC),                           KC_HENK,   KC_RGUI,   KC_RALT,   KC_RCTL,   KC_HOME, KC_PGDN, KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = KEYMAP(
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______, RGB_TOG,              RGB_VAI, \
  _______, _______, _______,_______,RESET,  _______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                       RGB_VAD, \
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                                \
  MO(_FL), _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  MO(_FL),               RGB_SAI,         \
  _______, _______, _______,_______,        RGB_MOD,RGB_MOD,                            _______,  _______,  _______,  _______, RGB_HUD,RGB_SAD,RGB_HUI),
};
