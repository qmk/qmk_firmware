#pragma once


#include "quantum.h"

#define LAYOUT_horizontal( \
	     K01, K02, \
	K10, K11, K12, \
	K20, K21, K22, \
	K30, K31, K32  \
) { \
	{ KC_NO, K01,   K02 }, \
	{ K10,   K11,   K12 }, \
	{ K20,   K21,   K22 }, \
	{ K30,   K31,   K32 }  \
}

