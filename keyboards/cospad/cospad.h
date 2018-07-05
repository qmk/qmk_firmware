#ifndef COSPAD_H
#define COSPAD_H

#include "quantum.h"

// readability
#define XXX KC_NO

/* COSPAD ortho matrix layout
   * ,-------------------.
   * | 00 | 01 | 02 | 03 |
   * |----|----|----|----|
   * | 10 | 11 | 12 | 13 |
   * |----|----|----|----|
   * | 20 | 21 | 22 | 23 |
   * |----|----|----|----|
   * | 30 | 31 | 32 | 33 |
   * |----|----|----|----|
   * | 40 | 41 | 42 | 43 |
   * |----|----|----|----|
   * | 50 | 51 | 52 | 53 |
   * `-------------------'
 */


/* COSPAD numpad matrix layout
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
   * |    50   | 52 |    |
   * `-------------------'
 */
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
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
	{k50, k51, k52, k53}  \
}

#define LAYOUT_numpad_6x4( \
  k00, k01, k02, k03,  \
	k10, k11, k12, k13,  \
	k20, k21, k22,       \
	k30, k31, k32, k23,  \
	k40, k41, k42,       \
	k50,      k52, k43   \
) \
{ \
	{k00, k01,   k02, k03},   \
	{k10, k11,   k12, k13},   \
	{k20, k21,   k22, k23},   \
	{k30, k31,   k32, KC_NO}, \
	{k40, k41,   k42, k43},   \
	{k50, KC_NO, k52, KC_NO}  \
}
void matrix_init_user(void);
void matrix_scan_user(void);

inline void cospad_bl_led_on(void)	{ PORTF &= ~(1<<7); }
inline void cospad_bl_led_off(void)	{ PORTF |= (1<<7); }

inline void cospad_bl_led_togg(void) {
   uint8_t bl_mask = PORTF&(1<<7);
   if (bl_mask) {
      PORTF &= ~(1<<7);
   } else {
      PORTF |= (1<<7);
   }
}
#endif
