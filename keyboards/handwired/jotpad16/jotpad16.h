#pragma once

#include "quantum.h"

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_ortho_4x4( \
	k00, k01, k02, k03, \
	k10, k11, k12, k13, \
	k20, k21, k22, k23, \
	k30, k31, k32, k33 \
) \
{ \
	{ k00, k01, k02, k03 }, \
	{ k10, k11, k12, k13 }, \
	{ k20, k21, k22, k23 }, \
	{ k30, k31, k32, k33 } \
}

