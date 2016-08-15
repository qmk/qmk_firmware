#ifndef BANTAM44_H
#define BANTAM44_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19,    K1A, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30,   K31,   K32,   K33,     K34,    K35,   K36, K37, K38  \
) \
{ \
    { K00, K01, K02, K03,   K04, K05,   K06, K07,   K08, K09, K0A,   K0B   }, \
    { K10, K11, K12, K13,   K14, K15,   K16, K17,   K18, K19, KC_NO, K2A }, \
	{ K20, K21, K22, K23,   K24, K25,   K26, K27,   K28, K29, K2A,   K2B   }, \
	{ K30, K31, K32, KC_NO, K33, KC_NO, K34, KC_NO, K35, K36, K37,   K38   }, \
}

#endif
