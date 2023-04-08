#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,                          R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                          R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                          R20, R21, R22, R23, R24, R25, \
              L32, L33,                                              R32, R33,    \
                        L34, L45, L43,                R42, R40, R31, \
                             L44, L42,                R43, R41 \
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { XXX, XXX, L32, L33, L34, XXX }, \
    { XXX, XXX, L42, L43, L44, L45 }, \
\
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { XXX, R31, R32, R33, XXX, XXX }, \
    { R40, R41, R42, R43, XXX, XXX } \
}

#define LAYOUT_split_3x5_3( \
    XXX, L00, L01, L02, L03, L04,                          R00, R01, R02, R03, R04, XXX, \
    XXX, L10, L11, L12, L13, L14,                          R10, R11, R12, R13, R14, XXX, \
    XXX, L20, L21, L22, L23, L24,                          R20, R21, R22, R23, R24, XXX, \
              XXX, XXX,                                              XXX, XXX,    \
                        L33, L44, L42,                R42, R40, R31, \
                             XXX, XXX,                XXX, XXX \
) { \
    { XXX, L00, L01, L02, L03, L04 }, \
    { XXX, L10, L11, L12, L13, L14 }, \
    { XXX, L20, L21, L22, L23, L24 }, \
    { XXX, XXX, XXX, XXX, L33, XXX }, \
    { XXX, XXX, XXX, L42, XXX, L44 }, \
\
    { R00, R01, R02, R03, R04, XXX }, \
    { R10, R11, R12, R13, R14, XXX }, \
    { R20, R21, R22, R23, R24, XXX }, \
    { XXX, R31, XXX, XXX, XXX, XXX }, \
    { R40, XXX, R42, XXX, XXX, XXX } \
}