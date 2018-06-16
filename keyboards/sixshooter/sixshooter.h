#ifndef SIXSHOOTER_H
#define SIXSHOOTER_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
	K00, K01, K02, \
	K03, K04, K05 \
) { \
	{ K00, K01, K02, K03, K04, K05 }, \
}

#endif
