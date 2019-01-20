#pragma once
#include "klackygears.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif
// #if (!defined(LAYOUT_kc) && defined(KEYMAP))
// #define LAYOUT_kc KEYMAP
// #endif

#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_kcwrap(...)                   LAYOUT_kc(__VA_ARGS__)

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

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________COLEMAK_L1________________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________        KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________        KC_J,    KC_L,    KC_U,       KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________        KC_H,    KC_N,    KC_E,       KC_I,    KC_O
#define _________________COLEMAK_R3________________        KC_K,    KC_M,    KC_COMQUES, KC_DTEX, KC_SLASH
/*
#define ______________COLEMAK_MOD_DH_L1____________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________        KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________        KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________        KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH
*/

#define _________________DVRK_L1___________________        KC_QUOT,    KC_COMQUES, KC_DTEX,    KC_P,       KC_Y
#define _________________DVRK_L2___________________        KC_A,       KC_O,       KC_E,       KC_U,       KC_I
#define _________________DVRK_L3___________________        KC_CSCN,    KC_ALTQ,    KC_GUIJ,    KC_K,       KC_X

#define _________________DVRK_R1___________________        KC_F,       KC_G,       KC_C,       KC_R,       KC_L
#define _________________DVRK_R2___________________        KC_D,       KC_H,       KC_T,       KC_N,       KC_S
#define _________________DVRK_R3___________________        KC_B,       KC_M,       KC_GUIW,    KC_ALTV,    KC_MDAZ

/*
#define ________________DVORAK_AU_L1_______________        KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define ________________DVORAK_AU_L2_______________        KC_O,    KC_A,    KC_E,   KC_I,     KC_U
#define ________________DVORAK_AU_L3_______________        KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define ________________DVORAK_AU_R1_______________        KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define ________________DVORAK_AU_R2_______________        KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define ________________DVORAK_AU_R3_______________        KC_B,    KC_M,    KC_W,    KC_V,    KC_Z
*/

#define _________________WORKMAN_L1________________        KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________        KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________        KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________        KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________        KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________        KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH

/*
#define _________________NORMAN_L1_________________       KC_Q,    KC_W,    KC_D,    KC_F,    KC_K
#define _________________NORMAN_L2_________________       KC_A,    KC_S,    KC_E,    KC_T,    KC_G
#define _________________NORMAN_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________NORMAN_R1_________________       KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN
#define _________________NORMAN_R2_________________       KC_Y,    KC_N,    KC_I,    KC_O,    KC_U
#define _________________NORMAN_R3_________________       KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH
*/


#define _________________MACARR_L1_________________       KC_PGUP,    KC_PGDN,    KC_HOME,    KC_END,     KC______
#define _________________MACARR_L2_________________       KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT,   KC______
#define _________________MACARR_L3_________________       KC______,   KC_CTLA,    KC_MCCPY,   KC_MCPIN,   KC_DEL

#define _________________NUMBER_L__________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R__________________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________NUMB_R1___________________       KC_MINPLS,  KC_7,       KC_8,       KC_9,       KC_COLN
#define _________________NUMB_R2___________________       KC_DIVMLT,  KC_4,       KC_5,       KC_6,       KC_CSTC
#define _________________NUMB_R3___________________       KC_DOTEQL,  KC_1,       KC_2,       KC_ALT3,    KC_LGUI
#define _________________NUMB_R4___________________       KC______,   KC_0,       KC_0,       KC______,   KC______
/*
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
*/
#define ___________________BLANK___________________       _____,  _____,   _____,   _____,   _____
#define _________________KC_BLANK__________________       KC______, KC______, KC______, KC______, KC______

#define _________________RGB_1_____________________       KC_LRST,   KC_LHUI,    KC_LSAI,    KC_LVAI,    KC_LSPI
#define _________________RGB_2_____________________       KC_LRMOD,  KC_LHUD,    KC_LSAD,    KC_LVAD,    KC_LSPD

#define _________________MEDIA_____________________       KC_MPLY,   KC_MUTE,    KC_VOLD,    KC_VOLU,    KC______
#define _________________LYOUT_____________________       KC______,  KC_QUER,    KC_DVRK,    KC______,   KC______

#define _________________KC_PUNC_L1________________       KC_BSLS,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC
#define _________________KC_PUNC_L2________________       KC_PLUS,    KC_MINS,    KC_ASTR,    KC_SLSH,    KC_EQL
#define _________________KC_PUNC_L3________________       KC_LBRC,    KC_RBRC,    KC_LPRN,    KC_RPRN,    KC_AMPR

#define _________________KC_FUNC_1_________________       KC______,   KC_F9,      KC_F10,     KC_F11,     KC_F12
#define _________________KC_FUNC_2_________________       KC______,   KC_F5,      KC_F6,      KC_F7,      KC_F8
#define _________________KC_FUNC_3_________________       KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4


//#define _________________MISSION___________________       LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_DOWN), LCTL(KC_RIGHT), KC______

/*

#define _________________LOWER_L1__________________        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________LOWER_L2__________________        _________________FUNC_LEFT_________________
#define _________________LOWER_L3__________________        _________________FUNC_RIGHT________________

#define _________________LOWER_R1__________________        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________LOWER_R2__________________        _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
#define _________________LOWER_R3__________________        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT



#define _________________RAISE_L1__________________        ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________        ___________________BLANK___________________
#define _________________RAISE_L3__________________        ___________________BLANK___________________

#define _________________RAISE_R1__________________        ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________        _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC
#define _________________RAISE_R3__________________        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END



#define _________________ADJUST_L1_________________        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________ADJUST_L2_________________        MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define _________________ADJUST_L3_________________        RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T

#define _________________ADJUST_R1_________________        KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
#define _________________ADJUST_R2_________________        AG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN
#define _________________ADJUST_R3_________________        MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT
*/
