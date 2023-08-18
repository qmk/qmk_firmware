#pragma once
#include "kuchosauronad0.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#  define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x12_wrapper(...)       LAYOUT_ortho_5x12(__VA_ARGS__)

#define LAYOUT_collide39_base_wrapper(...)   LAYOUT_collide39_base(__VA_ARGS__)

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

#define ___________________BLANK___________________        _______, _______, _______, _______, _______

#ifdef TAP_DANCE_ENABLE
#  define _________________QWERTY_L1_________________     KC_Q,    KC_DW,   KC_EOL,  KC_R,    KC_TMX
#  define _________________QWERTY_L2_________________     KC_BOL,  KC_S,    KC_D,    KC_NW,   KC_G
#  define _________________QWERTY_L3_________________     KC_Z,    KC_X,    KC_C,    KC_V,    KC_PW
#else
#  define _________________QWERTY_L1_________________     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#  define _________________QWERTY_L2_________________     KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#  define _________________QWERTY_L3_________________     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#endif

#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________PLOVER_L1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________PLOVER_L2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________PLOVER_L3_________________       KC_NO,   KC_NO,   KC_C,    KC_V,    KC_NO

#define _________________PLOVER_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________PLOVER_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________PLOVER_R3_________________       KC_NO,   KC_NO,   KC_N,    KC_M,    KC_NO

#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define ______________COLEMAK_MOD_DH_L1____________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________       KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________       KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________DVORAK_L1_________________       KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________       KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________       KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________       KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________       KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z

#define ________________DVORAK_AU_L1_______________       KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define ________________DVORAK_AU_L2_______________       KC_O,    KC_A,    KC_E,   KC_I,     KC_U
#define ________________DVORAK_AU_L3_______________       KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define ________________DVORAK_AU_R1_______________       KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define ________________DVORAK_AU_R2_______________       KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define ________________DVORAK_AU_R3_______________       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z

#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________NORMAN_L1_________________       KC_Q,    KC_W,    KC_D,    KC_F,    KC_K
#define _________________NORMAN_L2_________________       KC_A,    KC_S,    KC_E,    KC_T,    KC_G
#define _________________NORMAN_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________NORMAN_R1_________________       KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN
#define _________________NORMAN_R2_________________       KC_Y,    KC_N,    KC_I,    KC_O,    KC_U
#define _________________NORMAN_R3_________________       KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________MALTRON_L1________________       KC_Q,    KC_P,    KC_Y,    KC_C,    KC_B
#define _________________MALTRON_L2________________       KC_A,    KC_N,    KC_I,    KC_S,    KC_F
#define _________________MALTRON_L3________________       KC_SCLN, KC_SLSH, KC_J,    KC_G,    KC_COMM

#define _________________MALTRON_R1________________       KC_V,    KC_M,    KC_U,    KC_Z,    KC_L
#define _________________MALTRON_R2________________       KC_D,    KC_T,    KC_D,    KC_O,    KC_R
#define _________________MALTRON_R3________________       KC_DOT,  KC_W,    KC_K,    KC_MINS, KC_X

#define _________________EUCALYN_L1________________       KC_SLSH, KC_COMM, KC_DOT,  KC_F,    KC_Q
#define _________________EUCALYN_L2________________       KC_A,    KC_O,    KC_E,    KC_I,    KC_U
#define _________________EUCALYN_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_W

#define _________________EUCALYN_R1________________       KC_M,    KC_R,    KC_D,    KC_Y,    KC_P
#define _________________EUCALYN_R2________________       KC_G,    KC_T,    KC_K,    KC_S,    KC_N
#define _________________EUCALYN_R3________________       KC_B,    KC_H,    KC_J,    KC_L,    KC_SCLN

#define _____________CARPLAX_QFMLWY_L1_____________       KC_Q,    KC_F,    KC_M,    KC_L,    KC_W
#define _____________CARPLAX_QFMLWY_L2_____________       KC_D,    KC_S,    KC_T,    KC_N,    KC_R
#define _____________CARPLAX_QFMLWY_L3_____________       KC_Z,    KC_V,    KC_G,    KC_C,    KC_X

#define _____________CARPLAX_QFMLWY_R1_____________       KC_Y,    KC_U,    KC_O,    KC_B,    KC_J
#define _____________CARPLAX_QFMLWY_R2_____________       KC_I,    KC_A,    KC_E,    KC_H,    KC_SCLN
#define _____________CARPLAX_QFMLWY_R3_____________       KC_P,    KC_K,    KC_COMM, KC_DOT,  KC_SLSH

#define _____________CARPLAX_QGMLWB_L1_____________       KC_Q,    KC_G,    KC_M,    KC_L,    KC_W
#define _____________CARPLAX_QGMLWB_L2_____________       KC_D,    KC_S,    KC_T,    KC_N,    KC_R
#define _____________CARPLAX_QGMLWB_L3_____________       KC_Z,    KC_X,    KC_C,    KC_F,    KC_J

