#pragma once
#include "quantum.h"

// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_numpad_6x5( \
  k00, k01, k02, k03, \
  k10, k11, k12, k13, k14, \
  k20, k21, k22, k23,      \
  k30, k31, k32, k33, k24,  \
  k40, k41, k42, k43,      \
  k50,   k51,    k52, k44  \
) \
{ \
  {KC_NO, k00, k01, k02, k03}, \
  {k10, k11, k12, k13, k14}, \
  {k20, k21, k22, k23, k24}, \
  {k30, k31, k32, k33, KC_NO}, \
  {k40, k41, k42, k43, k44}, \
  {k50, k51, KC_NO, k52, KC_NO} \
}

/*  matrix layout
   * ,------------------------.
   * |    | 00 | 01 | 03 | 04 |
   * |----|----|----|----|----|
   * | 10 | 11 | 12 | 13 | 14 |
   * |----|----|----|----|----|
   * | 20 | 21 | 22 | 23 |    |
   * |----|----|----|----| 24 |
   * | 30 | 31 | 32 | 33 |    |
   * |----|----|----|----|----|
   * | 40 | 41 | 42 | 43 |    |
   * |----|----|----|----| 44 |
   * | 50 |   51    | 52 |    |
   * `------------------------'
 */


