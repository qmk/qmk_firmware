#ifndef KB_H
#define KB_H

#include "quantum.h"

#define LAYOUT_ortho_3x4( \
	K00, K01, K02, \
	K10, K11, K12, \
	K20, K21, K22, \
	K30, K31, K32 \
) { \
	{ K00,   K01,   K02 }, \
	{ K10,   K11,   K12 }, \
	{ K20,   K21,   K22 }, \
	{ K30,   K31,   K32 } \
}

#endif
