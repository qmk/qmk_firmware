#pragma once

#include "fossyl.h"

#define XXX KC_NO

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,                    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                    R10, R11, R12, R13, R14, R15, \
         L21, L22, L23, L24, L25,                    R20, R21, R22, R23, R24, \
                             L35,                    R30\
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { XXX, L21, L22, L23, L24, L25 }, \
    { XXX, XXX, XXX, XXX, XXX, L35 }, \
\
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, XXX }, \
    { R30, XXX, XXX, XXX, XXX, XXX } \
}
