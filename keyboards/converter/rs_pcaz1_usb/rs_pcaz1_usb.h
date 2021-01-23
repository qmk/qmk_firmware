#pragma once

#include "quantum.h"

#define LAYOUT(                                                 \
      K76,    K0F,  K05,K06,K08,K0A,   K0C,K0E,K10,K11,   K12,K07,K09,K0B,  K16,K17,K15,  K2D,K02,K04,K30, \
    K01,K03,  K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K58,K2A,  K2C,K34,K60,  K62,K2E,K2F,K47, \
    K19,K1A,  K35, K36,K37,K38,K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,   K2B,  K42,K4A,K7B,  K44,K45,K46,K7D, \
    K31,K33,  K4C,  K4D,K4E,K4F,K50,K51,K52,K53,K54,K55,K56,K57,      K59,                K5B,K5C,K5D,     \
    K48,K49,  K63,   K64,K65,K66,K67,K68,K69,K6A,K6B,K6C,K6D,         K6E,      K14,      K70,K71,K72,K5A, \
    K5F,K61,  K77,K13, K78, K73,        K79,      K74, K75, K7A, K43, K0D,  K18,K1B,K1C,  K5E,    K32      \
) { \
    { KC_NO,  K01 ,  K02 ,  K03 ,  K04 ,  K05 ,  K06 ,  K07  }, \
    {  K08 ,  K09 ,  K0A ,  K0B ,  K0C ,  K0D ,  K0E ,  K0F ,}, \
    {  K10 ,  K11 ,  K12 ,  K13 ,  K14 ,  K15 ,  K16 ,  K17  }, \
    {  K18 ,  K19 ,  K1A ,  K1B ,  K1C ,  K1D ,  K1E ,  K1F  }, \
    {  K20 ,  K21 ,  K22 ,  K23 ,  K24 ,  K25 ,  K26 ,  K27  }, \
    {  K28 ,  K29 ,  K2A ,  K2B ,  K2C ,  K2D ,  K2E ,  K2F  }, \
    {  K30 ,  K31 ,  K32 ,  K33 ,  K34 ,  K35 ,  K36 ,  K37  }, \
    {  K38 ,  K39 ,  K3A ,  K3B ,  K3C ,  K3D ,  K3E ,  K3F  }, \
    {  K40 ,  K41 ,  K42 ,  K43 ,  K44 ,  K45 ,  K46 ,  K47  }, \
    {  K48 ,  K49 ,  K4A , KC_NO,  K4C ,  K4D ,  K4E ,  K4F  }, \
    {  K50 ,  K51 ,  K52 ,  K53 ,  K54 ,  K55 ,  K56 ,  K57  }, \
    {  K58 ,  K59 ,  K5A ,  K5B ,  K5C ,  K5D ,  K5E ,  K5F  }, \
    {  K60 ,  K61 ,  K62 ,  K63 ,  K64 ,  K65 ,  K66 ,  K67  }, \
    {  K68 ,  K69 ,  K6A ,  K6B ,  K6C ,  K6D ,  K6E , KC_NO }, \
    {  K70 ,  K71 ,  K72 ,  K73 ,  K74 ,  K75 ,  K76 ,  K77  }, \
    {  K78 ,  K79 ,  K7A ,  K7B , KC_NO,  K7D , KC_NO, KC_NO }  \
}
