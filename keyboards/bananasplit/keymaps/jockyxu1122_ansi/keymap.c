/*
  Author: jockyxu1122

  Hightlight: split backspace, split space, arrows on bottom right,
    and backlighting support (capslock's backlighting cannot be controlled separately).

  Note that "Previous track" and "next track" might only work with Windows.
*/

#include QMK_KEYBOARD_H

#define DEFAULT_LAYER 0
#define LAYER_1 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  -------------------------------------------------------------
  |Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` |Del|
  -------------------------------------------------------------
  | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \  |
  -------------------------------------------------------------
  | Caps | A | S | D | F | G | H | J | K | L | ; | ' |  Enter |
  -------------------------------------------------------------
  | Shift  | Z | X | C | V | B | N | M | , | . | / | Shift| Up|
  -------------------------------------------------------------
  |Ctrl| GUI| Alt|  Space   |MoL1| Backspc| Hm|End| <-|Dwn| ->|
  -------------------------------------------------------------
  Hm: Home
  MoL1: Mo(L1)
  */
  [DEFAULT_LAYER] = LAYOUT_hhkb_arrow(
    // row 1
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, \
      KC_DEL, \
    // row 2
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, \
    // row 3
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, \
    // row 4
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, \
    // row 5
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(LAYER_1), KC_BSPC, KC_HOME, KC_END, KC_LEFT, KC_DOWN, \
      KC_RIGHT
  ),

  /*
  -------------------------------------------------------------
  |LED| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |Ins|
  -------------------------------------------------------------
  |     |   |   | @ |   |   |   |   |   |   |   |BDn|BUp|     |
  -------------------------------------------------------------
  |      |   |   |   |   |   |   |   |   |   |   |   |        |
  -------------------------------------------------------------
  |        |   |   |Cal|   |www|   |Mut|   |   |   |      |VUp|
  -------------------------------------------------------------
  |    |    |    |  Pause   |    |        |PUp|PDn|PTk|VDn|NTk|
  -------------------------------------------------------------
  @: Email
  BDn: LED brightness down
  BUp: LED brightness up
  Cal: Calculator
  Ins: Insert
  Mut: Mute
  NTk: Next track
  PDn: Page down
  PTk: Previous track
  PUp: Page up
  VDn: Volume down
  VUp: Volume up
  www: Browser home page
  */
  [LAYER_1] = LAYOUT_hhkb_arrow(
    // row 1
    BL_TOGG, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, \
      KC_F12, KC_TRNS, KC_INS, \
    // row 2
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MAIL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, BL_DEC, BL_INC, KC_TRNS, \
    // row 3
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, \
    // row 4
    KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_TRNS, KC_WHOM, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_VOLU, \
    // row 5
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_MPRV, KC_VOLD, \
      KC_MNXT
  )
};

const uint16_t PROGMEM fn_actions[] = {
};
