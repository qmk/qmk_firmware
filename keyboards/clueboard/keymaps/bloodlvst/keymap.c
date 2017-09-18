#include "clueboard.h"

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
  KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_INS,  KC_DEL,           KC_PGUP, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,                   KC_PGDN, \
  KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,                             \
  KC_LSPO, KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_RO,    KC_RSPC,          KC_UP,            \
  KC_LCTL, KC_LGUI, MO(_FL), KC_LALT,          KC_BSPC,KC_SPC,                       KC_RALT,  KC_APP,   MO(_FL),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_HOME, KC_END,           KC_VOLU, \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,KC_SLCK, KC_PAUS,  _______,  _______,  KC_MUTE,                   KC_VOLD, \
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  KC_PSCR,                            \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,          KC_MPLY,          \
  _______, KC_MYCM, MO(_FL), _______,        _______,_______,                        _______,  KC_CALC,  MO(_FL),  _______, KC_MPRV, KC_MSTP, KC_MNXT),

  /* Keymap _CL: Control layer
   */
[_CL] = KEYMAP(
  KC_PWR,  _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______, RGB_TOG,          RGB_VAI, \
  _______, _______, _______,_______,RESET,  _______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                   RGB_VAD, \
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  RGB_MOD,                            \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,RGB_HUD, RGB_HUI,  _______,  _______,  _______,          KC_WAKE,          \
  _______, _______, MO(_FL), _______,        RGB_SAD,RGB_SAI,                        _______,  _______,  MO(_FL),  _______, _______, KC_SLEP, _______),
};
