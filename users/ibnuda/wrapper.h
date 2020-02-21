#pragma once
#include "ibnuda.h"

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

#define KEYMAP_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define ________________DVORAK_L1_______________     KC_SCLN,KC_COMM,KC_DOT, KC_P,   KC_Y
#define ________________DVORAK_L2_______________     SH_A,   CT_O,   AL_E,   KC_U,   GU_I
#define ________________DVORAK_L3_______________     KC_QUOT,KC_Q,   KC_J,   KC_K,   KC_X

#define ________________DVORAK_R1_______________     KC_F,   KC_G,   KC_C,   KC_R,   KC_L
#define ________________DVORAK_R2_______________     GU_D,   KC_H,   AL_T,   CT_N,   SH_S
#define ________________DVORAK_R3_______________     KC_B,   KC_M,   KC_W,   KC_V,   KC_Z

#define ________________RAISE_L1________________     KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR
#define ________________RAISE_L2________________     KC_HASH,KC_LEFT,KC_DOWN,KC_RGHT,KC_DLR
#define ________________RAISE_L3________________     KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR

#define ________________RAISE_R1________________     KC_BSLS,KC_7,   KC_8,   KC_9,   KC_ASTR
#define ________________RAISE_R2________________     KC_EQL, KC_4,   KC_5,   KC_6,   KC_0
#define ________________RAISE_R3________________     KC_GRV, KC_1,   KC_2,   KC_3,   KC_PLUS

#define ________________LOWER_L1________________     KC_ESC, KC_QUES,KC_UNDS,KC_F1,  KC_F2
#define ________________LOWER_L2________________     KC_LSFT,KC_TAB, KC_PGUP,KC_F5,  KC_F6
#define ________________LOWER_L3________________     KC_CLCK,KC_SLCK,KC_PGDN,KC_F9,  KC_F10

#define ________________LOWER_R1________________     KC_F3,  KC_F4,  KC_MINS,KC_SLSH,KC_BSPC
#define ________________LOWER_R2________________     KC_F7,  KC_F8,  KC_HOME,KC_LALT,KC_ENT
#define ________________LOWER_R3________________     KC_F11, KC_F12, KC_END, KC_INS, KC_SLSH

#define ________________ADJUST_L1_______________     _______,EXPLR,  KC_UP,  PRVTAB, PRVWIN
#define ________________ADJUST_L2_______________     TSKMGR, KC_LEFT,KC_DOWN,KC_RGHT,UPTAB
#define ________________ADJUST_L3_______________     _______,CLSGUI, _______,CONPST, RESET

#define ________________ADJUST_R1_______________     NXTWIN, NXTTAB, _______,_______,LCKGUI
#define ________________ADJUST_R2_______________     DNTAB,  KC_ENT, KC_LGUI,_______,CALDL
#define ________________ADJUST_R3_______________     _______,_______,_______,_______,_______
