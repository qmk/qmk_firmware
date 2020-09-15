#ifndef KB_H
#define KB_H

#include "quantum.h"

#define KEYMAP( \
	     K01, K02, K03, K04, \
	     K11, K12, K13,      \
	     K21, K22, K23, K24, \
	     K31, K32, K33,      \
	K40, K41, K42, K43, K44  \
) { \
	{ KC_NO, K01,   K02,   K03,   K04 }, \
	{ KC_NO, K11,   K12,   K13,   KC_NO }, \
	{ KC_NO, K21,   K22,   K23,   K24 }, \
	{ KC_NO, K31,   K32,   K33,   KC_NO }, \
	{ K40,   K41,   K42,   K43,   K44 }  \
}

#endif