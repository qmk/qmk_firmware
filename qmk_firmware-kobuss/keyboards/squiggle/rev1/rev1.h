#pragma once

#include "squiggle.h"

#include "quantum.h"

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
  L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24, \
                 L33, L34,           R30, R31                 \
) \
{ \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { ___, ___, ___, L33, L34 }, \
    { R04, R03, R02, R01, R00 }, \
    { R14, R13, R12, R11, R10 }, \
    { R24, R23, R22, R21, R20 }, \
    { ___, ___, ___, R31, R30 }, \
}

#define LAYOUT_reversed( \
  R04, R03, R02, R01, R00,           L04, L03, L02, L01, L00, \
  R14, R13, R12, R11, R10,           L14, L13, L12, L11, L10, \
  R24, R23, R22, R21, R20,           L24, L23, L22, L21, L20, \
                 R31, R30,           L34, L33                 \
) \
{ \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { ___, ___, ___, L33, L34 }, \
    { R04, R03, R02, R01, R00 }, \
    { R14, R13, R12, R11, R10 }, \
    { R24, R23, R22, R21, R20 }, \
    { ___, ___, ___, R31, R30 }, \
}

#define LAYOUT_split_3x5_3(\
  L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24, \
            L32, L33, L34,           R30, R31, R32            \
) \
{ \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { ___, ___, L32, L33, L34 }, \
    { R04, R03, R02, R01, R00 }, \
    { R14, R13, R12, R11, R10 }, \
    { R24, R23, R22, R21, R20 }, \
    { ___, ___, R32, R31, R30 }, \
}

#define LAYOUT_complicated(\
  L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24, \
                 L33, L34,           R30, R31,                \
                 L31, L32,           R32, R33                 \
) \
{ \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { ___, L31, L32, L33, L34 }, \
    { R04, R03, R02, R01, R00 }, \
    { R14, R13, R12, R11, R10 }, \
    { R24, R23, R22, R21, R20 }, \
    { ___, R33, R32, R31, R30 }, \
}

#define LAYOUT_thumbrow(\
  L00, L01, L02, L03, L04,                     R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,                     R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,                     R20, R21, R22, R23, R24, \
                 L31, L32, L33, L34, R30, R31, R32, R33                 \
) \
{ \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { ___, L31, L32, L33, L34 }, \
    { R04, R03, R02, R01, R00 }, \
    { R14, R13, R12, R11, R10 }, \
    { R24, R23, R22, R21, R20 }, \
    { ___, R33, R32, R31, R30 }, \
}
