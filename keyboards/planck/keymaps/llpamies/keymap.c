#include QMK_KEYBOARD_H

#include "llpamies.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_planck_grid(
  KC_TAB,    KC_Q,        KC_W,    KC_F,          KC_P,      KC_B,      KC_J,   KC_L,    KC_U,           KC_Y,    KC_SCOLON, KC_BSLASH,
  KC_ESCAPE, MY_A,        MY_R,    MY_S,          KC_T,      KC_G,      KC_M,   KC_N,    MY_E,           MY_I,    MY_O,      KC_ENTER,
  KC_LSHIFT, KC_Z,        KC_X,    KC_C,          KC_D,      KC_V,      KC_K,   KC_H,    KC_COMMA,       KC_DOT,  KC_SLASH,  KC_QUOTE,
  KC_LCTRL,  KC_CAPSLOCK, KC_LALT, UNIQ(KC_LEFT), SYMB_BSPC, KC_DELETE, KC_TAB, NAV_SPC, UNIQ(KC_RIGHT), KC_COLN, _______,   _______
),

[_SYMBOL] = LAYOUT_planck_grid(
  KC_TILD,  KC_EXLM, KC_AT,   KC_HASH,     KC_DLR,      KC_PERC, KC_CIRC,   KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN,  KC_PIPE,
  KC_GRAVE, KC_1,    KC_2,    KC_3,        KC_4,        KC_5,    KC_6,      KC_7,    KC_8,     KC_9,    KC_0,     KC_BSLASH,
  _______,  KC_LCBR, KC_RCBR, KC_LBRACKET, KC_RBRACKET, KC_COLN, KC_SCOLON, KC_UNDS, KC_MINUS, KC_PLUS, KC_EQUAL, _______,
  _______,  _______, _______, _______,     _______,     _______, _______,   _______, _______,  _______, _______,  _______
),

[_NAVIGATION] = LAYOUT_planck_grid(
  _______, VIM_QUIT, VIM_WRITE, _______, _______, _______, LCTL(KC_H), LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), _______, _______,
  _______, _______,  _______,   _______, _______, _______, KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______, _______,
  _______, _______,  VIM_SAVE,  _______, _______, _______, KC_HOME,    KC_PGDOWN,  KC_PGUP,    KC_END,     _______, _______,
  _______, _______,  _______,   _______, _______, _______, _______,    _______,    _______,    _______,    _______, _______
),

[_ADJUST] = LAYOUT_planck_grid(
  _______, _______, DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, RESET,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)
};
