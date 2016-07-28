// Based on the canonical layout file for the Quantum project.
// to be used with grid layout (two space bars)
// Removed Colemak and Dvorak
// Moved RESET to bottom left (avoid typos that render the keyboard irresponsive)
// fn _MENTR Tap for enter, hold for _RS
// lg/e tap for enter, hold for LGUI


#include "planck.h"
#include "backlight.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _LW 1
#define _RS 2

#define _MSPC 0 // fn _MSPC  Tap for space, hold for _LW
#define _MENTR 1 // fn _MENTR Tap for enter, hold for _RS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* MIT Layout (QWERTY layer)
 *
 * ,-----------------------------------------------------------------------.
 * | tab |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  | bspc|
 * |-----------------------------------------------------------------------|
 * | esc |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |
 * |-----------------------------------------------------------------------|
 * |shift|  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |shift|
 * |-----------------------------------------------------------------------|
 * | led | ctl | alt | ctl | lw  | lg/e| alt |mspc |left |down | up  |right|
 * `-----------------------------------------------------------------------'
 */
[_QW] = { /* Qwerty */
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {M(0),    KC_LCTL, KC_LALT, KC_LCTL, MO(_LW), GUI_T(KC_ENT),  KC_LALT,  FUNC(_MSPC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
/* MIT Layout (Raised layer)
 *
 * ,-----------------------------------------------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |     |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |     |left |down | up  |right|     |     |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_RS] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
/* MIT Layout (Lowered layer)
 *
 * ,-----------------------------------------------------------------------.
 * |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  | del |

 * |-----------------------------------------------------------------------|
 * |     | F1  | F2  | F3  | F4  | F5  | F6  |  -  |  +  |  {  |  }  |  \  |
 * |-----------------------------------------------------------------------|
 * |     | F7  | F8  | F9  | F10 | F11 | F12 |  _  |  =  |  [  |  ]  |  |  |
 * |-----------------------------------------------------------------------|
 * | RST |     |     |     |     |     |     |     | NXT |VOLD |VOLU |PLAY |
 * `-----------------------------------------------------------------------'
 */
[_LW] = { /* LOWER */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DELT},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINUS,KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE},
  {RESET  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
}
};

const uint16_t PROGMEM fn_actions[] = {
  [_MSPC] = ACTION_LAYER_TAP_KEY(_RS, KC_SPC), // Tap for space, hold for _RS
  [_MENTR]= ACTION_LAYER_TAP_KEY(KC_LGUI, KC_ENT), // Tap for enter, hold for Command
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            backlight_step();
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
