#ifndef KB_H
#define KB_H

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02, K03, \
	K10, K11, K12, K13, \
	K20, K21  \
) { \
	{ K03,   K02,   K01,   K00 }, \
	{ K13,   K12,   K11,   K10 }, \
	{ K21,   K20,   KC_NO, KC_NO }  \
}

#endif