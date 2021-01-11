#pragma once

#include "ivy.h"

#define LAYOUT( \
	K00, \
    K01, \
    K02  \
	) \
	{ \
		{ K00, KC_NO, KC_NO }, \
		{ KC_NO, K01, KC_NO }, \
		{ KC_NO, KC_NO, K02 }, \
	}
