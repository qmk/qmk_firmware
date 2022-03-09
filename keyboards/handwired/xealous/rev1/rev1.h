#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06,      R06, R05, R04, R03, R02, R01, R00, \
    L10, L11, L12, L13, L14, L15,      R17, R16, R15, R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24, L25,           R26, R25, R24, R23, R22, R21, R20, \
    L30, L31, L32, L33, L34, L35,                R35, R34, R33, R32, R31, R30, \
    L40, L41, L42, L43, L44,                          R44, R43, R42, R41, R40 \
) { \
    { XXX, L06, L05, L04, L03, L02, L01, L00 }, \
    { XXX, XXX, L15, L14, L13, L12, L11, L10 }, \
    { XXX, XXX, L25, L24, L23, L22, L21, L20 }, \
    { XXX, XXX, L35, L34, L33, L32, L31, L30 }, \
    { XXX, XXX, XXX, L44, L43, L42, L41, L40 }, \
    { R00, R01, R02, R03, R04, R05, R06, XXX }, \
    { R10, R11, R12, R13, R14, R15, R16, R17 }, \
    { R20, R21, R22, R23, R24, R25, R26, XXX }, \
    { R30, R31, R32, R33, R34, R35, XXX, XXX }, \
    { R40, R41, R42, R43, R44, XXX, XXX, XXX } \
}

#define LAYOUT_split60 LAYOUT
