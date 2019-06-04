#pragma once

#include "../runner3680.h"

#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

#define LAYOUT( \
   L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, \
   L10, L11, L12, L13, L14, L15, L16, R10, R11, R12, R13, R14, R15, R16, \
   L20, L21, L22, L23, L24, L25, L26, R20, R21, R22, R23, R24, R25, R26  \
   ) \
   { \
     { L00, L01, L02, L03, L04, L05, L06 }, \
     { L10, L11, L12, L13, L14, L15, L16 }, \
     { L20, L21, L22, L23, L24, L25, L26 }, \
     { R06, R05, R04, R03, R02, R01, R00 }, \
     { R16, R15, R14, R13, R12, R11, R10 }, \
     { R26, R25, R24, R23, R22, R21, R20 }  \
   }
