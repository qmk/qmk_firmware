#pragma once

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
         k00, k01, k02, k03, k04, \
         k10, k11, k12, k13, k14, \
         k20, k21, k22, k23, k24, \
    k05, k30, k31, k32, k33, k34  \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, XXX }, \
    { k20, k21, k22, k23, k24, XXX }, \
    { k30, k31, k32, k33, k34, XXX }  \
}
