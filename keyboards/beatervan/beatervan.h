#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K169, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
    K300, K301, K302,           K303, K304,           K305, K306, K307  \
) \
{ \
    { K000,   K001,   K002,   K003,  K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011 }, \
    { K100,   K101,   K102,   K103,  K104,   K105,   K106,   K107,   K108,   K109,   K110,   K169 }, \
    { K200,   K201,   K202,   K203,  K204,   K205,   K206,   K207,   K208,   K209,   K210,   K211 }, \
    { K300,   K301,   K302,  KC_NO,  K303,  KC_NO,   K304,   K305,   K306,   K307,   KC_NO }  \
}

#define LAYOUT_arrow( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32,      K33, K37,      K38, K39, K3A, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   K32,   K33,  KC_NO, KC_NO, KC_NO, K37,   K38,   K39,   K3A,   K3B }  \
}

#define LAYOUT_command( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K34,      K33, K37,           K38, K39, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   K32,   K33,  K34,   KC_NO, KC_NO, K37,   K38,   K39, KC_NO,   K3B }  \
}

#define LAYOUT_arrow_command( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K34,      K33, K37,      K38, K39, K3A, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   K32,   K33,  K34,   KC_NO, KC_NO, K37,   K38,   K39,   K3A,   K3B }  \
}
