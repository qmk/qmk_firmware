#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, \
    k06, k07, k08, k09, k10, \
    k11, k12, k13, k14, k15, \
    k16, k17, k18, k19, k20 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, }, \
    { k06, k07, k08, k09, k10 },       \
    { k11, k12, k13, k14, k15 },       \
    { k16, k17, k18, k19, k20 }        \
}

