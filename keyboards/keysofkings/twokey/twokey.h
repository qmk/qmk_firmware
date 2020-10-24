#pragma once

#include "quantum.h"

#define LAYOUT( \
	K00,      \
	K10, K11  \
) { \
	{ K00,   KC_NO }, \
	{ K10,   K11 }  \
}

