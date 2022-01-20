#pragma once

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, K15, \
	K10, K11, K12, K13, K14, K16  \
) { \
	{ K00,   K01,   K02,   K03,  KC_NO, KC_NO, KC_NO }, \
	{ K10,   K11,   K12,   K13,  K14,   K15,   K16 },  \
}

