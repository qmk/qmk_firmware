#pragma once

#include "quantum.h"

#define XXX KC_NO

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
