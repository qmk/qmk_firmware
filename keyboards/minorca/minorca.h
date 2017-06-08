#ifndef MINORCA_H
#define MINORCA_H

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19,      K1B, \
	K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
	K30,      K32, K33, K34,           K37,      K39, K3A, K3B \
) \
{ \
	{ KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K0A, KC_##K0B }, \
	{ KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_NO, KC_##K1B }, \
	{ KC_##K20, KC_NO, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2A, KC_##K2B }, \
	{ KC_##K30, KC_NO, KC_##K32, KC_##K33, KC_##K34, KC_NO, KC_NO, KC_##K37, KC_NO, KC_##K39, KC_##K3A, KC_##K3B } \
}

#endif
