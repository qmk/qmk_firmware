#pragma once
#include "boboysdadda.h"


#if (!defined(LAYOUT) && defined(KEYMAP))
#   define LAYOUT KEYMAP
#endif

//clang-formate off
#define KEYMAP_wrapper(...)                 LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                 LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)      LAYOUT_ortho_4x12(__VA_ARGS__)
#define layout_ortho_5x12_wrapper(...)      LAYOUT_orth_5x12(__VA_ARGS__)

#define _________________QWERTY_L1_________________         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________         KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

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

#define _________________LOWER_L1__________________         UC_FLIP, UC_TABL, UC_SHRG, UC_DISA, XXXXXXX
#define _________________LOWER_L2__________________         KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX
#define _________________LOWER_L3__________________         KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX
#define _________________LOWER_L4__________________         ___________________BLANK___________________

#define _________________LOWER_R1__________________         ___________________BLANK___________________
#define _________________LOWER_R2__________________         ___________________BLANK___________________
#define _________________LOWER_R3__________________         XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
#define _________________LOWER_R4__________________         ___________________BLANK___________________


#define _________________RAISE_L1__________________         ___________________BLANK___________________
#define _________________RAISE_L2__________________         ___________________BLANK___________________
#define _________________RAISE_L3__________________         _________________FUNC_LEFT_________________
#define _________________RAISE_L4__________________         _________________FUNC_RIGHT________________

#define _________________RAISE_R1__________________         ___________________BLANK___________________
#define _________________RAISE_R2__________________         ___________________BLANK___________________
#define _________________RAISE_R3__________________         KC_F11,  KC_MINS,  KC_EQL,  KC_LBRC, KC_RBRC
#define _________________RAISE_R4__________________         KC_F12,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX

// clang-format on