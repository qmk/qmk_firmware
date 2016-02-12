// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _CM 1
#define _TK 2
#define _LW 3
#define _RS 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
/* MIT Layout (QWERTY layer)
 *
 * ,-----------------------------------------------------------------------.
 * | esc |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  | bspc|
 * |-----------------------------------------------------------------------|
 * | tab |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |
 * |-----------------------------------------------------------------------|
 * |shift|  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |enter|
 * |-----------------------------------------------------------------------|
 * | ctl | alt | win | TK  |lower|    spc    |raise|left |down | up  |right|
 * `-----------------------------------------------------------------------'
 */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_LSFT, KC_ENT) },
  {KC_LCTL, KC_LALT, KC_LGUI, TG(_TK), MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_CM] = { /* Colemak */
/* MIT Layout (Colemak layer)
 *
 * ,-----------------------------------------------------------------------.
 * | esc |  q  |  w  |  f  |  p  |  g  |  j  |  l  |  u  |  y  |  ;  | bspc|
 * |-----------------------------------------------------------------------|
 * | tab |  a  |  r  |  s  |  t  |  d  |  h  |  n  |  e  |  i  |  o  |  '  |
 * |-----------------------------------------------------------------------|
 * |shift|  z  |  x  |  c  |  v  |  b  |  k  |  m  |  ,  |  .  |  /  |enter|
 * |-----------------------------------------------------------------------|
 * | ctl | alt | win | TK  |lower|    spc    |raise|left |down | up  |right|
 * `-----------------------------------------------------------------------'
 */
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_LSFT, KC_ENT)},
  {KC_LCTL, KC_LALT, KC_LGUI, TG(_TK), MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_RS] = { /* RAISE */
/* MIT Layout (RAISE layer)
 *
 * ,-----------------------------------------------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | bspc|
 * |-----------------------------------------------------------------------|
 * | tab | F1  | F2  | F3  |  F4 |  F5 |  F6 |  -  |  =  |  [  |  ]  |  \  |
 * |-----------------------------------------------------------------------|
 * |shift|  F7 |  F8 |  F9 | F10 | F11 | F12 |  QW |  CM |  BL | RST |enter|
 * |-----------------------------------------------------------------------|
 * | ctl | alt | win | del |lower|    spc    |raise|next |vold |volu |PLAY |
 * `-----------------------------------------------------------------------'
 */

  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), M(0),    RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_LW] = { /* LOWER */
/* MIT Layout (Colemak layer)
 *
 * ,-----------------------------------------------------------------------.
 * | esc |  q  |  w  |  f  |  p  |  g  |  j  |  l  |  u  |  y  |  ;  | bspc|
 * |-----------------------------------------------------------------------|
 * | tab | F1  | F2  | F3  |  F4 |  F5 |  F6 |  _  |  +  |  {  |  }  |  |  |
 * |-----------------------------------------------------------------------|
 * |shift|  F7 |  F8 |  F9 | F10 | F11 | F12 |  QW |  CM |  BL | RST |enter|
 * |-----------------------------------------------------------------------|
 * | ctl | alt | win | TK  |lower|    spc    |raise|next |vold |volu |PLAY |
 * `-----------------------------------------------------------------------'
 */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), M(0),    RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_TK] = { /* Ten Key*/
/* MIT Layout (Ten Key layer)
 *
 * ,-----------------------------------------------------------------------.
 * | esc |  F9 | F10 | F11 | F12 | PGUP|  %  |  /  |  7  |  8  |  9  | bspc|
 * |-----------------------------------------------------------------------|
 * | tab |  F5 |  F6 | F7  |  F8 | PGDN| HOME|  *  |  4  |  5  |  6  |  \  |
 * |-----------------------------------------------------------------------|
 * |shift|  F1 |  F2 | F3  |  F4 | DEL | END |  0  |  1  |  2  |  3  |enter|
 * |-----------------------------------------------------------------------|
 * | ctl | alt | win | TK  |lower|    spc    |raise|left |down | up  |right|
 * `-----------------------------------------------------------------------'
 */
  {KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGUP, KC_PERC, KC_SLSH, KC_7,    KC_8,    KC_9,  KC_BSPC},
  {KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PGDN, KC_HOME, KC_ASTR, KC_4,    KC_5,    KC_6,  KC_PIPE},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_DEL,  KC_END,  KC_0,    KC_1,    KC_2,    KC_3,  KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}
}

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
