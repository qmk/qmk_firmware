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


#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x10_wrapper(...)       LAYOUT_ortho_5x10(__VA_ARGS__)
#define LAYOUT_ortho_5x5_wrapper(...)        LAYOUT_ortho_5x5(__VA_ARGS__)


/*
NOTE: If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,           KC_O,        KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,           KC_L,        KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    TD(TD_COMQUES), TD(TD_DTEX), LT(_MDIA,KC_SLASH)


#define _________________COLEMAK_L1________________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________        KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________        KC_J,    KC_L,    KC_U,           KC_Y,        KC_SCLN
#define _________________COLEMAK_R2________________        KC_H,    KC_N,    KC_E,           KC_I,        KC_O
#define _________________COLEMAK_R3________________        KC_K,    KC_M,    TD(TD_COMQUES), TD(TD_DTEX), KC_SLASH
/*
#define ______________COLEMAK_MOD_DH_L1____________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________        KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________        KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________        KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH
*/

#define _______________DVORAK_L1___________________        KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),        KC_P, KC_Y
#define _______________DVORAK_L2___________________        KC_A,                 KC_O,              KC_E,               KC_U, KC_I
#define _______________MACDVK_L3___________________        MT(MOD_LCTL,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LGUI, KC_J), KC_K, KC_X
#define _______________WINDVK_L3___________________        MT(MOD_LGUI,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LCTL, KC_J), KC_K, KC_X

#define _______________DVORAK_R1___________________        KC_F,       KC_G,       KC_C,              KC_R,              KC_L
#define _______________DVORAK_R2___________________        KC_D,       KC_H,       KC_T,              KC_N,              KC_S
#define _______________MACDVK_R3___________________        KC_B,       KC_M,       MT(MOD_LGUI,KC_W), MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z)
#define _______________WINDVK_R3___________________        KC_B,       KC_M,       MT(MOD_LCTL,KC_W), MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z)

#define __________c39__MACDVK_L3___________________        MT(MOD_LCTL,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LGUI, KC_J), LT(_SYMB,KC_K), TD(TD_XSPC)
#define __________c39__WINDVK_L3___________________        MT(MOD_LGUI,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LCTL, KC_J), LT(_SYMB,KC_K), TD(TD_XSPC)
#define __________c39__MACDVK_R3___________________        LT(_MNMB,KC_B),       LT(_SYMB,KC_M),    MT(MOD_LGUI,KC_W),  MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z)
#define __________c39__WINDVK_R3___________________        LT(_NUMB,KC_B),       LT(_SYMB,KC_M),    MT(MOD_LCTL,KC_W),  MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z)

/*
#define ________________DVORAK_AU_L1_______________        KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define ________________DVORAK_AU_L2_______________        KC_O,    KC_A,    KC_E,   KC_I,     KC_U
#define ________________DVORAK_AU_L3_______________        KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define ________________DVORAK_AU_R1_______________        KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define ________________DVORAK_AU_R2_______________        KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define ________________DVORAK_AU_R3_______________        KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define _________________WORKMAN_L1________________        KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________        KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________        KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________        KC_J,    KC_F,    KC_U,           KC_P,        KC_SCLN
#define _________________WORKMAN_R2________________        KC_Y,    KC_N,    KC_E,           KC_O,        KC_I
#define _________________WORKMAN_R3________________        KC_K,    KC_L,    TD(TD_COMQUES), TD(TD_DTEX), KC_SLASH


#define _________________NORMAN_L1_________________       KC_Q,    KC_W,    KC_D,    KC_F,    KC_K
#define _________________NORMAN_L2_________________       KC_A,    KC_S,    KC_E,    KC_T,    KC_G
#define _________________NORMAN_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________NORMAN_R1_________________       KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN
#define _________________NORMAN_R2_________________       KC_Y,    KC_N,    KC_I,    KC_O,    KC_U
#define _________________NORMAN_R3_________________       KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH
*/

//split thumb key layouts, not ergodox friendly
#define ________WIN_THUMB_CLUSTER_________                LT(_SYMB,KC_SPC), LT(_NUMB,KC_BSPC), LT(_NUMB,KC_TAB), LT(_SYMB,KC_ENT)
#define ________MAC_THUMB_CLUSTER_________                LT(_SYMB,KC_SPC), LT(_MNMB,KC_BSPC), LT(_MNMB,KC_TAB), LT(_SYMB,KC_ENT)

