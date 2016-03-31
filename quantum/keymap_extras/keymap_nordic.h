#ifndef KEYMAP_NORDIC_H
#define KEYMAP_NORDIC_H

#include "keymap_common.h"

// Alt gr
#define ALGR(kc) kc | 0x1400
#define NO_ALGR KC_RALT

// Normal characters
#define NO_HALF	KC_GRV
#define NO_PLUS	KC_MINS
#define NO_ACUT	KC_EQL

#define NO_AM	KC_LBRC
#define NO_QUOT	KC_RBRC
#define NO_AE	KC_SCLN
#define NO_OSLH	KC_QUOT
#define	NO_APOS	KC_NUHS

#define NO_LESS	KC_NUBS
#define NO_MINS KC_SLSH

// Shifted characters
#define NO_SECT LSFT(NO_HALF)
#define NO_QUO2	LSFT(KC_2)
#define NO_BULT LSFT(KC_4)
#define NO_AMP	LSFT(KC_6)
#define NO_SLSH LSFT(KC_7)
#define NO_LPRN	LSFT(KC_8)
#define NO_RPRN	LSFT(KC_9)
#define NO_EQL	LSFT(KC_0)
#define NO_QUES	LSFT(NO_PLUS)
#define NO_GRV	LSFT(NO_ACUT)

#define NO_CIRC LSFT(NO_QUOT)

#define NO_GRTR	LSFT(NO_LESS)
#define NO_SCLN LSFT(KC_COMM)
#define NO_COLN LSFT(KC_DOT)
#define NO_UNDS LSFT(NO_MINS)

// Alt Gr-ed characters
#define NO_AT	ALGR(KC_2)
#define NO_PND	ALGR(KC_3)
#define NO_DLR	ALGR(KC_4)
#define NO_LCBR ALGR(KC_7)
#define NO_LBRC ALGR(KC_8)
#define NO_RBRC ALGR(KC_9)
#define NO_RCBR	ALGR(KC_0)
#define NO_PIPE ALGR(KC_NUBS)

#define NO_EURO ALGR(KC_E)
#define NO_TILD ALGR(NO_QUOT)

#define NO_BSLS ALGR(KC_MINS)
#define NO_MU 	ALGR(KC_M)

#endif
