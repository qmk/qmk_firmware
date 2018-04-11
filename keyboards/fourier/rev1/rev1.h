#ifndef REV1_H
#define REV1_H

#include "../fourier.h"

#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

#define KEYMAP( \
	LA1, LA2, LA3, LA4, LA5, LA6, RA1, RA2, RA3, RA4, RA5, RA6, RA7, \
	LB1, LB2, LB3, LB4, LB5, LB6, RB1, RB2, RB3, RB4, RB5,      RB7, \
	LC1, LC2, LC3, LC4, LC5, LC6, RC1,      RC3, RC4, RC5, RC6, RC7, \
	LD1, LD2, LD3, LD4, LD5,      RD1,           RD4, RD5, RD6, RD7 \
	) \
	{ \
		{ LA1, LA2, LA3, LA4, LA5, LA6, KC_NO}, \
		{ LB1, LB2, LB3, LB4, LB5, LB6, KC_NO}, \
		{ LC1, LC2, LC3, LC4, LC5, LC6, KC_NO}, \
		{ LD1, LD2, LD3, LD4, LD5, KC_NO, KC_NO}, \
		{ RA1, RA2, RA3, RA4, RA5, RA6, RA7}, \
		{ RB1, RB2, RB3, RB4, RB5, KC_NO, RB7}, \
		{ RC1, KC_NO, RC3, RC4, RC5, RC6, RC7}, \
		{ RD1, KC_NO, KC_NO, RD4, RD5, RD6, RD7} \
	}

#endif
