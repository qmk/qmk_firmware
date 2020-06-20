#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer {
    _BASE,
    _FN1,
    _RGB2,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /**
  LA1, LA2, LA3, LA4, LA5, LA6, LA7, RA1, RA2, RA3, RA4, RA5, RA6, RA7, RA8, RA9, \
  LB1, LB2, LB3, LB4, LB5, LB6,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC1, LC2, LC3, LC4, LC5, LC6,      RC1, RC2, RC3, RC4, RC5, RC6,      RC8, RC9, \
  LD1,      LD3, LD4, LD5, LD6, LD7, RD1, RD2, RD3, RD4,      RD6, RD7, RD8, RD9, \
  LE1, LE2, LE3,      LE5,      LE7, RE1, RE2,      RE4, RE5, RE6, RE7, RE8, RE9 \
  ) \
  **/
  [_BASE] = LAYOUT_65(
    KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,       KC_5,       KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   _______,  KC_BSPC,  KC_HOME,  \
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,       KC_T,                 KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,   \
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,       KC_G,                 KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGUP,  \
    KC_LSFT,            KC_Z,     KC_X,     KC_C,       KC_V,       KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,  \
    KC_LCTL,  KC_LALT,  KC_LGUI,            KC_SPC,                 MO(_FN1), KC_SPC,   _______,            KC_RALT,  KC_RCTL,  MO(_FN1), KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_FN1] = LAYOUT_65(
    KC_GESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,      KC_F5,      KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  KC_MUTE,  KC_BRMU,  \
    _______,  _______,  _______,  _______,  _______,    _______,              _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_BRMD,  \
    _______,  _______,  _______,  _______,  _______,    _______,              _______,  _______,  _______,  _______,  _______,  _______,            KC_MPLY,  _______,  \
    _______,            _______,  _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_VOLU,  _______,  \
    _______,  _______,  _______,            TG(_RGB2),              _______,  _______,  _______,            _______,  _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT
  ),

  [_RGB2] = LAYOUT_65(
    KC_GESC,    RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW,   RGB_M_SN,   RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,  \
    _______,    _______,  _______,  _______,  _______,    _______,              _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAD,  \
    _______,    _______,  _______,  _______,  _______,    _______,              _______,  _______,  _______,  _______,  _______,  _______,            _______,  RGB_SAI,  \
    _______,              _______,  _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,            _______,  _______,  RGB_HUI,  RGB_SAD,  \
    _______,    _______,  _______,            _______,                _______,  _______,  _______,            _______,  _______,  _______,  RGB_RMOD, RGB_HUD,  RGB_MOD
  )
};
