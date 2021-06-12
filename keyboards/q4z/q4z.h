#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    K01, K06, K11, K16, K21, \
  K02, K07, K12, K17, K22, K26, K30, K34, K38,  K41, \
  K03,  K08, K13, K18, K23, K27, K31, K35, K39, K42, \
  K04,    K09, K14, K19, K24, K28, K32, K36,    K40, \
  K05, K10, K15,     K20,    K25,    K29, K33, K37 \
) { \
{ K01, K06, K11, K16, K21 }, \
{ K02, K07, K12, K17, K22, K26, K30, K34, K38, K41 }, \
{ K03, K08, K13, K18, K23, K27, K31, K35, K39, K42 }, \
{ K04, K09, K14, K19, K24, K28, K32, K36, K40 }, \
{ K05, K10, K15, K20, K25, K29, K33, K37 } \
}
