#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif
#include "config.h"
#include "quantum.h"

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

   - I found control too hard to get to.  I use it more than Tab, so
     switched it there.
   - Having dash on [lower-j] is a bit nonintuitive, but may be OK
   - I'll bet I should switch ESC/TAB
   - I'm suspicious that I want to shift M(0) from [4][1] to [4][2],
     and shift ESC off the first column so KC_LCTL and KC_LALT can
     be on the first column.
   - I needed to swap ' and ENTER

   - All of the above are done :-)

   - Dropped out support for Dvorak and friends.  They aren't 
     improvements to me
*/


/* Some interesting things implemented

   - There is a macro that writes out "cbbrowne" to show that I could
   - There is a (somewhat cruddy) linear congruential random number
     generator.
     - I would like to be seeding it with clock info to make it look
       more random
   - There are two macros that use the random number generators
     - one, M_RANDDIGIT, generates a random digit based on state
       of the random number generator
     - the other, M_RANDLETTER, generates a random letter based on state
       of the random number generator
     - in both, note the use of register_code()/unregister_code()
       to indicate the desired key
   - I do indeed want a sweet number pad!
*/

/* Other things to do...

   - Need to think about what zsh and readline actions I use lots
   - Ought to ensure that Control-Alt-Delete is convenient enough
   - How about Alt-F1 thru Alt-F8?
   - What's the keystroke to get from X to console these days?
   - A layer for doing console switching would not be a bad idea
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
  M_RANDDIGIT,
  M_RANDLETTER,
  M_VERSION
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
  {KC_ESC,  M(M_USERNAME),    M(M_VERSION),   KC_F10,   KC_F11,  KC_F12,   KC_PGUP, KC_KP_ENTER, KC_7, KC_8, KC_9, KC_BSPC},
  {KC_LCTL, M(M_RANDDIGIT),   KC_F5,   KC_F6,    KC_F7,   KC_F8,    KC_PGDN, KC_KP_MINUS, KC_4, KC_5, KC_6, KC_PIPE},
  {KC_LSFT, M(M_RANDLETTER),  KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_DEL,  KC_KP_PLUS,  KC_1, KC_2,  KC_3, KC_ENTER},
  {BL_STEP, M(M_LED), KC_LALT, KC_LGUI, KC_NO, KC_SPC,  KC_SPC,  DF(_QW),   KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT}
}
};

const uint16_t PROGMEM fn_actions[] = {
};

/* This bit of logic seeds a wee linear congruential random number generator */
/* lots of prime numbers everywhere... */
static uint16_t random_value = 157;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  uint8_t clockbyte=0;
  clockbyte = TCNT1 % 256;
  uint8_t rval;
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
      SEND_STRING("cbbrowne");
    }
    break;
  case M_VERSION:
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION "@" QMK_BUILDDATE);
    }
    break;
  case M_RANDDIGIT:
    /* Generate, based on random number generator, a keystroke for
       a numeric digit chosen at random */
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) {
      /* Here, we mix the LCRNG with low bits from one of the system
         clocks via XOR in the theory that this may be more random
         than either separately */ 
      rval = (random_value ^ clockbyte) % 10;
      /* Note that KC_1 thru KC_0 are a contiguous range */
      register_code (KC_1 + rval);
      unregister_code (KC_1 + rval);
    }
    break;
  case M_RANDLETTER:
    /* Generate, based on random number generator, a keystroke for
       a letter chosen at random */
    /* Here, we mix the LCRNG with low bits from one of the system
       clocks via XOR in the theory that this may be more random
       than either separately */ 
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) {
      rval = (random_value ^ clockbyte) % 26;
      register_code (KC_A + rval);
      unregister_code (KC_A + rval);
    }
    break;
  }
  return MACRO_NONE;
};
