#ifndef KEYMAP_DVORAK_H
#define KEYMAP_DVORAK_H

#include "keymap.h"

// Normal characters
#define DV_GRV	KC_GRV
#define DV_1	KC_1
#define DV_2	KC_2
#define DV_3	KC_3
#define DV_4	KC_4
#define DV_5	KC_5
#define DV_6	KC_6
#define DV_7	KC_7
#define DV_8	KC_8
#define DV_9	KC_9
#define DV_0	KC_0
#define DV_LBRC	KC_MINS
#define DV_RBRC	KC_EQL

#define DV_QUOT KC_Q
#define DV_COMM	KC_W
#define DV_DOT	KC_E
#define DV_P	KC_R
#define DV_Y	KC_T
#define	DV_F	KC_Y
#define DV_G	KC_U
#define DV_C 	KC_I
#define	DV_R	KC_O
#define DV_L	KC_P
#define DV_SLSH	KC_LBRC
#define DV_EQL	KC_RBRC

#define DV_A	KC_A
#define DV_O	KC_S
#define DV_E	KC_D
#define DV_U	KC_F
#define DV_I	KC_G
#define DV_D	KC_H
#define DV_H	KC_J
#define DV_T	KC_K
#define DV_N	KC_L
#define DV_S	KC_SCLN
#define DV_MINS	KC_QUOT

#define DV_SCLN	KC_Z
#define DV_Q	KC_X
#define DV_J	KC_C
#define DV_K	KC_V
#define DV_X	KC_B
#define DV_B	KC_N
#define DV_M	KC_M
#define DV_W	KC_COMM
#define DV_V	KC_DOT
#define DV_Z	KC_SLSH

// Shifted characters
#define DV_TILD	LSFT(DV_GRV)
#define DV_EXLM	LSFT(DV_1)
#define DV_AT	LSFT(DV_2)
#define DV_HASH	LSFT(DV_3)
#define DV_DLR	LSFT(DV_4)
#define DV_PERC	LSFT(DV_5)
#define DV_CIRC	LSFT(DV_6)
#define DV_AMPR	LSFT(DV_7)
#define DV_ASTR	LSFT(DV_8)
#define DV_LPRN	LSFT(DV_9)
#define DV_RPRN	LSFT(DV_0)
#define DV_LCBR	LSFT(DV_LBRC)
#define DV_RCBR	LSFT(DV_RBRC)
#define DV_UNDS LSFT(DV_MINS)
#define DV_PLUS LSFT(DV_EQL)

#endif
