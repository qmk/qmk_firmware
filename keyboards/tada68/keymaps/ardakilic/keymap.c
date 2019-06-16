#include QMK_KEYBOARD_H

//KC_NONUS_BSLASH (\|) is equivalent to ["é] key in Turkish keyboards.
//KC_GRV (~ `) is equivalent to [<>|] key in Turkish keyboards.
//I've put grave to bottom, and nonUS backslash to top to make it more similar to Turkish layout.  ["é] key is more above than [<>|] key.
//Default top right button was KC_GRV (~ `) (Grave key) even if it looks like Tilde key.

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |PWR |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |\ | |
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|~ ` |
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |CMD |        Space          |CMD |FN |Alt|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_POWER, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL, \
  KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_NONUS_BSLASH,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_GRV, \
  KC_LCTL, KC_LALT,KC_LGUI,                KC_SPC,                        KC_RGUI,MO(_FL),KC_RALT, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   | PP|PLA|PN |   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |MUT|VU-|VU+|   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS ,  \
  _______,_______,_______,_______,_______, _______,_______,_______,_______,_______,_______,_______,_______, _______,KC_HOME, \
  _______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,        _______,KC_END, \
  _______,_______,_______,BL_DEC, BL_TOGG,BL_INC, _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,_______,_______, \
  _______,_______,_______,                 _______,               _______,_______,_______,_______,_______,_______),
};
