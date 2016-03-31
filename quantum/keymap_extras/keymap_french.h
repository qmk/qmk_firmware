#ifndef KEYMAP_FRENCH_H
#define KEYMAP_FRENCH_H

#include "keymap_common.h"

// Alt gr
#define ALGR(kc) kc | 0x1400
#define NO_ALGR KC_RALT

// Normal characters
#define FR_SUP2	KC_GRV
#define FR_AMP	KC_1
#define FR_EACU	KC_2
#define FR_QUOT	KC_3
#define FR_APOS	KC_4
#define FR_LPRN	KC_5
#define FR_MINS	KC_6
#define FR_EGRV	KC_7
#define FR_UNDS	KC_8
#define FR_CCED	KC_9
#define FR_AGRV	KC_0
#define FR_RPRN	KC_MINS
#define FR_EQL	KC_EQL

#define FR_A 	KC_Q
#define FR_Z	KC_W
#define	FR_CIRC	KC_LBRC
#define FR_DLR	KC_RBRC

#define FR_Q 	KC_A
#define FR_M 	KC_SCLN
#define FR_UGRV	KC_QUOT
#define FR_ASTR	KC_NUHS

#define FR_LESS	KC_NUBS
#define FR_W	KC_Z
#define FR_COMM	KC_M
#define FR_SCLN	KC_COMM
#define FR_COLN	KC_DOT
#define FR_EXLM	KC_SLSH

// Shifted characters
#define FR_1 	LSFT(KC_1)
#define FR_2 	LSFT(KC_2)
#define FR_3 	LSFT(KC_3)
#define FR_4 	LSFT(KC_4)
#define FR_5 	LSFT(KC_5)
#define FR_6 	LSFT(KC_6)
#define FR_7 	LSFT(KC_7)
#define FR_8 	LSFT(KC_8)
#define FR_9 	LSFT(KC_9)
#define FR_0 	LSFT(KC_0)
#define FR_OVRR	LSFT(FR_RPRN)
#define FR_PLUS LSFT(FR_EQL)

#define FR_UMLT	LSFT(FR_CIRC)
#define FR_PND	LSFT(FR_DLR)
#define	FR_PERC	LSFT(FR_UGRV)
#define FR_MU 	LSFT(FR_ASTR)

#define FR_GRTR	LSFT(FR_LESS)
#define FR_QUES	LSFT(FR_COMM)
#define FR_DOT	LSFT(FR_SCLN)
#define FR_SLSH	LSFT(FR_COLN)
#define FR_SECT	LSFT(FR_EXLM)

// Alt Gr-ed characters
#define FR_TILD	ALGR(KC_2)
#define FR_HASH	ALGR(KC_3)
#define FR_LCBR ALGR(KC_4)
#define FR_LBRC	ALGR(KC_5)
#define FR_PIPE ALGR(KC_6)
#define FR_GRV 	ALGR(KC_7)
#define FR_BSLS	ALGR(KC_8)
#define FR_CIRC	ALGR(KC_9)
#define FR_AT 	ALGR(KC_0)
#define FR_RBRC	ALGR(FR_RPRN)
#define FR_RCBR ALGR(FR_EQL)

#define FR_EURO	ALGR(KC_E)
#define FR_BULT	ALGR(FR_DLR)

#endif