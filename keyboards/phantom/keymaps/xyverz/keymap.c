#include "phantom.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------------------------.
   * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|	|Prnt|ScLk|Paus|
   * |-----------------------------------------------------------|	|--------------|
   * | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |	| Ins|Home|PgUp|
   * |-----------------------------------------------------------|	|--------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|	| Del| End|PgDn|
   * |-----------------------------------------------------------|	`--------------'
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|		 ,----.
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |		 | Up |
   * |-----------------------------------------------------------|	 ,-------------.
   * |Ctrl|Gui |Alt |      Space            |ALT |GUI |_FL |CTRL |	 |Lft| Dn |Rig |
   * `-----------------------------------------------------------'	 `-------------'
   */
[_BL] = KEYMAP(
  KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SLCK, KC_PAUS, \
  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, \
  KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_BSLS, KC_DELETE, KC_END, KC_PGDN, \
  KC_CAPS, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT,  \
  KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, KC_UP, \
  KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, KC_RCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------------------------.
   * |RESET|  |   |   |   |  |   |   |   |   |   |   |   |   |   |	|    |    |    |
   * |-----------------------------------------------------------|	|--------------|
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |	|    |    |    |
   * |-----------------------------------------------------------|	|--------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |	|    |    |    |
   * |-----------------------------------------------------------|	`--------------'
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|		 ,----.
   * |        | F1| F2| F3| F4| F5|F6 |F7 |F8 |   |   |          |		 |    |
   * |-----------------------------------------------------------|	 ,-------------.
   * |    |    |    |                       |    |    |    |     |	 |   |    |    |
   * `-----------------------------------------------------------'	 `-------------'
   */
[_FL] = KEYMAP(
  KC_TRNS,	  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,	KC_TRNS,KC_TRNS,KC_SLEP, \
  RESET,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MUTE,KC_VOLD,KC_VOLU,KC_TRNS,	KC_TRNS,KC_TRNS,KC_TRNS, \
  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MSTP,KC_MPLY,KC_MPRV,KC_MNXT,KC_MSEL,	KC_TRNS,KC_TRNS,KC_TRNS, \
  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,	  KC_TRNS,                      \
  KC_TRNS,	  KC_TRNS,KC_TRNS,KC_CALC,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,	  KC_CAPS,		KC_TRNS,      \
  KC_TRNS,KC_TRNS,KC_TRNS,			  KC_TRNS,			  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,	KC_TRNS,KC_TRNS,KC_TRNS)
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {

};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
}
