#pragma once
#include "bocaj.h"

#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_wrapper(...)        LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...) LAYOUT_ergodox_pretty(__VA_ARGS__)

#define _________________QWERTY_L1__________________        KC_Q,     KC_W,           KC_E,           KC_R,           KC_T
#define _________________QWERTY_L2__________________        KC_A,     KC_S,    GUI_CTR(0, KC_D),      KC_F,           KC_G
#define _________________QWERTY_L3__________________        KC_Z,     KC_X,           KC_C,           KC_V,           KC_B

#define _________________QWERTY_R1__________________        KC_Y,     KC_U,           KC_I,           KC_O,           KC_P
#define _________________QWERTY_R2__________________        KC_H,     KC_J,    GUI_CTR(0, KC_K),      KC_L,           KC_SCLN
#define _________________QWERTY_R3__________________        KC_N,     KC_M,           KC_COMM,        KC_DOT,         KC_SLASH

// Hardware Driven Workman
#define _________________WORKMAN_L1_________________        KC_Q,     KC_D,           KC_R,           KC_W,           KC_B
#define _________________WORKMAN_L2_________________        KC_A,     KC_S,    GUI_CTR(0, KC_H),      KC_T,           KC_G // GUI_CTR(0, kc) behaves as GUI_T(kc)
#define ________________WWORKMAN_L2_________________        KC_A,     KC_S,    GUI_CTR(1, KC_H),      KC_T,           KC_G // GUI_CTR(1, kc) behaves as CTR_T(kc)
#define _________________WORKMAN_L3_________________        KC_Z,     KC_X,           KC_M,           KC_C,           KC_V

#define _________________WORKMAN_R1_________________        KC_J,     KC_F,           KC_U,           KC_P,           KC_SCLN
#define _________________WORKMAN_R2_________________        KC_Y,     KC_N,    GUI_CTR(0, KC_E),      KC_O,           KC_I // GUI_CTR(0, kc) behaves as GUI_T(kc)
#define ________________WWORKMAN_R2_________________        KC_Y,     KC_N,    GUI_CTR(1, KC_E),      KC_O,           KC_I // GUI_CTR(1, kc) behaves as CTR_T(kc)
#define _________________WORKMAN_R3_________________        KC_K,     KC_L,           KC_COMM,        KC_DOT,         KC_SLASH


#define __________________NUMBER_LEFT_______________        KC_1,     KC_2,           KC_3,           KC_4,           KC_5
#define __________________NUMBER_RIGHT______________        KC_6,     KC_7,           KC_8,           KC_9,           KC_0

#define __________________FUNCTION_LEFT_____________        KC_F1,    KC_F2,          KC_F3,          KC_F4,          KC_F5
#define __________________FUNCTION_RIGHT____________        KC_F6,    KC_F7,          KC_F8,          KC_F9,          KC_F10

#define ____________________BLANK___________________        KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS
