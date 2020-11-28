#pragma once

#include "quantum.h"

#define LAYOUT_ortho_3x14( \
	 K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D ,   \
	 K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D ,   \
	 K20,  K21,  K22,        K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D     \
) { \
    {K00,  K01,  K02,  K03,   K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D},   \
    {K10,  K11,  K12,  K13,   K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D},   \
    {K20,  K21,  K22,  KC_NO, K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D}    \
}
