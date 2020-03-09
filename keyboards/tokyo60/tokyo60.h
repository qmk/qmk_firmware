#pragma once

#include "quantum.h"
#include "via.h"

#define XXX KC_NO

#define LAYOUT_60_hhkb( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K1D,\
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K2D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K3D, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3C, K4D, \
         K42, K43,           K46,                          K4B, K4C       \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, K2D }, \
    { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
    { XXX, K42, K43, XXX, XXX, K46, XXX, XXX, XXX, XXX, XXX, K4B, K4C, K4D }  \
}
