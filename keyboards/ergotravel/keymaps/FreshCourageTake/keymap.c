#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _ARROWS 1
#define _SYMBOLS 2
#define _NUMFUN 3
#define _NUMPAD 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.                        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,                          _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|                        |--------+--------+--------+--------+--------+--------+--------|
     KC_TAB,  LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D),    KC_F,    KC_G,    _______,      _______, KC_H,    KC_J, RALT_T(KC_K), RSFT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|                        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, LCTL_T(KC_Z), LSFT_T(KC_X), LALT_T(KC_C), KC_V, KC_B, _______,                 _______, KC_N, KC_M, RALT_T(KC_COMM), RSFT_T(KC_DOT), RCTL_T(KC_SLSH), KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|                        |--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, MO(_NUMFUN),   LT(_NUMPAD, KC_DELETE),   LT(_ARROWS, KC_ENT),           LT(_SYMBOLS, KC_SPC),  LT(_NUMPAD, KC_BSPC), MO(_NUMFUN), _______,   _______, _______
  //`--------+--------+--------+--------+--------+--------+--------/                        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_ARROWS] = LAYOUT(
  _______, LCTL(KC_A),  LCTL(KC_S),   LCTL(KC_D), LCTL(KC_F),  LCTL(KC_R), _______,          _______,     KC_LABK, KC_HOME, KC_UP, KC_END, KC_LCBR, KC_BRIU,  \
  _______, KC_LCTL,    KC_LSFT,   KC_LALT,   KC_LGUI,   LGUI(KC_V),   _______,                  _______,     KC_RABK,   KC_LEFT, KC_DOWN, KC_RIGHT, KC_RCBR, KC_BRID, \
  _______, LCTL(KC_Z),    LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),  LCTL(KC_B),  _______,     _______,     _______,  KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LBRACKET, KC_RBRACKET, _______, \
  _______, _______,  _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______  \

  ),

  [_SYMBOLS] = LAYOUT(
 
  _______,  KC_GRAVE,    KC_PERCENT,  KC_PIPE,   KC_AMPR,    KC_EQUAL,     _______,          _______,     _______,    _______,    _______,    _______,    _______,    _______,  \
  KC_CAPSLOCK, KC_EXCLAIM,    KC_AT,  KC_HASH,   KC_DOLLAR, KC_RABK,  _______,          _______,   _______,   _______, _______,  _______, _______, _______, \
  _______,  KC_CIRC,    KC_ASTR,  KC_UNDERSCORE,   KC_PLUS, KC_MINUS,  _______,          _______,   _______,   _______, _______, _______, _______, _______, \
  _______, _______, _______,  _______, _______, _______,                                 _______, _______, _______, _______, _______, _______  \
  
  ),

  [_NUMPAD] = LAYOUT(
     RESET,  _______,  _______, _______, _______, _______, _______,         _______,  _______, KC_7, KC_8, KC_9, _______, SGUI(KC_S),
     _______, _______,  DM_REC1, DM_RSTP, DM_PLY1, _______, _______,         _______,  _______, KC_4, KC_5, KC_6, _______, _______,
     _______, _______,  DM_REC2, DM_RSTP, DM_PLY2, _______, _______,         _______,  _______, KC_1, KC_2, KC_3, _______, _______,
     _______, _______, _______, _______,           _______, _______,         KC_MINUS,  KC_KP_0,          _______, _______, _______, _______
  ),

  [_NUMFUN] = LAYOUT(
     _______,  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, _______,                   KC_VOLU,  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
     _______, KC_1,  KC_2, KC_3, KC_4, KC_5, _______,                         KC_VOLD,  KC_6, KC_7, KC_8, KC_9, KC_0, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
     _______, _______, _______, _______,           _______, _______,         _______,  _______,          _______, _______, _______, _______
  )

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
