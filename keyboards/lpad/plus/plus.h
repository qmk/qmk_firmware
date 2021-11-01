#pragma once

#include "quantum.h"

#define LAYOUT( \
	          K02, K03, K04,      \
	K10, K11, K12, K13, K14,      \
	K20, K21, K22, K23, K24,      \
	K30, K31, K32, K33,           \
	K40, K41, K42  \
) { \
	{ KC_NO, KC_NO, K02,   K03,   K04,   KC_NO }, \
	{ K10,   K11,   K12,   K13,   K14,   KC_NO }, \
	{ K20,   K21,   K22,   K23,   K24,   KC_NO }, \
	{ K30,   K31,   K32,   K33,   KC_NO, KC_NO }, \
	{ K40,   K41,   K42,   KC_NO, KC_NO, KC_NO }  \
}
