#pragma once

#include "quantum.h"
#include "rev1.h"

/*
 * Encoders: Disable SPI, enable internal pull-up on pins, read pin LOW for press
 * eswl: PB7
 * eswr: PB4
 */

#define LAYOUT( \
         E01,                                                          E02, \
/*       0    1    2    3    4    5    6    7    8    9    10   11     12 */\
/* 0 */  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11,   K12, \
/* 1 */  K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24,        \
/* 2 */  K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37,        \
/* 3 */  K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,   K50, \
/* 4 */  K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, K62         \
  ) { \
/* 0 */{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11,   K12   }, \
/* 1 */{ K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24,   KC_NO }, \
/* 2 */{ K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37,   KC_NO }, \
/* 3 */{ K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,   K50   }, \
/* 4 */{ K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, KC_NO, K62   }  \
  }
