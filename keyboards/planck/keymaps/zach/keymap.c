// Zach Nielsen     Custom Planck Keyboard layout
#include QMK_KEYBOARD_H
#define PLANCK_YES                  // This is the Planck
#include "zach_common_functions.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_planck_grid( /* Base Layer */
  KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_J,   KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_BSPC,
  KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_H,   KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
  SHFT_CAP,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_K,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  CTRLB,   TD(SUP), KC_LALT, KC_LCTL, TD(LOW), KC_SPC, KC_SPC, TD(RAI), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_SWCOLE] = LAYOUT_planck_grid( /* Software Colemak */
  _______, CM_Q,    CM_W,    CM_F,    CM_P,    CM_G,    CM_J,    CM_L,    CM_U,    CM_Y,    KC_QUOT, _______,
  _______, CM_A,    CM_R,    CM_S,    CM_T,    CM_D,    CM_H,    CM_N,    CM_E,    CM_I,    CM_O,    _______,
  _______, CM_Z,    CM_X,    CM_C,    CM_V,    CM_B,    CM_K,    CM_M,    CM_COMM, CM_DOT,  CM_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_planck_grid( /* RAISE - Numpad and Unicode symbols */
  KC_GRV,  SUPA2,   FACE,  DISFACE, SHRUG,   PLUMIN, IBANG,   KC_7,    KC_8, KC_9, KC_COLN, _______,
  KC_DEL,  DEGREE,  MICRO, WOMEGA,  OMEGA,   PENGY,  KC_ENT,  KC_4,    KC_5, KC_6, KC_SLSH, KC_ASTR,
  _______, KC_COLN, TFLIP, LAROW,   RAROW,   DUCK,   KC_SPC,  KC_1,    KC_2, KC_3, KC_MINS, KC_PLUS,
  _______, KC_PIPE, TPUT,  _______, _______, KC_TAB, KC_TAB,  _______, KC_0, KC_0, KC_DOT,  KC_EQL
),

[_LOWER] = LAYOUT_planck_grid( /* LOWER - Symbols, Paging, CtrAltDel */
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, KC_DQT,  KC_DEL,
  KC_DEL,  KC_LBRC, KC_RBRC, KC_MINS, KC_UNDS, KC_HOME, KC_END,  KC_LPRN, KC_RPRN, KC_SLSH, KC_SCLN, KC_PGUP,
  CPYPST,  XXXXXXX, C(KC_X), KC_LABK, KC_RABK, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_BSLS, KC_COLN, KC_PGDN,
  _______, _______, _______, _______, _______, KC_TAB,  KC_TAB,  _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_planck_grid( /* ADJUST - Macros, Layer Switching, Function Keys */
  UNIWIN,  XXXXXXX, XXXXXXX, PENGY,   DUCK,    KC_INS,  KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,
  UNILIN,  XXXXXXX, XXXXXXX, RANDIG,  RANDIG,  SWCOLE,  COLEMAK, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,
  _______, CADKEY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
  _______, _______, _______, _______, _______, RESET,   RESET,   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_UNICODES] = LAYOUT_planck_grid( /* UNICODES - Extra layer for unicode stuff */
  _______, TFLIP,   XXXXXXX, XXXXXXX, IBANG,   roman7,  XXXXXXX, XXXXXXX, ROMAN7,  XXXXXXX, XXXXXXX, _______,
  KC_DEL,  TPUT,    FACE,    DISFACE, SHRUG,   roman4,  roman5,  roman6,  ROMAN4,  ROMAN5,  ROMAN6,  _______,
  XXXXXXX, XXXXXXX, XXXXXXX, LAROW,   RAROW,   roman1,  roman2,  roman3,  ROMAN1,  ROMAN2,  ROMAN3,  XXXXXXX,
  _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, _______, _______, _______, _______
)
};
