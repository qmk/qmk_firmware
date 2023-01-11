#include QMK_KEYBOARD_H
#include "mechmerlin.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BL] = LAYOUT_66_ansi(
  QK_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL,      KC_BSPC,           KC_PGUP, \
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,                KC_PGDN, \
  KC_CTCP,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,      KC_ENT,                            \
  KC_LSFT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,        KC_UP,         \
  KC_LCTL,KC_LGUI,KC_LALT,                        KC_SPC,                                 MO(_FL),KC_RGUI,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

[_FL] = LAYOUT_66_ansi(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,      KC_DEL,            KC_VOLU, \
  BL_TOGG,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                KC_VOLD, \
  RGB_TOG,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,                             \
  _______,        _______,_______,_______,_______,_______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,        _______,        KC_PGUP,         \
  _______,_______,_______,                        MO(_CL),                                _______,_______,_______,KC_HOME,KC_PGDN,KC_END),

[_CL] = LAYOUT_66_ansi(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______,   _______,           RGB_VAI, \
  _______,_______,_______,EE_CLR, QK_BOOT,_______,_______,_______,_______,_______,_______,_______,_______,_______,                 RGB_VAD, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,                             \
  VK_TOGG,        _______,_______,_______,KC_VER,_______,_______,_______,_______,_______,_______,        _______,        RGB_SAI,         \
  CK_TOGG,_______,_______,                       _______,                                _______,_______,_______,RGB_HUD,RGB_SAD,RGB_HUI),
};
