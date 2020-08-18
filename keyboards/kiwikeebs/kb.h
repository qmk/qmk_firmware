#ifndef KB_H
#define KB_H

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02,      \
	K10, K11, K12, K13  \
) { \
	{ K00,   K01,   K02,   KC_NO }, \
	{ K10,   K11,   K12,   K13 }  \
}

#endif