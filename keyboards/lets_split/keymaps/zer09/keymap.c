#include "zer09.h"

#undef LAYOUT
#define LAYOUT( \
  L00, L01, L02, L03, L04,     R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,     R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,     R20, R21, R22, R23, R24, \
  L30, L31, L32, L33, L34,     R30, R31, R32, R33, R34, \
  L40, L41, L42, L43, L44,     R40, R41, R42, R43, R44 \
) { \
  { L00, L01, L02, L03, L04 }, \
  { L10, L11, L12, L13, L14 }, \
  { L20, L21, L22, L23, L24 }, \
  { L30, L31, L32, L33, L34 }, \
  { L40, L41, L42, L43, L44 }, \
  { R00, R01, R02, R03, R04 }, \
  { R10, R11, R12, R13, R14 }, \
  { R20, R21, R22, R23, R24 }, \
  { R30, R31, R32, R33, R34 }, \
  { R40, R41, R42, R43, R44 } \
}

#define _baseLayer LAYOUT( \
  KC_QUOTE,    KC_COMMA,    KC_DOT,      KC_P,        KC_Y,           /**/KC_F,           KC_G,        KC_C,        KC_R,        KC_L,        \
  CTL_T(KC_A), SFT_T(KC_O), ALT_T(KC_E), KC_U,        KC_I,           /**/KC_D,           KC_H,        ALT_T(KC_T), SFT_T(KC_N), CTL_T(KC_S), \
  KC_SCLN,     KC_Q,        KC_J,        KC_K,        KC_X,           /**/KC_B,           KC_M,        KC_W,        KC_V,        KC_Z,        \
  TD(DA_UPLY), MO(_VL),     KC_TAB,      KC_BSPC,     KC_ESC,         /**/KC_INS,         KC_HOME,     KC_PGUP,     MO(_VL),     TD(DA_UPLY), \
  TD(DA_DWLY), TD(DA_LCTL), KC_SPC,      TD(DA_LSPR), LSFT_T(KC_CAPS),/**/SFT_T(KC_CAPS), TD(DA_RALT), KC_ENT,      TD(DA_RCTL), TD(DA_DWLY))

#define _GMLayer LAYOUT(                                              \
  KC_QUOTE,    KC_COMMA,    KC_DOT,      KC_P,        KC_Y,           /**/KC_F,           KC_G,        KC_C,        KC_R,        KC_L, \
  KC_A,        KC_O,        KC_E,        KC_U,        KC_I,           /**/KC_D,           KC_H,        ALT_T(KC_T), SFT_T(KC_N), CTL_T(KC_S), \
  KC_SCLN,     KC_Q,        KC_J,        KC_K,        KC_X,           /**/KC_B,           KC_M,        KC_W,        KC_V,        KC_Z, \
  TD(DA_UPLY), MO(_VL),     KC_TAB,      KC_BSPC,     KC_ESC,         /**/KC_INS,         KC_HOME,     KC_PGUP,     MO(_VL),     TD(DA_UPLY), \
  TD(DA_DWLY), TD(DA_LCTL), KC_SPC,      TD(DA_LSPR), LSFT_T(KC_CAPS),/**/SFT_T(KC_CAPS), TD(DA_RALT), KC_ENT,      TD(DA_RCTL), TD(DA_DWLY))

#define _upLayer LAYOUT( \
  KC_4,          KC_5,          KC_6,          KC_YREG,  _______,/**/ _______,  KC_RBRC,  _______,  _______,  _______, \
  LCTL_T(KC_1),  LSFT_T(KC_2),  LALT_T(KC_3),  _______,  _______,/**/ KC_LBRC,  KC_BSLS,  _______,  _______,  _______, \
  KC_7,          KC_8,          KC_9,          KC_0,     KC_GRV, /**/ KC_SLSH,  _______,  _______,  _______,  _______, \
  _______,       _______,       _______,       _______,  _______,/**/ KC_DEL,   KC_END,   KC_PGDN,  _______,  _______, \
  _______,       _______,       _______,       _______,  _______,/**/ _______,  _______,  _______,  _______,  _______)

#define _downLayer LAYOUT( \
  KC_F4,         KC_F5,         KC_F6,         KC_F12,   _______,/**/ _______,  KC_RPRN,  _______,  _______,  _______,  \
  LCTL_T(KC_F1), LSFT_T(KC_F2), LALT_T(KC_F3), KC_F11,   _______,/**/ KC_LPRN,  KC_EQUAL, KC_LEFT,  KC_UP,    KC_RIGHT, \
  KC_F7,         KC_F8,         KC_F9,         KC_F10,   _______,/**/ KC_MINUS, _______,  _______,  KC_DOWN,  _______,  \
  _______,       _______,       _______,       _______,  _______,/**/ KC_PSCR,  KC_SCRL,  KC_PAUSE, _______,  _______,  \
  _______,       _______,       _______,       _______,  _______,/**/ _______,  _______,  _______,  _______,  _______)

#define _astdLayer LAYOUT( \
  KC_MPRV,     KC_MUTE,      _______,      _______,      _______,/**/KC_PSCR,   KC_SCRL,  KC_PAUSE, _______, KC_RGUP,  \
  KC_MPLY,     KC_VOLD,      _______,      _______,      _______,/**/_______,   _______,  _______,  _______, KC_RGDWN, \
  KC_MNXT,     KC_VOLU,      QK_BOOT,      _______,      _______,/**/_______,   _______,  QK_BOOT,  _______, _______,  \
  _______,     _______,      _______,      _______,      _______,/**/_______,   _______,  _______,  _______, _______,  \
  _______,     _______,      _______,      _______,      _______,/**/_______,   _______,  _______,  _______, _______)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = _baseLayer,
    [_UL] = _upLayer,
    [_DL] = _downLayer,
    [_VL] = _upLayer,
    [_AL] = _astdLayer,
    [_GM] = _GMLayer};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case YREG:
      SEND_STRING("\"0p");
      return false;
    }
  }

  return true;
}
