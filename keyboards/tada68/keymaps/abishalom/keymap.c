#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _NL 2

#define SEMI_FN LT(_FL, KC_SCLN)

//Tap Dance Declarations
enum {
  TD_WIN_LOCK = 0
};

//BL_BRTG - breathing mode. Would like to put in.

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_WIN_LOCK]  = ACTION_TAP_DANCE_DOUBLE(MAGIC_NO_GUI, MAGIC_UNNO_GUI)
};

//
////In Layer declaration, add tap dance item in place of a key code
//TD(TD_WIN_LOCK)

// Double Tap Fn button to get caps. FN + Tab to get to number layer -> Maybe switch to FN + space?. 
// Press fn+GUI once to lock, double tap to unlock.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |FNCAP|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter  |PgUp  |
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_GESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL, \
  LT(_FL, KC_CAPS), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   SEMI_FN,KC_QUOT,         KC_ENT,KC_PGUP,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_PGDN, \
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                        KC_RALT,MO(_FL),KC_RCTRL, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |    |
   * |----------------------------------------------------------------|
   * |#PAD |Pre| U |NXT|   |   |   |PGD| U |PGU|PSC|   |   |     |Ins |
   * |----------------------------------------------------------------|
   * |      |L  | D | R |PPl|   |   | L | D | R |   |   |        |Home|
   * |----------------------------------------------------------------|
   * |   CAPS |MUT|VU-|VU+|   |   |   |BRG|BL-|BL+|BLT|      |Stp|End |
   * |----------------------------------------------------------------|
   * |    |WTOG|    |                       |   |   |    |Pre|PPl|Nxt |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, _______ ,  \
  TO(_NL),KC_MPRV, KC_UP ,KC_MNXT,_______, _______,_______,KC_PGDN,KC_UP,KC_PGUP,KC_PSCR,_______,_______, _______,KC_INSERT, \
  _______,KC_LEFT,KC_DOWN,KC_RGHT,KC_MPLY,_______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,        _______,KC_HOME, \
  _______,KC_MUTE,KC_VOLD,KC_VOLU, _______,_______, _______,BL_BRTG,BL_DEC,BL_INC,BL_TOGG,_______, KC_STOP, KC_END, \
  _______,TD(TD_WIN_LOCK),_______,                 _______,               _______,KC_TRNS,_______,KC_MPRV,KC_MPLY, KC_MNXT),


//Press either of function keys to get back to base layer.

 /* Keymap _NL: Number Layer
   * ,----------------------------------------------------------------.
   * |ESC| F1 | F2| F3| F4|   |#L | 7 | 8 | 9 | - |   | = |       |    |
   * |----------------------------------------------------------------|
   * | TAB |   | UP|   |   |   | / | 4 | 5 | 6 | + |   |   |     | DEL|
   * |----------------------------------------------------------------|
   * | _BL  |LFT|DWN|RGT|   |   | * | 1 | 2 | 3 |ENT|   |   ENT  |PgUp|
   * |----------------------------------------------------------------|
   * |  SHIFT |   |   |   |   |   | 0 | 0 | , | . |BKS| SHIFT| U |PgDn|
   * |----------------------------------------------------------------|
   * |CTRL|WIN |ALT |                       |ALT| _BL |CTRL| L | D | R|
   * `----------------------------------------------------------------'
   */
[_NL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, _______, KC_NLCK, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_PEQL, KC_PEQL, _______, _______ ,  \
  KC_TAB,_______, KC_UP,_______,_______, _______,KC_PSLS,KC_P4,KC_P5,KC_P6,KC_PPLS,_______,_______, _______,KC_DEL, \
  TO(_BL),KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,KC_PAST,KC_P1,KC_P2,KC_P3,KC_PENT,_______,        KC_ENT,KC_PGUP, \
  KC_LSFT,_______,_______,_______, _______,_______, KC_P0,KC_P0,KC_PCMM,KC_PDOT,KC_BSPC,KC_RSFT, KC_UP, KC_PGDN, \
  KC_LCTRL,KC_LGUI,KC_LALT,                 KC_SPC,               KC_RALT,TO(_BL),KC_RCTRL,KC_LEFT,KC_DOWN, KC_RGHT),

};
