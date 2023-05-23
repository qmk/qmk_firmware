/*
Copyright 2021 Evan Sailer, Jetpacktuxedo, & QMK Firmware

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include "quantum.h"

#define LAYOUT(\
    K39, K40, K41, K42, K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7,\
    K32, K33, K34, K35, K8,  K9,  K10, K11, K12, K13, K14, K15,\
    K38, K45, K44, K36, K16, K17, K18, K19, K20, K21, K22, K23,\
    K37,  K43,   K24,      K26,      K27,  K28,  K29,    K31\
) {\
    { K0, K1, K2, K3, K4, K5, K6, K7 },\
    { K8, K9, K10, K11, K12, K13, K14, K15 },\
    { K16, K17, K18, K19, K20, K21, K22, K23 },\
    { KC_NO, K24, K26, K27, K28, K29, KC_NO, K31 },\
    { K32, K33, K34, K35, K36, K37, K38, KC_NO },\
    { K39, K40, K41, K42, K43, K44, K45, KC_NO }\
}

#define LAYOUT_arrow(\
    K39, K40, K41, K42, K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7,\
    K32, K33, K34, K35, K8,  K9,  K10, K11, K12, K13, K14, K15,\
    K38, K45, K44, K36, K16, K17, K18, K19, K20, K21, K22, K23,\
    K37,  K43,   K24,      K26,      K27,  K28,  K29, K30, K31\
) {\
    { K0, K1, K2, K3, K4, K5, K6, K7 }, \
    { K8, K9, K10, K11, K12, K13, K14, K15 }, \
    { K16, K17, K18, K19, K20, K21, K22, K23 }, \
    { K24, KC_NO, K26, K27, K28, K29, K30, K31 }, \
    { K32, K33, K34, K35, K36, K37, K38, KC_NO }, \
    { K39, K40, K41, K42, K43, K44, K45, KC_NO } \
}

#define LAYOUT_command(\
    K39, K40, K41, K42, K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7,\
    K32, K33, K34, K35, K8,  K9,  K10, K11, K12, K13, K14, K15,\
    K38, K45, K44, K36, K16, K17, K18, K19, K20, K21, K22, K23,\
    K37, K43, K24, K25,    K26,      K27,  K28,  K29,    K31\
) {\
    { K0, K1, K2, K3, K4, K5, K6, K7 }, \
    { K8, K9, K10, K11, K12, K13, K14, K15 }, \
    { K16, K17, K18, K19, K20, K21, K22, K23 }, \
    { K24, K25, K26, K27, K28, K29, KC_NO, K31 }, \
    { K32, K33, K34, K35, K36, K37, K38, KC_NO }, \
    { K39, K40, K41, K42, K43, K44, K45, KC_NO } \
}

// This layout is typically called "southpaw_arrow" or "southpaw + arrow", but
// using "all" here to match typical qmk conventions
#define LAYOUT_all(\
    K39, K40, K41, K42, K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7,\
    K32, K33, K34, K35, K8,  K9,  K10, K11, K12, K13, K14, K15,\
    K38, K45, K44, K36, K16, K17, K18, K19, K20, K21, K22, K23,\
    K37, K43, K24, K25,    K26,      K27,  K28,  K29, K30, K31\
) {\
    { K0, K1, K2, K3, K4, K5, K6, K7 }, \
    { K8, K9, K10, K11, K12, K13, K14, K15 }, \
    { K16, K17, K18, K19, K20, K21, K22, K23 }, \
    { K24, K25, K26, K27, K28, K29, K30, K31 }, \
    { K32, K33, K34, K35, K36, K37, K38, KC_NO }, \
    { K39, K40, K41, K42, K43, K44, K45, KC_NO } \
}

#define LAYOUT_jetvan(\
    K39, K40, K41, K42, K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7,\
    K32, K33, K34, K35, K8,  K9,  K10, K11, K12, K13, K14, K15,\
    K38, K45, K44, K36, K16, K17, K18, K19, K20, K21, K22, K23,\
    K37,  K43, K24,               K27,           K29, K30, K31\
) {\
    { K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7 }, \
    { K8,  K9,  K10, K11, K12, K13, K14, K15 }, \
    { K16, K17, K18, K19, K20, K21, K22, K23 }, \
    { K24, KC_NO, KC_NO, K27, KC_NO, K29, K30, K31 }, \
    { K32, K33, K34, K35, K36, K37, K38, KC_NO }, \
    { K39, K40, K41, K42, K43, K44, K45, KC_NO } \
}
