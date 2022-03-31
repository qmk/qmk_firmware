#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    L00, L01, L02, L03, L04,    R04, R03, R02, R01, R00, \
    L05, L06, L07, L08, L09,    R09, R08, R07, R06, R05, \
    L10, L11, L12, L13, L14,    R14, R13, R12, R11, R10, \
    L15, L16, L17, L18, L19,    R19, R18, R17, R16, R15 \
) \
{ \
    { L00,   L01,   L02,   L03,   L04 }, \
    { L05,   L06,   L07,   L08,   L09 }, \
    { L10,   L11,   L12,   L13,   L14 }, \
    { L15,   L16,   L17,   L18,   L19 }, \
    { R00,   R01,   R02,   R03,   R04 }, \
    { R05,   R06,   R07,   R08,   R09 }, \
    { R10,   R11,   R12,   R13,   R14 }, \
    { R15,   R16,   R17,   R18,   R19}, \
}
