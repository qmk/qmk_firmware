#pragma once
#include "curry.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x12_wrapper(...)       LAYOUT_ortho_5x12(__VA_ARGS__)

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

#define _________________QWERTY_L1_________________         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________         KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________COLEMAK_L1________________         KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define _________________COLEMAK_L2________________         KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define _________________COLEMAK_L3________________         KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define _________________COLEMAK_R1________________         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________         KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________         KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________DVORAK_L1_________________         KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________         KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________         KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________         KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________         KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define ________________NUMBER_LEFT________________         KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________         KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________FUNC_LEFT_________________         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define _________________SYM_LEFT__________________         KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________SYM_RIGHT_________________         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN


#define ___________________BLANK___________________         _______, _______, _______, _______, _______


#define _________________LOWER_L1__________________         _________________FUNC_LEFT_________________
#define _________________LOWER_L2__________________         _________________SYM_LEFT__________________
#define _________________LOWER_L3__________________         KC_DT1,  KC_DT2,  KC_DT3,  KC_DT4,  _______

#define _________________LOWER_R1__________________         _________________FUNC_RIGHT________________
#define _________________LOWER_R2__________________         _________________SYM_RIGHT_________________
#define _________________LOWER_R3__________________         _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR

#define _________________RAISE_L1__________________         ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________         KC_PGUP, KC_PGDN, KC_HOME, KC_END,  _______
#define _________________RAISE_L3__________________         _______, _______, _______, _______, _______

#define _________________RAISE_R1__________________         ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
#define _________________RAISE_R3__________________         _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC

#define _________________ADJUST_L1_________________         RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________ADJUST_L2_________________         MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  CG_NORM
#define _________________ADJUST_L3_________________         RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T

#define _________________ADJUST_R1_________________         KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
#define _________________ADJUST_R2_________________         CG_SWAP, QWERTY,  COLEMAK, DVORAK,  XXXXXXX
#define _________________ADJUST_R3_________________         MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT

// clang-format on
