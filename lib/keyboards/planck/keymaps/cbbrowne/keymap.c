#include "planck.h"
#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif
#include "config.h"
#include "quantum.h"
#include "version.h"

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
   - I haven't got page-up/page-down, let's have that...
*/

enum layers {
  _QWERTY = 0,  /* Qwerty mapping */
  _LOWER, /* Lower layer, where top line has symbols !@#$%^&*() */
  _RAISE, /* Raised layer, where top line has digits 1234567890 */
  _KEYPAD, /* Key pad */
  _ADJUST, /* Special Adjust layer coming via tri-placement */
};

enum macro_id {
  M_LED = 0,
  M_USERNAME,
  M_RANDDIGIT,
  M_RANDLETTER,
  M_VERSION,
  MACRO_UPPER,
  MACRO_LOWER,
};

#define M_LOWER M(MACRO_LOWER)
#define M_UPPER M(MACRO_UPPER)
#define ROT_LED M(M_LED)   /* Rotate LED */
#define QWERTY DF(_QWERTY)   /* Switch to QWERTY layout */
#define KEYPAD DF(_KEYPAD)   /* Switch to keypad */
#define USERNAME M(M_USERNAME) /* shortcut for username */
#define RANDDIG M(M_RANDDIGIT)
#define RANDALP M(M_RANDLETTER)
#define CTLENTER MT(MOD_RCTL, KC_ENT)
#define SHIFTQUOTE MT(MOD_RSFT, KC_QUOT)
#define ALTRIGHT MT(MOD_LALT, KC_RGHT)
#define MVERSION M(M_VERSION)
#define ALTSLASH LALT(KC_SLSH)


/* Note that Planck has dimensions 4 rows x 12 columns */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /* Qwerty */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTLENTER},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHIFTQUOTE },
  {KC_TAB,  KC_LALT, ROT_LED, KC_LGUI, M_LOWER, KC_SPC,  KC_SPC,  M_UPPER, KC_LEFT, KC_DOWN, KC_UP,   ALTRIGHT}
  /* Note that KC_SPC is recorded TWICE, so that either matrix position can activate it */
},
[_RAISE] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {_______, KC_4,    KC_5,    KC_6,    _______, _______, _______,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_7,    KC_8,    KC_9,    _______, _______, _______,  QWERTY,  KEYPAD,  KEYPAD,  ALTSLASH,_______},
  {_______, KC_0, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_HOME, KC_END,  KC_PGUP}
},
[_LOWER] = { /* LOWER */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QWERTY,  KEYPAD,  KEYPAD, ALTSLASH,   _______},
  {_______, KEYPAD, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_HOME,  KC_END, KC_PGUP}
    },
[_KEYPAD] = { /* Key Pad */
  {KC_ESC,  USERNAME,    MVERSION,   KC_F10,   KC_F11,  KC_F12,   KC_PGUP, KC_KP_ENTER, KC_7, KC_8, KC_9, KC_BSPC},
  {KC_LCTL, RANDDIG,   KC_F5,   KC_F6,    KC_F7,   KC_F8,    KC_PGDN, KC_KP_MINUS, KC_4, KC_5, KC_6, KC_PIPE},
  {KC_LSFT, RANDALP,   KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_DEL,  KC_KP_PLUS,  KC_1, KC_2,  KC_3, KC_ENTER},
  {KC_TAB,  KC_LALT, ROT_LED, KC_LGUI,  M_LOWER,  KC_SPC,    KC_SPC,  QWERTY,   KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT}
},

[_ADJUST] = { /* Adjustments - gonna shift the wild tools in here */
  {ROT_LED,USERNAME,MVERSION, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, RANDDIG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, RANDALP, _______, _______, _______,   RESET,   RESET, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
}  
};

/* What is fn_actions actually used for??? */
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
  case MACRO_UPPER:
    if (record->event.pressed)
      {
	layer_on(_RAISE);
#ifdef BACKLIGHT_ENABLE
	breathing_speed_set(2);
	breathing_pulse();
#endif
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    else
      {
	layer_off(_RAISE);
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    break;
  case MACRO_LOWER:
    if (record->event.pressed)
      {
	layer_on(_LOWER);
#ifdef BACKLIGHT_ENABLE
	breathing_speed_set(2);
	breathing_pulse();
#endif
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    else
      {
	layer_off(_LOWER);
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    break;
    
  }
  return MACRO_NONE;
};
