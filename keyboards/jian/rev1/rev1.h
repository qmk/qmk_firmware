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
  {L00, L01, L02, L03, L04, L05, L06}, \
  {XXX, L11, L12, L13, L14, L15, L16}, \
  {XXX, L21, L22, L23, L24, L25, L26}, \
  {XXX, XXX, XXX, XXX, L34, L35, L36}, \
  {R00, R01, R02, R03, R04, R05, R06}, \
  {XXX, R11, R12, R13, R14, R15, R16}, \
  {XXX, R21, R22, R23, R24, R25, R26}, \
  {XXX, XXX, XXX, XXX, R34, R35, R36} \
}

#define LAYOUT_symmetric( \
  K00, K01, K02, K03, K04, K05, K06, \
       K11, K12, K13, K14, K15, K16, \
       K21, K22, K23, K24, K25, K26, \
                      K34, K35, K36 \
) \
{ \
  {K00, K01, K02, K03, K04, K05, K06}, \
  {XXX, K11, K12, K13, K14, K15, K16}, \
  {XXX, K21, K22, K23, K24, K25, K26}, \
  {XXX, XXX, XXX, XXX, K34, K35, K36}, \
  {K00, K01, K02, K03, K04, K05, K06}, \
  {XXX, K11, K12, K13, K14, K15, K16}, \
  {XXX, K21, K22, K23, K24, K25, K26}, \
  {XXX, XXX, XXX, XXX, K34, K35, K36} \
}

#ifdef DIPS_ENABLE
#define LAYOUT_dips( \
  DL0, DL1, DL2, DL3, DL4, DL5, \
  DR5, DR4, DR3, DR2, DR1, DR0  \
) \
{ \
  {XXX, XXX, XXX, XXX, XXX, XXX, XXX}, \
  {DL0, XXX, XXX, XXX, XXX, XXX, XXX}, \
  {DL1, XXX, XXX, XXX, XXX, XXX, XXX}, \
  {DL2, DL3, DL4, DL5, XXX, XXX, XXX}, \
  {XXX, XXX, XXX, XXX, XXX, XXX, XXX}, \
  {DR0, XXX, XXX, XXX, XXX, XXX, XXX}, \
  {DR1, XXX, XXX, XXX, XXX, XXX, XXX}, \
  {DR2, DR3, DR4, DR5, XXX, XXX, XXX}, \
}
#endif // DIPS_ENABLE
