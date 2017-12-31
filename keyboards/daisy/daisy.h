#ifndef DAISY_H
#define DAISY_H

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K3A, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
	K30, K31, K32, K34, K35, K37, K38, K39 \
) \
{ \
	{ K00, K01, K02, K03,   K04, K05, K06,   K07, K08, K09, K0A }, \
	{ K10, K11, K12, K13,   K14, K15, K16,   K17, K18, K19, K1A }, \
	{ K20, K21, K22, K23,   K24, K25, K26,   K27, K28, K29, K2A }, \
	{ K30, K31, K32, KC_NO, K34, K35, KC_NO, K37, K38, K39, K3A }  \
}

#endif