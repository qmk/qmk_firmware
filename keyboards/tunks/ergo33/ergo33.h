#pragma once

#include "quantum.h"

/* The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* Matrix layout
 * ,---------.
 * | 00 | 01 |------------------------.
 * |----|----| 02 | 03 | 04 | 05 | 06 |
 * | 10 | 11 |----|----|----|----|----|
 * |----|----| 12 | 13 | 14 | 14 | 16 |
 * | 20 | 21 |----|----|----|----|----|
 * |----|----| 22 | 23 | 24 | 25 | 26 |
 * | 30 | 31 |----|----|----|----|----|  ,----.
 * |----|----| 32 | 33 | 34 | 35 | 36 |  | 46 |
 * | 40 | 41 |---------------------------|----'
 * `---------'            | 43 | 44 | 45 |
 *                        `--------------'
 */

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
    k30, k31, k32, k33, k34, k35, k36, \
    k40, k41,                          k46, \
                        k43, k44, k45 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, k36 }, \
    { k40, k41, KC_NO, k43, k44, k45, k46 }, \
}
