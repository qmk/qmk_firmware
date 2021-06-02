#pragma once

#include "../redox.h"

#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

// rows are doubled
#define LAYOUT( \
                            R5C6,                                  R11C6,  R11C5,                             \
  R0C0, R0C1, R0C2, R0C3, R0C4, R0C5,                                R6C5,  R6C4,  R6C3,  R6C2,  R6C1, R6C0,  \
  R1C0, R1C1, R1C2, R1C3, R1C4, R1C5, R0C6,                   R6C6,  R7C5,  R7C4,  R7C3,  R7C2,  R7C1, R7C0,  \
  R2C0, R2C1, R2C2, R2C3, R2C4, R2C5, R1C6,                   R7C6,  R8C5,  R8C4,  R8C3,  R8C2,  R8C1, R8C0,  \
  R3C0, R3C1, R3C2, R3C3, R3C4, R3C5, R2C6, R3C6,      R9C6,  R8C6,  R9C5,  R9C4,  R9C3,  R9C2,  R9C1, R9C0,  \
  R4C0, R4C1, R4C2, R4C3,    R4C4,    R4C5, R4C6,      R10C6, R10C5,    R10C4,    R10C3, R10C2, R10C1, R10C0  \
) \
{ \
    { R0C0,  R0C1,  R0C2,  R0C3,  R0C4,  R0C5,  R0C6 },  \
    { R1C0,  R1C1,  R1C2,  R1C3,  R1C4,  R1C5,  R1C6 },  \
    { R2C0,  R2C1,  R2C2,  R2C3,  R2C4,  R2C5,  R2C6 },  \
    { R3C0,  R3C1,  R3C2,  R3C3,  R3C4,  R3C5,  R3C6 },  \
    { R4C0,  R4C1,  R4C2,  R4C3,  R4C4,  R4C5,  R4C6 },  \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R5C6 },  \
\
    { R6C0,  R6C1,  R6C2,  R6C3,  R6C4,  R6C5,  R6C6  }, \
    { R7C0,  R7C1,  R7C2,  R7C3,  R7C4,  R7C5,  R7C6  }, \
    { R8C0,  R8C1,  R8C2,  R8C3,  R8C4,  R8C5,  R8C6  }, \
    { R9C0,  R9C1,  R9C2,  R9C3,  R9C4,  R9C5,  R9C6  }, \
    { R10C0, R10C1, R10C2, R10C3, R10C4, R10C5, R10C6 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R11C5, R11C6 }  \
}
