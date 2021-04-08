#ifndef MACROPAD21_H
#define MACROPAD21_H

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, K04, \
	K10, K11, K12, K13, K14, \
	K20, K21, K22, K23, K24, \
	K30, K31,      K33, K34, \
	K40,                K44  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }, \
	{ K10,   K11,   K12,   K13,   K14 }, \
	{ K20,   K21,   K22,   K23,   K24 }, \
	{ K30,   K31,   KC_NO, K33,   K34 }, \
	{ K40,   KC_NO, KC_NO, KC_NO, K44 }  \
}

#endif
