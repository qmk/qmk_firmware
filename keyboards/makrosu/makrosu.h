#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K02, K03, K04, \
    K00, K01, K05  \
) \
{ \
    { K00, K01, K02, K03, K04, K05 }, \
}

