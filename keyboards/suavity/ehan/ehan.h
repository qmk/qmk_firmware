#pragma once

#include "quantum.h"
#define ___ KC_NO

#define LAYOUT_default_ansi( \
    K00,  K01, K02, K03, K04,  K05,        K06, K07, K08, K09,  K0A, K0B, K0C, K0D,        K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16,       K17, K18, K19, K1A, K1B, K1C, K1D,            K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25,          K26, K27, K28, K29, K2A, K2B, K2C, K2D,         K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35,          K36, K37, K38, K39, K3A, K3B, K3C,                             \
    K40, K41, K42, K43, K44, K45,         K46, K47, K48, K49, K4A, K4B, K4C,                    K4G,      \
    K50,           K53,      K55          K56,      K58, K59,                 K5D,         K5F, K5G, K5H  \
) { \
    {    K00, K01, K02, K03, K04,  K05,        K06, K07, K08, K09, K0A, K0B, K0C, K0D, ___,       K0F, K0G, K0H,   }, \
    {    K10, K11, K12, K13, K14, K15, K16,       K17, K18, K19, K1A, K1B, K1C, K1D, ___,         K1F, K1G, K1H,   }, \
    {    K20, K21, K22, K23, K24, K25,          K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___,      K2F, K2G, K2H,   }, \
    {    K30, K31, K32, K33, K34, K35,          K36, K37, K38, K39, K3A, K3B, K3C, K3D, ___,      ___, ___, ___,   }, \
    {    K40, K41, K42, K43, K44, K45,         K46, K47, K48, K49, K4A, K4B, ___, ___, ___,       ___, K4G, ___,   }, \
    {    K50, ___, ___, K53, ___, K55,         K56, ___, K58, K59, ___, ___, ___, K5D, ___,       K5F, K4G, K5H    }  \
}
