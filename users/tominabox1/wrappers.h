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
#define LAYOUT_arrow_wrapper(...) 	         LAYOUT_arrow_command(__VA_ARGS__)
#define LAYOUT_catalyst(...)                 LAYOUT_arrow(__VA_ARGS__)
#define LAYOUT_brutal_wrap(...)				       LAYOUT_brutal(__VA_ARGS__)
#define LAYOUT_33_BIG_SPACEwrap(...)         LAYOUT_33_BIG_SPACE(__VA_ARGS__)


/* Colemak */
#define _______________COLEMAK1____________________       KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN
#define _______________COLEMAK2____________________       KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O
#define _______________COLEMAK3____________________       KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH

/* Num/Symbol Layer */
#define __________________NUM_1____________________       KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
#define __________________NUM_2____________________       KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_MINS
#define __________________NUM_3____________________       KC_LCBR, KC_LBRC, KC_LPRN, KC_UNDS, KC_RPRN, KC_RBRC, KC_RCBR

/* F-key layer */
#define ___________________FKEY1___________________       KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10

/* Nav */
#define ___________________NAV1____________________       KC_NO, KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_PGDN, KC_UP, KC_PGUP,KC_NO
#define ___________________NAV2____________________       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END

/* No */
#define ___________________NO______________________       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO

/* Homerow Mods */
#define _______________HOMEROW_MOD_________________       LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_D, KC_H, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O)
