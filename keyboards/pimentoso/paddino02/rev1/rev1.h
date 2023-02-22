#pragma once

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, \
	K10, K11, K12, K13, \
	          K22, K23  \
) { \
	{ K00,   K01,   K02,   K03 }, \
	{ K10,   K11,   K12,   K13 }, \
	{ KC_NO, KC_NO, K22,   K23 }  \
}
