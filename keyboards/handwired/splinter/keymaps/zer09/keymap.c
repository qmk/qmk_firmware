#include "splinter.h"
#include "tap_dance.h"
#include "zer09.h"

#define _baseLayer KEYMAP( \
  KC_QUOTE,    KC_COMMA,    KC_DOT,          KC_P,        KC_Y,        KC_F,   KC_G,        KC_C,            KC_R,        KC_L,        \
  CTL_T(KC_A), SFT_T(KC_O), ALT_T(KC_E),     KC_U,        KC_I,        KC_D,   KC_H,        ALT_T(KC_T),     SFT_T(KC_N), CTL_T(KC_S), \
  KC_SCOLON,   KC_Q,        KC_J,            KC_K,        KC_X,        KC_B,   KC_M,        KC_W,            KC_V,        KC_Z,        \
  TT(_UL),     MO(_VL),     KC_TAB,          KC_BSPACE,   TD(DA_EGRV), KC_INS, KC_HOME,     KC_PGUP,         MO(_VL),     TT(_UL),     \
  TT(_DL),     TD(DA_LCTL), LSFT_T(KC_CAPS), TD(DA_LSPR), KC_SPC,      KC_ENT, TD(DA_RALT), RSFT_T(KC_CAPS), TD(DA_RCTL), TT(_DL))

#define _upLayer KEYMAP( \
  KC_4,          KC_5,          KC_6,          _______,  _______,     _______,  KC_RBRC,  _______,  KC_RGUP,   _______, \
  LCTL_T(KC_1),  LSFT_T(KC_2),  LALT_T(KC_3),  _______,  _______,     KC_LBRC,  KC_BSLS,  _______,  KC_RGDWN,  _______, \
  KC_7,          KC_8,          KC_9,          KC_0,     KC_GRV,      KC_SLSH,  _______,  _______,  _______,   _______, \
  _______,       _______,       _______,       _______,  _______,     KC_DEL,   KC_END,   KC_PGDN,  _______,   _______, \
  _______,       KC_MPLY,       KC_MPRV,       KC_MNXT,  _______,     _______,  _______,  _______,  _______,   _______)

#define _downLayer KEYMAP( \
  KC_F4,          KC_F5,          KC_F6,          KC_F12,   _______,     RESET,     KC_RPRN,   _______,   KC_UP,    KC_RIGHT, \
  LCTL_T(KC_F1),  LSFT_T(KC_F2),  LALT_T(KC_F3),  KC_F11,   _______,     KC_LPRN,   KC_EQUAL,  KC_LEFT,   KC_DOWN,  _______,  \
  KC_F7,          KC_F8,          KC_F9,          KC_F10,   _______,     KC_MINUS,  _______,   _______,   _______,  _______,  \
  _______,        _______,        _______,        _______,  _______,     KC_PSCR,   KC_SLCK,   KC_PAUSE,  _______,  _______, \
  _______,        KC_MUTE,        KC_VOLD,        KC_VOLU,  _______,     _______,   _______,   _______,   _______,  _______)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = _baseLayer,
  [_UL] = _upLayer,
  [_DL] = _downLayer,
  [_VL] = _upLayer
};
