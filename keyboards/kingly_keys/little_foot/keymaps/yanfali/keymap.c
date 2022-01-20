
#include QMK_KEYBOARD_H

// Layer names
enum{
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN,
  // - Alternate Function layer:
  _LN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_split_space_base(
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,             KC_0,
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,             KC_P,
    LCTL_T(KC_A),   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,          KC_SCLN,
    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,         KC_SLSH,
                LSFT_T(KC_ESC),          LGUI_T(KC_SPACE),          LT(_LN, KC_BSPC),                 LT(_FN, KC_ENT)
  ),

  [_FN] = LAYOUT_split_space_base(
    LT(_LN, KC_ESC), _______, _______, _______, _______, _______, _______,  _______, KC_MINS, RESET,
    KC_TAB,  _______, _______, _______, _______, _______, _______, _______, LSFT(KC_MINS),    KC_BSLS,
    KC_LSFT, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC,          KC_QUOT,
    AU_TOG,  CK_TOGG , _______, _______, _______, _______, _______, _______, _______,          _______,
                  _______,            KC_LALT,        RGB_MOD,              _______
  ),

  [_LN] = LAYOUT_split_space_base(
    _______,   KC_F1,   KC_F2,  KC_F3,    _______,    _______,   _______,    KC_7,    KC_8,    KC_9,
    _______,   KC_F4,   KC_F5,  KC_F6,    _______,    _______,   _______,    KC_4,    KC_5,    KC_6,
    _______,   KC_F7,   KC_F8,  KC_F9,    _______,    _______,   _______,    KC_1,    KC_2,    KC_3,
    _______,   KC_F10,  KC_F11, KC_F12,   _______,    _______,   _______,   _______,  KC_0, _______,
                  _______,             _______,          _______,                _______
  )
};
