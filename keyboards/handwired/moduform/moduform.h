#pragma once

#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif


#define LAYOUT( \
	L00, L01, L02, L03, L04,                	   R00, R01, R02, R03, R04, \
	L10, L11, L12, L13, L14,                	   R10, R11, R12, R13, R14, \
	L20, L21, L22, L23, L24,                	   R20, R21, R22, R23, R24, \
	          L33, L34, L35,                	   R30, R31, R32 \
	) \
	{ \
		{ L00, L01, L02, L03, L04 },	 \
		{ L10, L11, L12, L13, L14 },	 \
		{ L20, L21, L22, L23, L24 },	 \
		{ KC_NO, KC_NO, L33, L34, L35 },	 \
\
		{ R00, R01, R02, R03, R04 },    \
		{ R10, R11, R12, R13, R14 },    \
		{ R20, R21, R22, R23, R24 },    \
		{ R30, R31, R32, KC_NO, KC_NO },    \
}
