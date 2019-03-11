#pragma once
#include "octapoos.h"

#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
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

#define _________________QWERTY_L1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________DVORAK_L1_________________       KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________       KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________       KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________       KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________       KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH


#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___________________BLANK___________________       _______, _______, _______, _______, _______
#define ___________________BLOCK___________________       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX


#define _________________LOWER_L1__________________       XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX
#define _________________LOWER_L2__________________       KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_TD1
#define _________________LOWER_L3__________________       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR

#define _________________LOWER_R1__________________       KC_CALC, KC_P7,   KC_P8,   KC_P9,   KC_EQL
#define _________________LOWER_R2__________________       KC_TD2,  KC_P4,   KC_P5,   KC_P6,   KC_PLUS
#define _________________LOWER_R3__________________       KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS


#define _________________RAISE_L1__________________       XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX
#define _________________RAISE_L2__________________       XXXXXXX, KC_PGDN, KC_MPRV, KC_MNXT, KC_VOLU
#define _________________RAISE_L3__________________       XXXXXXX, XXXXXXX, KC_MSTP, KC_MPLY, KC_VOLD

#define _________________RAISE_R1__________________       RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN
#define _________________RAISE_R2__________________       XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI
#define _________________RAISE_R3__________________       XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD


#define _________________ADJUST_L1_________________       RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________ADJUST_L2_________________       MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define _________________ADJUST_L3_________________       RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, XXXXXXX

#define _________________ADJUST_R1_________________       ___________________BLOCK___________________
#define _________________ADJUST_R2_________________       AG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN
#define _________________ADJUST_R3_________________       XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT
