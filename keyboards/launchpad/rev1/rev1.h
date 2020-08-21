#ifndef REV1_H
#define REV1_H

#include "../launchpad.h"

#include "quantum.h"

#define LAYOUT( \
	K00, K01, \
	K10, K11, \
	K20, K21, \
	K30, K31  \
	) \
	{ \
		{ K00, K01 }, \
		{ K10, K11 }, \
		{ K20, K21 }, \
		{ K30, K31 } \
	}

#endif
