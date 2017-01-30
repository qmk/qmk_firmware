#ifndef XK66_H
#define XK66_H

#include "quantum.h"
#include "led.h"


// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c, K0d, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b,      K2d, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, K3c,      \
    K40, K41, K42, K43, K44, K45, K46,      K48, K49, K4a, K4b, K4c, K4d  \
) { \
    { K00, K01,   K02, K03, K04, K05, K06, K07,   K08, K09, K0a, K0b, K0c,   K0d   }, \
    { K10, K11,   K12, K13, K14, K15, K16, K17,   K18, K19, K1a, K1b, K1c,   K1d   }, \
    { K20, K21,   K22, K23, K24, K25, K26, K27,   K28, K29, K2a, K2b, KC_NO, K2d   }, \
    { K30, KC_NO, K32, K33, K34, K35, K36, K37,   K38, K39, K3a, K3b, K3c,   KC_NO }, \
    { K40, K41,   K42, K43, K44, K45, K46, KC_NO, K48, K49, K4a, K4b, K4c,   K4d   } \
}

#endif