// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QW 0
#define _RS 1
#define _LW 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    SFT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
    KC_ESC, KC_TAB, KC_LCTL,  MO(_LW), KC_SPC, KC_BSPC, LALT(KC_GRV), KC_ENT,  MO(_RS), KC_MINS, KC_QUOT, KC_BSPC
  ),


  /*
   *  1       2     3     4     5        ||     6    7     8     9    0
   *  #     left   down  UP   right      ||     _    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * TRANS  TRANS TRANS TRANS TRANS TRANS|| TRANS TRANS  fn    .     0    =
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,   KC_9, KC_0 ,
    KC_HASH, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,                   KC_UNDS, KC_4,    KC_5,   KC_6, KC_PLUS ,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                   KC_GRV,  KC_1,    KC_2,   KC_3, KC_BSLS ,
    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_DOT, KC_0, KC_EQL  ),

  /*
   * !        @     #    $     %        ||     ^    &    *     (    )
   *  F1    F2    F3   F4    F5        ||     F6    F7   F8    F9    F10
   *  F11    F12              reset      ||                    UP
   *  TRNS  TRNS  TRNS TRNS TRNS TRNS||TRNS TRNS  TRNS  LEFT DPWM RGHT
   */

  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN  ,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10  ,
    KC_F11,  KC_F12,  KC_NO,   KC_NO,   RESET,                     KC_NO,   KC_NO,   KC_NO,   KC_UP,   KC_NO  ,
    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LALT, KC_ENT,  TO(_QW), KC_LEFT, KC_DOWN, KC_RGHT )
};

const uint16_t PROGMEM fn_actions[] = {

};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
    break;
  }
  return MACRO_NONE;
};
