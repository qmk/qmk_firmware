#ifndef KEYMAP_NORDIC_H
#define KEYMAP_NORDIC_H

#include "keymap_common.h"

// Alt gr
#define ALGR(kc) kc | 0x1400
#define NO_ALGR KC_RALT

// Normal characters
#define NO_HALF	KC_GRV
#define NO_PLUS	KC_MINS
#define NO_TICK	KC_EQL

#define NO_AM	KC_LBRC
#define NO_QUOT	KC_RBRC
#define NO_AE	KC_SCLN
#define NO_OSLH	KC_QUOT
#define	NO_APOS	KC_NUHS

#define NO_LESS	KC_NUBS
#define NO_DASH KC_SLSH

// Shifted characters
#define NO_SECT LSFT(NO_HALF)
#define NO_QUO2	LSFT(KC_2)
#define NO_BULT LSFT(KC_4)
#define NO_AMP	LSFT(KC_6)
#define NO_SLSH LSFT(KC_7)
#define NO_LPAR	LSFT(KC_8)
#define NO_RPAR	LSFT(KC_9)
#define NO_EQL	LSFT(KC_0)
#define NO_QUES	LSFT(NO_PLUS)
#define NO_BTCK	LSFT(NO_TICK)

#define NO_SUPR LSFT(NO_QUOT)

#define NO_GRTR	LSFT(NO_LESS)
#define NO_SEMI LSFT(KC_COMM)
#define NO_COLN LSFT(KC_DOT)
#define NO_UNDR LSFT(NO_DASH)

// Alt Gr-ed characters
#define NO_AT	ALGR(KC_2)
#define NO_PND	ALGR(KC_3)
#define NO_DLR	ALGR(KC_4)
#define NO_LBRC ALGR(KC_7)
#define NO_LBRK ALGR(KC_8)
#define NO_RBRK ALGR(KC_9)
#define NO_RBRC	ALGR(KC_0)
#define NO_PIPE ALGR(NO_TICK)

#define NO_EURO ALGR(KC_E)
#define NO_TILD ALGR(NO_QUOT)

#define NO_BSLS ALGR(NO_LESS)
#define NO_NU 	ALGR(KC_M)

#endif