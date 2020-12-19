#ifndef KB_H
#define KB_H

#include "quantum.h"

#define KEYMAP( \
	K00, K01, K02, K03,                \
	K10, K11, K12, K13, K14, K15, K16, \
	K20, K21, K22, K23, K24, K25, K26, \
	               K33, K34, K35,      \
	     K41,      K43, K44, K45,      \
	K50, K51, K52,      K54, K55, K56  \
) { \
	{ K00,   K01,   K02,   K03,   KC_NO, KC_NO, KC_NO }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26 }, \
	{ KC_NO, KC_NO, KC_NO, K33,   K34,   K35,   KC_NO }, \
	{ KC_NO, K41,   KC_NO, K43,   K44,   K45,   KC_NO }, \
	{ K50,   K51,   K52,   KC_NO, K54,   K55,   K56 }  \
}

#endif