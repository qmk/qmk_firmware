#include "350mimi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: defuault */
  LAYOUT_60_tsangan_hhkb(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLASH, KC_GRAVE,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPACE,
   MT(MOD_LGUI, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, LT(2, KC_ENTER),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
    KC_LCTL, MO(1), KC_LALT,                   KC_SPC,                   KC_RGUI, KC_RALT, KC_RCTL
  ),
/*numpad layer*/
   LAYOUT_60_tsangan_hhkb(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_P7,    KC_P8,    KC_P9,    KC_0,    KC_KP_MINUS, KC_KP_PLUS,  KC_BSLASH, KC_GRAVE,
    KC_TAB,  KC_Q,    TO(4),    KC_E,    KC_R,    KC_T,    KC_Y,    KC_P4,    KC_P5,    KC_P6,    KC_KP_EQUAL,    KC_LBRC, KC_RBRC, KC_BSPACE,
   MT(MOD_LGUI, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H, KC_P1,    KC_P2,    KC_P3,    KC_KP_ASTERISK, KC_QUOT, LT(2, KC_KP_ENTER),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_KP_0,    KC_COMM, KC_KP_DOT,  KC_KP_SLASH, KC_RSFT, MO(1),
    KC_LCTL, MO(1), KC_LALT,                   KC_SPC,                    KC_RGUI, KC_RALT, KC_RCTL
    ),

  /* 1: winkeyless */
  LAYOUT_60_tsangan_hhkb(
    KC_GRAVE,  KC_BRID,    KC_BRIU,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MRWD,    KC_MPLY,    KC_MFFD,    KC_MUTE,    KC_VOLD, KC_VOLU, KC_INS, KC_DEL,
    KC_CAPS,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_UP, KC_RBRC, KC_DEL,
    KC_TRNS, KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_LEFT, KC_RIGHT, LT(2, KC_ENTER),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_DOWN, KC_RSFT,  MO(3),
    KC_LCTL, MO(1), KC_LALT,                   KC_SPC,                   KC_RGUI, KC_RALT, MO(3)
  ),
  /* 3: fn */
  LAYOUT_60_tsangan_hhkb(
    KC_GRAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_INS, KC_DEL,
    KC_CAPS, _______, _______,   _______, RESET, _______, _______, _______, _______, _______, _______, KC_UP,   _______, KC_DEL,
    _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, _______,
    _______, _______, _______, _______, _______, HPT_TOG,HPT_DWLI,HPT_DWLD, _______, _______, KC_DOWN, _______, MO(2),
    _______, _______, _______,                    _______,                  _______, _______,  _______
  ),
  LAYOUT_60_tsangan_hhkb(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLASH, KC_GRAVE,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPACE,
   MT(MOD_LCTL, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, LT(6, KC_ENTER),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(5),
    MO(5), KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RGUI, KC_RCTL
  ),
 LAYOUT_60_tsangan_hhkb(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_P7,    KC_P8,    KC_P9,    KC_0,    KC_KP_MINUS, KC_KP_PLUS,  KC_BSLASH, KC_GRAVE,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_P4,    KC_P5,    KC_P6,    KC_KP_EQUAL,    KC_LBRC, KC_RBRC, KC_BSPACE,
   MT(MOD_LCTL, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H, KC_P1,    KC_P2,    KC_P3,    KC_KP_ASTERISK, KC_QUOT, LT(6, KC_KP_ENTER),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_KP_0,    KC_COMM, KC_KP_DOT,  KC_KP_SLASH, KC_RSFT, MO(2),
    MO(5), KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RGUI, KC_RCTL
    ),
LAYOUT_60_tsangan_hhkb(
    KC_GRAVE,  KC_BRID,    KC_BRIU,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MRWD,    KC_MPLY,    KC_MFFD,    KC_MUTE,    KC_VOLD, KC_VOLU,  KC_INS, KC_DEL,
    KC_CAPS,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_UP, KC_RBRC, KC_BSPACE,
    KC_TRNS, KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_LEFT, KC_RIGHT, LT(7, KC_ENTER),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_DOWN, KC_RSFT,  MO(3),
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                     KC_RALT, KC_RALT, MO(7)
  ),
LAYOUT_60_tsangan_hhkb(
    KC_GRAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_INS,KC_DEL,
    KC_CAPS, _______, _______,   _______, RESET, _______, _______, _______, _______, _______, _______, KC_UP,   _______, KC_BSPACE,
    _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, _______,
    _______, _______, _______, _______, _______, HPT_TOG,HPT_DWLI,HPT_DWLD, _______, _______, KC_DOWN, _______, MO(2),
    _______, _______, _______,                    _______,                    _______, _______,  _______
  ),
};
