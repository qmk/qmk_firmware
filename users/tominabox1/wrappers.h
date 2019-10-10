#pragma once
#include "tominabox1.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_arrow_wrapper(...) 	     LAYOUT_arrow(__VA_ARGS__)

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts
NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

#define __________________DIMPLE1__________________       KC_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC
#define __________________DIMPLE2__________________       LCTL_T(KC_TAB), KC_A,    KC_R,    KC_S,    KC_T,    KC_D, KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT
#define __________________DIMPLE3L_________________       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#define __________________DIMPLE3R_________________       KC_K,    KC_M,    KC_COMM, KC_UP,  LT(_FKEY,KC_DOT)
#define __________________DIMPLE4__________________       KC_LCTL, KC_LGUI, KC_LALT, KC_ENT_LOW,  KC_SPC_RSE,  KC_LEFT, KC_DOWN, KC_RGHT


#define __________________MINIVAN1_________________       __________________DIMPLE1__________________
#define __________________MINIVAN2_________________       __________________DIMPLE2__________________
#define __________________MINIVAN3_________________       __________________DIMPLE3L_________________, __________________DIMPLE3R_________________, KC_RSFT
#define __________________MINIVAN4_________________       KC_LCTL, KC_LGUI, KC_LALT, KC_ENT_LOW,  KC_SPC_RSE,  KC_LEFT, KC_DOWN, KC_RGHT, MO(_FKEY)

#define ___________________CRKBD1__________________       __________________DIMPLE1__________________
#define ___________________CRKBD2__________________       __________________DIMPLE2__________________
#define ___________________CRKBD3__________________       __________________DIMPLE3L_________________, KC_K,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH,  KC_BBB
#define ___________________CRKBD4__________________       KC_LGUI, KC_LALT, KC_ENT_LOW,  KC_SPC_RSE, KC_ARROW, KC_FKEY


#define ___________________BLANK___________________        _______, _______, _______, _______, _______

#define ___________________RAISE1__________________       KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC
#define ___________________RAISE2__________________       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS

#define _________________LOWER_1___________________       KC_GESC, KC_EXLM, TD(KC_EMAIL),   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL
#define _________________LOWER_2___________________       KC_DEL,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE
#define _________________LOWER_3___________________       KC_CAPS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_PGUP, KC_QUES
#define _________________LOWER_4___________________       LCA(KC_DEL),   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_END

// clang-format on
