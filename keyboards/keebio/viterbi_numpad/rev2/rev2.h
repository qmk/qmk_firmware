#pragma once

#include "viterbi.h"
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

#define LAYOUT( \
    R00, R01, R02, R03, R04, \
	R10, R11, R12, R13, R14, \
	R20, R21, R22, R23, R24, \
	R30, R31, R32, R33, R34, \
	R40, R41, R42, R43, R44, \
	R50, R51, R52, R53, R54, \
	R60, R61, R62, R63, R64 \
	) \
	{ \
		{ R00, R01, R02, R03, R04}, \
		{ R10, R11, R12, R13, R14}, \
		{ R20, R21, R22, R23, R24}, \
		{ R30, R31, R32, R33, R34}, \
		{ R40, R41, R42, R43, R44}, \
		{ R50, R51, R52, R53, R54}, \
		{ R60, R61, R62, R63, R64}, \
	}

#define LAYOUT_ortho_7x5 LAYOUT
