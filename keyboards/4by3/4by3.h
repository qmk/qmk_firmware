#pragma once

#include "quantum.h"

#define LAYOUT_horizontal( \
	K00, K01, K02, K03, \
	K10, K11, K12, K13, \
	K20, K21, K22, K23  \
) { \
	{ K00, K01, K02, K03 }, \
	{ K10, K11, K12, K13 }, \
	{ K20, K21, K22, K23 }  \
}

#define LAYOUT_vertical_right( \
	K20, K10, K00, \
    K21, K11, K01, \
    K22, K12, K02, \
    K23, K13, K03  \
) { \
	{ K00, K01, K02, K03 }, \
	{ K10, K11, K12, K13 }, \
	{ K20, K21, K22, K23 }  \
}

#define LAYOUT_vertical_left( \
	K03, K13, K23, \
    K02, K12, K22, \
    K01, K11, K21, \
    K00, K10, K20  \
) { \
	{ K00, K01, K02, K03 }, \
	{ K10, K11, K12, K13 }, \
	{ K20, K21, K22, K23 }  \
}

#define LAYOUT LAYOUT_horizontal
