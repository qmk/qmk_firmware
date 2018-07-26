#ifndef AMJPAD_H
#define ADMJPAD_H

#include "quantum.h"

// readability
#define XXX KC_NO

/* AMJPAD matrix layout
   * ,-------------------.
   * | 00 | 01 | 02 | 03 |
   * |----|----|----|----|
   * | 10 | 11 | 12 | 13 |
   * |----|----|----|----|
   * | 20 | 21 | 22 |    |
   * |----|----|----| 23 |
   * | 30 | 31 | 32 |    |
   * |----|----|----|----|
   * | 40 | 41 | 42 |    |
   * |----|----|----| 43 |
   * |   50    | 52 |    |
   * `-------------------'
 */
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_numpad_6x4( \
  k00, k01, k02, k03, \
  k10, k11, k12, k13, \
  k20, k21, k22,      \
  k30, k31, k32, k23, \
  k40, k41, k42,      \
     k50,   k52, k43  \
) \
{ \
  {k00, k01, k02, k03}, \
  {k10, k11, k12, k13}, \
  {k20, k21, k22, k23}, \
  {k30, k31, k32, XXX}, \
  {k40, k41, k42, k43}, \
  {k50, XXX, k52, XXX} \
}

#define LAYOUT_ortho_6x4( \
  k00, k01, k02, k03, \
  k10, k11, k12, k13, \
  k20, k21, k22, k23, \
  k30, k31, k32, k33, \
  k40, k41, k42, k43, \
  k50, k51, k52, k53  \
) \
{ \
  {k00, k01, k02, k03}, \
  {k10, k11, k12, k13}, \
  {k20, k21, k22, k23}, \
  {k30, k31, k32, k33}, \
  {k40, k41, k42, k43}, \
  {k50, k51, k52, k53} \
}

void matrix_init_user(void);
void matrix_scan_user(void);

#endif
