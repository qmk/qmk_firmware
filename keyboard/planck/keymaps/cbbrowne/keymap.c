#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

/* Each layer is given a name to aid in readability, which is then
   used in the keymap matrix below.  The underscores do not denote 
   anything - you can have a layer called STUFF or any other name.

   Layer names don't all need to be of the same length, obviously, and
   you could also skip them entirely and just use numbers, though that
   means needing to manage the numbers.

   It is preferable to keep the symbols short so that a line worth of
   key mappings fits compactly onto a line of code. */

/* This was originally based on planck/keymaps/default/default.c, and
   then cbbrowne has revised things */

/* Things I did not like about the default mapping 

   - I find control too hard to get to.  I think I'll want it on a
     left finger.  Gonna need to lose something to do that...
   - Almost certainly, KC_LCTL should be on [2][1]
   - having dash on [lower-j] is a bit nonintuitive, but may be OK
   - I'll bet I should switch ESC/TAB
   - I'm suspicious that I want to shift M(0) from [4][1] to [4][2],
     and shift ESC off the first column so KC_LCTL and KC_LALT can
     be on the first column.
   - I think I wanna swap ' and ENTER

   - All of the above are done :-)

   - I'm keeping Colemak and Dvorak around for reference, and added
     Workman just for fun.  They're useless to me, though.
*/

/* Other things to do...

   - Need to think about what zsh and readline actions I use lots
   - Wanna figure out macros, so I can put in a "cbbrowne" macro
   - Ought to ensure that Control-Alt-Delete is convenient enough
   - How about Alt-F1 thru Alt-F8?
   - What's the keystroke to get from X to console these days?
   - I do indeed want a sweet number pad!
   - A layer for doing console switching would not be a bad idea
   - Random data generator
     - A key that generates values in the range 0-9 at random
     - A key that generates values in the range a-z at random
     - A key that generates values in the range a-z,A-Z,0-9 at random

   - Figure out the MACRO example in https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/doc/keymap.md
     - section 2.3.2
     - where does the HELLO come from???
     - What are the types of the T() calls? 
*/

enum layers {
  _QW = 0,  /* Qwerty mapping */
  _LW, /* Lower layer, where top line has symbols !@#$%^&*() */
  _RS, /* Raised layer, where top line has digits 1234567890 */
  _KP, /* Key pad */
};

enum macro_id {
  M_LED = 0,
  M_USERNAME,
  M_RANDDIGIT
};

/* Note that Planck has dimensions 4 rows x 12 columns */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT },
  {KC_TAB,  M(M_LED), KC_LALT, KC_LGUI, MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_RS] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_KP), DF(_KP), RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_LW] = { /* LOWER */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_KP), DF(_KP), RESET,   KC_TRNS},
  {KC_TRNS, DF(_KP), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_KP] = { /* Key Pad */
  {KC_ESC,  M(M_USERNAME),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_KP_ENTER, KC_KP_PLUS, KC_KP_PLUS, KC_KP_ENTER, KC_KP_ENTER},
  {KC_LCTL, M(M_RANDDIGIT),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_KP_MINUS, KC_7, KC_8,    KC_9,  KC_KP_DOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_KP_PLUS,    KC_4, KC_5,  KC_6, KC_0},
  {BL_STEP, M(M_LED), KC_LALT, KC_LGUI, KC_NO, KC_SPC,  KC_SPC,  DF(_QW),   KC_1, KC_2, KC_3,  KC_0}
}
};

const uint16_t PROGMEM fn_actions[] = {
};

static uint16_t random_value = 157;
#define randadd 53
#define randmul 181
#define randmod 167

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
  case M_LED:
    if (record->event.pressed) {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
    } else {
      unregister_code(KC_RSFT);
    }
    break;	    
  case M_USERNAME:
    if (record->event.pressed) {
      return MACRO( I(1), T(C), T(B), T(B), T(R), T(O), T(W), T(N), T(E));
    } else {
      return MACRO_NONE ;
    }
    break;
  case M_RANDDIGIT:
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) 
    switch(random_value % 10) {
    case 0:
      return MACRO(T(0));
      break;
    case 1:
      return MACRO(T(1));
      break;
    case 2:
      return MACRO(T(2));
      break;
    case 3:
      return MACRO(T(3));
      break;
    case 4:
      return MACRO(T(4));
      break;
    case 5:
      return MACRO(T(5));
      break;
    case 6:
      return MACRO(T(6));
      break;
    case 7:
      return MACRO(T(7));
      break;
    case 8:
      return MACRO(T(8));
      break;
    case 9:
      return MACRO(T(9));
      break;
    }
    break;
  }
  return MACRO_NONE;
};
