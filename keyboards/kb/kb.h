#ifndef KB_H
#define KB_H

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02, \
	K10, K11, K12, \
	               \
	     K31,      \
	K40, K41, K42  \
) { \
	{ K00,   K01,   K02 }, \
	{ K10,   K11,   K12 }, \
	{ KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, K31,   KC_NO }, \
	{ K40,   K41,   K42 }  \
}

#endif