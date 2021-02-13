#pragma once
#include "quantum.h"

// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_numpad_5x4( \
  k00, k01, k02, k03, \
  k10, k11, k12,      \
  k20, k21, k22, k13,  \
  k30, k31, k32,      \
    k40,    k41, k33  \
) \
{ \
  {k00, k01, k02, k03}, \
  {k10, k11, k12, k13}, \
  {k20, k21, k22, KC_NO}, \
  {k30, k31, k32, k33}, \
  {k40, KC_NO, k41, KC_NO} \
}

/*  matrix layout
   * ,-------------------.
   * | 00 | 01 | 02 | 03 |
   * |----|----|----|----|
   * | 10 | 11 | 12 |    |
   * |----|----|----| 13 |
   * | 20 | 21 | 22 |    |
   * |----|----|----|----|
   * | 30 | 31 | 32 |    |
   * |----|----|----| 33 |
   * |   40    | 41 |    |
   * `-------------------'
 */


