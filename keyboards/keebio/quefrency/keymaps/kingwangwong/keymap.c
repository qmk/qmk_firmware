#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN1
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ESC  │  1  │  2  │  3  │  4  │  5  │  6  │     │  7  │  8  │  9  │  0  │  -  │  =  │BSLS │ DEL │ 
   * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┘  ┌──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────┤
   * │TAB     │  Q  │  W  │  E  │  R  │  T  │     │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │BSPC    │
   * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐    └┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┤
   * │CAPS     │  A  │  S  │  D  │  F  │  G  │     │  H  │  J  │  K  │  L  │  ;  │  '  │ENTER        │
   * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┤
   * │LSHFT       │  Z  │  X  │  C  │  V  │  B  │     │  N  │  M  │  ,  │  .  │  /  │RSHFT     │ UP  │
   * ├──────┬─────┴─┬───┴──┬──┴─────┴────┬┴─────┤     ├─────┴┬────┴────┬┴────┬┴────┬┴────┬─────┼─────┤
   * │LCTRL │L_GUI  │L_ALT │SPC          │FN1   │     │SPC   │BSPC     │R_ALT│R_CTR│LEFT │DOWN │RIGHT│
   * └──────┴───────┴──────┴─────────────┴──────┘     └──────┴─────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS, KC_EQL,  KC_BSLS, KC_DEL, 
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, 
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN, KC_QUOT, KC_ENT, 
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,     KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, KC_UP, 
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  MO(_FN1),                               KC_BSPC, KC_BSPC,  KC_RALT,  KC_RCTL, KC_LEFT, KC_RGHT, KC_DOWN
  ),

  [_FN1] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC, 
    _______, _______, KC_HOME, KC_UP,   KC_END,  _______,              _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                       _______, KC_MINS, KC_EQL,  _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______, 
    RESET,   _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______, _______

  )
};