#define __________________WIN_THUMB_CLUSTER_V2______________ LT(_FUNC,KC_ENT), LT(_NUMB,KC_BSPC), MT(MOD_LSFT,KC_SPC), LT(_NUMB,KC_TAB), LT(_SYMB,KC_ENT), KC_RSFT
#define __________________MAC_THUMB_CLUSTER_V2______________ LT(_FUNC,KC_ENT), LT(_MNMB,KC_BSPC), MT(MOD_LSFT,KC_SPC), LT(_MNMB,KC_TAB), LT(_SYMB,KC_ENT), KC_RSFT
#define ________MAC_THUMB_L______                            LT(_FUNC,KC_ENT), LT(_MNMB,KC_BSPC), MT(MOD_LSFT,KC_SPC)
#define ________MAC_THUMB_R______                            LT(_MNMB,KC_TAB), LT(_SYMB,KC_ENT),    LT(_MDIA,KC_ENT)
#define ________WIN_THUMB_L______                            LT(_FUNC,KC_ENT), LT(_NUMB,KC_BSPC), MT(MOD_LSFT,KC_SPC)
#define ________WIN_THUMB_R______                            LT(_NUMB,KC_TAB), LT(_SYMB,KC_ENT),    LT(_MDIA,KC_ENT)


#define ________MAC_MISSION_CTRL__________                LCTL(KC_LEFT),    LCTL(KC_UP),       LCTL(KC_DOWN),    LCTL(KC_RGHT)

#define _________________MACNAV_L1_________________       KC_PGUP,    KC_PGDN,    KC_HOME,       KC_END,         KC_____
#define _________________MACNAV_L2_________________       KC_LEFT,    KC_UP,      KC_DOWN,       KC_RIGHT,       KC_____
#define _________________MACNAV_L3_________________       KC_____,    LGUI(KC_A), TD(TD_MCCCPY), TD(TD_MCPSTIN), KC_DEL

#define _________________WINNAV_L1_________________       KC_PGUP,     KC_PGDN,    KC_HOME,     KC_END,      TD(TD_FNDR)
#define _________________WINNAV_L2_________________       KC_LEFT,     KC_UP,      KC_DOWN,     KC_RIGHT,    TD(TD_PTSP)
#define _________________WINNAV_L3_________________       TD(TD_ACCW), LCTL(KC_A), TD(TD_CCPY), TD(TD_PSTI), TD(TD_DDEL)

#define _________________NUMBER_L__________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R__________________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________NUMB_R1___________________       TD(TD_MINPLS), KC_7, KC_8,              KC_9,              KC_COLN
#define _________________NUMB_R2___________________       TD(TD_DIVMLT), KC_4, KC_5,              KC_6,              C_S_T(KC_COLN)
#define _________________NUMB_R3_MAC_______________       TD(TD_DOTEQL), KC_1, MT(MOD_LGUI,KC_2), MT(MOD_LALT,KC_3), MT(MOD_LCTL,KC_0)
#define _________________NUMB_R3_WIN_______________       TD(TD_DOTEQL), KC_1, MT(MOD_LCTL,KC_2), MT(MOD_LALT,KC_3), MT(MOD_LGUI,KC_0)
#define _________________NUMB_R4___________________       KC_____,       KC_0, KC_0,              KC_____,           KC_____
/*
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
*/
#define _________________KC_BLANK__________________       KC_____, KC_____, KC_____, KC_____, KC_____

#define _________________RGB_1_____________________       RGBRST,     RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI
#define _________________RGB_2_____________________       RGB_MOD,    RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD

#define _________________MEDIA_____________________       KC_MPLY,    KC_MUTE,     KC_VOLD,      KC_VOLU,     KC_____
#define _________________MEDIA_V2__________________       KC_EJCT,    KC_MRWD,     KC_MPLY,      KC_MFFD,     KC_____
#define _________________LYOUT_____________________       KC_____,    KC_QWERTY,   KC_MACBASE,   KC_WINBASE,  KC_____

#define _________________PUNC_L1___________________       KC_BSLS,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC
#define _________________PUNC_L1_ALT_______________       KC_DQT,     KC_AT,      KC_HASH,    KC_DLR,     KC_PERC
#define _________________PUNC_L2___________________       KC_PLUS,    KC_MINS,    KC_ASTR,    KC_SLSH,    KC_EQL
#define _________________PUNC_L3___________________       KC_LBRC,    KC_RBRC,    KC_LPRN,    KC_RPRN,    KC_AMPR
#define _________________PUNC_L3_ALT_______________       KC_____,    KC_____,    KC_TILD,    KC_CIRC,    KC_GRV

#define _________________PUNC_R1___________________       TD(TD_MINPLS), KC_DQT,  KC_EQL,  KC_____, KC_____
#define _________________PUNC_R2___________________       TD(TD_DIVMLT), KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS
#define _________________PUNC_R3___________________       TD(TD_DOTEQL), KC_EQL,  KC_BSLS, KC_____, KC_____

#define _____________FUNC_1_______________                KC_F9,      KC_F10,     KC_F11,     KC_F12
#define _____________FUNC_2_______________                KC_F5,      KC_F6,      KC_F7,      KC_F8
#define _____________FUNC_3_______________                KC_F1,      KC_F2,      KC_F3,      KC_F4

#define _____________FUNC_L1_______________________       MAKEKF,   MAKEK,   KC_____, KC_ESC,  LCTL(LALT(KC_DEL))
#define _____________FUNC_L3_______________________       KC_LGUI, KC_RALT, KC_LCTL, KC_TAB,  KC_____
