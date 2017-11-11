#ifndef REV2_H
#define REV2_H

#include "../splinter.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);

#define KEYMAP(L00, L01, L02, L03, L04,     R00, R01, R02, R03, R04, \
               L10, L11, L12, L13, L14,     R10, R11, R12, R13, R14, \
               L20, L21, L22, L23, L24,     R20, R21, R22, R23, R24, \
               L30, L31, L32, L33, L34,     R30, R31, R32, R33, R34, \
               L40, L41, L42, L43, L44,     R40, R41, R42, R43, R44) \
               { \
                 { L00, L01, L02, L03, L04 }, \
                 { L10, L11, L12, L13, L14 }, \
                 { L20, L21, L22, L23, L24 }, \
                 { L30, L31, L32, L33, L34 }, \
                 { L40, L41, L42, L43, L44 }, \
                 { R00, R01, R02, R03, R04 }, \
                 { R10, R11, R12, R13, R14 }, \
                 { R20, R21, R22, R23, R24 }, \
                 { R30, R31, R32, R33, R34 }, \
                 { R40, R41, R42, R43, R44 }  \
               }

#endif
