#pragma once

#include "quantum.h"

#define LAYOUT_ortho_2x5( \
	K00, K01, K02, K03, K04, \
	K10, K11, K12, K13, K14  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }, \
	{ K10,   K11,   K12,   K13,   K14 }  \
}
