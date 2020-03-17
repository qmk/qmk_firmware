#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT(k00, k01, k02, k03, k04, k05, k06, k07, k08) {   \
        { k00, k01, k02 },                                      \
        { k03, k04, k05 },                                      \
        { k06, k07, k08 }                                       \
    }
