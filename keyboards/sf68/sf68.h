#ifndef SF68_H 
#define SF68_H

#include "quantum.h"

#define xxx KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, k1f, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      k2e, k2f, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, k3f, \
	k40, k41, k42, k43,           k46,      k48,           k4b, k4c, k4d, k4e, k4f \
) \
{ \
	{k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f}, \
	{k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, xxx, k1e, k1f}, \
	{k20, xxx, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, xxx, k2e, k2f}, \
	{k30, xxx, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, xxx, k3d, k3e, k3f}, \
	{k40, k41, k42, k43, xxx, xxx, k46, xxx, k48, xxx, xxx, k4b, k4c, k4d, k4e, k4f}  \
}
/*#define KEYMAP( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E, k1F, \
  k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, k2F, \
  k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, k3F, \
  k40, k41, k42, k43,           k56,      k48,           k4B, k4C, k4D, k4E, k4F \
) \
{ \
	{ k00, k01,   k02, k03, k04,   k05,   k06, k07,   k08, k09,   k0A,   k0B, k0C,   k0D,   k0E, k0F }, \
	{ k10, k11,   k12, k13, k14,   k15,   k16, k17,   k18, k19,   k1A,   k1B, k1C,   KC_NO, k1E, k1F }, \
	{ k20, KC_NO, k22, k23, k24,   k25,   k26, k27,   k28, k29,   k2A,   k2B, k2C,   KC_NO, k2E, k2F }, \
	{ k30, KC_NO, k32, k33, k34,   k35,   k36, k37,   k38, k39,   k3A,   k3B, KC_NO, k3D,   k3E, k3F }, \
    { k40, k41,   k42, k43, KC_NO, ___,   k56, KC_NO, k48, KC_NO, KC_NO, k4B, k4C,   k4D,   k4E, k4F } \
}*/

void matrix_init_user(void);
void matrix_scan_user(void);

#endif
