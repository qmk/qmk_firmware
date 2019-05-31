#pragma once

#include "quantum.h"

#define LAYOUT_REV11( \
    K00, K01, K02, K03, \
	K10, K11, K12, K13 \
) { \
	{ K13, K12, K11, K10 }, \
    { K03, K02, K01, K00 } \
}

#define LAYOUT_REV12( \
    K00, K01, K02, K03, \
	K10, K11, K12, K13 \
) { \
    { K03, K02, K01, K00 }, \
	{ K13, K12, K11, K10 } \
}
