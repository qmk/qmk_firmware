#pragma once

#include "quantum.h"

#define NOPE KC_NO

#define LAYOUT( \
                                            K08,           K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B \
) { \
    { NOPE,NOPE,NOPE,NOPE,NOPE,NOPE,NOPE,NOPE,K08, NOPE,NOPE,K0B }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B } \
}