#define _____________CARPLAX_QGMLWB_R1_____________       KC_B,    KC_Y,    KC_U,    KC_V,    KC_SCLN
#define _____________CARPLAX_QGMLWB_R2_____________       KC_I,    KC_A,    KC_E,    KC_O,    KC_H
#define _____________CARPLAX_QGMLWB_R3_____________       KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH

#define _____________CARPLAX_QGMLWY_L1_____________       KC_Q,    KC_G,    KC_M,    KC_L,    KC_W
#define _____________CARPLAX_QGMLWY_L2_____________       KC_D,    KC_S,    KC_T,    KC_N,    KC_R
#define _____________CARPLAX_QGMLWY_L3_____________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_J

#define _____________CARPLAX_QGMLWY_R1_____________       KC_Y,    KC_F,    KC_U,    KC_B,    KC_SCLN
#define _____________CARPLAX_QGMLWY_R2_____________       KC_I,    KC_A,    KC_E,    KC_O,    KC_H
#define _____________CARPLAX_QGMLWY_R3_____________       KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH

#ifdef UNICODE_ENABLE
#  define _______________UNICODE_L1__________________     UC_DISA,UC_DISA, UC_DISA, UC_DISA, UC_DISA
#  define _______________UNICODE_L2__________________     UC_DISA,UC_DISA, UC_DISA, UC_DISA, UC_DISA
#  define _______________UNICODE_L3__________________     UC_DISA,UC_DISA, UC_DISA, UC_DISA, UC_DISA

#  define _______________UNICODE_R1__________________     UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG
#  define _______________UNICODE_R2__________________     UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG
#  define _______________UNICODE_R3__________________     UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG
#endif

#ifdef UNICODEMAP_ENABLE
#  define _______________UNICODE_L1__________________     X(SMRK),  X(THINK),  X(CLOWN), X(HUNDR),  X(BANG)
#  define _______________UNICODE_L2__________________     X(GRIN),  X(MONKEY), X(OKOK),  X(EGGPL),  X(LIT)
#  define _______________UNICODE_L3__________________     X(WEARY), X(UNAMU),  X(EFFU),  X(MONOCL), X(IRONY)

#  define _______________UNICODE_R1__________________     X(DRUG0),   X(THUP),  X(INUP),  X(DIZZY), X(COOL)
#  define _______________UNICODE_R2__________________     X(FIST0),   X(FIST2), X(FIST3), X(FIST1), X(OKOK)
#  define _______________UNICODE_R3__________________     X(MNDBLWN), X(THDN),  X(SPOCK), X(HOLE),  X(DASH)
#endif

#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define _________________MEDIA_RIGHT_______________       KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define _________________MEDIA_LEFT________________       KC_VOLD, KC_VOLD, KC_MUTE, KC_VOLU, KC_VOLU

#define _________________LOWER_L1__________________       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________LOWER_L2__________________       ___________________BLANK___________________
#define _________________LOWER_L3__________________       _______, _______, _______, OS_UNI,  TM_X

#define _________________LOWER_R1__________________       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________LOWER_R2__________________       _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
#define _________________LOWER_R3__________________       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT

#define _________________RAISE_L1__________________       ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________       ___________________BLANK___________________
#define _________________RAISE_L3__________________       ___________________BLANK___________________

#define _________________RAISE_R1__________________       ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC
#define _________________RAISE_R3__________________       _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END

#define _________________ADJUST_L1_________________       QWERTY,  COLEMAK, DVORAK,  WORKMAN, PLOVER
#define _________________ADJUST_L2_________________       _________________FUNC_LEFT_________________
#define _________________ADJUST_L3_________________       _________________MEDIA_LEFT________________

#define _________________ADJUST_R1_________________       SEC1,    SEC2,    SEC3,    SEC4,    SEC5
#define _________________ADJUST_R2_________________       _________________FUNC_RIGHT________________
#define _________________ADJUST_R3_________________       _________________MEDIA_RIGHT_______________

#define _________________RGB_UP____________________       RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________RGB_CENTER________________       MU_TOGG,  CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define _________________RGB_DOWN__________________       RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_RGB_T

#define _________________RGB_R1____________________       RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________RGB_R2____________________       MU_TOGG,  CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define _________________RGB_R3____________________       RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_RGB_T

#define __________________GAMEPAD_L1_______________       _______,  KC_Q,    KC_W,    KC_E,     _______
#define __________________GAMEPAD_L2_______________       _______,  KC_A,    KC_S,    KC_D,     _______
#define __________________GAMEPAD_L3_______________       KC_1,     KC_2,    KC_3,    KC_4,     KC_5

#define __________________GAMEPAD_R1_______________       _______,  KC_U,    KC_UP,   KC_O,     _______
#define __________________GAMEPAD_R2_______________       _______,  KC_LEFT, KC_DOWN, KC_RIGHT, _______
#define __________________GAMEPAD_R3_______________       KC_6,     KC_7,    KC_8,    KC_9,     KC_0
/* vi: ft=c:tw=80:sw=2:ts=2:sts=2:et */

