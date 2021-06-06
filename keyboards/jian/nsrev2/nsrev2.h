#pragma once

#include "jian.h"

#define XXX KC_NO

#define LAYOUT( \
  L20, L00, L01, L12, L02, L03, L04,    R04, R03, R02, R12, R01, R00, R20, \
       L10, L11, L22, L13, L14, L05,    R05, R14, R13, R22, R11, R10, \
       L21, L32, L33, L23, L24, L15,    R15, R24, R23, R33, R32, R21, \
                      L34, L25, L35,    R35, R25, R34 \
) \
{ \
  {L00, L01, L02, L03, L04, L05 }, \
  {L10, L11, L12, L13, L14, L15 }, \
  {L20, L21, L22, L23, L24, L25 }, \
  {XXX, XXX, L32, L33, L34, L35 }, \
  {R00, R01, R02, R03, R04, R05 }, \
  {R10, R11, R12, R13, R14, R15 }, \
  {R20, R21, R22, R23, R24, R25 }, \
  {XXX, XXX, R32, R33, R34, R35 }  \
}

#define LAYOUT_symmetric( \
  K20, K00, K01, K12, K02, K03, K04, \
       K10, K11, K22, K13, K14, K05, \
       K21, K32, K33, K23, K24, K15, \
                      K34, K25, K35  \
) \
{ \
  {K00, K01, K02, K03, K04, K05 }, \
  {K10, K11, K12, K13, K14, K15 }, \
  {K20, K21, K22, K23, K24, K25 }, \
  {XXX, XXX, K32, K33, K34, K35 }, \
  {K00, K01, K02, K03, K04, K05 }, \
  {K10, K11, K12, K13, K14, K15 }, \
  {K20, K21, K22, K23, K24, K25 }, \
  {XXX, XXX, K32, K33, K34, K35 }  \
}
