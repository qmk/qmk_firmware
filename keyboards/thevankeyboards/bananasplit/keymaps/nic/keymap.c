#include QMK_KEYBOARD_H

#define DEFAULT_LAYER 0
#define THUMB_LAYER   1
#define NORMAN_LAYER  2
#define MOD_LAYER     3

#define HYPER_TAB ALL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT_LAYER] = LAYOUT_hhkb_arrow( \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_DEL, \
    HYPER_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSPC, \
    CTL_T(KC_ESC),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_QUOT, KC_ENT, \
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT,  RSFT_T(KC_SLSH),  KC_UP, TG(NORMAN_LAYER), \
    KC_CAPS,  KC_LALT,  KC_LGUI,  KC_SPC,      MO(THUMB_LAYER),      KC_SPC,  KC_LGUI, KC_LALT,  KC_LEFT, KC_DOWN, KC_RIGHT \
  ),

  [THUMB_LAYER] = LAYOUT_hhkb_arrow( \
    MO(MOD_LAYER), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, \
    _______,  _______,   _______,   _______,   _______,   _______,   _______,   KC_UNDS,   KC_PLUS,   KC_LCBR,   KC_RCBR,   _______, _______, _______, \
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_MINS,   KC_EQL,   KC_LBRC, KC_RBRC,  _______, _______, \
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, _______, \
    _______,  _______,  _______, _______,      _______,      _______,  _______, _______,  _______, _______, _______ \
  ),

  [NORMAN_LAYER] = LAYOUT_hhkb_arrow( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______,  _______,   _______,   KC_D,   KC_F,   KC_K,   KC_J,   KC_U,   KC_R,   KC_L,   KC_SCLN,   _______, _______, _______, \
    _______,   _______,   _______,   KC_E,   KC_T,  _______,   KC_Y,   KC_N,   KC_I,   KC_O,   KC_H,  _______, _______, \
    _______,   _______,   _______,   _______,   _______,   _______,   KC_P,   _______,   _______,  _______,  _______,  _______, _______, \
    _______,  _______,  _______, _______,      _______,      _______,  _______, _______,  _______, _______, _______ \
  ),

  [MOD_LAYER] = LAYOUT_hhkb_arrow( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______,  _______,   _______,   _______,  RESET,  _______,   _______,   _______,   _______,   _______,   _______,   _______, _______, _______, \
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______, _______, \
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, _______, \
    _______,  _______,  _______, _______,      _______,      _______,  _______, _______,  _______, _______, _______ \
  ),
};

const uint16_t PROGMEM fn_actions[] = {
};
