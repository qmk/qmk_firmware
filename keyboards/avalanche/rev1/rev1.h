#pragma once

#include "../avalanche.h"

#include "quantum.h"

#define LAYOUT( \
         L00, L10, L20, L30, L40, L50,           R50, R40, R30, R20, R10, R00, \
         L01, L11, L21, L31, L41, L51,           R51, R41, R31, R21, R11, R01, \
    L04, L02, L12, L22, L32, L42, L52, L55, R55, R52, R42, R32, R22, R12, R02, R04, \
         L03, L13, L23, L33, L43, L53, L54, R54, R53, R43, R33, R23, R13, R03, \
                        L14, L24, L34, L44, R44, R34, R24, R14 \
) \
{ \
    { L00, L01, L02, L03, L04, KC_NO}, \
    { L10, L11, L12, L13, L14, KC_NO}, \
    { L20, L21, L22, L23, L24, KC_NO}, \
    { L30, L31, L32, L33, L34, KC_NO}, \
    { L40, L41, L42, L43, L44, KC_NO}, \
    { L50, L51, L52, L53, L54, L55}, \
    { R00, R01, R02, R03, R04, KC_NO}, \
    { R10, R11, R12, R13, R14, KC_NO}, \
    { R20, R21, R22, R23, R24, KC_NO}, \
    { R30, R31, R32, R33, R34, KC_NO}, \
    { R40, R41, R42, R43, R44, KC_NO}, \
    { R50, R51, R52, R53, R54, R55}, \
}
