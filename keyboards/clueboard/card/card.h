#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
	k00,      k01,      k02, \
	     k10,      k12,      \
	k20,      k21,      k22, \
	     k11,                \
	          k30, k31, k32  \
) { \
	{ k00, k01, k02, }, \
	{ k10, k11, k12, }, \
	{ k20, k21, k22, }, \
	{ k30, k31, k32, } \
}
