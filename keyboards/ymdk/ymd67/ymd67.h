#pragma once

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,      \
	K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, \
	K40, K41, K42, K43,                K47, K48, K49, K4A, K4B, K4C, K4D       \
) { \
	{ K00,  K01,    K02,  K03,  K04,    K05,    K06,    K07,  K08,  K09,  K0A,  K0B,  K0C,    K0D,  K0E   }, \
	{ K10,  K11,    K12,  K13,  K14,    K15,    K16,    K17,  K18,  K19,  K1A,  K1B,  K1C,    K1D,  KC_NO }, \
	{ K20,  K21,    K22,  K23,  K24,    K25,    K26,    K27,  K28,  K29,  K2A,  K2B,  KC_NO,  K2D,  KC_NO }, \
	{ K30,  KC_NO,  K32,  K33,  K34,    K35,    K36,    K37,  K38,  K39,  K3A,  K3B,  K3C,    K3D,  K3E   }, \
	{ K40,  K41,    K42,  K43,  KC_NO,  KC_NO,  KC_NO,  K47,  K48,  K49,  K4A,  K4B,  K4C,    K4D,  KC_NO }  \
}
