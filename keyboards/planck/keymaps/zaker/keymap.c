// Sondre Naustdal       Custom Planck Keyboard layout
#include "planck.h"
#define PLANCK_YES                  // This is the Planck
#include "zaker_common_functions.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = { /* Base Layer */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP, KC_ENT},
  {CTRLB,   TD(SUP), KC_LALT, KC_LCTL, TD(LOW), KC_SPC, KC_BSPC, TD(RAI), KC_SLSH, KC_LEFT, KC_DOWN,   KC_RGHT}
},
[_RAISE] = { /* RAISE - Numpad and Unicode symbols */
  {KC_GRV,  SUPA2,   RANDIG, LSQBRKT, RSQBRKT,   KC_AT,    KC_7,    KC_8,  KC_9, KC_COLN, XXXXXXX,    XXXXXXX},
  {KC_DEL,  ALPHA,  DOLLAR,  LSPRNTS, RSPRNTS,   KC_MINS,  KC_4,    KC_5,  KC_6, KC_SLSH, KC_ENT,   KC_ASTR},
  {_______, KC_COLN, XXXXXXX,  INTER,   FNUTT,     KC_SLSH,  KC_1,    KC_2,  KC_3, KC_0, KC_PGUP,  _______},
  {_______, KC_PIPE, _______,  _______, _______, KC_TAB, KC_DEL,  _______, _______, KC_HOME, KC_PGDN,  KC_END}
},
[_LOWER] = { /* LOWER - Symbols, Paging, CtrAltDel */
  {KC_TILD,KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, KC_DQT,  KC_DEL},
  {_______, KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_HOME, KC_END,  KC_LPRN, KC_RPRN, KC_SLSH, KC_SCLN, KC_PGUP},
  {_______,KC_F9,   KC_F10,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_BSLS, KC_COLN, _______},
  {_______, _______, _______, _______, _______, KC_TAB,  KC_DEL,  _______, _______, _______, _______, _______}
},

[_ADJUST] = { /* ADJUST - Macros, Layer Switching, Function Keys */
  {_______,  XXXXXXX, XXXXXXX, _______,   _______,    KC_INS,  KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX},
  {_______,  XXXXXXX, XXXXXXX, RANDIG,  RANDIG,  _______,  _______,     KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX},
  {_______, CADKEY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX},
  {_______, _______, _______, _______, _______, RESET,   RESET,   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
}
};
