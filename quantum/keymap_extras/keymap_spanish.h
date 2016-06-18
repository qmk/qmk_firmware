#ifndef KEYMAP_SPANISH_H
#define KEYMAP_SPANISH_H

#include "keymap.h"

// Alt gr
#define ALGR(kc) kc | 0x1400
#define NO_ALGR KC_RALT

// Normal characters
#define ES_OVRR KC_GRV
#define ES_APOS	KC_MINS
#define ES_IEXL	KC_EQL

#define ES_GRV	KC_LBRC
#define ES_PLUS	KC_RBRC

#define ES_NTIL	KC_SCLN
#define ES_ACUT	KC_QUOT
#define ES_CCED	KC_NUHS

#define ES_LESS	KC_NUBS
#define ES_MINS	KC_SLSH

// Shifted characters
#define ES_ASML	LSFT(ES_OVRR)
#define ES_QUOT	LSFT(KC_2)
#define ES_OVDT	LSFT(KC_3)
#define ES_AMPR	LSFT(KC_6)
#define ES_SLSH LSFT(KC_7)
#define ES_LPRN LSFT(KC_8)
#define ES_RPRN LSFT(KC_9)
#define ES_EQL	LSFT(KC_0)
#define ES_QUES	LSFT(ES_APOS)
#define ES_IQUE	LSFT(ES_IEXL)

#define ES_CIRC	LSFT(ES_GRV)
#define ES_ASTR	LSFT(ES_PLUS)

#define ES_UMLT	LSFT(ES_GRV)

#define ES_GRTR	LSFT(ES_LESS)
#define ES_SCLN	LSFT(ES_COMM)
#define ES_COLN	LSFT(ES_DOT)
#define ES_UNDS	LSFT(ES_MINS)

// Alt Gr-ed characters
#define ES_BSLS	ALGR(ES_OVRR)
#define ES_PIPE	ALGR(KC_1)
#define ES_AT 	ALGR(KC_2)
#define ES_HASH	ALGR(KC_3)
#define ES_TILD	ALGR(KC_4)
#define ES_EURO	ALGR(KC_5)
#define ES_NOT	ALGR(KC_6)

#define ES_LBRC	ALGR(ES_GRV)
#define ES_RBRC ALGR(ES_PLUS)

#define ES_LCBR	ALGR(ES_ACUT)
#define ES_RCRB	ALGR(ES_CCED)

#endif