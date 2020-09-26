// Zach Nielsen     Custom Preonic Keyboard layout
#include QMK_KEYBOARD_H
#define PREONIC_YES                 // This is the Preonic
#include "zach_common_functions.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_preonic_1x2uC(  /* Base Layer */
  KC_ESC,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_ENT,  \
  KC_BSPC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,  \
  SHFT_CAP, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  CTRLB,    TD(SUP), KC_LALT, KC_LCTL, TD(LOW),      KC_SPC,      TD(RAI), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

[_SWCOLE] = LAYOUT_preonic_1x2uC(  /* Software Colemak */
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, CM_Q,    CM_W,    CM_F,    CM_P,    CM_G,    CM_J,    CM_L,    CM_U,    CM_Y,    KC_QUOT, _______, \
  _______, CM_A,    CM_R,    CM_S,    CM_T,    CM_D,    CM_H,    CM_N,    CM_E,    CM_I,    CM_O,    _______, \
  _______, CM_Z,    CM_X,    CM_C,    CM_V,    CM_B,    CM_K,    CM_M,    CM_COMM, CM_DOT,  CM_SLSH, _______, \
  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______  \
),

[_RAISE] = LAYOUT_preonic_1x2uC(  /* RAISE - Numpad and Unicode symbols */
  KC_TILD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_GRV,  SUPA2,   FACE,    DISFACE, SHRUG,   PLUMIN,  IBANG,   KC_7,    KC_8,    KC_9,    KC_COLN, _______, \
  KC_DEL,  DEGREE,  MICRO,   WOMEGA,  OMEGA,   XXXXXXX, KC_ENT,  KC_4,    KC_5,    KC_6,    KC_SLSH, KC_ASTR, \
  _______, KC_COLN, TFLIP,   LAROW,   RAROW,   XXXXXXX, KC_SPC,  KC_1,    KC_2,    KC_3,    KC_MINS, KC_PLUS, \
  _______, KC_PIPE, TPUT,    _______, _______,      KC_TAB,      _______, KC_0,    KC_0,    KC_DOT,  KC_EQL   \
),

[_LOWER] = LAYOUT_preonic_1x2uC(  /* LOWER - Symbols, Paging, CtrAltDel */
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, KC_DQT,  KC_DEL,  \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, KC_DQT,  KC_DEL,  \
  KC_DEL,  KC_LBRC, KC_RBRC, KC_MINS, KC_UNDS, KC_HOME, KC_END,  KC_LPRN, KC_RPRN, KC_SLSH, KC_SCLN, KC_PGUP, \
  CPYPST,  XXXXXXX, C(KC_X), KC_LABK, KC_RABK, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_BSLS, KC_COLN, KC_PGDN, \
  _______, _______, _______, _______, _______,      KC_TAB,      _______, _______, _______, _______, _______  \
),

[_ADJUST] = LAYOUT_preonic_1x2uC(  /* ADJUST - Macros, Layer Switching, Function Keys */
  UNIWIN,  XXXXXXX, XXXXXXX, RANDIG,  RANDIG,  KC_INS,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, AU_TOG, MU_TOG,  \
  UNILIN,  SUPA2,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,    KC_F2,   KC_F3,   KC_F4,  XXXXXXX, \
  XXXXXXX, DEGREE,  IBANG,   LAROW,   RAROW,   SWCOLE,  COLEMAK, KC_F5,    KC_F6,   KC_F7,   KC_F8,  BL_INC,  \
  _______, CADKEY,  MICRO,   WOMEGA,  OMEGA,   XXXXXXX, XXXXXXX, KC_F9,    KC_F10,  KC_F11,  KC_F12, BL_DEC,  \
  _______, _______, _______, _______, _______,      RESET,       _______,  XXXXXXX, MUV_DE,  MUV_IN, BL_TOGG  \
),

[_UNICODES] = LAYOUT_preonic_1x2uC(  /* UNICODES - Extra layer for unicode stuff */
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, TFLIP,   XXXXXXX, XXXXXXX, IBANG,   roman7,  XXXXXXX, XXXXXXX, ROMAN7,  XXXXXXX, XXXXXXX, _______, \
  KC_DEL,  TPUT,    FACE,    DISFACE, SHRUG,   roman4,  roman5,  roman6,  ROMAN4,  ROMAN5,  ROMAN6,  _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, LAROW,   RAROW,   roman1,  roman2,  roman3,  ROMAN1,  ROMAN2,  ROMAN3,  XXXXXXX, \
  _______, _______, _______, _______, _______,     KC_SPC,       _______, _______, _______, _______, _______  \
)
};
