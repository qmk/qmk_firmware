#pragma once

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, K04, \
	K10, K11, K12, K13, K14, K25 \
) { \
	{ K00,    K01,    K02,    K03,    K04,    KC_NO }, \
	{ K10,    K11,    K12,    K13,    K14,    KC_NO }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  K25 }, \
}
