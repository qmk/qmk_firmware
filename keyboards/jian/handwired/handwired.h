#pragma once

#include "jian.h"

#define XXX KC_NO
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06,    R06, R05, R04, R03, R02, R01, R00, \
       L11, L12, L13, L14, L15, L16,    R16, R15, R14, R13, R12, R11, \
       L21, L22, L23, L24, L25, L26,    R26, R25, R24, R23, R22, R21, \
                      L34, L35, L36,    R36, R35, R34 \
) \
{ \
  {L00, L01, L02, L03, L04, L05, L06,   R06, R05, R04, R03, R02, R01, R00}, \
  {XXX, L11, L12, L13, L14, L15, L16,   R16, R15, R14, R13, R12, R11, XXX}, \
  {XXX, L21, L22, L23, L24, L25, L26,   R26, R25, R24, R23, R22, R21, XXX}, \
  {XXX, XXX, XXX, XXX, L34, L35, L36,   R36, R35, R34, XXX, XXX, XXX, XXX} \
}

#define LAYOUT_symmetric( \
  K00, K01, K02, K03, K04, K05, K06, \
       K11, K12, K13, K14, K15, K16, \
       K21, K22, K23, K24, K25, K26, \
                      K34, K35, K36 \
) \
{ \
  {K00, K01, K02, K03, K04, K05, K06,   K06, K05, K04, K03, K02, K01, K00}, \
  {XXX, K11, K12, K13, K14, K15, K16,   K16, K15, K14, K13, K12, K11, XXX}, \
  {XXX, K21, K22, K23, K24, K25, K26,   K26, K25, K24, K23, K22, K21, XXX}, \
  {XXX, XXX, XXX, XXX, K34, K35, K36,   K36, K35, K34, XXX, XXX, XXX, XXX} \
}
