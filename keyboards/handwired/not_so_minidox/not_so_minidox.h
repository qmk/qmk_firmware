#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,     R05, R04, R03, R02, R01, R00, \
    L10, L11, L12, L13, L14, L15,     R15, R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24, L25,     R25, R24, R23, R22, R21, R20, \
                   LT1, LT2, LT3,     RT3, RT2, RT1 \
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { XXX, XXX, XXX, LT1, LT2, LT3 }, \
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { XXX, XXX, XXX, RT1, RT2, RT3 } \
}
