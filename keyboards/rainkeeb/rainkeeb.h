#pragma once

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02, K03, K04,      \
	K10, K11,      K13, K14, K15, \
	K20, K21, K22, K23, K24, K25, \
	K30, K31, K32, K33, K34,      \
	K40, K41, K42, K43, K44, K45, \
	K50, K51, K52, K53, K54,      \
	K60, K61, K62,      K64, K65, \
	K70,      K72, K73, K74  \
) { \
	{ K00,   K01,   K02,   K03,   K04,   KC_NO }, \
	{ K10,   K11,   KC_NO, K13,   K14,   K15 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25 }, \
	{ K30,   K31,   K32,   K33,   K34,   KC_NO }, \
	{ K40,   K41,   K42,   K43,   K44,   K45 }, \
	{ K50,   K51,   K52,   K53,   K54,   KC_NO }, \
	{ K60,   K61,   K62,   KC_NO, K64,   K65 }, \
	{ K70,   KC_NO, K72,   K73,   K74,   KC_NO }  \
}

#endif