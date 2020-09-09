#ifndef REV1_H
#define REV1_H

#include "keaboard.h"

#include "quantum.h"

#define LAYOUT( \
    L01, L05, L09, L13, L17, L21,                 R21, R17, R13, R09, R05, R01, \
    L02, L06, L10, L14, L18, L22,                 R22, R18, R14, R10, R06, R02, \
    L03, L07, L11, L15, L19, L23, L24,       R24, R23, R19, R15, R11, R07, R03, \
    L04, L08, L12, L16, L20,      L25,       R25,      R20, R16, R12, R08, R04  \
    ) \
    { \
        { L01,   L05,   L09,   L13,   L17,   L21,   KC_NO }, \
        { L02,   L06,   L10,   L14,   L18,   L22,   KC_NO }, \
        { L03,   L07,   L11,   L15,   L19,   L23,   L24   }, \
        { L04,   L08,   L12,   L16,   L20,   KC_NO, L25   }, \
        { R01,   R05,   R09,   R13,   R17,   R21,   KC_NO }, \
        { R02,   R06,   R10,   R14,   R18,   R22,   KC_NO }, \
        { R03,   R07,   R11,   R15,   R19,   R23,   R24   }, \
        { R04,   R08,   R12,   R16,   R20,   KC_NO, R25   }  \
    }

#endif
