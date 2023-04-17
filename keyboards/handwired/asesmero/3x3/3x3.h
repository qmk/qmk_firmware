#pragma once

#include "quantum.h"

#define LAYOUT_9( \
	K00, K01, K02, \
	K03, K04, K05, \
	K06, K07, K08  \
) { \
	{ K00,   K01,   K02, }, \
	{ K03,   K04,   K05, }, \
	{ K06,   K07,   K08  }  \
}
