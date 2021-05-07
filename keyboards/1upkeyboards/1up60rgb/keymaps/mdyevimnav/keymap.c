#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Layer 0
 * ,-----------------------------------------------------------------------------------------.
 * |  ~  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * | Esc     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  Sup  |  L1   | Ctrl  |
 * \-----------------------------------------------------------------------------------------/
 *
 */
  LAYOUT_all(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_ENT,
    KC_LSHIFT, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSHIFT, KC_RSHIFT,
    KC_LCTL, MO(1), KC_LALT, KC_SPC, KC_RALT, KC_RGUI, MO(1), KC_RCTL),

/*
 * Layer 1
 * ,-----------------------------------------------------------------------------------------.
 * |     |  f1 |  f2 |  f3 |  f4 |  f5 |  f6 |  f7 |  f8 |  f9 | f10 | f11 | f12 |    Del    |
 * |-----------------------------------------------------------------------------------------+
 * |        |     |     |     |     |     |     |     | Ins |     | Paus|     |     |  Prnt  |
 * |-----------------------------------------------------------------------------------------+
 * |         |     |     |     |     |     |  L  |  D  |  U  |  R  |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |            |     |     |     |     |     | Hom | PDn | PUp | End |     |                |
 * |-----------------------------------------------------------------------------------------+
 * |       |       |       |                                 |       |       |       |       |
 * \-----------------------------------------------------------------------------------------/
 *
 */
  LAYOUT_all(
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_TRNS, KC_PAUS, KC_TRNS, KC_TRNS, KC_PSCR,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
